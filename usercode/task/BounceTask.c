/*
 * @Description: 拍球执行线程
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-06-08 11:39:20
 */

#include "BounceTask.h"

uint8_t externFlag_startSensor = 0;  //信号量 用于指示状态机在何时开始拍球返回检测

void BounceTask(void* argument)
{
    uint8_t flag_countUnitreeRelease = 0;  //标志变量 用于支撑结构关闭一段时间后置电流为零，宇树卸力
    uint8_t flag_frictionGearReachSpeed = 0;  //标志变量 用于指示何时摩擦轮转动稳定
    uint8_t flag_frictionGearReverse = 0;   // 标志变量 用于指示何时摩擦轮反转
    uint8_t flag_countPawlBack = 0; //标志变量 用于夹爪快速抓球一段时间后转位置伺服
    for(;;)
    {
        if (throwhsm.wholestate == WHOLE_BOUNCE || throwhsm.wholestate == WHOLE_CONBOUNCE)
        {
            if (throwhsm.bouncestate == BOUNCE_CATCHING)
            {
                HAL_GPIO_WritePin(PAWL_GPIO_Port,PAWL_Pin,GPIO_PIN_SET);  //气缸夹爪闭合
                positionServo(PAWL_POSITION, &hDJI[1]);
            }
            else if (throwhsm.bouncestate == BOUNCE_GETTOPOSITION) //只有非连续拍球进入此状态
            {
                hDJI[0].speedPID.output = 0;
                positionServo(PAWL_POSITION, &hDJI[1]);
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 2.8, 0.15, unitreeStartPos1+1.9, 0.55, 0.15);
            }
            else if (throwhsm.bouncestate == BOUNCE_READY)
            {
                if(throwhsm.wholestate == WHOLE_BOUNCE)
                {
                    while (flag_countUnitreeRelease < 200)
                    {
                        hDJI[2].speedPID.output = 8000;
                        hDJI[3].speedPID.output = -8000;
                        positionServo(PAWL_POSITION, &hDJI[1]);
                        ++flag_countUnitreeRelease;
                        HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_SET);  //伸缩气缸推出
                        osDelay(2);
                    }
                    hDJI[2].speedPID.output = 0;
                    hDJI[3].speedPID.output = 0;
                    positionServo(PAWL_POSITION, &hDJI[1]);
                    Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                    Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
                }
                HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_SET);  //伸缩气缸推出
            }
            else if (throwhsm.bouncestate == BOUNCE_BOUNCE)
            {
                while (flag_frictionGearReachSpeed < 250)
                {
                    if(throwhsm.wholestate == WHOLE_BOUNCE) positionServo(0, &hDJI[1]);
                    speedServo(4000, &hDJI[4]);
                    speedServo(-4000, &hDJI[5]);
                    ++flag_frictionGearReachSpeed;
                    osDelay(2);
                }
                while (flag_frictionGearReverse < 250)
                {
                    speedServo(4000, &hDJI[4]);
                    speedServo(-4000, &hDJI[5]);
                    HAL_GPIO_WritePin(PAWL_GPIO_Port,PAWL_Pin,GPIO_PIN_RESET);  //气缸夹爪张开
                    ++flag_frictionGearReverse;
                    osDelay(2);
                }
                speedServo(-4000, &hDJI[4]);
                speedServo(4000, &hDJI[5]);
                // externFlag_startSensor = 1;
            }
            else if (throwhsm.bouncestate == BOUNCE_CATCHANDADJUSTPOSTURE)
            {
                if (throwhsm.wholestate == WHOLE_BOUNCE) 
                {
                    while (flag_countPawlBack < 50)
                    {
                        if (throwhsm.wholestate == WHOLE_BOUNCE) speedServo(5000, &hDJI[0]);
                        hDJI[1].speedPID.output = -9000;
                        ++flag_countPawlBack;
                        osDelay(2);
                    }
                    speedServo(5000, &hDJI[0]);
                    // positionServo(-130, &hDJI[1]);
                    hDJI[1].speedPID.output = 8000;//关
                }
                else if(throwhsm.wholestate == WHOLE_CONBOUNCE) 
                {
                    HAL_GPIO_WritePin(PAWL_GPIO_Port,PAWL_Pin,GPIO_PIN_SET);  //气缸夹爪闭合
                }
                hDJI[4].speedPID.output = 0;
                hDJI[5].speedPID.output = 0;
                flag_frictionGearReachSpeed = 0;
                flag_frictionGearReverse = 0;
                flag_countPawlBack = 0;
                // externFlag_startSensor = 0;
            }
            else if (throwhsm.bouncestate == BOUNCE_RESERVEMOTOR)
            {
                speedServo(-4000, &hDJI[4]);
                speedServo(4000, &hDJI[5]);
            }
            else if (throwhsm.bouncestate == BOUNCE_WAITBALL)
            {
                HAL_GPIO_WritePin(PAWL_GPIO_Port,PAWL_Pin,GPIO_PIN_RESET);  //摩擦轮拍球，气缸夹爪张开
            }
            osDelay(2);
        }
        else
        {
            flag_countUnitreeRelease = 0;
            flag_frictionGearReachSpeed = 0;
            flag_frictionGearReverse = 0;
            flag_countPawlBack = 0;
            // externFlag_startSensor = 0;
            osDelay(10);
        }
    }
}