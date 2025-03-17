/*
 * @Description: 宇树初始化线程
 * @Author: Alex
 * @Date: 2025-03-06 23:15:10
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 16:41:13
 */
#ifndef UNITREEINITTASK_H
#define UNITREEINITTASK_H

#include "main.h"
#include "cmsis_os.h"
#include "AllUserTask.h"
#include "Unitree_user.h"
#include "ThrowHSM.h"

extern uint8_t flag_unitreeInitComplete;
extern UnitreeMotor myMotor0;
extern UnitreeMotor myMotor1;
extern float unitreeStartPos0;
extern float unitreeStartPos1;

void UnitreeInitTask(void *argument);

#endif
