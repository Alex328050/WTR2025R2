/*
 * @Description: 
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-12 14:15:02
 */
// #include "AllUserTask.h"
// #include "HSM.h"
// #include "rmctl.h"

// /**
//  * @brief 状态机线程
//  * @author thrzer
//  * @date 2024-11-23
//  */
// void HsmTask(void *argument)
// {
//     int ledcnt = 0;
//     for (;;) {//signal LED
//         HSM_start(&wtrV1);
//         ledcnt++;
//         if (ledcnt >= 100)
//         {
//           ledcnt = 0;
//           // HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_2);
//         }
//         osDelay(5);
//     }
// }