
#include <iostream>
#include <glfwpp/glfwpp.h>
#include <vulkan/vulkan.hpp>



auto main() -> int{
	auto glfw_instance = glfw::init();
	glfw::Window window{ 640, 480, "Hello GLFWPP"};

	while (!window.shouldClose())
        glfw::pollEvents();
}
