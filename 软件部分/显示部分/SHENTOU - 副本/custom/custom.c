// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void color_changer_anim_cb(void * var, int32_t v);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t session_desktop = 1000;
static uint32_t session_tablet = 1000;
static uint32_t session_mobile = 1000;

static bool down1 = false;
static bool down2 = false;
static bool down3 = false;

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

void textarea_event_cb(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_obj_set_height(guider_ui.WidgetsDemo_tabview_Main, LV_VER_RES - lv_obj_get_height(kb));
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
    }
    else if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_set_height(guider_ui.WidgetsDemo_tabview_Main, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    }
    else if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_set_height(guider_ui.WidgetsDemo_tabview_Main, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
    }
}

void color_changer_event_cb(lv_event_t * e)
{
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_obj_t * color_cont = lv_event_get_user_data(e);
        if(lv_obj_get_width(color_cont) < LV_HOR_RES / 2) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 0, 256);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
        else {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 256, 0);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
    }
}

static void color_changer_anim_cb(void * var, int32_t v)
{
    lv_obj_t * obj = var;
    lv_coord_t max_w = lv_obj_get_width(lv_obj_get_parent(obj)) - WIDTH_REFER(20);
    lv_coord_t w;

    w = lv_map(v, 0, 256, WIDTH_REFER(40), max_w);
    lv_obj_set_width(obj, w);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_RIGHT, - WIDTH_REFER(10), - WIDTH_REFER(10));

    if(v > LV_OPA_COVER) v = LV_OPA_COVER;

    uint32_t i;
    for(i = 0; i < lv_obj_get_child_cnt(obj); i++) {
        lv_obj_set_style_opa(lv_obj_get_child(obj, i), v, 0);
    }

}

void color_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_obj_t * color_cont = lv_obj_get_parent(obj);
        if(lv_obj_get_width(color_cont) < LV_HOR_RES / 2) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 0, 256);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
    }
    else if(code == LV_EVENT_CLICKED) {
        lv_obj_t * btn = lv_event_get_user_data(e);
        lv_color_t color = lv_obj_get_style_bg_color(btn, 0);

        lv_obj_set_style_text_color(lv_tabview_get_tab_btns(guider_ui.WidgetsDemo_tabview_Main), color, LV_PART_ITEMS|LV_STATE_CHECKED);
        lv_obj_set_style_border_color(lv_tabview_get_tab_btns(guider_ui.WidgetsDemo_tabview_Main), color, LV_PART_ITEMS|LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(lv_tabview_get_tab_btns(guider_ui.WidgetsDemo_tabview_Main), color, LV_PART_ITEMS|LV_STATE_CHECKED);
        
        lv_obj_set_style_text_color(guider_ui.WidgetsDemo_label_IconCall, color, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.WidgetsDemo_label_IconEmail, color, LV_PART_MAIN|LV_STATE_DEFAULT);

        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_btn_ColorSW, color, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_btn_Logout, color, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_btn_Logout, color, LV_PART_MAIN|LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_btn_Invite, color, LV_PART_MAIN|LV_STATE_DEFAULT);

        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_slider_Exp, color, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_slider_Exp, color, LV_PART_INDICATOR|LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_slider_Exp, color, LV_PART_KNOB|LV_STATE_DEFAULT);

        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_sw_HardWork, color, LV_PART_INDICATOR|LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(guider_ui.WidgetsDemo_sw_TeamPlayer, color, LV_PART_INDICATOR|LV_STATE_CHECKED);

        lv_obj_set_style_bg_color(lv_dropdown_get_list(guider_ui.WidgetsDemo_ddlist_Gender), color, LV_PART_SELECTED|LV_STATE_CHECKED);

        lv_chart_set_series_color(guider_ui.WidgetsDemo_chart_UV, lv_chart_get_series_next(guider_ui.WidgetsDemo_chart_UV, NULL), color);
        lv_chart_set_series_color(guider_ui.WidgetsDemo_chart_MR, lv_chart_get_series_next(guider_ui.WidgetsDemo_chart_MR, NULL), color);

        for (int8_t i = 0; i < lv_obj_get_child_cnt(guider_ui.WidgetsDemo_cont_Notification); i++) {
            lv_obj_t * cb = lv_obj_get_child(guider_ui.WidgetsDemo_cont_Notification, i);
            if (lv_obj_get_class(cb) == &lv_checkbox_class) {
                lv_obj_set_style_border_color(cb, color, LV_PART_INDICATOR|LV_STATE_DEFAULT);
                lv_obj_set_style_bg_color(cb, color, LV_PART_INDICATOR|LV_STATE_CHECKED);
                lv_obj_set_style_border_color(cb, color, LV_PART_INDICATOR|LV_STATE_CHECKED);
            }
        }
    }
}

