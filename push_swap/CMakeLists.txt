cmake_minimum_required(VERSION 3.5)
project(push_swap)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SOURCE_DIR cmake.debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

set(SRCS
./src/utils/alloca_to.c
./src/utils/ft_atoi.c
./src/utils/ft_atoss.c
./src/utils/ft_isdigit.c
./src/utils/ft_isspace.c
./src/utils/ft_memset.c
./src/utils/ft_memcpy.c
./src/utils/ft_strchr.c
./src/utils/ft_strdup_until.c
./src/utils/ft_strlen.c
./src/utils/ft_strlen_until.c
./src/utils/ft_qsort.c
./src/utils/issorted.c
./src/main.c
./src/error.c
./src/stack.c
./src/stackex.c
)

add_executable(push_swap ${SRCS})
