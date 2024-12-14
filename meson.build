project(
  'nix-diff',
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


libflake_dep = dependency('nix-flake', fallback: 'libflake')
libstore_dep = dependency('nix-store', fallback: 'libstore')
libexpr_dep = dependency('nix-expr', fallback: 'libexpr')

libnixs = [
  libflake_dep,
  libstore_dep,
  libexpr_dep,
]
# libstore_dep = libstore_c.get_variable('nix-store-c')

nix_target_system = target_machine.cpu_family() + '-' + target_machine.system()

project_target = executable(
  meson.project_name(),
  project_source_files,
  dependencies: libnixs,
  install : true,
  cpp_args : [ '-DHAVE_BOEHMGC=1', '-DSYSTEM="' + nix_target_system + '"'],
)
