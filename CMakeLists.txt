cmake_minimum_required(VERSION 3.25)
set(LLVM_MOS_PLATFORM mega65)

find_package(llvm-mos-sdk REQUIRED)
find_package(mega65libc REQUIRED)

project(myproject LANGUAGES C CXX ASM)

add_compile_options(-Os -Wall -Wextra -Wconversion)

add_executable(my_c_app main.c)
target_include_directories(my_c_app PUBLIC "/usr/local/include/mega65")
target_link_libraries(my_c_app mega65libc::mega65libc)

set_target_properties(my_c_app PROPERTIES OUTPUT_NAME my_c_app.prg)

add_custom_command(
    TARGET my_c_app POST_BUILD
    DEPENDS my_c_app.d81
    COMMAND c1541 -format "disk,0" d81 my_c_app.d81
    COMMAND c1541 -attach my_c_app.d81 -write my_c_app.prg my_c_app
    VERBATIM)


add_executable(my_cpp_app main.cpp)

target_include_directories(my_cpp_app PUBLIC "/usr/local/include/mega65")
target_link_libraries(my_cpp_app mega65libc::mega65libc)

set_target_properties(my_cpp_app PROPERTIES OUTPUT_NAME my_cpp_app.prg)

add_custom_command(
    TARGET my_cpp_app POST_BUILD
    DEPENDS my_cpp_app.d81
    COMMAND c1541 -format "disk,0" d81 my_cpp_app.d81
    COMMAND c1541 -attach my_cpp_app.d81 -write my_cpp_app.prg my_cpp_app
    VERBATIM)