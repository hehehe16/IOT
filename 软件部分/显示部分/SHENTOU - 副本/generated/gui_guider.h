/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *WidgetsDemo;
	bool WidgetsDemo_del;
	lv_obj_t *g_kb_WidgetsDemo;
	lv_obj_t *WidgetsDemo_tabview_Main;
	lv_obj_t *WidgetsDemo_tabview_Main_tab_1;
	lv_obj_t *WidgetsDemo_tabview_Main_tab_2;
	lv_obj_t *WidgetsDemo_tabview_Main_tab_3;
	lv_obj_t *WidgetsDemo_cont_Skills;
	lv_obj_t *WidgetsDemo_sw_TeamPlayer;
	lv_obj_t *WidgetsDemo_sw_HardWork;
	lv_obj_t *WidgetsDemo_slider_Exp;
	lv_obj_t *WidgetsDemo_label_Skils;
	lv_obj_t *WidgetsDemo_label_TP;
	lv_obj_t *WidgetsDemo_label_HW;
	lv_obj_t *WidgetsDemo_label_Exp;
	lv_obj_t *WidgetsDemo_cont_Profile;
	lv_obj_t *WidgetsDemo_ta_UName;
	lv_obj_t *WidgetsDemo_ta_Password;
	lv_obj_t *WidgetsDemo_ddlist_Gender;
	lv_obj_t *WidgetsDemo_datetext_Birthday;
	lv_obj_t *WidgetsDemo_label_UName;
	lv_obj_t *WidgetsDemo_label_Password;
	lv_obj_t *WidgetsDemo_label_Birthday;
	lv_obj_t *WidgetsDemo_label_Gender;
	lv_obj_t *WidgetsDemo_label_Profile;
	lv_obj_t *WidgetsDemo_cont_Card;
	lv_obj_t *WidgetsDemo_btn_Logout;
	lv_obj_t *WidgetsDemo_btn_Logout_label;
	lv_obj_t *WidgetsDemo_btn_Invite;
	lv_obj_t *WidgetsDemo_btn_Invite_label;
	lv_obj_t *WidgetsDemo_label_Dsc;
	lv_obj_t *WidgetsDemo_label_Name;
	lv_obj_t *WidgetsDemo_label_Email;
	lv_obj_t *WidgetsDemo_label_Tele;
	lv_obj_t *WidgetsDemo_label_IconEmail;
	lv_obj_t *WidgetsDemo_label_IconCall;
	lv_obj_t *WidgetsDemo_img_Avatar;
	lv_obj_t *WidgetsDemo_cont_Revenue;
	lv_obj_t *WidgetsDemo_chart_MR;
	lv_chart_series_t *WidgetsDemo_chart_MR_0;
	lv_chart_series_t *WidgetsDemo_chart_MR_1;
	lv_obj_t *WidgetsDemo_label_MR;
	lv_obj_t *WidgetsDemo_cont_Sessions;
	lv_obj_t *WidgetsDemo_label_Sessions;
	lv_obj_t *WidgetsDemo_label_Desktop;
	lv_obj_t *WidgetsDemo_label_Mobile;
	lv_obj_t *WidgetsDemo_label_Tablet;
	lv_obj_t *WidgetsDemo_meter_Sessions;
	lv_meter_indicator_t *WidgetsDemo_meter_Sessions_scale_0_arc_0;
	lv_meter_indicator_t *WidgetsDemo_meter_Sessions_scale_0_arc_1;
	lv_meter_indicator_t *WidgetsDemo_meter_Sessions_scale_0_arc_2;
	lv_obj_t *WidgetsDemo_RedCircle_Sessions;
	lv_obj_t *WidgetsDemo_GreenCircle_Sessions;
	lv_obj_t *WidgetsDemo_BlueCircle_Sessions;
	lv_obj_t *WidgetsDemo_cont_NS;
	lv_obj_t *WidgetsDemo_label_NS;
	lv_obj_t *WidgetsDemo_label_NS_Red;
	lv_obj_t *WidgetsDemo_label_NS_Green;
	lv_obj_t *WidgetsDemo_label_NS_Blue;
	lv_obj_t *WidgetsDemo_meter_NS;
	lv_meter_indicator_t *WidgetsDemo_meter_NS_scale_0_ndline_0;
	lv_meter_indicator_t *WidgetsDemo_meter_NS_scale_0_arc_0;
	lv_meter_indicator_t *WidgetsDemo_meter_NS_scale_0_arc_1;
	lv_meter_indicator_t *WidgetsDemo_meter_NS_scale_0_arc_2;
	lv_obj_t *WidgetsDemo_GreenCircle_NS;
	lv_obj_t *WidgetsDemo_BlueCircle_NS;
	lv_obj_t *WidgetsDemo_RedCircle_NS;
	lv_obj_t *WidgetsDemo_label_NS_Num;
	lv_obj_t *WidgetsDemo_label_NS_Mbps;
	lv_obj_t *WidgetsDemo_cont_UV;
	lv_obj_t *WidgetsDemo_chart_UV;
	lv_chart_series_t *WidgetsDemo_chart_UV_0;
	lv_obj_t *WidgetsDemo_label_UV;
	lv_obj_t *WidgetsDemo_cont_MT;
	lv_obj_t *WidgetsDemo_label_MT;
	lv_obj_t *WidgetsDemo_arc_Blue;
	lv_obj_t *WidgetsDemo_arc_Red;
	lv_obj_t *WidgetsDemo_arc_Green;
	lv_obj_t *WidgetsDemo_label_Revenue;
	lv_obj_t *WidgetsDemo_label_Costs;
	lv_obj_t *WidgetsDemo_label_Sales;
	lv_obj_t *WidgetsDemo_GreenCircle_MT;
	lv_obj_t *WidgetsDemo_BlueCircle_MT;
	lv_obj_t *WidgetsDemo_RedCircle_MT;
	lv_obj_t *WidgetsDemo_cont_Notification;
	lv_obj_t *WidgetsDemo_cb_ItemPur;
	lv_obj_t *WidgetsDemo_cb_NewCon;
	lv_obj_t *WidgetsDemo_cb_NewMsg;
	lv_obj_t *WidgetsDemo_cb_NewSub;
	lv_obj_t *WidgetsDemo_cb_Milestone;
	lv_obj_t *WidgetsDemo_cb_OutofStock;
	lv_obj_t *WidgetsDemo_label_Notification;
	lv_obj_t *WidgetsDemo_cont_Products;
	lv_obj_t *WidgetsDemo_img_Clothes1;
	lv_obj_t *WidgetsDemo_label_ClothCat1;
	lv_obj_t *WidgetsDemo_label_Prince1;
	lv_obj_t *WidgetsDemo_label_TopProducts;
	lv_obj_t *WidgetsDemo_label_ClothCat2;
	lv_obj_t *WidgetsDemo_label_Prince2;
	lv_obj_t *WidgetsDemo_img_Clothes2;
	lv_obj_t *WidgetsDemo_label_ClothCat3;
	lv_obj_t *WidgetsDemo_label_Prince3;
	lv_obj_t *WidgetsDemo_img_Clothes3;
	lv_obj_t *WidgetsDemo_label_ClothCat4;
	lv_obj_t *WidgetsDemo_label_Prince4;
	lv_obj_t *WidgetsDemo_img_Clothes4;
	lv_obj_t *WidgetsDemo_label_ClothCat5;
	lv_obj_t *WidgetsDemo_label_Prince5;
	lv_obj_t *WidgetsDemo_img_Clothes5;
	lv_obj_t *WidgetsDemo_cont_Summary;
	lv_obj_t *WidgetsDemo_label_MS;
	lv_obj_t *WidgetsDemo_label_Date;
	lv_obj_t *WidgetsDemo_label_Growth;
	lv_obj_t *WidgetsDemo_chart_MS;
	lv_chart_series_t *WidgetsDemo_chart_MS_0;
	lv_obj_t *WidgetsDemo_cont_ColorChanger;
	lv_obj_t *WidgetsDemo_btn_Blue;
	lv_obj_t *WidgetsDemo_btn_Blue_label;
	lv_obj_t *WidgetsDemo_btn_Green;
	lv_obj_t *WidgetsDemo_btn_Green_label;
	lv_obj_t *WidgetsDemo_btn_Grey;
	lv_obj_t *WidgetsDemo_btn_Grey_label;
	lv_obj_t *WidgetsDemo_btn_Orange;
	lv_obj_t *WidgetsDemo_btn_Orange_label;
	lv_obj_t *WidgetsDemo_btn_Red;
	lv_obj_t *WidgetsDemo_btn_Red_label;
	lv_obj_t *WidgetsDemo_btn_Purple;
	lv_obj_t *WidgetsDemo_btn_Purple_label;
	lv_obj_t *WidgetsDemo_btn_Teal;
	lv_obj_t *WidgetsDemo_btn_Teal_label;
	lv_obj_t *WidgetsDemo_btn_ColorSW;
	lv_obj_t *WidgetsDemo_btn_ColorSW_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_move_animation(void * var, int32_t duration, int32_t delay, int32_t x_end, int32_t y_end, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_scale_animation(void * var, int32_t duration, int32_t delay, int32_t width, int32_t height, lv_anim_path_cb_t path_cb,
                        uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                        lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_zoom_animation(void * var, int32_t duration, int32_t delay, int32_t zoom, lv_anim_path_cb_t path_cb,
                           uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                           lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_rotate_animation(void * var, int32_t duration, int32_t delay, lv_coord_t x, lv_coord_t y, int32_t rotate,
                   lv_anim_path_cb_t path_cb, uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time,
                   uint32_t playback_delay, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_WidgetsDemo(lv_ui *ui);
LV_IMG_DECLARE(_avatar_alpha_96x96);
LV_IMG_DECLARE(_clothes_alpha_39x53);
LV_IMG_DECLARE(_clothes_alpha_39x53);
LV_IMG_DECLARE(_clothes_alpha_39x53);
LV_IMG_DECLARE(_clothes_alpha_39x53);
LV_IMG_DECLARE(_clothes_alpha_39x53);

LV_FONT_DECLARE(lv_font_montserratMedium_10)
LV_FONT_DECLARE(lv_font_montserratMedium_13)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)


#ifdef __cplusplus
}
#endif
#endif
