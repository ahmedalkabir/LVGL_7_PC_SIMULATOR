#include "demo.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

static lv_obj_t *tv;
static lv_obj_t *t1;
static lv_obj_t *t2;
static lv_obj_t *t3;
static lv_obj_t *kb;
static lv_obj_t *spinbox;

static lv_style_t style_box;

static void kb_event_cb(lv_obj_t *_kb, lv_event_t e)
{
    lv_keyboard_def_event_cb(kb, e);

    if (e == LV_EVENT_CANCEL)
    {
        if (kb)
        {
            lv_obj_set_height(tv, LV_VER_RES);
            lv_obj_del(kb);
            kb = NULL;
        }
    }
}

static void slider_event_cb(lv_obj_t *slider, lv_event_t e)
{
    if (e == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_slider_get_type(slider) == LV_SLIDER_TYPE_NORMAL)
        {
            static char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d", lv_slider_get_value(slider));
            lv_obj_set_style_local_value_str(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, buf);
        }
        else
        {
            static char buf[32];
            lv_snprintf(buf, sizeof(buf), "%d-%d", lv_slider_get_left_value(slider), lv_slider_get_value(slider));
            lv_obj_set_style_local_value_str(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, buf);
        }
    }
}

static void ta_event_cb(lv_obj_t *ta, lv_event_t e)
{
    if (e == LV_EVENT_FOCUSED)
    {
        if (kb == NULL)
        {
            lv_obj_set_height(tv, LV_VER_RES / 2);
            kb = lv_keyboard_create(lv_scr_act(), NULL);
            lv_obj_set_event_cb(kb, kb_event_cb);
        }
        lv_textarea_set_cursor_hidden(ta, false);
        lv_page_focus(t1, lv_textarea_get_label(ta), LV_ANIM_ON);
        lv_keyboard_set_textarea(kb, ta);
    }
    else if (e == LV_EVENT_DEFOCUSED)
    {
        lv_textarea_set_cursor_hidden(ta, true);
    }
}

static void controls_create(lv_obj_t *parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    lv_coord_t grid_w = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_SMALL ? 1 : 2, 1);

#if LV_DEMO_WIDGETS_SLIDESHOW == 0
    static const char *btns[] = {"Cancel", "Ok", ""};

    lv_obj_t *m = lv_msgbox_create(lv_scr_act(), NULL);
    lv_msgbox_add_btns(m, btns);
    lv_obj_t *btnm = lv_msgbox_get_btnmatrix(m);
    lv_btnmatrix_set_btn_ctrl(btnm, 1, LV_BTNMATRIX_CTRL_CHECK_STATE);
