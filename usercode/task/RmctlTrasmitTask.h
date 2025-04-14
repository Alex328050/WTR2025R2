/*
 * @Description: 遥控器消息传递线程
 * @Author: Alex
 * @Date: 2025-03-28 20:59:32
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-28 21:06:54
 */

#ifndef RMCTLTRASMITTASK_H
#define RMCTLTRASMITTASK_H

#include "rmctl.h"
#include "main.h"
#include "ThrowHSM.h"
#include "cmsis_os.h"
#include "AllUserTask.h"

void RmctlTrasmitTask(void* argument);

#endif