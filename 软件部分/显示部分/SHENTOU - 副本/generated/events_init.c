/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


#include "custom.h"

static lv_meter_indicator_t * meter_indic[3];


static void WidgetsDemo_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SCREEN_LOADED:
	{
		lv_obj_add_state(guider_ui.WidgetsDemo_btn_Invite, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.WidgetsDemo_cb_Milestone, LV_STATE_CHECKED);
		lv_obj_add_state(guider_ui.WidgetsDemo_cb_NewSub, LV_STATE_CHECKED);
		lv_obj_clear_flag(guider_ui.WidgetsDemo, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_state(guider_ui.WidgetsDemo_cb_NewMsg, LV_STATE_DISABLED);
		
	    //create animation for meter_NS
	    lv_anim_t meterNS_anim;
	    lv_anim_init(&meterNS_anim);
	    lv_anim_set_values(&meterNS_anim, 10, 60);
	    lv_anim_set_repeat_count(&meterNS_anim, LV_ANIM_REPEAT_INFINITE);
	    lv_anim_set_exec_cb(&meterNS_anim, meterNS_anim_cb);
	    lv_anim_set_var(&meterNS_anim, guider_ui.WidgetsDemo_meter_NS_scale_0_ndline_0);
	    lv_anim_set_time(&meterNS_anim, 4100);
	    lv_anim_set_playback_time(&meterNS_anim, 800);
	    lv_anim_start(&meterNS_anim);
	    
	    //create animation for arcs of Monthly Target
	    lv_anim_t arc_MT_anim;
	    lv_anim_init(&arc_MT_anim);
	    lv_anim_set_values(&arc_MT_anim, 20, 100);
	    lv_anim_set_repeat_count(&arc_MT_anim, LV_ANIM_REPEAT_INFINITE);
	    //Red: Revenue
	    lv_anim_set_exec_cb(&arc_MT_anim, arc_MT_anim_cb);
	    lv_anim_set_var(&arc_MT_anim, guider_ui.WidgetsDemo_arc_Red);
	    lv_anim_set_time(&arc_MT_anim, 2600);
	    lv_anim_set_playback_time(&arc_MT_anim, 3200);
	    lv_anim_start(&arc_MT_anim);
	    //Blue: Sales
	    lv_anim_set_exec_cb(&arc_MT_anim, arc_MT_anim_cb);
	    lv_anim_set_var(&arc_MT_anim, guider_ui.WidgetsDemo_arc_Blue);
	    lv_anim_set_time(&arc_MT_anim, 4100);
	    lv_anim_set_playback_time(&arc_MT_anim, 2700);
	    lv_anim_start(&arc_MT_anim);
	    //Green: Costs
	    lv_anim_set_exec_cb(&arc_MT_anim, arc_MT_anim_cb);
	    lv_anim_set_var(&arc_MT_anim, guider_ui.WidgetsDemo_arc_Green);
	    lv_anim_set_time(&arc_MT_anim, 2800);
	    lv_anim_set_playback_time(&arc_MT_anim, 1800);
	    lv_anim_start(&arc_MT_anim);
	    
	    //create timer for meter sessions
	    meter_indic[0] = guider_ui.WidgetsDemo_meter_Sessions_scale_0_arc_0;
	    meter_indic[1] = guider_ui.WidgetsDemo_meter_Sessions_scale_0_arc_1;
	    meter_indic[2] = guider_ui.WidgetsDemo_meter_Sessions_scale_0_arc_2;
	    lv_timer_create(meter_sessions_timer_cb, 100, meter_indic);
	
		lv_obj_clear_flag(guider_ui.WidgetsDemo_arc_Green, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_clear_flag(guider_ui.WidgetsDemo_arc_Red, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_clear_flag(guider_ui.WidgetsDemo_arc_Blue, LV_OBJ_FLAG_CLICKABLE);
		break;
	}
	default:
		break;
	}
}
void events_init_WidgetsDemo(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->WidgetsDemo, WidgetsDemo_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{

}
