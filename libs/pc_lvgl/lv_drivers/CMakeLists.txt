set(LV_DRIVERS_INCLUDES 
            "./" 
            "${CMAKE_CURRENT_SOURCE_DIR}/display" 
            "${CMAKE_CURRENT_SOURCE_DIR}/indev"
)

set(LV_DRIVERS_LIBRARY
            "${CMAKE_CURRENT_SOURCE_DIR}/win_drv.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/fbdev.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/monitor.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/R61581.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/SHARP_MIP.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/SSD1963.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/ST7565.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/display/UC1610.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/AD_touch.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/evdev.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/FT5406EE8.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/keyboard.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/libinput.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/mouse.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/mousewheel.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/indev/XPT2046.c"
)
add_library(LV_DRIVERS STATIC ${LV_DRIVERS_LIBRARY})

target_include_directories(LV_DRIVERS PUBLIC ${LV_DRIVERS_INCLUDES})