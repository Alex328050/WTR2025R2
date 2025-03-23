/*
 * @Description: 各部件初始化线程
 * @Author: Alex
 * @Date: 2025-03-23 21:15:25
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 22:00:33
 */
#include "InitTask.h"

uint8_t flag_initComplete = 0;          //信号 指示初始化情况 1为完成

UnitreeMotor myMotor0;                  //宇树电机0号结构体
UnitreeMotor myMotor1;                  //宇树电机1号结构体
float unitreeStartPos0 = 0.0;           //宇树电机0号初始位置
float unitreeStartPos1 = 0.0;           //宇树电机1号初始位置

void InitTask(void* argument)
{
    //角编码器初始化检测
    if (Encoder_Init() == HAL_ERROR)
    {
        throwhsm.wholestate = WHOLE_ERROR;
        throwhsm.errorstate = ERROR_ECODERINITFAIL;
    }

    //拍球传感器初始化检测
    uint8_t i = 0;
    for (uint8_t i = 0; i < 10; ++i)
    {
        if (HAL_GPIO_ReadPin(PNPSensor1_GPIO_Port, PNPSensor1_Pin) != GPIO_PIN_SET ||
            HAL_GPIO_ReadPin(PNPSensor2_GPIO_Port, PNPSensor2_Pin) != GPIO_PIN_SET)    break;
    }
    if (i < 10)
    {
        throwhsm.wholestate = WHOLE_ERROR;
        throwhsm.errorstate = ERROR_SENSORINITFAIL;
    }

    //大疆电机初始化检测
    hDJI[0].motorType = M2006;//自旋电机
    hDJI[1].motorType = M3508;
    hDJI[2].motorType = M2006;//支撑右电机
    hDJI[3].motorType = M2006;
    if (DJI_Init() == HAL_ERROR)
    {
        throwhsm.wholestate = WHOLE_ERROR;
        throwhsm.errorstate = ERROR_DJIINITFAIL;
    }
    
    //宇树电机初始化检测
    uint8_t j = 0;
    while(Unitree_init(&myMotor0, &huart6, 0) == HAL_ERROR)
    {
        ++j;
        if (j >= 10)
        {
            throwhsm.wholestate = WHOLE_ERROR;
            throwhsm.errorstate = ERROR_UNITREEINITFAIL0;
            break;
        }
        osDelay(500);
    }
    j = 0;
    while(Unitree_init(&myMotor1, &huart6, 1) == HAL_ERROR)
    {
        ++j;
        if (j >= 10)
        {
            throwhsm.wholestate = WHOLE_ERROR;
            throwhsm.errorstate = ERROR_UNITREEINITFAIL1;
        }
        osDelay(500);
    }
    osDelay(100);

    //测量宇树初始位置
    for(int i = 0; i < 5; i++)
    {
        Unitree_UART_tranANDrev(&myMotor0,0,1,0,0,0,0,0 );
        unitreeStartPos0 += myMotor0.data.Pos/UNITREE_REDUCTION_RATE;
        osDelay(5);
    }
    for(int i = 0; i < 5; i++)
    {
        Unitree_UART_tranANDrev(&myMotor1,1,1,0,0,0,0,0 );
        unitreeStartPos1 += myMotor1.data.Pos/UNITREE_REDUCTION_RATE;
        osDelay(5);
    }
    unitreeStartPos0 /= 5;
    unitreeStartPos1 /= 5;

    for (;;)
    {
        osDelay(10);
    }
}