#ifndef OMNIWHEEL_CHASSIS_H
#define OMNIWHEEL_CHASSIS_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file omniwheel_chassis.h
 * @author thrzer
 * @brief 用于四轮全向轮底盘
 * @date 2024-10-31
 */

#include "DJI.h"
#include "wtr_can.h"
#include "Caculate.h"

#define WHEEL_RADIUS 0.078f //轮子半径
#define CENTRE2WHEEL_LENGTH 0.149f  //底盘中心到轮子距离
#define COS_ANGLE 0.707f    //angle = arctan(width/length) = arctan(351.94mm/351.94mm)
#define SIN_ANGLE 0.707f

typedef struct {
    float vx;
    float vy;
    float vw;
}owChassis_velocity_t;

typedef struct {
    DJI_t* motor;    //所用电机
    float targetspeed;  //目标角速度rpm
}owChassis_wheel_t;

typedef struct{
    CAN_HandleTypeDef* hcanx;   //CAN
    owChassis_velocity_t target_velocity;   //底盘速度
    owChassis_wheel_t wheel[4]; //左前1 右前2 右后3 左后4
}owChassis_t;

HAL_StatusTypeDef owChassisInit(owChassis_t* this);
void owChassis_set_targetVelocity(owChassis_t* this, float vx, float vy, float vw);
void owChassis_executor(owChassis_t* this);

extern owChassis_t chassis;

#ifdef __cplusplus
}
#endif

#endif