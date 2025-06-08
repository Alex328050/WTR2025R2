/*
 * @Description: 准备姿态线程
 * @Author: Alex
 * @Date: 2025-03-15 23:47:24
 * @LastEditors: Alex
 * @LastEditTime: 2025-06-05 21:41:25
 */

#include "ReadyTask.h"

void ReadyTask(void* argument)
{
    uint8_t flag_countOpenBrace = 0;
    for(;;)
    {
        if (throwhsm.wholestate == WHOLE_READY)
        {
            while (flag_countOpenBrace < 100)
            {
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
                hDJI[0].speedPID.output = 0;
                hDJI[2].speedPID.output = -8000;
                hDJI[3].speedPID.output = 8000;
                hDJI[4].speedPID.output = 0;
                hDJI[5].speedPID.output = 0;
                positionServo(0, &hDJI[1]);
                ++flag_countOpenBrace;
                osDelay(2);
            }
            Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
            Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
            hDJI[0].speedPID.output = 0;
            hDJI[2].speedPID.output = 0;
            hDJI[3].speedPID.output = 0;
            hDJI[4].speedPID.output = 0;
            hDJI[5].speedPID.output = 0;
            //positionServo(0, &hDJI[1]);
            HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_RESET);  //拍球气缸收回
            HAL_GPIO_WritePin(PAWL_GPIO_Port,PAWL_Pin,GPIO_PIN_RESET);  //气缸夹爪张开
            osDelay(2);
        }
        else
        {
            flag_countOpenBrace = 0;
            osDelay(10);
        }
    }
}