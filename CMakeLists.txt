cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# ---- Project ----

project(magic_enum_example LANGUAGES CXX)

# ---- Fetch CPM ----

set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# ---- Add dependencies via CPM ----
# See https://github.com/TheLartians/CPM.cmake for details and examples

CPMAddPackage(
  NAME namagic_enum
  GITHUB_REPOSITORY sthagen/magic_enum
  GIT_TAG 2021.09
)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY sthagen/doctest
  GIT_TAG 2020.12
)

# ---- Create binary ----

add_executable(magic_enum_example main.cpp)
target_link_libraries(magic_enum_example doctest)
set_target_properties(magic_enum_example PROPERTIES CXX_STANDARD 17)

# ---- Enable testing ----

enable_testing() 
add_test(magic_enum_example magic_enum_example)