void shop_chart_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
        /*Set the markers' text*/
        if(dsc->part == LV_PART_TICKS && dsc->id == LV_CHART_AXIS_PRIMARY_X) {
            const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
            lv_snprintf(dsc->text, dsc->text_length, "%s", month[dsc->value]);
        }
        if(dsc->part == LV_PART_ITEMS) {
            dsc->rect_dsc->bg_opa = LV_OPA_TRANSP; /*We will draw it later*/
        }
    }
    if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
        /*Add the faded area before the lines are drawn */
        if(dsc->part == LV_PART_ITEMS) {
            static const uint32_t devices[10] = {32, 43, 21, 56, 29, 36, 19, 25, 62, 35};
            static const uint32_t clothes[10] = {12, 19, 23, 31, 27, 32, 32, 11, 21, 32};
            static const uint32_t services[10] = {56, 38, 56, 13, 44, 32, 49, 64, 17, 33};

            lv_draw_rect_dsc_t draw_rect_dsc;
            lv_draw_rect_dsc_init(&draw_rect_dsc);

            lv_coord_t h = lv_area_get_height(dsc->draw_area);

            lv_area_t a;
            a.x1 = dsc->draw_area->x1;
            a.x2 = dsc->draw_area->x2;

            a.y1 = dsc->draw_area->y1;
            a.y2 = a.y1 + 4 + (devices[dsc->id] * h) / 100; /*+4 to overlap the radius*/
            draw_rect_dsc.bg_color = lv_palette_main(LV_PALETTE_RED);
            draw_rect_dsc.radius = 4;
            lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);

            a.y1 = a.y2 - 4;                                    /*-4 to overlap the radius*/
            a.y2 = a.y1 + (clothes[dsc->id] * h) / 100;
            draw_rect_dsc.bg_color = lv_palette_main(LV_PALETTE_BLUE);
            draw_rect_dsc.radius = 0;
            lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);

            a.y1 = a.y2;
            a.y2 = a.y1 + (services[dsc->id] * h) / 100;
            draw_rect_dsc.bg_color = lv_palette_main(LV_PALETTE_GREEN);
            lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);
        }
    }
}

