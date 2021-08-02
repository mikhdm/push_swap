cmake_minimum_required(VERSION 3.5)
project(push_swap)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SOURCE_DIR cmake.debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

set(SRCS
./src/utils/alloca_to.c
./src/utils/ft_memset.c
./src/stackop.c
./src/main.c
)

add_executable(push_swap ${SRCS})
