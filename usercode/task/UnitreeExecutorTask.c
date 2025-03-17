/*
 * @Description: 宇树电机控制线程
 * @Author: Alex
 * @Date: 2025-03-04 22:53:47
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 17:25:30
 */
#include "UnitreeExecutorTask.h"

void UnitreeExecutorTask(void* argument)
{
    for(;;)
    {
        if (throwhsm.wholestate != WHOLE_INITING && throwhsm.wholestate != WHOLE_ERROR)
        {
            Unitree_UART_tranANDrev(&myMotor0,myMotor0.m_data.id,myMotor0.m_data.mode,myMotor0.m_data.T,myMotor0.m_data.W,myMotor0.m_data.Pos,myMotor0.m_data.K_P,myMotor0.m_data.K_W);
            osDelay(1);            
            Unitree_UART_tranANDrev(&myMotor1,myMotor1.m_data.id,myMotor1.m_data.mode,myMotor1.m_data.T,myMotor1.m_data.W,myMotor1.m_data.Pos,myMotor1.m_data.K_P,myMotor1.m_data.K_W);
            osDelay(1);
        }
        else osDelay(5);
    }
}