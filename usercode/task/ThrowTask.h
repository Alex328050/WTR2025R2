/*
 * @Description: 抛射执行线程
 * @Author: Alex
 * @Date: 2025-03-10 17:36:12
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 21:57:11
 */

#ifndef THROWTASK_H
#define THROWTASK_H

#include "AllUserTask.h"
#include "main.h"
#include "ThrowHSM.h"
#include "retarget.h"
#include "Caculate.h"
#include "DJI.h"
#include "InitTask.h"

void ThrowTask(void *argument);

#endif