#include "oled.h"
#include "key.h"
#include "UART.h"
#include "temp.h"

extern char Contr;
extern char State;


void setup() {
  //LED_Init();
  WIFI_Init();
  key_init();
 OLED_Init();
 CAI_listIinit();//*初始化菜单
 Serial.println("test go");

}

void loop() {
  


oled_task();//oled处理
key_task();
client.loop();
  if (millis() - lastMs >= 1000)
   {//定时检查或上报数据
        lastMs = millis();
       mqttCheckConnect(); 
   }
           // 上报 
if(State!=0) mqttIntervalPost();




}
