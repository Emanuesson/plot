
deps = [
  cc.find_library('m', required : true),
]

libplot_header_subdir = join_paths(package_subdir, 'plot')

src = files([
  'display.c',
  'follow.c',
  'input.c',
  'plot.c',
  'util.c',
])

headers = files([
  'display.h',
  'follow.h',
  'input.h',
  'plot.h',
  'util.h',
])

install_headers(headers, subdir: libplot_header_subdir)

libplot = library(
  'plot',
  src,
  pic: true,
  dependencies : deps,
  install : true,
  implicit_include_directories: true,
  include_directories: [ include_directories('.'), plot_root_inc ],
  version : library_version,
  soversion : soversion,
)

libplot_dep = declare_dependency(
  link_with : libplot,
  include_directories : [ plot_root_inc ],
  dependencies : deps,
)

pkgg.generate(
      subdirs: libplot_header_subdir,
      version: meson.project_version(),
         name: 'libplot',
     filebase: 'plot',
  description: 'A library to create chart plots',
  install_dir: join_paths(libdir, 'pkgconfig'),
)

plot = executable('plot',
  sources: ['main.c', 'opts.c'],
  dependencies: deps,
  install: true,
  link_with: libplot,
  include_directories:  plot_root_inc,
)

