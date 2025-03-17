#include "pawl.h"
#include "pop.h"
#include "main.h"
// pawl_t pawl;


/**
 * @brief 夹爪张开PID初始化
 * @param 
 */
void girp_pawl_open_init()
{
  hDJI[1].posPID.outputMax=4000;
  hDJI[1].posPID.KP=30;
  hDJI[1].posPID.KI=3;
  hDJI[1].posPID.KD=0.0;
  hDJI[1].speedPID.outputMax=4000;
  hDJI[1].speedPID.KI=0.02;
  hDJI[1].speedPID.KD=0.1;
  hDJI[1].speedPID.KP=0.8;  
}

/**
 * @brief 夹爪闭合PID初始化
 * @param 
 */
void girp_pawl_close_init()
{
  hDJI[1].posPID.outputMax=4000;
  hDJI[1].posPID.KP=30;
  hDJI[1].posPID.KI=6;
  hDJI[1].posPID.KD=0.0;
  hDJI[1].speedPID.outputMax=4000;
  hDJI[1].speedPID.KI=0.02;
  hDJI[1].speedPID.KD=0.1;
  hDJI[1].speedPID.KP=0.8;   
}

/**
 * @brief 夹爪机构电机张开执行器
 * @param reset_speed 复位速度
 */
// void OpenPawlExecutor(float reset_speed)
// {
//   girp_pawl_open_init();
//   int overcnt = 0,breakflag = 1;
//   while(breakflag)//检测电流
//   {
//     if(hDJI[1].FdbData.current < OPEN_STALL_CURRENT)//避免摩擦毛刺  (需要测试改电流参数)
//     {
//       overcnt++;
//       if(overcnt >= 3)
//       {
//         breakflag = 0;
//       }
//     }
//     else
//     {
//       overcnt = 0;
//     }
//     speedServo(reset_speed,&hDJI[1]);
//     CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);//进行了个人的修改
//     osDelay(5);
//   }
//   positionServo(0, &hDJI[1]); // 爪子维持
//   CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);
//   osDelay(5);
// }

/**
 * @brief 夹爪机构电机闭合执行器
 * @param reset_speed 复位速度
 */
void ClosePawlExecutor(float reset_speed)
{
  girp_pawl_close_init();
  int overcnt = 0,breakflag = 1;
  while(breakflag)//检测电流
  {
    if(hDJI[1].FdbData.current < CLOSE_STALL_CURRENT)//避免摩擦毛刺  (需要测试改电流参数)
    {
      overcnt++;
      if(overcnt >= 3)
      {
        breakflag = 0;
      }
    }
    else
    {
      overcnt = 0;
    }
    speedServo(reset_speed,&hDJI[1]);
    CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);//进行了个人的修改
    osDelay(5);
  }
  positionServo(0, &hDJI[1]); // 爪子维持
  CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);
  osDelay(5);
}

//以下均为爪子PID先速度环,再位置环,用电流检测的代码

// hDJI[1].posPID.outputMax=4000;
//     hDJI[1].posPID.KP=60;
//     hDJI[1].posPID.KI=3;
//     hDJI[1].posPID.KD=0.0;
//     hDJI[1].speedPID.outputMax=4000;
//     hDJI[1].speedPID.KI=0.4;
//     hDJI[1].speedPID.KD=0.4;
//     hDJI[1].speedPID.KP=12;  

    // hDJI[0].posPID.outputMax=4000;
    // hDJI[0].posPID.KP=60;
    // hDJI[0].posPID.KI=3;
    // hDJI[0].posPID.KD=0.0;
    // hDJI[0].speedPID.outputMax=4000;
    // hDJI[0].speedPID.KI=0.4;
    // hDJI[0].speedPID.KD=0.4;
    // hDJI[0].speedPID.KP=12; 
    // reset_degree = hDJI[1].AxisData.AxisAngle_inDegree;
    // while(breakflag)//检测电流
    // {
    //   if(hDJI[1].FdbData.current > CLOSE_STALL_CURRENT)//避免摩擦毛刺  (需要测试改电流参数)
    //   {
    //     overcnt++;
    //     reset_end_position[overcnt] = hDJI[1].AxisData.AxisAngle_inDegree;
    //     if(overcnt >= 10)
    //     {
    //       breakflag = 0;
    //     }
    //   }
    //   else
    //   {
    //     overcnt = 0;
    //   }
    //   speedServo(close_speed,&hDJI[1]);
    //   // speedServo(close_speed,&hDJI[0]);
    //   CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);//进行了个人的修改
    //   osDelay(5);
    // }
    // close_reset_position = (reset_end_position[7] + reset_end_position[8] + reset_end_position[9])/3- reset_degree;
    // new_close_reset_position = close_reset_position + BUFFER_POSITION;   
    // positionServo(new_close_reset_position, &hDJI[1]); // 爪子维持
    // speedServo(5400,&hDJI[1]);
    // positionServo(200, &hDJI[1]); // 爪子维持
    // CanTransmit_DJI_1234(&hcan1, 0, hDJI[1].speedPID.output, 0, 0);
    // CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, 0, 0);