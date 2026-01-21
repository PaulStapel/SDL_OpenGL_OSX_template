cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_CXX_STANDARD 20)

option(RELEASE_BUILD "Make this a release build" OFF)

# Include static runtimes to make building on different OS' easier. 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

# Main CMakeLists file: 

project(game)

set(SDL_STATIC ON)

add_subdirectory(lib/SDL-release-2.30.5)		#SDL version 2.30.5
add_subdirectory(lib/glad)			            #OpenGL version 4.1 
add_subdirectory(lib/glm)			            #GLM version 1.0.3

# MY_SOURCES is defined to be a list of all the source files for my game 
# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1) # needed for cross-platform. 

if(RELEASE_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ASSET_PATH="./assets/") 
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADER_PATH="./shaders/") 
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RELEASE_BUILD=1) 

else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders/") 
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RELEASE_BUILD=0) 

endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} ) 

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/") # For header files. 

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm 
	glad SDL2-static)