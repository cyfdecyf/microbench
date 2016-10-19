set(CMAKE_C_FLAGS "-g -O2 -Wall -Werror -Wno-tautological-compare")
set(CMAKE_CXX_FLAGS "-g -O2 -Wall -Werror -Wno-tautological-compare -std=c++1y")

add_executable(memory memory.cc)
target_link_libraries(memory benchmark pthread)
