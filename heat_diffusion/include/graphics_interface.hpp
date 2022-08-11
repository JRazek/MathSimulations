#include <glfwpp/glfwpp.h>

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <thread>
#include <vector>
#include <vulkan/vulkan.hpp>

#include "vulkan/vulkan_handles.hpp"

namespace jr::graphics {
struct QueueFamilyIndices {
  std::optional<std::uint32_t> graphics_family;
  std::optional<std::uint32_t> present_family;
  auto is_complete() const -> bool {
    return graphics_family.has_value() && present_family.has_value();
  }
};
class Pipeline {
  static inline auto glfw_instance = glfw::init();
  vk::Instance vulkan_instance_;
  glfw::Window window_;

  std::optional<vk::PhysicalDevice> physical_device_;

  std::thread graphics_thread_;

 public:
  Pipeline(std::uint32_t width, std::uint32_t height, std::string const& title);
  ~Pipeline();
  static auto read_file(std::string const& path) -> std::vector<std::uint8_t>;

  /**
   * @brief chooses first suitable physical device
   *
   * @param is_suitable - predicate whether device is suitable
   */
  auto choose_physical_device(
      std::function<bool(vk::PhysicalDevice const&)> is_suitable = {}) -> void;
  auto find_queue_family_indices(vk::PhysicalDevice const& physical_device) -> QueueFamilyIndices;
  auto read_vertex_shader(std::string const& path) -> void;
  auto create_logical_device(vk::PhysicalDevice& device) -> vk::Device;
};
}  // namespace jr::graphics
