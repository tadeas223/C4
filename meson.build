project('c4', 'c')

sources = []
incl_dirs = include_directories('include', 'src')

subdir('src')

c4_lib = library(
  'c4',
  sources,
  include_directories: [incl_dirs],
)

executable(
  'c4c',
  'src/exe/c4c.c',
  link_with: [c4_lib],
  include_directories: [incl_dirs],
)
