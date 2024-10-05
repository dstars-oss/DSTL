#++
# Copyright (c) 2024.  D.Stars <d.stars@163.com>
# All rights reserved.
#

cmake_minimum_required(VERSION 3.20)

project(DSTL)

set(CMAKE_CXX_STANDARD 20)

file(GLOB DSTL_HPP
    include
    )
include_directories(include)

# For IDE Edit.
add_executable(main
    ${DSTL_HPP}
    src/main.cpp
    )

# unit test.
add_subdirectory(test)
