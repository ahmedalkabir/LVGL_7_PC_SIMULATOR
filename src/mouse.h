#ifndef MOUSE_H
#define MOUSE_H

#include <lvgl/lvgl.h>
#include <SDL2/SDL.h>

void mouse_init(void);
bool mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
void mouse_handler(SDL_Event *event);


#endif