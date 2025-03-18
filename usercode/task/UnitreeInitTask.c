/*
 * @Description: 宇树初始化线程
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-18 22:17:40
 */

#include "UnitreeInitTask.h"

UnitreeMotor myMotor0;                  //宇树电机0号结构体
UnitreeMotor myMotor1;                  //宇树电机1号结构体
uint8_t flag_unitreeInitComplete = 0;   //信号 指示宇树电机初始化情况 1为完成
float unitreeStartPos0 = 0.0;           //宇树电机0号初始位置
float unitreeStartPos1 = 0.0;           //宇树电机1号初始位置

/**
 * @brief 宇树电机初始化线程
 * 
 * @param argument 
 */
void UnitreeInitTask(void *argument)
{
  uint8_t flag_unitreeInitOutOfTime = 0;
  /*检测宇树电机初始化过没过*/
  
  while(Unitree_init(&myMotor0, &huart6, 0) == HAL_ERROR)
  {
    ++flag_unitreeInitOutOfTime;
    if (flag_unitreeInitOutOfTime >= 10)
    {
        throwhsm.wholestate = WHOLE_ERROR;
        break;
    }
    osDelay(1000);
  }
  
 
  flag_unitreeInitOutOfTime = 0;
  while(Unitree_init(&myMotor1, &huart6, 1) == HAL_ERROR)
  {
    ++flag_unitreeInitOutOfTime;
    if (flag_unitreeInitOutOfTime >= 10)  throwhsm.wholestate = WHOLE_ERROR;
    osDelay(1000);
  }
  osDelay(100);
    
   
  /*测量宇树初始位置*/
  
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
  
  flag_unitreeInitComplete = 1;
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
}
