/*
 * @Description: 准备姿态线程
 * @Author: Alex
 * @Date: 2025-03-15 23:47:24
 * @LastEditors: Alex
 * @LastEditTime: 2025-04-11 22:37:42
 */

#include "ReadyTask.h"

void ReadyTask(void* argument)
{
    uint8_t flag_countOpenBrace = 0;
    for(;;)
    {
        if (throwhsm.wholestate == WHOLE_READY)
        {
            while (flag_countOpenBrace < 50)
            {
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
                hDJI[0].speedPID.output = 0;
                hDJI[2].speedPID.output = -8000;
                hDJI[3].speedPID.output = 8000;
                positionServo(0, &hDJI[1]);
                ++flag_countOpenBrace;
                osDelay(2);
            }
            Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
            Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
            hDJI[0].speedPID.output = 0;
            hDJI[2].speedPID.output = 0;
            hDJI[3].speedPID.output = 0;
            positionServo(0, &hDJI[1]);
            //speedServo(5000, &hDJI[1]);
            osDelay(2);
        }
        else
        {
            flag_countOpenBrace = 0;
            osDelay(10);
        }
    }
}