add_rules("mode.debug", "mode.release")
add_requires("cli11")

target("lcj++")
set_kind("binary")
add_files("src/*.cpp")
add_packages("cli11")

set_languages("c++23")
set_toolchains("clang")