void chart_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_PRESSED || code == LV_EVENT_RELEASED) {
        lv_obj_invalidate(obj); /*To make the value boxes visible*/
    }
    else if(code == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
        /*Set the markers' text*/
        if(dsc->part == LV_PART_TICKS && dsc->id == LV_CHART_AXIS_PRIMARY_X) {
            if(lv_chart_get_type(obj) == LV_CHART_TYPE_BAR) {
                const char * month[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII"};
                lv_snprintf(dsc->text, dsc->text_length, "%s", month[dsc->value]);
            }
            else {
                const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
                lv_snprintf(dsc->text, dsc->text_length, "%s", month[dsc->value]);
            }
        }

        /*Add the faded area before the lines are drawn */
        else if(dsc->part == LV_PART_ITEMS) {
            /*Add  a line mask that keeps the area below the line*/
            if(dsc->p1 && dsc->p2) {
                lv_draw_mask_line_param_t line_mask_param;
                lv_draw_mask_line_points_init(&line_mask_param, dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y,
                                              LV_DRAW_MASK_LINE_SIDE_BOTTOM);
                int16_t line_mask_id = lv_draw_mask_add(&line_mask_param, NULL);

                /*Add a fade effect: transparent bottom covering top*/
                lv_coord_t h = lv_obj_get_height(obj);
                lv_draw_mask_fade_param_t fade_mask_param;
                lv_draw_mask_fade_init(&fade_mask_param, &obj->coords, LV_OPA_COVER, obj->coords.y1 + h / 8, LV_OPA_TRANSP,
                                       obj->coords.y2);
                int16_t fade_mask_id = lv_draw_mask_add(&fade_mask_param, NULL);

                /*Draw a rectangle that will be affected by the mask*/
                lv_draw_rect_dsc_t draw_rect_dsc;
                lv_draw_rect_dsc_init(&draw_rect_dsc);
                draw_rect_dsc.bg_opa = LV_OPA_50;
                draw_rect_dsc.bg_color = dsc->line_dsc->color;

                lv_area_t obj_clip_area;
                _lv_area_intersect(&obj_clip_area, dsc->draw_ctx->clip_area, &obj->coords);
                const lv_area_t * clip_area_ori = dsc->draw_ctx->clip_area;
                dsc->draw_ctx->clip_area = &obj_clip_area;
                lv_area_t a;
                a.x1 = dsc->p1->x;
                a.x2 = dsc->p2->x - 1;
                a.y1 = LV_MIN(dsc->p1->y, dsc->p2->y);
                a.y2 = obj->coords.y2;
                lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);
                dsc->draw_ctx->clip_area = clip_area_ori;
                /*Remove the masks*/
                lv_draw_mask_remove_id(line_mask_id);
                lv_draw_mask_remove_id(fade_mask_id);
            }

            const lv_chart_series_t * ser = dsc->sub_part_ptr;

            if(lv_chart_get_pressed_point(obj) == dsc->id) {
                if(lv_chart_get_type(obj) == LV_CHART_TYPE_LINE) {
                    dsc->rect_dsc->outline_color = lv_color_white();
                    dsc->rect_dsc->outline_width = 2;
                }
                else {
                    dsc->rect_dsc->shadow_color = ser->color;
                    dsc->rect_dsc->shadow_width = 15;
                    dsc->rect_dsc->shadow_spread = 0;
                }

                char buf[8];
                lv_snprintf(buf, sizeof(buf), "%"LV_PRIu32, dsc->value);

                lv_point_t text_size;
                lv_txt_get_size(&text_size, buf, lv_obj_get_style_text_font(guider_ui.WidgetsDemo_chart_UV, LV_PART_TICKS|LV_STATE_DEFAULT), 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

                lv_area_t txt_area;
                if(lv_chart_get_type(obj) == LV_CHART_TYPE_BAR) {
                    txt_area.y2 = dsc->draw_area->y1 - LV_DPX(15);
                    txt_area.y1 = txt_area.y2 - text_size.y;
                    if(ser == lv_chart_get_series_next(obj, NULL)) {
                        txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2;
                        txt_area.x2 = txt_area.x1 + text_size.x;
                    }
                    else {
                        txt_area.x2 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2;
                        txt_area.x1 = txt_area.x2 - text_size.x;
                    }
                }
                else {
                    txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
                    txt_area.x2 = txt_area.x1 + text_size.x;
                    txt_area.y2 = dsc->draw_area->y1 - LV_DPX(15);
                    txt_area.y1 = txt_area.y2 - text_size.y;
                }

                lv_area_t bg_area;
                bg_area.x1 = txt_area.x1 - LV_DPX(8);
                bg_area.x2 = txt_area.x2 + LV_DPX(8);
                bg_area.y1 = txt_area.y1 - LV_DPX(8);
                bg_area.y2 = txt_area.y2 + LV_DPX(8);

                lv_draw_rect_dsc_t rect_dsc;
                lv_draw_rect_dsc_init(&rect_dsc);
                rect_dsc.bg_color = ser->color;
                rect_dsc.radius = LV_DPX(5);
                lv_draw_rect(dsc->draw_ctx, &rect_dsc, &bg_area);

                lv_draw_label_dsc_t label_dsc;
                lv_draw_label_dsc_init(&label_dsc);
                label_dsc.color = lv_color_white();
                label_dsc.font = lv_obj_get_style_text_font(guider_ui.WidgetsDemo_chart_UV, LV_PART_TICKS|LV_STATE_DEFAULT);
                lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area,  buf, NULL);
            }
            else {
                dsc->rect_dsc->outline_width = 0;
                dsc->rect_dsc->shadow_width = 0;
            }
        }
    }
}

