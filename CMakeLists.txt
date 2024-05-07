cmake_minimum_required(VERSION 3.14...3.22)

project(work-test VERSION 0.0.1 LANGUAGES CXX)

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif ()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
endif ()

if (MSVC)
  # С клангом проще, у него такие же флаги (-march=haswell -mavx2), как и у GCC
  message(FATAL_ERROR "MSVC Not Supported - use clang on Windows")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main_1 main_1.cpp)


if (MSVC)
  target_compile_options(main_1 PRIVATE /arch:AVX2)
else ()
  target_compile_options(main_1 PRIVATE
#    -march=haswell -mavx2
    #-mavx512f -mfma
    -march=native
  )
endif ()


include(get_cpm.cmake)
CPMAddPackage(
  NAME Catch2
  URL "https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.4.tar.gz"
  URL_HASH "SHA3_256=6908501ace10bca5ece01a972e4834777f3b3cb5e14b391cec015caeb5470eff"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "CATCH_INSTALL_DOCS OFF"
  "CATCH_INSTALL_EXTRAS OFF"
  "CATCH_ENABLE_REPRODUCIBLE_BUILD OFF"
)
target_link_libraries(main_1 PRIVATE Catch2::Catch2WithMain)

CPMAddPackage(
  NAME xsimd
  URL "https://github.com/xtensor-stack/xsimd/archive/5ac7edf30d0f519e0b7344b933382e4fc02fdee7.tar.gz"
  URL_HASH "SHA3_256=d4d5152794f987ff2e2e1a06c291019a9d4810b9c1fc94b9ecaa5dc6ab070fc9"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)
target_link_libraries(main_1 PRIVATE xsimd)


function(create_benchmark TARGET)

endfunction()