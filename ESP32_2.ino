/************************************************* 
 File name: ESP32_2.ion// 文件名
 Author: LiShuangLong  
 Version:V1.1 Date: 2023.4.20// 作者、版本及完成日期
 Description: 函数入口程序主程序// 用于详细说明此程序文件完成的主要功能，与其他模块
 Others: 无   // 其它内容的说明
 Function List: mqttIntervalPost();//数据上报  mqttCheckConnect(); //连接阿里云   
 oled_task();//oled处理   key_task();//按键处理
 // 主要函数列表，每条记录应包括函数名及功能简要说明
*************************************************/

#include "oled.h"
#include "key.h"
#include "UART.h"
#include "temp.h"

extern char Contr;
extern char State;


void setup() 
{
    //LED_Init();
    WIFI_Init();
    key_init();
    OLED_Init();
    CAI_listIinit();//*初始化菜单
    Serial.println("test go");

}

void loop() 
{
  
  oled_task();//oled处理
  key_task();//按键处理
  client.loop();
  if (millis() - lastMs >= 1000)//定时检查或上报数据
  {     
   lastMs = millis();
   mqttCheckConnect(); 
  }
           // 上报 
 if (State != 0) mqttIntervalPost();

}