void arc_MT_anim_cb(void * var, int32_t v)
{
    if(var == guider_ui.WidgetsDemo_arc_Blue) {
        lv_arc_set_value(guider_ui.WidgetsDemo_arc_Blue, v);
        lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_Sales, "Sales: %"LV_PRId32" %%", v);
    } else if(var == guider_ui.WidgetsDemo_arc_Red) {
        lv_arc_set_value(guider_ui.WidgetsDemo_arc_Red, v);
        lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_Revenue, "Revenue: %"LV_PRId32" %%", v);
    } else if(var == guider_ui.WidgetsDemo_arc_Green) {
        lv_arc_set_value(guider_ui.WidgetsDemo_arc_Green, v);
        lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_Costs, "Costs: %"LV_PRId32" %%", v);
    }
}

void meter_sessions_timer_cb(lv_timer_t * timer)
{
    lv_meter_indicator_t ** indics = timer->user_data;

    if(down1) {
        session_desktop -= 137;
        if(session_desktop < 1400) down1 = false;
    }
    else {
        session_desktop += 116;
        if(session_desktop > 4500) down1 = true;
    }

    if(down2) {
        session_tablet -= 3;
        if(session_tablet < 1400) down2 = false;
    }
    else {
        session_tablet += 9;
        if(session_tablet > 4500) down2 = true;
    }

    if(down3) {
        session_mobile -= 57;
        if(session_mobile < 1400) down3 = false;
    }
    else {
        session_mobile += 76;
        if(session_mobile > 4500) down3 = true;
    }

    uint32_t all = session_desktop + session_tablet + session_mobile;
    uint32_t pct1 = (session_desktop * 97) / all;
    uint32_t pct2 = (session_tablet * 97) / all;

    lv_meter_set_indicator_start_value(guider_ui.WidgetsDemo_meter_Sessions, indics[0], 0);
    lv_meter_set_indicator_end_value(guider_ui.WidgetsDemo_meter_Sessions, indics[0], pct1);

    lv_meter_set_indicator_start_value(guider_ui.WidgetsDemo_meter_Sessions, indics[1], pct1 + 1);
    lv_meter_set_indicator_end_value(guider_ui.WidgetsDemo_meter_Sessions, indics[1], pct1 + 1 + pct2);

    lv_meter_set_indicator_start_value(guider_ui.WidgetsDemo_meter_Sessions, indics[2], pct1 + 1 + pct2 + 1);
    lv_meter_set_indicator_end_value(guider_ui.WidgetsDemo_meter_Sessions, indics[2], 99);

    lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_Desktop, "Desktop: %"LV_PRIu32, session_desktop);

    lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_Tablet, "Tablet: %"LV_PRIu32, session_tablet);

    lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_Mobile, "Mobile: %"LV_PRIu32, session_mobile);
}

void meterNS_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_value(guider_ui.WidgetsDemo_meter_NS, var, v);

    lv_label_set_text_fmt(guider_ui.WidgetsDemo_label_NS_Num, "%"LV_PRId32, v);
}