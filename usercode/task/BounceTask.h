/*
 * @Description: 拍球执行线程
 * @Author: Alex
 * @Date: 2025-03-12 15:04:54
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-12 15:06:00
 */

#ifndef BOUNCETASK_H
#define BOUNCETASK_H

#include "AllUserTask.h"
#include "main.h"
#include "ThrowHSM.h"
#include "Unitree_user.h"
#include "DJI.h"

extern uint8_t externFlag_startSensor;

void BounceTask(void* argument);

#endif