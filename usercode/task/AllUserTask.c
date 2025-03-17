/*
 * @Description: 
 * @Author: Alex
 * @Date: 2025-03-02 19:35:06
 * @LastEditors: Alex
 * @LastEditTime: 2025-03-15 23:49:03
 */
#include "AllUserTask.h"

/* 宇树电机初始化 */
osThreadId_t UnitreeInitTaskHandle;
const osThreadAttr_t UnitreeInitTask_attributes = {
  .name = "UnitreeInitTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* 大疆电机初始化 */
osThreadId_t DJIInitTaskHandle;
const osThreadAttr_t DJIInitTask_attributes = {
  .name = "DJIInitTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* 状态机 */
osThreadId_t hsmtaskHandle;
const osThreadAttr_t hsmtask_attributes = {
  .name = "hsmtask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* 遥控器 */
osThreadId_t rmctltaskHandle;
const osThreadAttr_t rmctltask_attributes = {
  .name = "rmctltask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* 抛射全车状态机修改线程 */
osThreadId_t ThrowHSMTaskHandle;
const osThreadAttr_t ThrowHSMTaskTask_attributes = {
  .name = "ThrowHSMTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/*宇树电机控制线程*/
osThreadId_t UnitreeExecutorTaskHandle;
const osThreadAttr_t UnitreeExecutorTask_attributes = {
  .name = "UnitreeExecutorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/*大疆电机控制线程*/
osThreadId_t DJIExecutorTaskHandle;
const osThreadAttr_t DJIExecutorTask_attributes = {
  .name = "DJIExecutorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* 抛球机构 */
osThreadId_t ThrowTaskHandle;
const osThreadAttr_t ThrowTask_attributes = {
  .name = "ThrowTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* 底盘 */
osThreadId_t chassistaskHandle;
const osThreadAttr_t chassistask_attributes = {
  .name = "chassistask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* 弹射机构 */
osThreadId_t poptaskHandle;
const osThreadAttr_t poptask_attributes = {
  .name = "poptask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* 拍球机构 */
osThreadId_t BounceTaskHandle;
const osThreadAttr_t BounceTask_attributes = {
  .name = "BounceTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/*初始抓球并抬升部分 */
osThreadId_t CatchingTaskHandle;
const osThreadAttr_t CatchingTask_attributes = {
  .name = "CatchingTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t ReadyTaskHandle;
const osThreadAttr_t ReadyTask_attributes = {
    .name = "ReadyTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};

/**
 * @brief 自定义线程初始化函数，在freertos.c的defaulttask调用
 * @date 2024-11-23
 */
void User_FREERTOS_Init(void)
{
    UnitreeInitTaskHandle = osThreadNew(UnitreeInitTask, NULL, &UnitreeInitTask_attributes);
    DJIInitTaskHandle = osThreadNew(DJIInitTask, NULL, &DJIInitTask_attributes);

    // hsmtaskHandle = osThreadNew(HsmTask, NULL, &hsmtask_attributes);
    rmctltaskHandle = osThreadNew(RmctlTask, NULL, &rmctltask_attributes);
    ThrowHSMTaskHandle = osThreadNew(ThrowHSMTask, NULL, &ThrowHSMTaskTask_attributes);

    UnitreeExecutorTaskHandle = osThreadNew(UnitreeExecutorTask, NULL, &UnitreeExecutorTask_attributes);
    DJIExecutorTaskHandle = osThreadNew(DJIExecutorTask, NULL, &DJIExecutorTask_attributes);

    ThrowTaskHandle = osThreadNew(ThrowTask, NULL, &ThrowTask_attributes);
    BounceTaskHandle = osThreadNew(BounceTask, NULL, &BounceTask_attributes);
    ReadyTaskHandle = osThreadNew(ReadyTask, NULL, &ReadyTask_attributes);
    // chassistaskHandle = osThreadNew(ChassisTask, NULL, &chassistask_attributes);
    // CatchingTaskHandle = osThreadNew(Catchingtask, NULL, &CatchingTask_attributes);
    // poptaskHandle = osThreadNew(PopTask, NULL, &poptask_attributes);
    
}
