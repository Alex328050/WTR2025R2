#include "AllUserTask.h"
#include "HSM.h"
#include "pop.h"
#include "rmctl.h"

// /**
//  * @brief 弹射机构线程
//  * @author thrzer
//  * @date 2024-11-23
//  */
// void PopTask(void *argument)
// {
//   wtrV1.pop_mechanism = HSM_pSTATE_ON;
//   wtrV1.pop_mechanism = HSM_pSTATE_INIT;
//   if (wtrV1.state == HSM_STATE_RUNNING)
//   {
//     PopInit(&pop);
//     PopCorrect(&pop);
//     wtrV1.pop_mechanism = HSM_pSTATE_SET;
//   }
//   float inputposition = 0.0f;
//   while (wtrV1.state == HSM_STATE_RUNNING)
//   {//一代车为遥控器控制蓄力，后续会改为由上位机数据控制

//     //复位完成状态、蓄力状态、蓄力完成状态变为蓄力状态
//     if (wtrV1.pop_mechanism == HSM_pSTATE_SET
//         || wtrV1.pop_mechanism == HSM_pSTATE_CHARGE
//         || wtrV1.pop_mechanism == HSM_pSTATE_READY)
//     {
//       if (rmctl.rmctl_msg.btn_Btn0 == 1)//蓄力
//       {
//         inputposition += 4.0f;
//         if (inputposition >= 5000.0f)
//         {
//           inputposition = 5000.0f;
//         }
//         wtrV1.pop_mechanism = HSM_pSTATE_CHARGE;
//       }
//       else if (rmctl.rmctl_msg.btn_Btn1 == 1)//反蓄力
//       {
//         inputposition -= 4.0f;
//         if (inputposition <= 0.0f)
//         {
//           inputposition = 0.0f;
//         }
//         wtrV1.pop_mechanism = HSM_pSTATE_CHARGE;
//       }
//     }

//     //蓄力状态变为蓄力完成状态
//     if (wtrV1.pop_mechanism == HSM_pSTATE_CHARGE)
//     {
//       if (inputposition - pop.nowposition <= 30.0f && inputposition - pop.nowposition >= -30.0f)
//       {
//         wtrV1.pop_mechanism = HSM_pSTATE_READY;
//       }
//     }

//     //蓄力完成状态变为发射状态
//     if (wtrV1.pop_mechanism == HSM_pSTATE_READY)
//     {
//       if (rmctl.rmctl_msg.btn_Btn2 == 1)
//       {
//         wtrV1.pop_mechanism = HSM_pSTATE_RESET;
//         PopRelease(&pop);
//       }
//     }

//     //发射状态变为复位完成状态
//     if (wtrV1.pop_mechanism == HSM_pSTATE_RESET)
//     {
//       if (inputposition - pop.nowposition <= 30.0f && inputposition - pop.nowposition >= -30.0f)
//       {
//         wtrV1.pop_mechanism = HSM_pSTATE_SET;
//       }
//     }

//     PopCharge(&pop,inputposition);
//     PopExecutor(&pop);
//     osDelay(5);
//   }
// }

void PopTask(void *argument)
{
  while(1)
  {
    if (rmctl.rmctl_msg.btn_Btn0 == 1)
    {
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      osDelay(100);
    }
    osDelay(5);
  }
}