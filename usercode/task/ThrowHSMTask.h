/*
 * @Description: 抛射全车状态机更改线程
 * @Author: Alex
 * @Date: 2025-03-10 16:06:28
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 17:09:24
 */

#ifndef THROWHSMTASK_H
#define THROWHSMTASK_H

#include "AllUserTask.h"
#include "main.h"
#include "rmctl.h"
#include "ThrowHSM.h"
#include "encoder.h"
#include "DJI.h"
#include "BounceTask.h"

void ThrowHSMTask(void* argument);

#endif