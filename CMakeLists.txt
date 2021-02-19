# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (Multithread)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

# Set debug flag
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_executable(part1 src/part1.cpp)
target_link_libraries(part1 pthread)

add_executable(bind_example src/bind.cpp)
target_link_libraries(bind_example pthread)

add_executable(detach_example src/detach.cpp)
target_link_libraries(detach_example pthread)

add_executable(threadRAII_example src/threadRAII.cpp)
target_link_libraries(threadRAII_example pthread)

add_executable(heap_stack_example src/heap_stack.cpp)
target_link_libraries(heap_stack_example)

