set(CMAKE_C_FLAGS "-g -O2 -Wall -Werror")
set(CMAKE_CXX_FLAGS "-g -O2 -Wall -Werror -std=c++1y")

add_executable(memory memory.cc)
target_link_libraries(memory benchmark pthread)

add_executable(timing timing.cc)
target_link_libraries(timing benchmark pthread)
