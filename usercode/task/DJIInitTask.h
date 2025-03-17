/*
 * @Description: 大疆电机初始化线程
 * @Author: Alex
 * @Date: 2025-03-06 23:32:51
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 16:11:54
 */

#ifndef DJIINITTASK_H
#define DJIINITTASK_H

#include "main.h"
#include "AllUserTask.h"
#include "DJI.h"
#include "cmsis_os.h"

extern uint8_t flag_DJIInitComplete;

void DJIInitTask(void *argument);

#endif
