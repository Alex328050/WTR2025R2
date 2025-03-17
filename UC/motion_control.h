#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include "main.h"         // 你的主配置文件
#include "stm32f4xx_hal.h" // HAL库
#include "FreeRTOS.h"
#include "task.h"
#include "can.h"
#include "usart.h"
#include "encoder.h"
#include "Unitree_user.h"
#include "stdio.h"
#include "cmsis_os.h"


// 运动控制模块相关函数声明
float InitUnitreeMotor(UnitreeMotor myMotor1, UART_HandleTypeDef* huart);
void ControlClaw(uint8_t key, int* state);
//void ReceiveAndPrintAngleData(CAN_HandleTypeDef* hcan, EncoderData* encoderData);
void ControlUnitreeMotion(UnitreeMotor myMotor1, float unitree_offest, int* flag, int* state);

extern EncoderData encoderData;
extern UnitreeMotor  myMotor1;
extern osSemaphoreId_t State1SemHandle;



#endif // MOTION_CONTROL_H
