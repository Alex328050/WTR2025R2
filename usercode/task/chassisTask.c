/*
 * @Description: 
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 16:18:18
 */
#include "AllUserTask.h"
#include "HSM.h"
#include "omniwheel_chassis.h"
#include "rmctl.h"

/**
 * @brief 全向轮底盘线程
 * @author thrzer
 * @date 2024-11-23
 */
void ChassisTask(void *argument)
{
  wtrV1.chassis_mechanism = HSM_cSTATE_ON;
  if (wtrV1.state == HSM_STATE_RUNNING)
    wtrV1.chassis_mechanism = HSM_cSTATE_INIT;
  if (owChassisInit(&chassis) == HAL_OK)
  {
    owChassis_set_targetVelocity(&chassis,0,0,0);
    wtrV1.chassis_mechanism = HSM_cSTATE_RUNNING;
  }
  while (wtrV1.state == HSM_STATE_RUNNING && wtrV1.chassis_mechanism == HSM_cSTATE_RUNNING)
  {
    owChassis_set_targetVelocity(&chassis,1,1,1);
    owChassis_executor(&chassis);
    osDelay(5);
  }
}