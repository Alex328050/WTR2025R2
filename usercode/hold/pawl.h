#ifndef PAWL_H
#define PAWL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file pawl.h
 * @author Man
 * @brief wtr一代车爪子机构
 * @date 2025-1-6
 */

#include "DJI.h"
#include "Caculate.h"
#include "cmsis_os.h"  //为了不报warning而加

#define CLOSE_STALL_CURRENT -4000.0f    //闭合堵转电流标志//需要修改
#define CLOSE_SPEED -7200.0f //关爪子速度rpm
#define CATCH_SPEED 30000.0f //夹球速度rpm
#define BUFFER_POSITION -75.0f    //缓冲距离

typedef struct
{
    DJI_t *motor;   //蓄力电机
    float nowposition;      //当前位置(电机角度)
    float position; //蓄力位置(电机角度)
    float reset_position;   //复位点位置
    float close_reset_position;    //夹爪闭合复位点位置
    float open_reset_position;     //夹爪张开复位点位置
} pawl_t;            //夹爪机构

void girp_pawl_open_init();
void girp_pawl_close_init();
void OpenPawlExecutor(float reset_speed);
void ClosePawlExecutor(float reset_speed);
#ifdef __cplusplus
}
#endif
#endif //PAWL_H
