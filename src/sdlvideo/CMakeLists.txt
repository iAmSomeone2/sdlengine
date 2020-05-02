add_library(sdlvideo STATIC ImgSurface.cxx ImgSurface.hxx)

target_include_directories(sdlvideo PUBLIC SYSTEM
    ${SDL2_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS})

target_link_libraries(sdlvideo PUBLIC 
    ${SDL2_LIBRARIES}
    ${PNG_LIBRARIES}
    ${Boost_LIBRARIES})