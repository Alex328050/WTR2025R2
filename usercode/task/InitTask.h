/*
 * @Description: 各部件初始化线程
 * @Author: Alex
 * @Date: 2025-03-23 21:15:38
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 21:56:22
 */

#ifndef INITTASK_H
#define INITTASK_H

#include "main.h"
#include "AllUserTask.h"
#include "DJI.h"
#include "Unitree_user.h"
#include "wtr_can.h"
#include "encoder.h"
#include "ThrowHSM.h"

extern uint8_t flag_initComplete;

extern UnitreeMotor myMotor0;
extern UnitreeMotor myMotor1;
extern float unitreeStartPos0;
extern float unitreeStartPos1;

void InitTask(void* argument);

#endif