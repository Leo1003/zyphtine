project(
  'zyphtine',
  'c',
  version: '0.0.0',
  meson_version: '>=0.46.0',
  default_options : ['c_std=c99'],
)

soversion = 0

incdir = include_directories('include')
subdir('include')

source_files = []
subdir('src')

lib_zyphtine = library(
  'zyphtine', source_files,
  include_directories : incdir,
  soversion: soversion,
  install: true,
)

zyphtine = declare_dependency(
  link_with: lib_zyphtine,
  include_directories: incdir,
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(lib_zyphtine,
  description: 'Library for building a Zhuyin input method engine',
)
