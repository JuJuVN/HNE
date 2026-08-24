cmake_minimum_required(VERSION 3.20)

project(HNE
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_executable(hne
    src/main.cpp
    thirdparty/glad/src/gl.c
)

target_include_directories(hne PRIVATE 
    thirdparty/glad/include
)

target_link_libraries(hne PRIVATE
	glfw
	Threads::Threads
)

if (WIN32)
	target_link_libraries(hne PRIVATE opengl32)
elseif(UNIX AND NOT APPLE)
	target_link_libraries(hne PRIVATE GL ${CMAKE_DL_LIBS})
endif()
