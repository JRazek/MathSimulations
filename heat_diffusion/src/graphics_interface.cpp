#include "graphics_interface.hpp"

#include <fstream>
#include <iterator>
#include <stdexcept>

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
auto Pipeline::read_vertex_shader(std::string const& path) -> void {
  auto binary = read_file(path);
}
}  // namespace jr::graphics
