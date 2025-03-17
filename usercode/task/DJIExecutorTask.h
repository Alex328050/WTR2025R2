/*
 * @Description: 大疆电机控制线程
 * @Author: Alex
 * @Date: 2025-03-10 17:25:58
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 17:27:13
 */

#ifndef DJIEXECUTORTASK_H
#define DJIEXECUTORTASK_H

#include "AllUserTask.h"
#include "DJI.h"
#include "wtr_can.h"

void DJIExecutorTask(void* argument);

#endif