project(
    'epicycle_drawing', 'c', 'cpp', 'cuda',
    version: '0.1.0',
    default_options : ['c_std=c18', 'cpp_std=c++20']
)

cmake = import('cmake')

cuda_calc_proj = subproject('cuda_calc')
cuda_calc_dep = dependency('cuda_calc_dep',  fallback : ['cuda_calc', 'cuda_calc_dep'])

range_v3_proj_options = cmake.subproject_options()
range_v3_proj_options.add_cmake_defines({
  'RANGE_V3_DOCS': false,
  'RANGE_V3_TESTS': false,
  'RANGE_V3_EXAMPLES': false,
  'RANGE_V3_PERF': false,
})
range_v3_proj = cmake.subproject('range-v3', options: range_v3_proj_options)
range_v3_dep = range_v3_proj.dependency('range-v3')

sfml_system_dep = dependency('sfml-system', required: true)
sfml_graphics_dep = dependency('sfml-graphics', required: true)
sfml_window_dep = dependency('sfml-window', required: true)

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
    'src/epicycle_visualizer.cpp',
    include_directories : incdir,
    cpp_args: cpp_build_args,
	link_args: cpp_link_args,
    dependencies: [
      cuda_calc_dep, 
      range_v3_dep,
      sfml_system_dep,
      sfml_graphics_dep,
      sfml_window_dep,
    ]
)
