/*
 * @Description: 拍球执行线程
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-28 18:11:14
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
        if (throwhsm.wholestate == WHOLE_BOUNCE || throwhsm.wholestate == WHOLE_CONBOUNCE)
        {
            if (throwhsm.bouncestate == BOUNCE_CATCHING)
            {
                positionServo(-115, &hDJI[1]);
                speedServo(5000, &hDJI[0]);
            }
            else if (throwhsm.bouncestate == BOUNCE_GETTOPOSITION)
            {
                positionServo(-115, &hDJI[1]);
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 2.8, 0.15, unitreeStartPos1+1.9, 0.55, 0.15);
                hDJI[0].speedPID.output = 0;
            }
            else if (throwhsm.bouncestate == BOUNCE_READY)
            {
                while (flag_countUnitreeRelease < 100)
                {
                    hDJI[2].speedPID.output = 8000;
                    hDJI[3].speedPID.output = -8000;
                    positionServo(-115, &hDJI[1]);
                    ++flag_countUnitreeRelease;
                    osDelay(2);
                }
                hDJI[2].speedPID.output = 0;
                hDJI[3].speedPID.output = 0;
                positionServo(-115, &hDJI[1]);
                Unitree_ChangeState(&myMotor0, 0, 1, 0, 0, 0, 0, 0);
                Unitree_ChangeState(&myMotor1, 1, 1, 0, 0, 0, 0, 0);
                HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_SET);  //伸缩气缸推出
            }
            else if (throwhsm.bouncestate == BOUNCE_BOUNCE)
            {
                while (flag_countBounceCylinderContract < 80)
                {
                    hDJI[1].speedPID.output = 9000;
                    HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_SET);  //拍球气缸推出
                    ++flag_countBounceCylinderContract;
                    osDelay(2);
                }
                HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_RESET);  //拍球气缸收回
                hDJI[1].speedPID.output = 0;
                osDelay(50);//传感器信号延迟，由于传感器信号传输需要时间
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
                positionServo(-115, &hDJI[1]);
                if (throwhsm.wholestate == WHOLE_BOUNCE) HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_RESET); //伸缩气缸收回
                flag_countBounceCylinderContract = 0;
                externFlag_startSensor = 0;
            }
            else if (throwhsm.bouncestate == BOUNCE_WAITBALL)
            {
                positionServo(0, &hDJI[1]);
                hDJI[0].speedPID.output = 0;
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