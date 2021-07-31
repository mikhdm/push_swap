cmake_minimum_required(VERSION 3.5)
project(push_swap)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SOURCE_DIR cmake.debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

set(SRCS
./src/stack.c
./src/push_swap.c
./src/utils/alloca_to.c
)

add_executable(push_swap ${SRCS})
