/*
 * @Description: 抛射全车状态机更改线程
 * @Author: Alex
 * @Date: 2025-03-02 19:43:40
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 23:32:02
 */

#include "ThrowHSMTask.h"

/**
 * @brief 抛射全车状态机修改线程
 * 
 * @param argument 
 */
void ThrowHSMTask(void* argument)
{
    mavlink_joystick_air_dashboard_set_title_t  mavlink_wholestate_title;
    mavlink_joystick_air_dashboard_set_msg_t    mavlink_wholestate_msg;
    mavlink_joystick_air_dashboard_set_title_t  mavlink_throwstate_title;
    mavlink_joystick_air_dashboard_set_msg_t    mavlink_throwstate_msg;
    mavlink_joystick_air_dashboard_set_title_t  mavlink_bouncestate_title;
    mavlink_joystick_air_dashboard_set_msg_t    mavlink_bouncestate_msg;
    mavlink_joystick_air_dashboard_set_title_t  mavlink_errorstate_title;
    mavlink_joystick_air_dashboard_set_msg_t    mavlink_errorstate_msg;

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
                else if (throwhsm.throwstate == THROW_GATHERSTRENGTH && rmctl.rmctl_msg.btn_Btn1 == 1)  throwhsm.throwstate = THROW_CLEARBRACE;
                else if (throwhsm.throwstate == THROW_CLEARBRACE && rmctl.rmctl_msg.btn_Btn2 == 1)  throwhsm.throwstate = THROW_ACCELERATE;
                else if (throwhsm.throwstate == THROW_ACCELERATE && (caldata.angle>=20500.0 && caldata.angle<27500.0))  throwhsm.throwstate = THROW_THROWOUT;
                else if (throwhsm.throwstate == THROW_THROWOUT && hDJI[1].Calculate.RotorRound > 2)  throwhsm.throwstate = THROW_BACK;
                
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
                else if (throwhsm.throwstate == THROW_CATCHING && rmctl.rmctl_msg.btn_Btn1 == 1)  throwhsm.throwstate = THROW_GATHERSTRENGTH;
                else if (throwhsm.throwstate == THROW_CLEARBRACE && rmctl.rmctl_msg.btn_Btn2 == 1)  throwhsm.throwstate = THROW_ACCELERATE;
                else if (throwhsm.throwstate == THROW_ACCELERATE && (caldata.angle>=20500.0 && caldata.angle<27500.0))  throwhsm.throwstate = THROW_THROWOUT;
                else if (throwhsm.throwstate == THROW_THROWOUT && hDJI[1].Calculate.RotorRound > 2)  throwhsm.throwstate = THROW_BACK;
            }
            //拍球状态修改
            else if (throwhsm.wholestate == WHOLE_BOUNCE)
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
        //修改遥控器信息
        JoystickSwitchTitle(2, "WholeState", &mavlink_wholestate_title);
        JoystickSwitchTitle(3, "ThrowState", &mavlink_throwstate_title);
        JoystickSwitchTitle(4, "BounceState", &mavlink_bouncestate_title);
        JoystickSwitchTitle(5, "ErrorState", &mavlink_errorstate_title);

        if      (throwhsm.wholestate == WHOLE_INITING)                  JoystickSwitchMsg(2, "Initing", &mavlink_wholestate_msg);
        else if (throwhsm.wholestate == WHOLE_READY)                    JoystickSwitchMsg(2, "Ready", &mavlink_wholestate_msg);
        else if (throwhsm.wholestate == WHOLE_BOUNCE)                   JoystickSwitchMsg(2, "Bounce", &mavlink_wholestate_msg);
        else if (throwhsm.wholestate == WHOLE_CONBOUNCE)                JoystickSwitchMsg(2, "ConBounce", &mavlink_wholestate_msg);
        else if (throwhsm.wholestate == WHOLE_THROW)                    JoystickSwitchMsg(2, "Throw", &mavlink_wholestate_msg);
        else if (throwhsm.wholestate == WHOLE_CONTHROW)                 JoystickSwitchMsg(2, "ConThrow", &mavlink_wholestate_msg);
        else if (throwhsm.wholestate == WHOLE_ERROR)                    JoystickSwitchMsg(2, "Error", &mavlink_wholestate_msg);

        if      (throwhsm.bouncestate == BOUNCE_IDLE)                   JoystickSwitchMsg(4, "Idle", &mavlink_bouncestate_msg);
        else if (throwhsm.bouncestate == BOUNCE_WAITBALL)               JoystickSwitchMsg(4, "WaitBall", &mavlink_bouncestate_msg);
        else if (throwhsm.bouncestate == BOUNCE_CATCHING)               JoystickSwitchMsg(4, "Catching", &mavlink_bouncestate_msg);
        else if (throwhsm.bouncestate == BOUNCE_GETTOPOSITION)          JoystickSwitchMsg(4, "GetToPositon", &mavlink_bouncestate_msg);
        else if (throwhsm.bouncestate == BOUNCE_READY)                  JoystickSwitchMsg(4, "Ready", &mavlink_bouncestate_msg);
        else if (throwhsm.bouncestate == BOUNCE_BOUNCE)                 JoystickSwitchMsg(4, "Bounce", &mavlink_bouncestate_msg);
        else if (throwhsm.bouncestate == BOUNCE_CATCHANDADJUSTPOSTURE)  JoystickSwitchMsg(4, "CatchAndAdjustPosture", &mavlink_bouncestate_msg);

        if      (throwhsm.throwstate == THROW_IDLE)                     JoystickSwitchMsg(3, "Idle", &mavlink_throwstate_msg);
        else if (throwhsm.throwstate == THROW_GATHERSTRENGTH)           JoystickSwitchMsg(3, "GatherStrength", &mavlink_throwstate_msg);
        else if (throwhsm.throwstate == THROW_CLEARBRACE)               JoystickSwitchMsg(3, "ClearBrace", &mavlink_throwstate_msg);
        else if (throwhsm.throwstate == THROW_ACCELERATE)               JoystickSwitchMsg(3, "Acclerate", &mavlink_throwstate_msg);
        else if (throwhsm.throwstate == THROW_THROWOUT)                 JoystickSwitchMsg(3, "ThrowOut", &mavlink_throwstate_msg);
        else if (throwhsm.throwstate == THROW_BACK)                     JoystickSwitchMsg(3, "Back", &mavlink_throwstate_msg);
        else if (throwhsm.throwstate == THROW_CATCHING)                 JoystickSwitchMsg(3, "Catching", &mavlink_throwstate_msg);
        
        if      (throwhsm.errorstate == ERROR_CANINITFAIL1)             JoystickSwitchMsg(5, "Can1Fail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_CANINITFAIL2)             JoystickSwitchMsg(5, "Can2Fail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_UNITREEINITFAIL0)         JoystickSwitchMsg(5, "Unitree0Fail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_UNITREEINITFAIL1)         JoystickSwitchMsg(5, "Unitree1Fail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_ECODERINITFAIL)           JoystickSwitchMsg(5, "EncoderFail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_SENSORINITFAIL)           JoystickSwitchMsg(5, "SensorFail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_DJIINITFAIL)              JoystickSwitchMsg(5, "DJIFail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_DJITRANSMITFAIL)          JoystickSwitchMsg(5, "DJIMegFail", &mavlink_errorstate_msg);
        else if (throwhsm.errorstate == ERROR_NONE)                     JoystickSwitchMsg(5, "None", &mavlink_errorstate_msg);
        osDelay(2);
    }
}