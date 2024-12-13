project(
  'myexec',
  'cpp',
  version : '1.1.0',
  default_options : ['warning_level=3']
)

project_source_files = [
  'main.cc'
]

# includes = include_directories ('/home/peter/dev/nix/nix/outputs/dev/include/nix/')
mylibpath = '/home/peter/dev/nix/nix/outputs/out/lib/libnixexprc.so'

nix_subproject = subproject('nix_subproject',
  default_options : {'bindings': false}
)


libflake_dep = dependency('nix-flake-c', fallback: 'libflake-c')

libstore_dep = dependency('nix-store-c', fallback: 'libstore-c')

libX_deps = [
  libflake_dep,
  libstore_dep
]
# libstore_dep = libstore_c.get_variable('nix-store-c')

project_target = executable(
  meson.project_name(),
  project_source_files,
  # include_directories : [ libX_c_incr_dirs ],
  # link_with : mylibpath,
  dependencies: libX_deps,
  install : true,
  c_args : [],
  # link_args : [ '-L/home/peter/dev/nix/nix/outputs/out/lib/libnixexprc.so' ]
)
