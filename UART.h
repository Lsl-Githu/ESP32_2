#ifndef _UART_h
#define _UART_h
 char Contr=0;
 char State=0;
const char* kouwei[4]={"默认","微辣","中辣","特辣"};

#include<WiFi.h>
#include<PubSubClient.h>
 
const char* ssid ="nova";//wifi名
const char*password ="12345678";//wifi密码
const char*mqttHostUrl = "a1WZaCEwkny.iot-as-mqtt.cn-shanghai.aliyuncs.com";//阿里云服务器域名
const int mqttPort =1883;//端口号
const char*mqttUser = "DianCan&a1WZaCEwkny";//username
const char*mqttPassword = "eb6e1c9038df6f972369b509c30da93f7ec5f06445edc869f4883d135ab66f44";//密钥
const char*clientId = "a1WZaCEwkny.DianCan|securemode=2,signmethod=hmacsha256,timestamp=1681216576659|" ;//连接id

#define PRODUCT_KEY       "a1WZaCEwkny"
#define DEVICE_NAME       "DianCan"
//下面组包用
#define ALINK_BODY_FORMAT         "{\"id\":\"level\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post"
#define ALINK_TOPIC_PROP_POST2    "/a1WZaCEwkny/DianCan/user/update"
unsigned long lastMs = 0;

WiFiClient espClient;
PubSubClient client(espClient);


//连接wifi
void wifiInit()
{
  WiFi.begin(ssid,password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.println("Connectingto WiFi..");
  }
     Serial.println("Connectedto the WiFi network"); 
}


//mqtt连接
void mqttCheckConnect()
{
   client.setServer(mqttHostUrl,mqttPort);
  while (!client.connected()){
    Serial.println("Connectingto MQTT...");
    if (client.connect(clientId,mqttUser, mqttPassword )) {
      Serial.println("connected");
    }else {
      Serial.print("failedwith state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

}


//组数据帧并发送
void mqttIntervalPost()
{  
  static char count_time=0;
    char param[50];
    char jsonBuf[150];
switch(State)
{
case 0:break;
case 1:
{
  Contr=0;
//清除
  memset(param,0,50);
  memset(jsonBuf,0,150);
  for(char i=1;i<9;i++)  
  {
     sprintf(param, "{\"flag%d\":%d,\"kw%d\":\"%s\",\"num%d\":%d}",i,Contr,i,kouwei[0],i,0);
     sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
     Serial.println(jsonBuf);
     client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
     delay(100);
  }
  State=2;
}break;

case 2:
{
  memset(param,0,50);
  memset(jsonBuf,0,150);
  Contr=1;
 count_time++;
 if(count_time>=30)
 {
    count_time=0;
     for(char i=0;i<ge_fg;i++)  
    {
     sprintf(param, "{\"xs\":%d,\"flag%d\":%d,\"kw%d\":\"%s\",\"num%d\":%d}",arr1[i].Id+1,arr1[i].Id+1,Contr,arr1[i].Id+1,kouwei[arr1[i].kou],arr1[i].Id+1,arr1[i].num);
     sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
     Serial.println(jsonBuf);
     client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
     delay(2000);
    }
    ge_fg=0;
    State=0;
 }
}break;

}
   
}


void WIFI_Init() {
  Serial.begin(115200);
  wifiInit();//连接wifi
  mqttCheckConnect();//连接阿里云
}
 


















#endif
