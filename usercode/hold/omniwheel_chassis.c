#include "omniwheel_chassis.h"

owChassis_t chassis;

void owChassis_calculateVelocity(owChassis_t* this);

/**
 * @brief 全向轮底盘初始化
 * @param this
 */
HAL_StatusTypeDef owChassisInit(owChassis_t* this)
{
    this->hcanx = &hcan1;
    CANFilterInit(&hcan1);
    for (int i = 0; i < 4; i++)
    {
        this->wheel[i].motor->motorType = M3508;
        this->wheel[i].targetspeed = 0;
        this->wheel[i].motor = &hDJI[i];
    }
    for (int i = 0; i < 4; i++)
    {
		// 速度环PID
		this->wheel[i].motor->speedPID.KP = 0.8;
		this->wheel[i].motor->speedPID.KI = 0.02;
		this->wheel[i].motor->speedPID.KD = 0.1;
		this->wheel[i].motor->speedPID.outputMax = 8000;
		// 位置环PID
		this->wheel[i].motor->posPID.KP = 80.0f;
        this->wheel[i].motor->posPID.KI=1.5f;
        this->wheel[i].motor->posPID.KD=0.0f;
		this->wheel[i].motor->posPID.outputMax = 5000;
		// this->wheel[i].motor->posPID.outputMin = 1500;
		this->wheel[i].motor->f_current = 0;
        this->wheel[i].motor->reductionRate = 3591.0f / 187.0f; // 2006减速比为36 3508减速比约为19
    }
    return HAL_OK;
}

/**
 * @brief 全向轮底盘设置目标速度
 * @param this
 * @param vx 左右速度m/s
 * @param vy 前后速度m/s
 * @param vw 角速度rad/s
 */
void owChassis_set_targetVelocity(owChassis_t* this, float vx, float vy, float vw)
{
    this->target_velocity.vx = vx;
    this->target_velocity.vy = vy;
    this->target_velocity.vw = vw;
    owChassis_calculateVelocity(this);  //速度解算
}

/**
 * @brief (内部函数)四轮全向轮底盘速度解算
 * @param this
 */
void owChassis_calculateVelocity(owChassis_t* this)
{
    this->wheel[0].targetspeed = (this->target_velocity.vy / COS_ANGLE
                                 + this->target_velocity.vx / SIN_ANGLE
                                 - this->target_velocity.vw * CENTRE2WHEEL_LENGTH)/WHEEL_RADIUS/6;
    this->wheel[1].targetspeed = (this->target_velocity.vy / COS_ANGLE
                                 - this->target_velocity.vx / SIN_ANGLE
                                 + this->target_velocity.vw * CENTRE2WHEEL_LENGTH)/WHEEL_RADIUS/6;
    this->wheel[2].targetspeed = (this->target_velocity.vy / COS_ANGLE
                                 + this->target_velocity.vx / SIN_ANGLE
                                 + this->target_velocity.vw * CENTRE2WHEEL_LENGTH)/WHEEL_RADIUS/6;
    this->wheel[3].targetspeed = (this->target_velocity.vy / COS_ANGLE
                                 - this->target_velocity.vx / SIN_ANGLE
                                 - this->target_velocity.vw * CENTRE2WHEEL_LENGTH)/WHEEL_RADIUS/6;
}

/**
 * @brief 全向轮底盘执行器函数，调用PID并发送，建议周期为5ms
 * @param this
 */
void owChassis_executor(owChassis_t* this)
{
    //PID
    for (int i = 0; i < 4; i++)
    {
        speedServo(this->wheel[i].targetspeed,this->wheel[i].motor);
    }
    //CAN发送
    CanTransmit_DJI_1234(this->hcanx, this->wheel[0].motor->speedPID.output,
                                      this->wheel[1].motor->speedPID.output,
                                      this->wheel[2].motor->speedPID.output,
                                      this->wheel[3].motor->speedPID.output);
}

