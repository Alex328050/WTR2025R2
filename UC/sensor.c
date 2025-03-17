// #include "sensor.h"
// #include "string.h"
// #include "stdlib.h"

// volatile float measuredDistance = 0;  // 解析出的测距数据
// volatile uint8_t dataReadyFlag = 0;   // 标记数据是否接收完整
// uint8_t ringBuffer[RX_BUFFER_SIZE] = {0};  // UART DMA 环形缓冲区
// uint16_t ringBufferHead = 0;  // 缓冲区头指针
// uint16_t ringBufferTail = 0;  // 缓冲区尾指针
// int processDataFlag = 0;

// /**
//  * @brief  传感器初始化，启动DMA接收
//  */
// void Sensor_Init(void) {
//     HAL_UART_Receive_DMA(&huart8, ringBuffer, RX_BUFFER_SIZE);
//     char commandClose[] = "iLD:0\r\n";  // 关闭激光
//     HAL_UART_Transmit(&huart8, (uint8_t*)commandClose, strlen(commandClose), HAL_MAX_DELAY);
// }

// /**
//  * @brief  发送快速连续测量命令
//  */
// void Sensor_RequestDistance(void) {
//     char command[] = "iFACM\r\n";  // 启动快速测量模式
//     HAL_UART_Transmit(&huart8, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
// }

// /**
//  * @brief  处理环形缓冲区中的数据
//  */
// void Sensor_ProcessResponse(void) {
//     while (ringBufferHead != ringBufferTail) {  // 缓冲区不为空
//         // **寻找 "D=" 作为起点**
//         if (ringBuffer[ringBufferHead] == 'D' && ringBuffer[(ringBufferHead + 1) % RX_BUFFER_SIZE] == '=') {
//             char distanceStr[10] = {0};  // 存储解析到的测距数据
//             uint16_t end = (ringBufferHead + 2) % RX_BUFFER_SIZE;
            
//             // **向后查找 "m" 作为终止符**
//             while (ringBuffer[end] != 'm' && end != ringBufferTail) {
//                 end = (end + 1) % RX_BUFFER_SIZE;
//             }

//             // **确保找到 "m"，然后提取数据**
//             if (ringBuffer[end] == 'm') {
//                 strncpy(distanceStr, (char*)&ringBuffer[(ringBufferHead + 2) % RX_BUFFER_SIZE], end - ringBufferHead - 2);
//                 distanceStr[end - ringBufferHead - 2] = '\0';  // **确保字符串结束符**
                
//                 // **转换数据**
//                 float tempDistance = strtof(distanceStr, NULL);
//                 if (tempDistance > 0) {  // **检查是否解析成功**
//                     measuredDistance = tempDistance;
//                 }
//             }
//         }

//         // **更新缓冲区头部索引**
//         ringBufferHead = (ringBufferHead + 1) % RX_BUFFER_SIZE;
//     }
//     dataReadyFlag = 0;  // **标记数据处理完成**
// }

// /**
//  * @brief  串口回调函数，DMA接收完成后触发
//  */
// void Sensor_UART_Callback(UART_HandleTypeDef *huart) {
//     if (huart->Instance == UART8) {
//         dataReadyFlag = 1;  // **标记数据已接收**
//         processDataFlag = 1;  
//         HAL_UART_Receive_DMA(&huart8, ringBuffer, RX_BUFFER_SIZE);  // **继续DMA接收**
//     }
// }



// #include "sensor.h"
// #include "string.h"
// #include "stdlib.h"

// volatile float measuredDistance = 0;
// volatile uint8_t dataReadyFlag = 0;
// uint8_t ringBuffer[RX_BUFFER_SIZE] = {0};  // 环形缓冲区
// uint16_t ringBufferHead = 0;  // 缓冲区头部索引
// uint16_t ringBufferTail = 0;  // 缓冲区尾部索引
// int processDataFlag = 0;  

// /**
//  * @brief  初始化传感器，启动DMA接收
//  */
// void Sensor_Init(void) {
//     HAL_UART_Receive_DMA(&huart8, ringBuffer, RX_BUFFER_SIZE);
//     char commandClose[] = "iLD:0";  // 关闭激光
//     HAL_UART_Transmit(&huart8, (uint8_t*)commandClose, strlen(commandClose), HAL_MAX_DELAY);
// }

// /**
//  * @brief  发送快速连续测量命令
//  */
// void Sensor_RequestDistance(void) {
//     char command[] = "iFACM\r\n";  // 启动快速测量
//     HAL_UART_Transmit(&huart8, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
// }

