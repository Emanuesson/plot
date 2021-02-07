foreach t: [
	'basic.sh',
	'follow.sh',
	'valgrind.sh',
]
	test(
		t,
		find_program(t),
		args: [plot],
		workdir: meson.current_build_dir()
	)
endforeach

test_deps = [
  libplot_dep,
  cc.find_library('cunit', required : true),
]

foreach t: [
  ['test_plot'],
]
  test_name = t.get(0)
  test_srcs = ['@0@.c'.format(test_name), t.get(1, [])]
  test(test_name,
    executable(test_name, test_srcs,
    include_directories: [plot_root_inc, plot_src_inc ],
    dependencies: test_deps),
  )
endforeach

