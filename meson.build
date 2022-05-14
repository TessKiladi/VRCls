project('vrcls', 'cpp')
srcs = [
    'src/MainForm.cpp',
    ]
includedirs = [
    ]
cpp = meson.get_compiler('cpp')
fltklibs = [
    cpp.find_library('fltk', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    cpp.find_library('fltk_forms', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    cpp.find_library('fltk_gl', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    cpp.find_library('fltk_images', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    cpp.find_library('fltk_jpeg', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    cpp.find_library('fltk_png', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    cpp.find_library('fltk_z', dirs: meson.project_source_root() / 'tmp/fltk/lib/'),
    ]
fltk_inc = include_directories(['fltk', 'tmp/fltk'])
add_project_link_arguments('-static', language: 'cpp')
add_project_link_arguments('-lcomctl32', language: 'cpp')
add_project_arguments('-std=c++20', language: 'cpp')

executable('vrcls', sources: [files(srcs)], include_directories: [include_directories(includedirs), fltk_inc], dependencies: [fltklibs])