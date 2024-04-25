#ifndef _DEVICE_
#define _DEVICE_

// 设备结构体
typedef struct device {
    int did;
    char name[20];
    int status; // 设备状态：空闲、忙碌等
}DEVICE;

void initDevices(DEVICE devices[], int numDevices);
// 设备请求
void requestDevice(DEVICE devices[], int numDevices);

#endif