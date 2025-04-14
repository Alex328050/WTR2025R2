/*
 * @Description: 
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 21:57:02
 */
#ifndef ALLUSERTASK_H
#define ALLUSERTASK_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file AllUserTask.h
 * @author thrzer
 * @brief wtr一代车freertos任务定义，在freertos.c中include
 * @date 2024-11-23
 */

#include "main.h"
#include "cmsis_os.h"

#include "InitTask.h"
#include "ThrowHSMTask.h"
#include "UnitreeExecutorTask.h"
#include "DJIExecutorTask.h"
#include "RmctlTask.h"
#include "ThrowTask.h"
#include "ReadyTask.h"
#include "BounceTask.h"
#include "RmctlTrasmitTask.h"

void User_FREERTOS_Init(void);
void HsmTask(void *argument);
// void ChassisTask(void *argument);
// void PopTask(void *argument);
#ifdef __cplusplus
}
#endif

#endif