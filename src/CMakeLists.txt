add_subdirectory(sdlvideo)

# Main executable
add_executable(hello_sdl helloSDL.cxx helloSDL.hxx)

target_include_directories(hello_sdl PRIVATE SYSTEM
    ${SDL2_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS})

target_link_libraries(hello_sdl PRIVATE
    ${SDL2_LIBRARIES}
    ${Boost_LIBRARIES}
    sdlvideo)