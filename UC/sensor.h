// #ifndef SENSOR_H
// #define SENSOR_H

// #include "stdint.h"
// #include "cmsis_os.h"
// #include "usart.h"

// #define RX_BUFFER_SIZE 128  // 环形缓冲区大小
// #define DATA_FRAME_SIZE 10   // 每帧数据大小（D=xxxm\r\n）

// extern volatile float measuredDistance;
// extern volatile uint8_t dataReadyFlag;
// extern uint8_t ringBuffer[RX_BUFFER_SIZE];  // 环形缓冲区
// extern int processDataFlag;  // 标记是否需要处理数据
// extern uint16_t ringBufferHead;  // 环形缓冲区头索引
// extern uint16_t ringBufferTail;  // 环形缓冲区尾索引

// void Sensor_Init(void);
// void Sensor_RequestDistance(void);
// void Sensor_ProcessResponse(void);
// void Sensor_UART_Callback(UART_HandleTypeDef *huart);

// #endif // SENSOR_H




#ifndef SENSOR_H
#define SENSOR_H

#include "stdint.h"
#include "cmsis_os.h"
#include "usart.h"

#define RX_BUFFER_SIZE 20  // 接收缓冲区大小

extern volatile float measuredDistance;
extern volatile uint8_t dataReadyFlag;
extern uint8_t uartRxBuffer[RX_BUFFER_SIZE];  // UART DMA 接收缓冲区
extern int processDataFlag;  // 标记是否需要处理数据

void Sensor_Init(void);
void Sensor_RequestDistance(void);
void Sensor_ProcessResponse(void);
void Sensor_UART_Callback(UART_HandleTypeDef *huart);

#endif // SENSOR_H

// #ifndef SENSOR_H
// #define SENSOR_H

// #include "stdint.h"
// #include "cmsis_os.h"
// #include "usart.h"

// // #define RX_BUFFER_SIZE 64  // 缓冲区大小
// #define RX_BUFFER_SIZE 20  // 缓冲区大小

// extern volatile float measuredDistance;
// extern volatile uint8_t modbusReceivedFlag;
// extern volatile uint16_t modbusErrorCode;
// extern uint8_t uartRxBuffer[RX_BUFFER_SIZE];  // DMA接收缓冲区
// extern uint8_t uartProcessBuffer[RX_BUFFER_SIZE];  // 解析缓冲区
// extern int ProcessDataFlag;  // 标记是否需要处理数据
// void Sensor_Init(void);
// void Sensor_RequestDistance(void);
// void Sensor_ProcessResponse(void);
// void Sensor_UART_Callback(UART_HandleTypeDef *huart);

// #endif // SENSOR_H





// #ifndef SENSOR_H
// #define SENSOR_H

// #include "stdint.h"
// #include "cmsis_os.h"
// #include "usart.h"

// extern volatile uint32_t measuredDistance;  
// extern volatile uint8_t modbusReceivedFlag;  
// extern volatile uint16_t modbusErrorCode;  
// extern uint8_t modbusRxBuffer[8];  // Modbus 接收缓冲区
// extern uint8_t modbusTxBuffer[8];  // Modbus 发送缓冲区

// void Sensor_RequestDistance(void);        
// void Sensor_ProcessResponse(void);        
// void Sensor_UART_Callback(UART_HandleTypeDef *huart); 

// #endif // SENSOR_H
