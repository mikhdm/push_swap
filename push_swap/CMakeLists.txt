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
./src/utils/ft_strlen_until.c
./src/utils/ft_qsort.c
./src/utils/issorted.c
./src/utils/swap.c
./src/utils/nth_element.c
./src/utils/ft_min.c
./src/utils/ft_max.c
./src/utils/ft_lstnew.c
./src/utils/ft_lstiter.c
./src/utils/ft_lstadd_back.c
./src/utils/ft_lstadd_front.c
./src/utils/ft_lstdelone.c
./src/utils/ft_lstclear.c
./src/utils/ft_strcmp.c
./src/utils/find_gt.c
./src/utils/find_lt.c
./src/op.c
./src/push_swap.c
./src/main.c
./src/error.c
./src/stack.c
./src/stackex.c
)

add_executable(push_swap ${SRCS})
