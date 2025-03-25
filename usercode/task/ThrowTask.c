/*
 * @Description: 抛射执行线程
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 23:07:17
 */

#include "ThrowTask.h"

/**
 * @brief 抛射执行线程
 * 
 * @param argument 
 */
void ThrowTask(void *argument)
{
    uint8_t flag_countBraceDelay = 0; //标志变量 用于支撑结构打开一段时间后置电流为0
    uint8_t flag_countPawlDelay = 0;  //标志变量 用于夹爪关闭一段时间后置电流为0
  for(;;)   
  {
    if (throwhsm.wholestate == WHOLE_THROW || throwhsm. wholestate == WHOLE_CONTHROW)
    {
        if      (throwhsm.throwstate == THROW_CATCHING)
        {
            speedServo(5000, &hDJI[0]);
            positionServo(-85.8, &hDJI[1]);
        }
        else if (throwhsm.throwstate == THROW_GATHERSTRENGTH)
        {
            speedServo(5000, &hDJI[0]);
            positionServo(-85.8, &hDJI[1]);
            Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
            Unitree_ChangeState(&myMotor1, 1, 1, 1.6, 0, unitreeStartPos1+1.6, 0.4, 0.2);
            hDJI[2].speedPID.output = 0;
            hDJI[3].speedPID.output = 0;
        }
        else if (throwhsm.throwstate == THROW_CLEARBRACE)
        {
            while (flag_countBraceDelay < 50)
            {
                speedServo(-5000, &hDJI[0]);
                positionServo(-85.4, &hDJI[1]);
                hDJI[2].speedPID.output = -5000;
                hDJI[3].speedPID.output = 5000;
                ++flag_countBraceDelay;
                osDelay(2);
            }
            speedServo(-5000, &hDJI[0]);
            positionServo(-85.8, &hDJI[1]);
            hDJI[2].speedPID.output = 0;
            hDJI[3].speedPID.output = 0;
        }
        else if (throwhsm.throwstate == THROW_ACCELERATE)
        {
            hDJI[0].speedPID.output = 0;
            positionServo(-85.8, &hDJI[1]);
            Unitree_ChangeState(&myMotor0, 0, 1, 20, 0, 0, 0, 0);        
            Unitree_ChangeState(&myMotor1, 1, 1, -20, 0, 0, 0, 0);
        }
        else if (throwhsm.throwstate == THROW_THROWOUT)
        {
            hDJI[1].speedPID.output = 8000;
            Unitree_ChangeState(&myMotor0, 0, 1, 20, 0, 0, 0, 0);        
            Unitree_ChangeState(&myMotor1, 1, 1, -20, 0, 0, 0, 0);
        }
        else if (throwhsm.throwstate == THROW_BACK)
        {
            Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
            Unitree_ChangeState(&myMotor1, 1, 1, 2, 0.5, unitreeStartPos1, 0.5, 0.1);
            while (flag_countPawlDelay < 100)
            {
                hDJI[1].speedPID.output = -8000;
                ++flag_countPawlDelay;
                osDelay(2);
            }
            positionServo(0, &hDJI[1]);
        }
        osDelay(2);
    }
    else
    {
        flag_countBraceDelay = 0;
        flag_countPawlDelay = 0;
        osDelay(10);
    }
  }


  /* USER CODE END encoderRead */
}
