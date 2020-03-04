project(
  'zyphtine',
  'c',
  version: '0.0.0',
  default_options : ['c_std=c99'],
)

soversion = 0

incdir = include_directories('include')

source_files = []
subdir('src')

library(
  'zyphtine', source_files,
  include_directories : incdir,
  soversion: soversion,
  install: true,
)
