#ifndef MONITOR_H
#define MONITOR_H

#include <lvgl/lvgl.h>

void monitor_init(void);
void monitor_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

#endif