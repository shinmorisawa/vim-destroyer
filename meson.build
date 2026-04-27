project('firesurv', 'c',
  version: '0.1',
  default_options: ['warning_level=3', 'c_std=gnu2x', 'werror=true', 'optimization=3']
)

add_project_arguments(
  '-Wno-gnu-statement-expression-from-macro-expansion',
  language: 'c'
)

srcs = files(
  # files go here
  # (or in 'folder'/meson.build)
)

# optional subdir('folder')
subdir('src')

include = include_directories(
  'include',
  'lib/tengine/include'
)

cc = meson.get_compiler('c')
math_dep = cc.find_library('m', required: true)
tengine = custom_target('build-tengine',
  output: ['libtengine.so', 'libtengine.a'],
  command: [
    'sh', '-c',
    'cd @0@/lib/tengine && ./build.sh && cp build/libtengine.a @1@ && cp build/libtengine.so @1@'.format(meson.current_source_dir(), meson.current_build_dir())
  ],
  build_by_default: true,
)

executable('fire', srcs,
  include_directories: include,
  install: true,
  dependencies: [math_dep],
  link_with: tengine[1]
)
