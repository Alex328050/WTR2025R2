/*
 * @Description: 大疆电机初始化线程
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-10 16:11:48
 */
#include "DJIInitTask.h"

uint8_t flag_DJIInitComplete = 0; //信号 指示大疆电机初始化情况 1为完成

/*对自旋和夹爪两个大疆电机进行初始化*/
void DJIInitTask(void *argument)
{
    /*夹爪电机参数初始化 */
    hDJI[0].posPID.outputMax=4000;
    hDJI[0].posPID.KP=60;
    hDJI[0].posPID.KI=3;
    hDJI[0].posPID.KD=0.0;
    hDJI[0].speedPID.outputMax=4000;
    hDJI[0].speedPID.KI=0.4;
    hDJI[0].speedPID.KD=0.4;
    hDJI[0].speedPID.KP=12;

    /*自旋电机参数初始化*/
    hDJI[1].posPID.outputMax=4000;
    hDJI[1].posPID.KP=60;
    hDJI[1].posPID.KI=3;
    hDJI[1].posPID.KD=0.0;
    hDJI[1].speedPID.outputMax=4000;
    hDJI[1].speedPID.KI=0.4;
    hDJI[1].speedPID.KD=0.4;
    hDJI[1].speedPID.KP=12;

    flag_DJIInitComplete = 1;
    for(;;)
    {
        osDelay(10);
    }
}