#endif

    lv_obj_t *h = lv_cont_create(parent, NULL);
    lv_cont_set_layout(h, LV_LAYOUT_PRETTY_MID);
    lv_obj_add_style(h, LV_CONT_PART_MAIN, &style_box);
    lv_obj_set_drag_parent(h, true);

    lv_obj_set_style_local_value_str(h, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, "Basics");

    lv_cont_set_fit2(h, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_set_width(h, grid_w);
    lv_obj_t *btn = lv_btn_create(h, NULL);
    lv_btn_set_fit2(btn, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_set_width(btn, lv_obj_get_width_grid(h, disp_size <= LV_DISP_SIZE_SMALL ? 1 : 2, 1));
    lv_obj_t *label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Button");

    btn = lv_btn_create(h, btn);
    lv_btn_toggle(btn);
    label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Button");

    lv_switch_create(h, NULL);

    lv_checkbox_create(h, NULL);

    lv_coord_t fit_w = lv_obj_get_width_fit(h);

    lv_obj_t *slider = lv_slider_create(h, NULL);
    lv_slider_set_value(slider, 40, LV_ANIM_OFF);
    lv_obj_set_event_cb(slider, slider_event_cb);
    lv_obj_set_width_margin(slider, fit_w);

    /*Use the knobs style value the display the current value in focused state*/
    lv_obj_set_style_local_margin_top(slider, LV_SLIDER_PART_BG, LV_STATE_DEFAULT, LV_DPX(25));
    lv_obj_set_style_local_value_font(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, lv_theme_get_font_small());
    lv_obj_set_style_local_value_ofs_y(slider, LV_SLIDER_PART_KNOB, LV_STATE_FOCUSED, -LV_DPX(25));
    lv_obj_set_style_local_value_opa(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_value_opa(slider, LV_SLIDER_PART_KNOB, LV_STATE_FOCUSED, LV_OPA_COVER);
    lv_obj_set_style_local_transition_time(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, 300);
    lv_obj_set_style_local_transition_prop_5(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, LV_STYLE_VALUE_OFS_Y);
    lv_obj_set_style_local_transition_prop_6(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, LV_STYLE_VALUE_OPA);

    slider = lv_slider_create(h, slider);
    lv_slider_set_type(slider, LV_SLIDER_TYPE_RANGE);
    lv_slider_set_value(slider, 70, LV_ANIM_OFF);
    lv_slider_set_left_value(slider, 30, LV_ANIM_OFF);
    lv_obj_set_style_local_value_ofs_y(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, -LV_DPX(25));
    lv_obj_set_style_local_value_font(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, lv_theme_get_font_small());
    lv_obj_set_style_local_value_opa(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_event_cb(slider, slider_event_cb);
    lv_event_send(slider, LV_EVENT_VALUE_CHANGED, NULL); /*To refresh the text*/
    if (lv_obj_get_width(slider) > fit_w)
        lv_obj_set_width(slider, fit_w);

    h = lv_cont_create(parent, h);
    lv_cont_set_fit(h, LV_FIT_NONE);
    lv_obj_set_style_local_value_str(h, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, "Text input");
    lv_obj_set_style_local_pad_inner(h, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_DPI / 10);

    lv_obj_t *ta = lv_textarea_create(h, NULL);
    lv_cont_set_fit2(ta, LV_FIT_PARENT, LV_FIT_NONE);
    lv_textarea_set_text(ta, "");
    lv_textarea_set_placeholder_text(ta, "E-mail address");
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_cursor_hidden(ta, true);
    lv_obj_set_event_cb(ta, ta_event_cb);

    ta = lv_textarea_create(h, ta);
    lv_textarea_set_pwd_mode(ta, true);
    lv_textarea_set_placeholder_text(ta, "Password");

    ta = lv_textarea_create(h, NULL);
    lv_cont_set_fit2(ta, LV_FIT_PARENT, LV_FIT_NONE);
    lv_textarea_set_text(ta, "");
    lv_textarea_set_placeholder_text(ta, "Message");
    lv_textarea_set_cursor_hidden(ta, true);
    lv_obj_set_event_cb(ta, ta_event_cb);
    lv_cont_set_fit4(ta, LV_FIT_PARENT, LV_FIT_PARENT, LV_FIT_NONE, LV_FIT_PARENT);

#if LV_DEMO_WIDGETS_SLIDESHOW
    tab_content_anim_create(parent);
#endif
}

static void color_chg_event_cb(lv_obj_t *sw, lv_event_t e)
{
    if (e == LV_EVENT_VALUE_CHANGED)
    {
        uint32_t flag = LV_THEME_MATERIAL_FLAG_LIGHT;
        if (lv_switch_get_state(sw))
            flag = LV_THEME_MATERIAL_FLAG_DARK;

        LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_primary(),
                              flag,
                              lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    }
}

void lv_demo(void)
{
    tv = lv_tabview_create(lv_scr_act(), NULL);

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
    if (disp_size >= LV_DISP_SIZE_MEDIUM)
    {
        lv_obj_set_style_local_pad_left(tv, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, LV_HOR_RES / 2);
        lv_obj_t *sw = lv_switch_create(lv_scr_act(), NULL);
        lv_obj_set_event_cb(sw, color_chg_event_cb);
        lv_obj_set_pos(sw, LV_DPX(10), LV_DPX(10));
        lv_obj_set_style_local_value_str(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, "Dark");
        lv_obj_set_style_local_value_align(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_ALIGN_OUT_RIGHT_MID);
        lv_obj_set_style_local_value_ofs_x(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_DPI / 35);
    }

    t1 = lv_tabview_add_tab(tv, "Controls");
    t2 = lv_tabview_add_tab(tv, "Visuals");
    t3 = lv_tabview_add_tab(tv, "Selectors");

    lv_style_init(&style_box);
    lv_style_set_value_align(&style_box, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_LEFT);
    lv_style_set_value_ofs_y(&style_box, LV_STATE_DEFAULT, -LV_DPX(10));
    lv_style_set_margin_top(&style_box, LV_STATE_DEFAULT, LV_DPX(30));

    controls_create(t1);
}

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        printf("Clicked\n");
    }
    else if (event == LV_EVENT_VALUE_CHANGED)
    {
        printf("Toggled\n");
    }
}

void lv_demo2(void)
{
    navbar();
    // LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_primary(),
    //                       0x01,
    //                       lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    lv_obj_t *label;

    lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Toggled");
}

void navbar()
{	
	lv_obj_t* page_state = NULL;

	page_state = lv_layer_top();
	lv_obj_reset_style_list(page_state, LV_OBJ_PART_MAIN);
	lv_obj_set_size(page_state, lv_obj_get_width(page_state), 30);
	lv_obj_set_style_local_bg_opa(page_state, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_100);
	lv_obj_set_style_local_bg_color(page_state, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xe5e5e5));
	// state_signal_page_init(page_state, LV_ALIGN_IN_TOP_LEFT, 10, 2);
	// state_power_page_init(page_state, LV_ALIGN_IN_TOP_RIGHT, -10, 4);

	return;
}