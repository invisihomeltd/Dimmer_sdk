/*
 * @Author: sky
 * @Date: 2020-03-09 18:34:28
 * @LastEditTime: 2020-03-09 18:53:03
 * @LastEditors: Please set LastEditors
 * @Description: ota
 * @FilePath: \mqtt_example\components\light_device\light_handle.c
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <string.h>

#include "mwifi.h"
#include "mupgrade.h"
#include "mlink.h"

#include "utlis.h"

#ifndef _HUE_H

#define _HUE_H

void hue_init(void);

#endif  // _HUE_H