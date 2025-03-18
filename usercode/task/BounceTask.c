/*
 * @Description: 拍球执行线程
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-18 23:07:23
 */

#include "BounceTask.h"

uint8_t externFlag_startSensor = 0;  //信号量 用于指示状态机在何时开始拍球返回检测

void BounceTask(void* argument)
{
    uint8_t flag_countUnitreeRelease = 0;  //标志变量 用于支撑结构关闭一段时间后置电流为零，宇树卸力
    uint8_t flag_countBounceCylinderContract = 0;  //标志变量 用于拍球气缸向下拍一段时间后收回
    uint8_t flag_countPawlBack = 0; //标志变量 用于夹爪快速抓球一段时间后转位置伺服
    for(;;)
    {
        if (throwhsm.wholestate == WHOLE_BOUNCE)
        {
            if (throwhsm.bouncestate == BOUNCE_CATCHING)
            {
                positionServo(-85.4, &hDJI[1]);
            }
            else if (throwhsm.bouncestate == BOUNCE_GETTOPOSITION)
            {
                positionServo(-85.4, &hDJI[1]);
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 2.2, 0.15, unitreeStartPos0+1.6, 0.6, 0.15);
            }
            else if (throwhsm.bouncestate == BOUNCE_READY)
            {
                while (flag_countUnitreeRelease < 100)
                {
                    hDJI[2].speedPID.output = 8000;
                    hDJI[3].speedPID.output = -8000;
                    positionServo(-85.4, &hDJI[1]);
                    Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                    Unitree_ChangeState(&myMotor1, 1, 1, 2.2, 0.15, unitreeStartPos0+1.6, 0.6, 0.15);
                    ++flag_countUnitreeRelease;
                    osDelay(2);
                }
                hDJI[2].speedPID.output = 0;
                hDJI[3].speedPID.output = 0;
                positionServo(-85.4, &hDJI[1]);
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
                HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_SET);
            }
            else if (throwhsm.bouncestate == BOUNCE_BOUNCE)
            {
                while (flag_countBounceCylinderContract < 100)
                {
                    hDJI[1].speedPID.output = 9000;
                    HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_SET);
                    ++flag_countBounceCylinderContract;
                    osDelay(2);
                }
                HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_RESET);
                hDJI[1].speedPID.output = 0;
                osDelay(150);//传感器信号延迟打开（未测试）
                externFlag_startSensor = 1;
            }
            else if (throwhsm.bouncestate == BOUNCE_CATCHANDADJUSTPOSTURE)
            {
                while (flag_countPawlBack < 50)
                {
                    hDJI[1].speedPID.output = -9000;
                    ++flag_countPawlBack;
                    osDelay(2);
                }
                positionServo(-85.4, &hDJI[1]);
                HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_RESET);
                speedServo(5000, &hDJI[0]);
            }
            osDelay(2);
        }
        else
        {
            flag_countBounceCylinderContract = 0;
            flag_countUnitreeRelease = 0;
            flag_countPawlBack = 0;
            externFlag_startSensor = 0;
            osDelay(10);
        }
    }
}