// /**
//  * @brief  处理环形缓冲区中的数据
//  */
// void Sensor_ProcessResponse(void) {
//     while (ringBufferHead != ringBufferTail) {  // 缓冲区不为空
//         if (ringBuffer[ringBufferHead] == 'D' && ringBuffer[(ringBufferHead + 1) % RX_BUFFER_SIZE] == '=') {
//             char distanceStr[10] = {0};
//             uint16_t end = (ringBufferHead + 2) % RX_BUFFER_SIZE;
//             while (ringBuffer[end] != 'm' && end != ringBufferTail) {
//                 end = (end + 1) % RX_BUFFER_SIZE;
//             }
//             if (ringBuffer[end] == 'm') {
//                 strncpy(distanceStr, (char*)&ringBuffer[(ringBufferHead + 2) % RX_BUFFER_SIZE], end - ringBufferHead - 2);
//                 measuredDistance = strtof(distanceStr, NULL);  // 转换为浮点数
//             }
//         }
//         ringBufferHead = (ringBufferHead + 1) % RX_BUFFER_SIZE;  // 移动头部索引
//     }
//     dataReadyFlag = 0;
// }

// /**
//  * @brief  串口回调处理
//  */
// void Sensor_UART_Callback(UART_HandleTypeDef *huart) {
//     if (huart->Instance == UART8) {
//         dataReadyFlag = 1;  
//         processDataFlag = 1;  
//         HAL_UART_Receive_DMA(&huart8, ringBuffer, RX_BUFFER_SIZE);  
//     }
// }





#include "sensor.h"
#include "string.h"
#include "stdlib.h"

volatile float measuredDistance = 0;//传感器解析后的数值
volatile uint8_t dataReadyFlag = 0;//数据接收标志，0为未接收，1为接收
uint8_t uartRxBuffer[RX_BUFFER_SIZE] = {0};  // UART DMA 接收缓冲区
int processDataFlag = 0;  // 标记是否需要处理数据

/**
 * @brief  初始化传感器，启动DMA接收
 */
void Sensor_Init(void) {
    HAL_UART_Receive_DMA(&huart8, uartRxBuffer, RX_BUFFER_SIZE);
    // Sensor_RequestDistance();
    // char commandClose[] = "iLD:0";  // 激光关闭
    // HAL_UART_Transmit(&huart8, (uint8_t*)commandClose, strlen(commandClose), HAL_MAX_DELAY);
}

/**
 * @brief  发送快速连续测量命令
 */
