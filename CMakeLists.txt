# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(DynamicSystems)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT APPLE)
    # set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

# Find dependencies provided by vcpkg (via vcpkg.cmake)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(implot3d CONFIG REQUIRED)

set(
    CPP_TEMPLATE_SOURCES
    src/main.cpp
    src/DynamicSystems/Lorenz.h
    src/DynamicSystems/Lorenz.cpp
    src/DynamicSystems/Rossler.h
    src/DynamicSystems/Rossler.cpp
    src/DynamicSystems/Aizawa.h
    src/DynamicSystems/Aizawa.cpp
)
set(
    CPP_TEMPLATE_TEST_SOURCES
    src/test.cpp
)

# main target
add_executable(main ${CPP_TEMPLATE_SOURCES})
target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3 fmt::fmt-header-only SDL3::SDL3 imgui::imgui implot::implot implot3d::implot3d)
set_property(TARGET main PROPERTY CXX_STANDARD 23)

# tests target
add_executable(tests ${CPP_TEMPLATE_TEST_SOURCES})
target_link_libraries(tests PRIVATE unofficial::sqlite3::sqlite3 fmt::fmt-header-only)
set_property(TARGET tests PROPERTY CXX_STANDARD 23)
enable_testing()
add_test(tests tests)

add_custom_target(
    check-format
    COMMAND clang-format --dry-run ${CPP_TEMPLATE_SOURCES} ${CPP_TEMPLATE_TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)

add_custom_target(
    format
    COMMAND clang-format -i ${CPP_TEMPLATE_SOURCES} ${CPP_TEMPLATE_TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)

# Resources
add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_PROPERTY:main,SOURCE_DIR>/Resources
        $<TARGET_FILE_DIR:main>/Resources
        DEPENDS $<TARGET_PROPERTY:main,SOURCE_DIR>/Resources  # Optional: triggers re-copy on change
        COMMENT "Copying resources directory to build folder"
)