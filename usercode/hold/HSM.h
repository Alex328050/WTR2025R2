#ifndef HSM_H
#define HSM_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file HSM.h
 * @author thrzer
 * @brief wtr一代车状态机
 * @date 2024-11-3
 */

//暂时写了两种方案的情况，还可以再加
//#define THROWMETHOD //抛射
#define POPMETHOD   //弹射

typedef enum
{
    HSM_STATE_ON,       //上电
    HSM_STATE_RUNNING,  //正在运行
    HSM_STATE_ERROR     //错误状态
} HSM_State_e;          //整车状态

typedef enum
{
    HSM_rSTATE_DISCONNECTED, //未连接
    HSM_rSTATE_CONNECTED,    //已连接
} HSM_RemotectlState_e;      //遥控器状态

typedef enum
{
    HSM_cSTATE_ON,       //上电
    HSM_cSTATE_INIT,     //初始化
    HSM_cSTATE_RUNNING,  //正在运行
    HSM_cSTATE_ERROR     //错误状态
} HSM_ChassisState_e;    //底盘状态

#ifdef THROWMETHOD
typedef enum
{
    HSM_tSTATE_ON,       //上电
    HSM_tSTATE_INIT,     //初始化
    //HSM_tSTATE_XXX,    //其他
    HSM_tSTATE_ERROR     //错误状态
} HSM_ThrowState_e;     //抛射机构状态，可增改
#endif

#ifdef POPMETHOD
typedef enum
{
    HSM_pSTATE_ON,       //上电
    HSM_pSTATE_INIT,     //初始化
    HSM_pSTATE_SET,      //复位完成
    HSM_pSTATE_CHARGE,   //蓄力中
    HSM_pSTATE_READY,    //蓄力完成
    HSM_pSTATE_RESET,    //发射并复位中
    HSM_pSTATE_ERROR     //错误状态
} HSM_PopState_e;       //弹射机构状态
#endif

typedef enum
{
    HSM_bSTATE_ON,       //上电
    HSM_bSTATE_INIT,     //初始化
    //HSM_bSTATE_XXX,    //其他
    HSM_bSTATE_ERROR     //错误状态
} HSM_BounceState_e;     //拍球机构状态，可增改

typedef enum
{
    HSM_iSTATE_ON,       //上电
    HSM_iSTATE_INIT,     //初始化
    //HSM_iSTATE_XXX,    //其他
    HSM_iSTATE_ERROR     //错误状态
} HSM_InterceptState_e;  //拦截机构状态，可增改

typedef struct
{
    HSM_State_e state;
    char** error_msg;   //错误信息
    HSM_RemotectlState_e remotectl;
    HSM_ChassisState_e chassis_mechanism;
    #ifdef THROWMETHOD
    HSM_ThrowState_e throw_mechanism;
    #endif
    #ifdef POPMETHOD
    HSM_PopState_e pop_mechanism;
    #endif
    HSM_BounceState_e bounce_mechanism;
    HSM_InterceptState_e intercept_mechanism;
} HSM_t;  //一代车

void HSM_start(HSM_t* this);

extern HSM_t wtrV1;
extern char HSM_error_msg[5][20];

#ifdef __cplusplus
}
#endif

#endif