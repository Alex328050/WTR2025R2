/*
 * @Description: 
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-06 23:25:20
 */
// #include "encoder.h"
// #include "main.h"
// #include "Unitree_user.h"
// #include "DJI.h"
// #include "Caculate.h"
// #include "pawl.h"
// #include "allusertask.h"
// #include "HSM.h"
// #include "rmctl.h"

// extern float close_reset_position ;
// extern float new_close_reset_position ;
// extern int carmode ;
// extern float reset_degree ;
// extern float reset_end_position[4];
// int breakf = 1,over =0;

// /*初始抓球并抬升部分*/
// void Catchingtask(void *argument)
// {
//     for(;;)
//     {
//         if (carmode == 3)//初始夹爪抓住球
//         {

//         reset_degree = hDJI[1].AxisData.AxisAngle_inDegree;
//         while(breakf)//检测电流
//         {
//             if(hDJI[1].FdbData.current < CLOSE_STALL_CURRENT)//避免摩擦毛刺  (需要测试改电流参数)
//             {
//             over++;
//             reset_end_position[over] = hDJI[1].AxisData.AxisAngle_inDegree;
//             if(over >= 4)
//             {
//                 breakf= 0;
//             }
//             }
//             else
//             {
//             over = 0;
//             }
//             speedServo(CLOSE_SPEED,&hDJI[1]);
            
//             CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);//进行了个人的修改
//             osDelay(5);
//         }
//         close_reset_position = (reset_end_position[1] + reset_end_position[2] + reset_end_position[3])/3- reset_degree;
//         new_close_reset_position = close_reset_position + BUFFER_POSITION;   
//         positionServo(new_close_reset_position, &hDJI[1]); // 爪子维持
//         CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, -4000,4000);
//         osDelay(5);
        
//         }
//         if(rmctl.rmctl_msg.btn_Btn0 == 1)//宇树电机向后转达到拍球位置
//         {
//             // Unitree_UART_tranANDrev(&myMotor1,0,1,-3,0,unitree_offest_bounce-7,0.02,0.05);
//             // Unitree_UART_tranANDrev(&myMotor1,0,1,-3.3,0,0,0,0);
//             Unitree_UART_tranANDrev(&myMotor1,1,1,3.3,0,0,0,0);
//         }
        
//         else if(rmctl.rmctl_msg.btn_Btn1 == 1)//支撑关闭，宇树电机卸力
//         {
//             for(int i=0;i<40;i++)
//             {
//                 CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 6000, -6000);
//                 osDelay(5);
//             }
//             // Unitree_UART_tranANDrev(&myMotor1,0,0,0,0,0,0,0);
//             Unitree_UART_tranANDrev(&myMotor1,0,0,0,0,0,0,0);
//             // Unitree_UART_tranANDrev(&myMotor1,0,0,0,0,unitree_offest_bounce-6,0.05,0.05);
        
//         }
//         osDelay(10);
//     }
// }