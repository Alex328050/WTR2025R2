// // /**
// //  * @file throwtask.c
// //  * @author 00Man00 (973085947@qq.com)
// //  * @brief 
// //  * @version 0.1
// //  * @date 2024-12-01
// //  * 
// //  * @copyright Copyright (c) 2024
// //  * 
// //  */

// #include "allusertask.h"
// #include "HSM.h"
// #include "rmctl.h"
// #include "encoder.h"
// #include "main.h"
// #include "DJI.h"
// #include "Caculate.h"
// #include "pawl.h"

// int bounceflag = 0;
// int overcnt = 0,breakflag = 1;
// int bouncemode=0;
// int catchflag = 0;
// int bouncedownflag = 0; 
// float reset_degree = 0;
// float reset_end_position[4];
// float close_reset_position = 0;
// float new_close_reset_position = 0;
// extern int carmode;
// extern int initflag_bounce;


// int electricflag = 0;
// int breakf_bounce = 1,over_bounce =0;
// int breakf_round = 1,over_round =0;
// // void BounceTask(void *argument)
// // {
// //   osDelay(1000);
// // }

// /**
//  * @description: 
//  * @param {void} *argument
//  * @return {*}
//  */
// void BounceTask(void *argument)
// {
//   for(;;)
//   {
//    if(carmode == 1)//拍球的完整过程
//    {
//     if(electricflag == 0) //上电之后就爪子夹紧球
//     {
//       reset_degree = hDJI[1].AxisData.AxisAngle_inDegree;
//       while(breakf_bounce)//检测电流
//       {
//         if(hDJI[1].FdbData.current < CLOSE_STALL_CURRENT)//避免摩擦毛刺  (需要测试改电流参数)
//         {
//           over_bounce++;
//           reset_end_position[over_bounce] = hDJI[1].AxisData.AxisAngle_inDegree;
//           if(over_bounce >= 4)
//           {
//             breakf_bounce= 0;
//           }
//         }
//         else
//         {
//           over_bounce = 0;
//         }
//         speedServo(CLOSE_SPEED,&hDJI[1]);
        
//         CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);//进行了个人的修改
//         osDelay(5);
        
//       }
//       close_reset_position = (reset_end_position[1] + reset_end_position[2] + reset_end_position[3])/3- reset_degree;
//       new_close_reset_position = close_reset_position + BUFFER_POSITION;   
//       positionServo(new_close_reset_position, &hDJI[1]); // 爪子维持
//       // speedServo(4000,&hDJI[0]);
//       // CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, 0, 0);
//       CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);
//       osDelay(5);
//     }

//     if(rmctl.rmctl_msg.btn_Btn2 == 1)//气缸推开
//     {
//       HAL_GPIO_WritePin(CYLIN_GPIO_Port,CYLIN_Pin,GPIO_PIN_SET);
//     }

//     if(rmctl.rmctl_msg.btn_Btn3 == 1)//开始拍球
//     {
//       electricflag = 1;
//       HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_SET);
//       CanTransmit_DJI_1234(&hcan1, 0, 7000, 0, 0);//爪子开启
//       HAL_GPIO_WritePin(BOUNCE_GPIO_Port,BOUNCE_Pin,GPIO_PIN_RESET);
//       osDelay(5);
//     }

//     if(HAL_GPIO_ReadPin(BOUNCE_GPIO_Port,BOUNCE_Pin) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(PNPSensor_GPIO_Port,PNPSensor_Pin) == GPIO_PIN_SET)//拍球气缸收回之后，接收到PNP信号，爪子抓球
//     {
//       osDelay(100);
//       CanTransmit_DJI_1234(&hcan1, 0, -7000, 0, 0);//爪子关闭
//       osDelay(5);
//       //bounceflag = 3;
//       // HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
//     }
//    }
   
//    else if(carmode == 0)//拍球结束调整姿态
//    {
//       reset_degree = hDJI[1].AxisData.AxisAngle_inDegree;
//       while(breakf_round)//检测电流
//       {
//         if(hDJI[1].FdbData.current < CLOSE_STALL_CURRENT)//避免摩擦毛刺  (需要测试改电流参数)
//         {
//           over_round++;
//           reset_end_position[over_round] = hDJI[1].AxisData.AxisAngle_inDegree;
//           if(over_round >= 4)
//           {
//             breakf_round= 0;
//           }
//         }
//         else
//         {
//           over_round = 0;
//         }
//         speedServo(CLOSE_SPEED,&hDJI[1]);
        
//         CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);//进行了个人的修改
//         osDelay(5);
//       }
//       close_reset_position = (reset_end_position[1] + reset_end_position[2] + reset_end_position[3])/3- reset_degree;
//       new_close_reset_position = close_reset_position + BUFFER_POSITION;   
//       positionServo(-90, &hDJI[1]); // 爪子维持
//       // speedServo(6000,&hDJI[0]);
//       speedServo(4000,&hDJI[0]);
//       CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, 0, 0);
//       osDelay(5);
//     }
//     osDelay(10);
//   }
// }