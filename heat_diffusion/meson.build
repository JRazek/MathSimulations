project(
    'heat_diffusion', 'c', 'cpp', 'cuda',
    version: '0.1.0',
    default_options : ['c_std=c18', 'cpp_std=c++20']
)

cuda_calc_proj = subproject('cuda_calc')
cuda_calc_dep = cuda_calc_proj.get_variable('cuda_calc_dep')

incdir = include_directories(
    'include',
    'src',
)

cpp_args=[]
cpp_link_args=[]
cuda_args=[]

exec=executable(
    'heat_diffusion',
    'src/main.cpp',
    include_directories : incdir,
    cpp_args: cpp_args,
	link_args: cpp_link_args,
    cuda_args: cuda_args,
    dependencies: [cuda_calc_dep]
)

