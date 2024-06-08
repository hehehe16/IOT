// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void custom_init(lv_ui *ui);

void textarea_event_cb(lv_event_t * e);

void color_changer_event_cb(lv_event_t * e);

void color_event_cb(lv_event_t * e);

void shop_chart_event_cb(lv_event_t * e);

void arc_MT_anim_cb(void * var, int32_t v);

void chart_event_cb(lv_event_t * e);

void meter_sessions_timer_cb(lv_timer_t * timer);

void meterNS_anim_cb(void * var, int32_t v);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
