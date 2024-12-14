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


libflake_dep = dependency('nix-flake', fallback: 'libflake')
libstore_dep = dependency('nix-store', fallback: 'libstore')
libexpr_dep = dependency('nix-expr', fallback: 'libexpr')
libflakec_dep = dependency('nix-flake-c', fallback: 'libflake-c')
libstorec_dep = dependency('nix-store-c', fallback: 'libstore-c')
libexprc_dep = dependency('nix-expr-c', fallback: 'libexpr-c')

libX_deps = [
  libflake_dep,
  libstore_dep,
  libexpr_dep,
  # libflakec_dep,
  # libstorec_dep,
  # libexprc_dep
]
# libstore_dep = libstore_c.get_variable('nix-store-c')

nix_target_system = target_machine.cpu_family() + '-' + target_machine.system()

project_target = executable(
  meson.project_name(),
  project_source_files,
  # include_directories : [ libX_c_incr_dirs ],
  # link_with : mylibpath,
  dependencies: libX_deps,
  install : true,
  cpp_args : [ '-DHAVE_BOEHMGC=1', '-DSYSTEM="' + nix_target_system + '"'],
  # link_args : [ '-L/home/peter/dev/nix/nix/outputs/out/lib/libnixexprc.so' ]
)
