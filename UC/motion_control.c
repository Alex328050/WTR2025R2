#include "motion_control.h"
#include "math.h"
#include "usart.h"

// Unitree 电机初始化函数
float InitUnitreeMotor(UnitreeMotor myMotor1, UART_HandleTypeDef* huart) {
    float unitree_offest = 0.0;
    
    // 循环初始化直到成功
    while(Unitree_init(&myMotor1, huart, 0) == HAL_ERROR) {
        printf("Unitree_init error!\n");
        osDelay(100);
    }

    // 采集5次数据计算初始偏移
    for(int i = 0; i < 5; i++) {
        Unitree_UART_tranANDrev(&myMotor1, 0, 1, 0, 0, 0, 0, 0.001);
        unitree_offest += myMotor1.data.Pos / UNITREE_REDUCTION_RATE;
        printf("unitree_offest:%d\n", (int)unitree_offest);
        osDelay(10);
    }
    unitree_offest /= 5;
    printf("unitree_offest:%d\n", (int)unitree_offest);
    return unitree_offest;
    
}


// 夹爪控制函数
void ControlClaw(uint8_t key, int* state) {
    if(1) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); // 夹爪不动
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
    } else if(0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);   // 夹爪闭合
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
    } else if (0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); // 夹爪张开
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    }
}

// // 接收并打印角度信息函数
// void ReceiveAndPrintAngleData(CAN_HandleTypeDef* hcan, EncoderData* encoderData) {
//     ReceiveCANData(hcan, encoderData);
//     //printf("Angle: %.2f, Angular Speed: %.2f, Revolutions: %d\n",
//         //    encoderData->angle, encoderData->angularSpeed, encoderData->revolutions);
// }

// Unitree 电机状态控制函数
void ControlUnitreeMotion(UnitreeMotor myMotor1, float unitree_offest, int* flag, int* state) {
    float current_position =myMotor1.data.Pos / UNITREE_REDUCTION_RATE - unitree_offest;
    float current_speed = myMotor1.data.W; // 当前转速（rad/s）
    
    switch(*flag) {
        case 0: // 状态零：机构后转摆动
            Unitree_UART_tranANDrev(&myMotor1, 0, 1, 2 * sin(current_position), 0, unitree_offest - 2.7, 0.1, 0.05);
            if(current_position <= unitree_offest - 1.0) {
                *flag = 1;
            }
            break;
        case 1: // 状态一：机构停滞蓄力
            vTaskDelay(pdMS_TO_TICKS(2000));
            *flag = 2;
            break;
        case 2: // 状态二：机构前冲摆动
            Unitree_UART_tranANDrev(&myMotor1, 0, 1, 2 * sin(current_position), 1.5, 2.7 + unitree_offest, 0.8, 0.05);
            if(current_position >= 1.5 + unitree_offest) {
                *state = 1;
                *flag = 3;
            }
            break;
        case 3: // 状态三：机构暂停摆动
            Unitree_UART_tranANDrev(&myMotor1, 0, 1, 2 * sin(current_position), 0, 2.7 + unitree_offest, 0, 0.5);
            break;
        default:
            break;
    }

    printf("Unitree offset: %d, Current Speed: %d rad/s, Current Position: %d rad\n",
           (int)unitree_offest, (int)(current_speed * 100), (int)(current_position * 100));
}
