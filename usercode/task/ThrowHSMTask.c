/*
 * @Description: 抛射全车状态机更改线程
 * @Author: Alex
 * @Date: 2025-03-02 19:43:40
 * @LastEditors: Alex
 * @LastEditTime: 2025-04-17 00:53:39
 */

#include "ThrowHSMTask.h"

/**
 * @brief 抛射全车状态机修改线程
 * 
 * @param argument 
 */
void ThrowHSMTask(void* argument)
{
    for(;;)
    {
        if (flag_initComplete == 1)
        {
            //整车状态修改
            //当所有电机初始化工作完成后，整车就绪态
            if (flag_initComplete == 1 && throwhsm.wholestate != WHOLE_ERROR)  throwhsm.wholestate = WHOLE_READY;  
            if (throwhsm.wholestate != WHOLE_INITING && throwhsm.wholestate != WHOLE_ERROR)
            {
                //左开关打开上，准备态
                if      (rmctl.rmctl_msg.left_switch == 1)
                {
                    throwhsm.wholestate = WHOLE_READY;
                    throwhsm.throwstate = THROW_IDLE;
                    throwhsm.bouncestate = BOUNCE_IDLE;
                }
                //左开关闭合下，右开关打开上，拍球模式
                else if (rmctl.rmctl_msg.left_switch == 0 && rmctl.rmctl_msg.right_switch == 1)
                {
                    if (rmctl.rmctl_msg.usr_left_knob >= 8) throwhsm.wholestate = WHOLE_CONBOUNCE; //连续拍球模式
                    else throwhsm.wholestate = WHOLE_BOUNCE;
                    throwhsm.throwstate = THROW_IDLE;
                }
                //左右开关都向下，抛球模式
                else if (rmctl.rmctl_msg.left_switch == 0 && rmctl.rmctl_msg.right_switch == 0)
                {
                    if (rmctl.rmctl_msg.usr_left_knob <= -8) throwhsm.wholestate = WHOLE_CONTHROW; //连续抛球模式
                    else throwhsm.wholestate = WHOLE_THROW;
                    throwhsm.bouncestate = BOUNCE_IDLE;
                }
            }
            //抛球状态修改
            if (throwhsm.wholestate == WHOLE_THROW)
            {
                if      (throwhsm.throwstate == THROW_IDLE && rmctl.rmctl_msg.btn_Btn0 == 1)  throwhsm.throwstate = THROW_GATHERSTRENGTH;
                if (throwhsm.throwstate == THROW_GATHERSTRENGTH && rmctl.rmctl_msg.btn_Btn1 == 1)  throwhsm.throwstate = THROW_CLEARBRACE;
                if (throwhsm.throwstate == THROW_CLEARBRACE && rmctl.rmctl_msg.btn_Btn2 == 1)  throwhsm.throwstate = THROW_ACCELERATE;
                if (throwhsm.throwstate == THROW_ACCELERATE && caldata.angle>=23000.0)  throwhsm.throwstate = THROW_THROWOUT;
                if (throwhsm.throwstate == THROW_THROWOUT && (hDJI[1].Calculate.RotorRound > -1 || caldata.angle >= 32000.0))  throwhsm.throwstate = THROW_BACK;
                
            }
            //连续抛球状态修改
            else if (throwhsm.wholestate == WHOLE_CONTHROW)
            {
                if      ((throwhsm.throwstate == THROW_IDLE || throwhsm.throwstate == THROW_BACK) &&
                        rmctl.rmctl_msg.btn_Btn0 == 1
                        ) 
                {
                    throwhsm.throwstate = THROW_CATCHING;
                }
                if (throwhsm.throwstate == THROW_CATCHING && rmctl.rmctl_msg.btn_Btn1 == 1)  throwhsm.throwstate = THROW_GATHERSTRENGTH;
                if (throwhsm.throwstate == THROW_GATHERSTRENGTH && rmctl.rmctl_msg.btn_Btn2 == 1)  throwhsm.throwstate = THROW_ACCELERATE;
                if (throwhsm.throwstate == THROW_ACCELERATE && caldata.angle>=23000.0)  throwhsm.throwstate = THROW_THROWOUT;
                if (throwhsm.throwstate == THROW_THROWOUT && (hDJI[1].Calculate.RotorRound > -1 || caldata.angle >= 32000.0))  throwhsm.throwstate = THROW_BACK;
            }
            //拍球状态修改
            else if (throwhsm.wholestate == WHOLE_BOUNCE)
            {
                if      (throwhsm.bouncestate == BOUNCE_IDLE && rmctl.rmctl_msg.btn_Btn0 == 1)  throwhsm.bouncestate = BOUNCE_CATCHING;
                else if (throwhsm.bouncestate == BOUNCE_CATCHING && rmctl.rmctl_msg.btn_Btn1 == 1)  throwhsm.bouncestate = BOUNCE_GETTOPOSITION;
                else if (throwhsm.bouncestate == BOUNCE_GETTOPOSITION && rmctl.rmctl_msg.btn_Btn2 == 1)  throwhsm.bouncestate = BOUNCE_READY;
                else if (throwhsm.bouncestate == BOUNCE_READY && rmctl.rmctl_msg.btn_Btn3 == 1)  throwhsm.bouncestate = BOUNCE_BOUNCE;
                else if (throwhsm.bouncestate == BOUNCE_BOUNCE && //externFlag_startSensor == 1 &&
                        //(HAL_GPIO_ReadPin(PNPSensor1_GPIO_Port, PNPSensor1_Pin) == GPIO_PIN_SET ||
                        //HAL_GPIO_ReadPin(PNPSensor2_GPIO_Port, PNPSensor2_Pin) == GPIO_PIN_SET)
                        rmctl.rmctl_msg.btn_LeftCrossDown
                        )
                {
                    throwhsm.bouncestate = BOUNCE_CATCHANDADJUSTPOSTURE;
                }
            }
            //连续拍球状态修改
            else if (throwhsm.wholestate == WHOLE_CONBOUNCE)
            {
                if      (throwhsm.bouncestate == BOUNCE_IDLE && rmctl.rmctl_msg.btn_Btn0 == 1)  throwhsm.bouncestate = BOUNCE_CATCHING;
                else if (throwhsm.bouncestate == BOUNCE_CATCHING && rmctl.rmctl_msg.btn_Btn1 == 1)  throwhsm.bouncestate = BOUNCE_GETTOPOSITION;
                else if (throwhsm.bouncestate == BOUNCE_GETTOPOSITION && rmctl.rmctl_msg.btn_Btn2 == 1)  throwhsm.bouncestate = BOUNCE_READY;
                else if (throwhsm.bouncestate == BOUNCE_READY && rmctl.rmctl_msg.btn_Btn3 == 1)  throwhsm.bouncestate = BOUNCE_BOUNCE;
                else if (throwhsm.bouncestate == BOUNCE_BOUNCE && externFlag_startSensor == 1 &&
                        (HAL_GPIO_ReadPin(PNPSensor1_GPIO_Port, PNPSensor1_Pin) == GPIO_PIN_SET ||
                        HAL_GPIO_ReadPin(PNPSensor2_GPIO_Port, PNPSensor2_Pin) == GPIO_PIN_SET)
                        )
                {
                    throwhsm.bouncestate = BOUNCE_CATCHANDADJUSTPOSTURE;
                }
                else if (throwhsm.bouncestate == BOUNCE_CATCHANDADJUSTPOSTURE && rmctl.rmctl_msg.btn_Btn3 == 1)  throwhsm.bouncestate = BOUNCE_BOUNCE;
                else if (throwhsm.bouncestate == BOUNCE_CATCHANDADJUSTPOSTURE && rmctl.rmctl_msg.btn_Btn4 == 1)  throwhsm.bouncestate = BOUNCE_WAITBALL;
                else if (throwhsm.bouncestate == BOUNCE_WAITBALL && rmctl.rmctl_msg.btn_Btn5 == 1)  throwhsm.bouncestate = BOUNCE_CATCHANDADJUSTPOSTURE;
            }
        }
        osDelay(2);
    }
}