#include "graphics_interface.hpp"

#include <fstream>
#include <iterator>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/zip.hpp>
#include <stdexcept>

#include "vulkan/vulkan_enums.hpp"
#include "vulkan/vulkan_handles.hpp"
#include "vulkan/vulkan_structs.hpp"

namespace jr::graphics {

Pipeline::Pipeline(std::uint32_t width, std::uint32_t height,
                   std::string const& title)
    : window_(glfw::Window(width, height, title.c_str())) {
  graphics_thread_ = std::thread([&window = window_]() {
    while (!window.shouldClose()) glfw::pollEvents();
  });
}
Pipeline::~Pipeline() { graphics_thread_.join(); }
auto Pipeline::read_file(std::string const& path) -> std::vector<std::uint8_t> {
  std::fstream fstream{path, std::ios::ate | std::ios::binary};
  if (!fstream.is_open())
    throw std::runtime_error("could not load shader: " + path);
  std::istreambuf_iterator<char> it{fstream};

  std::vector<std::uint8_t> res(it, std::istreambuf_iterator<char>());

  return res;
}
auto Pipeline::choose_physical_device(
    std::function<bool(vk::PhysicalDevice const&)> is_suitable) -> void {
  auto physical_devices = vulkan_instance_.enumeratePhysicalDevices();
  for (auto physical_device : physical_devices) {
    if ((is_suitable && is_suitable(physical_device)) || !is_suitable) {
      physical_device_ = physical_device;
      break;
    }
  }
}
auto find_queue_family_indices(vk::PhysicalDevice const& physical_device) {
  QueueFamilyIndices indices;

  auto queue_families = physical_device.getQueueFamilyProperties();
  /*
        // Provided by VK_VERSION_1_0
        typedef enum VkQueueFlagBits {
                VK_QUEUE_GRAPHICS_BIT = 0x00000001,
                VK_QUEUE_COMPUTE_BIT = 0x00000002,
                VK_QUEUE_TRANSFER_BIT = 0x00000004,
                VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
          // Provided by VK_VERSION_1_1
                VK_QUEUE_PROTECTED_BIT = 0x00000010,
   */

  for (auto i = 0u; i < queue_families.size(); i++) {
    auto& queue_family = queue_families[i];
    if (queue_family.queueFlags & vk::QueueFlagBits::eGraphics) {
      indices.graphics_family = i;
      indices.present_family = i;
    }
  }
  return indices;
}
auto Pipeline::create_logical_device(vk::PhysicalDevice& physical_device)
    -> vk::Device {
  auto queue_family_indices = find_queue_family_indices(physical_device);
  float queue_priority = 1.0;
  auto queue_create_info =
      vk::DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(),
                                queue_family_indices.graphics_family.value());

  auto device_features = vk::PhysicalDeviceFeatures(); //todo
}
auto Pipeline::read_vertex_shader(std::string const& path) -> void {
  auto binary = read_file(path);
}
}  // namespace jr::graphics
