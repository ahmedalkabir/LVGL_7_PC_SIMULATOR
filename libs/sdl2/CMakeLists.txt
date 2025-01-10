set(SDL2_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SDL2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/libSDL2.dll.a")
set(SDL2_MAIN_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/libSDL2main.a")

add_library(SDL2 STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl.c")
target_link_libraries(SDL2 PUBLIC ${SDL2_LIBRARY} ${SDL2_MAIN_LIBRARY} setupapi hid )
target_include_directories(SDL2 PUBLIC "./" ${SDL2_INCLUDES})