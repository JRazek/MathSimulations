project(
    'heat_diffusion', 'c', 'cpp', 'cuda',
    version: '0.1.0',
    default_options : ['c_std=c18', 'cpp_std=c++20']
)

cmake = import('cmake')

cuda_calc_proj = subproject('cuda_calc')
cuda_calc_dep = cuda_calc_proj.get_variable('cuda_calc_dep')

glfwpp_proj = cmake.subproject('glfwpp')
glfwpp_dep = glfwpp_proj.dependency('GLFWPP')

vulkan_dep = dependency('vulkan')
glfw_dep = dependency('glfw3')

incdir = include_directories(
    'include',
    'src',
)

cpp_build_args=[
  '-stdlib=libc++', 
  '-xcuda',
]
cpp_link_args=[
  '-stdlib=libc++',
]


exec=executable(
    'heat_diffusion',
    'src/main.cpp',
    include_directories : incdir,
    cpp_args: cpp_build_args,
	link_args: cpp_link_args,
    dependencies: [
      cuda_calc_dep, 
      vulkan_dep,
      glfw_dep,
      glfwpp_dep,
    ]
)
