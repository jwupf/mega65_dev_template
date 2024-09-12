cmake_minimum_required(VERSION 3.25)
set(LLVM_MOS_PLATFORM mega65)
find_package(llvm-mos-sdk REQUIRED)


project(myproject LANGUAGES C CXX ASM)
find_package(mega65libc REQUIRED)

add_compile_options(-Os -Wall -Wextra -Wconversion)

# add_executable(main main.c)
add_executable(main main.cpp)

target_include_directories(main PUBLIC "/usr/local/include/mega65")
target_link_libraries(main mega65libc::mega65libc)

set_target_properties(main PROPERTIES OUTPUT_NAME main.prg)

add_custom_command(
    TARGET main POST_BUILD
    DEPENDS main.d81
    COMMAND c1541 -format "disk,0" d81 main.d81
    COMMAND c1541 -attach main.d81 -write main.prg main
    VERBATIM)