void Sensor_RequestDistance(void) {
    char command[] = "iFACM\r\n";  // 发送快速连续测量指令
    HAL_UART_Transmit(&huart8, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
}

/**
 * @brief  处理接收的数据
 */
void Sensor_ProcessResponse(void) {
    if (!dataReadyFlag) return;  // 没有数据可处理，直接返回

    char *start = strstr((char*)uartRxBuffer, "D=");
    if (start) {
        char *end = strchr(start, 'm');  // 直接查找 ‘m’ 作为结束标志
        if (end && (end > start + 2)) {
            char distanceStr[10] = {0};
            strncpy(distanceStr, start + 2, end - (start + 2));
            measuredDistance = strtof(distanceStr, NULL);  // 转换为浮点数
        }
    }
    dataReadyFlag = 0;  // 复位标志
    memset(uartRxBuffer, 0, RX_BUFFER_SIZE);  // 清空缓冲区
}

/**
 * @brief  串口回调处理
 */
void Sensor_UART_Callback(UART_HandleTypeDef *huart) {
    if (huart->Instance == UART8) {
        dataReadyFlag = 1;  // 标记数据已接收
        processDataFlag = 1;  // 让任务处理数据
        HAL_UART_Receive_DMA(&huart8, uartRxBuffer, RX_BUFFER_SIZE);  // 继续DMA接收
    }
}

// #include "sensor.h"
// #include "string.h"
// #include "stdlib.h"

// volatile float measuredDistance = 0;
// volatile uint8_t modbusReceivedFlag = 0;
// volatile uint16_t modbusErrorCode = 0;

// uint8_t uartRxBuffer[RX_BUFFER_SIZE] = {0};  // DMA接收缓冲区
// uint8_t uartProcessBuffer[RX_BUFFER_SIZE] = {0};  // 解析缓冲区
// uint8_t receivedDataComplete = 0;  // 标记数据是否完整
// int ProcessDataFlag = 0;  // 标记是否需要处理数据

// void Sensor_Init(void) {
//     HAL_UART_Receive_DMA(&huart8, uartRxBuffer, RX_BUFFER_SIZE);
//     Sensor_RequestDistance();
// }

// /* 发送快速连续测量命令 */
// void Sensor_RequestDistance(void) {
//     char command[] = "iFACM\r\n";  // 发送快速连续测量指令
//     HAL_UART_Transmit(&huart8, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
// }

// /* 处理接收的数据 */
// void Sensor_ProcessResponse(void) {
//     memcpy(uartProcessBuffer, uartRxBuffer, RX_BUFFER_SIZE); // 先拷贝数据，防止解析时被覆盖

//     char *start = strstr((char*)uartProcessBuffer, "D=");
//     char *end = strstr((char*)uartProcessBuffer, "m");

//     if (start && end && (end > start)) {
//         char distanceStr[10] = {0};
//         strncpy(distanceStr, start + 2, end - (start + 2));  // 提取 D= 和 m 之间的数据
//         measuredDistance = strtof(distanceStr, NULL);  // 转换为浮点数
//         modbusReceivedFlag = 1;
//     }

//     receivedDataComplete = 0;
//     memset(uartRxBuffer, 0, RX_BUFFER_SIZE);  // 清空接收缓冲区，确保不影响下一次解析
// }

// /* 串口回调处理 */
// void Sensor_UART_Callback(UART_HandleTypeDef *huart) {
//     if (huart->Instance == UART8) {
//         receivedDataComplete = 1;  // 标记数据已接收
//         HAL_UART_Receive_DMA(&huart8, uartRxBuffer, RX_BUFFER_SIZE);
//         ProcessDataFlag = 1;  // 标记需要处理数据
//         // osSignalSet(sensorTaskHandle, 0x01);  // 通知任务处理数据
//     }
// }







// #include "sensor.h"

// /* 全局变量 */
// volatile uint32_t measuredDistance = 0; 
// volatile uint8_t modbusReceivedFlag = 0; 
// volatile uint16_t modbusErrorCode = 0; 
// uint8_t modbusRxBuffer[8] = {0};  // Modbus 接收缓冲区
// uint8_t modbusTxBuffer[8] = {0};  // Modbus 发送缓冲区

// // CRC16高位字节值表
// const uint8_t auchCRCHi[] = { 
//     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
//     0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
//     0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
//     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
//     0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
//     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
// }; 
// // CRC16低位字节值表
// const uint8_t auchCRCLo[] = { 
//     0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 
//     0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 
//     0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 
//     0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 
//     0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
//     0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 
//     0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 
//     0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 
//     0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 
//     0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
//     0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 
//     0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 
//     0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 
//     0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 
//     0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
//     0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
// }; 


// uint16_t CRC16(uint8_t *data, uint16_t length) {
//     uint16_t crc = 0xFFFF;
//     for (uint16_t i = 0; i < length; i++) {
//         crc ^= data[i]; 
//         for (uint8_t j = 0; j < 8; j++) {
//             if (crc & 0x0001) {
//                 crc >>= 1;
//                 crc ^= 0xA001;
//             } else {
//                 crc >>= 1;
//             }
//         }
//     }
//     return crc;
// }
// void Sensor_RequestDistance(void) {
//     uint8_t requestData[6] = {0x01, 0x03, 0x00, 0x0F, 0x00, 0x02};
//     uint16_t crc = CRC16(requestData, 6); // 计算 CRC16

//     modbusTxBuffer[0] = requestData[0];
//     modbusTxBuffer[1] = requestData[1];
//     modbusTxBuffer[2] = requestData[2];
//     modbusTxBuffer[3] = requestData[3];
//     modbusTxBuffer[4] = requestData[4];
//     modbusTxBuffer[5] = requestData[5];
//     modbusTxBuffer[6] = crc & 0xFF;        // 低字节
//     modbusTxBuffer[7] = (crc >> 8) & 0xFF; // 高字节

//     HAL_UART_Transmit_DMA(&huart1, modbusTxBuffer, 8);
// }

// void Sensor_ProcessResponse(void) {
//     if (modbusRxBuffer[0] == 0x01 && modbusRxBuffer[1] == 0x03) { 
//         uint16_t receivedCRC = (modbusRxBuffer[6] << 8) | modbusRxBuffer[7]; 
//         uint16_t calculatedCRC = CRC16(modbusRxBuffer, 6);

//         if (receivedCRC != calculatedCRC) {
//             modbusErrorCode = 0x05; // CRC 校验错误
//             modbusReceivedFlag = 0;
//             return;
//         }

//         if (modbusRxBuffer[2] == 0x04) { // 正确的响应格式
//             uint32_t distance = (modbusRxBuffer[3] << 8) | modbusRxBuffer[4]; 
//             measuredDistance = distance; // 转换单位为 mm
//             modbusReceivedFlag = 1;
//         } else {
//             modbusErrorCode = 0x02; // 数据格式错误
//             modbusReceivedFlag = 0;
//         }
//     } else {
//         modbusErrorCode = 0x01; // 功能码错误
//         modbusReceivedFlag = 0;
//     }
// }


// void Sensor_UART_Callback(UART_HandleTypeDef *huart) {
//     if (huart->Instance == USART1) {
//         if (modbusRxBuffer[0] != 0) { 
//             modbusReceivedFlag = 1;
//         }
//         HAL_UART_Receive_DMA(&huart1, modbusRxBuffer, 8); 
//     }
// }
