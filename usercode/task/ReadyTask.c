/*
 * @Description: 准备姿态线程
 * @Author: Alex
 * @Date: 2025-03-15 23:47:24
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-15 23:54:41
 */

#include "ReadyTask.h"

void ReadyTask(void* argument)
{
    for(;;)
    {
        if (throwhsm.wholestate == WHOLE_READY)
        {
            Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
            Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
            speedServo(0, &hDJI[0]);
            speedServo(0, &hDJI[2]);
            speedServo(0, &hDJI[3]);
            positionServo(0, &hDJI[1]);
            osDelay(2);
        }
        else osDelay(10);
    }
}