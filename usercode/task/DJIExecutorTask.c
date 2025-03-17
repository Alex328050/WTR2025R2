/*
 * @Description: 大疆电机控制线程
 * @Author: Alex
 * @Date: 2025-03-10 17:25:15
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 17:34:54
 */

#include "DJIExecutorTask.h"

void DJIExecutorTask(void* argument)
{
    for(;;)
    {
        CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, hDJI[2].speedPID.output, hDJI[3].speedPID.output);
        osDelay(2);
    }
}