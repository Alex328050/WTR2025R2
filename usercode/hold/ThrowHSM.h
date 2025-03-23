/*
 * @Description: 抛射机构状态机
 * @Author: Alex
 * @Date: 2025-03-06 22:15:48
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-23 23:24:27
 */

#ifndef THROWHSM_H
#define THROWHSM_H

#include "rmctl.h"
#include "wtr_can.h"
#include "DJI.h"
#include "encoder.h"

/**
 * @brief 整车状态机
 * 
 */
typedef enum
{
    WHOLE_INITING,      //整车初始化状态
    WHOLE_READY,        //整车就绪状态
    WHOLE_BOUNCE,       //整车拍球状态
    WHOLE_CONBOUNCE,    //整车连续拍球状态
    WHOLE_THROW,        //整车抛球状态
    WHOLE_CONTHROW,     //整车连续抛球状态
    WHOLE_ERROR,        //整车错误状态
}WHOLESTATE;

/**
 * @brief 抛球子状态机
 * 
 */
typedef enum
{
    THROW_IDLE,                     //抛球子状态 抛球机构未使用
    THROW_GATHERSTRENGTH,           //抛球子状态 夹爪收回 宇树电机向后发力紧靠
    THROW_CLEARBRACE,               //抛球子状态 去除支撑结构
    THROW_ACCELERATE,               //抛球子状态 宇树电机发力加速 夹爪未打开 球未抛出
    THROW_THROWOUT,                 //抛球子状态 夹爪打开 球抛出
    THROW_BACK,                     //抛球子状态 夹爪收回 机构回到悬垂状态

    THROW_CATCHING,                 //连续抛球特有状态 夹球
}THROWSTATE;

/**
 * @brief 拍球子状态机
 * 
 */
typedef enum
{
    BOUNCE_IDLE,                    //拍球子状态 拍球机构未使用
    BOUNCE_CATCHING,                //拍球子状态 夹球
    BOUNCE_GETTOPOSITION,           //拍球子状态 宇树电机向后发力紧靠 机构到达拍球位置
    BOUNCE_READY,                   //拍球子状态 支撑打开 宇树卸力 拍球气缸推出 准备拍球
    BOUNCE_BOUNCE,                  //拍球子状态 拍球
    BOUNCE_CATCHANDADJUSTPOSTURE,   //拍球子状态 抓球 自旋调整篮球姿态 拍球气缸收回

    BOUNCE_WAITBALL,                //连续拍球特有状态 夹爪打开等待放球
}BOUNCESTATE;

/**
 * @brief 错误态子状态机
 * 
 */
typedef enum
{
    ERROR_DJIINITFAIL,              //错误子状态 大疆电机初始化失败
    ERROR_UNITREEINITFAIL0,         //错误子状态 0号宇树电机初始化失败
    ERROR_UNITREEINITFAIL1,         //错误子状态 1号宇树电机初始化失败
    ERROR_ECODERINITFAIL,           //错误子状态 角编码器初始化失败
    ERROR_CANINITFAIL1,             //错误子状态 can1初始化失败
    ERROR_CANINITFAIL2,             //错误子状态 can2初始化失败
    ERROR_SENSORINITFAIL,           //错误子状态 拍球传感器初始化失败

    ERROR_DJITRANSMITFAIL,          //错误子状态 大疆电机信息传输失败
}ERRORSTATE;

/**
 * @brief 整车全状态结构体
 * 
 */
typedef struct 
{
    WHOLESTATE wholestate;
    THROWSTATE throwstate;
    BOUNCESTATE bouncestate;
    ERRORSTATE errorstate;
}THROWHSM;

extern THROWHSM throwhsm;

#endif