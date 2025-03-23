#include "RmctlTask.h"

/**
 * @brief 遥控器线程
 * @author thrzer
 * @date 2024-11-23
 */
void RmctlTask(void *argument)
{
  wtrV1.remotectl = HSM_rSTATE_DISCONNECTED;
  rmctl_Init(&rmctl);
  wtrV1.remotectl = HSM_rSTATE_CONNECTED;
  rmctl_decode(&rmctl.rmctl_msg);
}
