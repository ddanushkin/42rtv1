cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 99)
set(EXECUTABLE_NAME 42rtv1)
project(42rtv1 C)

file(GLOB_RECURSE PROJ_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE LIBFT_SRC RELATIVE ${CMAKE_SOURCE_DIR} "libft/src/*.c")

include_directories("include")
include_directories("libft/include")

if(MSVC OR MSYS OR MINGW)
    message("-- WINDOWS --")
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    include_directories("sdl2/win32/include/SDL2/")
    link_directories(sdl2/win32/lib/)
    add_executable(${CMAKE_PROJECT_NAME} ${PROJ_SRC} ${LIBFT_SRC})
    target_link_libraries(${CMAKE_PROJECT_NAME} "-lmingw32 -lSDL2main -lSDL2")
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/sdl2/win32/bin/"
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
endif()

if(APPLE)
    message("-- MACOS --")
    include_directories("/Users/$ENV{USER}/Library/Frameworks/SDL2.framework/Versions/A/Headers/")
    add_executable(${CMAKE_PROJECT_NAME} ${PROJ_SRC} ${LIBFT_SRC})
    target_link_libraries(${CMAKE_PROJECT_NAME} "-F /Users/$ENV{USER}/Library/Frameworks/ -framework SDL2")
endif()