add_compile_definitions(SDL_MAIN_HANDLED)
add_executable(${EXECUTABLE_NAME} 
                                main.c 
                                demo.c
                                monitor.c
                                mouse.c
                                mouse_cursor_icon.c
                                )


target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL2 LVGL)
target_include_directories(${EXECUTABLE_NAME} PUBLIC "./")