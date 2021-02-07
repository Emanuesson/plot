project(
	'plot',
	'c',
	version: '0.3.0',
	license: 'GPL-3.0-only',
	meson_version: '>=0.44.1',
	default_options: [
		'c_std=c99',
		'warning_level=3',
	],
)

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
	'-Wundef',
	'-Wlogical-op',
	'-Wmissing-include-dirs',
	'-Wold-style-definition',
	'-Wpointer-arith',
	'-Winit-self',
	'-Wstrict-prototypes',
	'-Wimplicit-fallthrough=2',
	'-Wendif-labels',
	'-Wstrict-aliasing=2',
	'-Woverflow',

	'-Wno-missing-braces',
	'-Wno-missing-field-initializers',
	'-Wno-unused-parameter',
]), language: 'c')

package_subdir = get_option('package_subdir') # When used as subproject
libdir = join_paths(get_option('libdir'))
plot_root_inc = include_directories('.')
plot_src_inc = include_directories('./plot')

pkgg = import('pkgconfig')

version_arr = meson.project_version().split('.')
major_version = version_arr[0].to_int()
minor_version = version_arr[1].to_int()
micro_version = version_arr[2].to_int()

soversion = 0
# Maintain compatibility with previous libtool versioning
# current = minor * 100 + micro
interface_age = minor_version.is_odd() ? 0 : micro_version
binary_age = 100 * minor_version + micro_version
current = binary_age - interface_age
library_version = '@0@.@1@.@2@'.format(soversion, current, interface_age)

subdir('plot')

if get_option('test')
	subdir('tests')
endif

if get_option('build_docs') != 'disabled'
	subdir('docs')
endif
