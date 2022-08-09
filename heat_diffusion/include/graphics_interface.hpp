#include <glfwpp/glfwpp.h>

#include <string>
#include <thread>
#include <vector>
#include <vulkan/vulkan.hpp>

namespace jr::graphics {
class Pipeline {
  static inline auto glfw_instance = glfw::init();
  glfw::Window window_;

  std::thread graphics_thread_;

 public:
  Pipeline(std::uint32_t width, std::uint32_t height, std::string const& title);
  ~Pipeline();
  static auto read_file(std::string const& path) -> std::vector<std::uint8_t>;
  auto read_vertex_shader(std::string const& path) -> void;
};
}  // namespace jr::graphics
