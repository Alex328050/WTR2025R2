/*
 * @Description: 大疆电机控制线程
 * @Author: Alex
 * @Date: 2025-03-10 17:25:15
 * @LastEditors: Alex
 * @LastEditTime: 2025-05-29 22:47:18
 */

#include "DJIExecutorTask.h"

void DJIExecutorTask(void* argument)
{
    for(;;)
    {
        if (throwhsm.wholestate != WHOLE_INITING && throwhsm.wholestate != WHOLE_ERROR)
        {
            CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, hDJI[2].speedPID.output, hDJI[3].speedPID.output);
            CanTransmit_DJI_5678(&hcan1, hDJI[4].speedPID.output, hDJI[5].speedPID.output, 0, 0);
            osDelay(2);
        }
        else osDelay(10);
    }
}