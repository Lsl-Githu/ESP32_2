#ifndef _oled_h
#define _oled_h
#include "hanzi.h"//*汉子取模
#include "temp.h"
//#include "UART.h"

// 引入驱动OLED0.96所需的库
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>// 引入IIC通讯所需的Wire库文件

#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素

// 自定义重置引脚,虽然教程未使用,但却是Adafruit_SSD1306库文件所必需的
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);








unsigned char Cmode=0;//模式选择

unsigned char oled_flag=0;//界面标志
unsigned char Ye=0;//菜单页面标志
unsigned char Xu=0;//菜单序号标志
char xs_fg=0;//查询用的fg
char ge_fg=0;//有效菜个数
unsigned char kw=1;//口味序号上标志
unsigned char temp=0;//临时份数标志


 char Cont=0;//*计时
 char Cont_fh=0;//*计时标志
unsigned char key_val=0;//*按键值
unsigned char up=0;//菜单序号上标志
unsigned char x=0;//口味保存标志
unsigned char feng_flag=0;//调节标志
unsigned char cha_fg=0;

void OLED_Init();
void oled_task();
void Oled_call();
void Oled_callsucc();
void Oled_dianFaill();
void oled_zhu();
void Oled_mode(unsigned char md_flag);
void Oled_cai(unsigned char ye,unsigned char xu);
void Oled_taste(unsigned char kw_flag);
void Oled_cha();
void hanzi_xz(unsigned char id,int wz);
void cha_task();
void cai_id();
void less_3(unsigned char ge_fg);
void More_3();
void Oled_dianSuuc();

void OLED_Init()
{
  // 初始化OLED并设置其IIC地址为 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);// 设置字体颜色,白色可见
  display.setTextSize(1);  //设置字体大小 
  display.clearDisplay();//*清屏
}



/********************************************oled显示处理*********************************/
void oled_task()
{
switch(oled_flag)
{
case 0:oled_zhu();       break;
case 1:Oled_mode(Cmode);  break;
case 2:Oled_cai(Ye,Xu);  break;
case 3:Oled_taste(kw);   break;
case 4:Oled_cha();       break;
case 5:Oled_call();      break;
case 6:Oled_callsucc();  break;
case 7:Oled_dianFaill(); break;
case 8: {display.clearDisplay();display.display();}break;
case 9:Oled_dianSuuc();break;
}
}



/*************************************呼叫界面****************************/
void Oled_call()
{
    display.clearDisplay();
    display.drawBitmap(16 * 0, 0, hans_36, 16, 16, 1);//请确定是否呼叫
    display.drawBitmap(16 * 1, 0, hans_2, 16, 16, 1);
    display.drawBitmap(16 * 2, 0, hans_3, 16, 16, 1);
    display.drawBitmap(16 * 3, 0, hans_0, 16, 16, 1);
    display.drawBitmap(16 * 4, 0, hans_1, 16, 16, 1);
    display.drawBitmap(16 * 5, 0, hans_26, 16, 16, 1);
    display.drawBitmap(16 * 6, 0, hans_27, 16, 16, 1);
      display.setCursor(16*7, 0);        
      display.print("?");  
    display.drawBitmap(16 * 0, 48, hans_2, 16, 16, 1);//确定取消
    display.drawBitmap(16 * 1, 48, hans_3, 16, 16, 1);
    display.drawBitmap(16 * 6, 48, hans_4, 16, 16, 1);
    display.drawBitmap(16 * 7, 48, hans_5, 16, 16, 1); 
    display.display();//*显示
}


/*********************************呼叫中操作*****************************/
void Oled_callsucc()
{

    display.clearDisplay();
    display.drawBitmap(16 * 2, 16, hans_26, 16, 16, 1);//呼叫中
    display.drawBitmap(16 * 3, 16, hans_27, 16, 16, 1);
    display.drawBitmap(16 * 4, 16, hans_37, 16, 16, 1);
    display.display();//*显示
for(char i=0;i<10;i++)
{  /****加呼叫功能声光报警*****/

    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
}
    oled_flag=0;
}



////*******点餐失败******************/
void Oled_dianFaill()
{
    display.clearDisplay();
    display.drawBitmap(16 * 2, 16, hans_6, 16, 16, 1);//点餐失败
    display.drawBitmap(16 * 3, 16, hans_7, 16, 16, 1);
    display.drawBitmap(16 * 4, 16, hans_42, 16, 16, 1);
    display.drawBitmap(16 * 5, 16, hans_43, 16, 16, 1);
    display.display();//*显示
    delay(2000);//2s
}



////*******点餐成功******************/
void Oled_dianSuuc()
{
    display.clearDisplay();
    display.drawBitmap(16 * 2, 16, hans_6, 16, 16, 1);//点餐成功
    display.drawBitmap(16 * 3, 16, hans_7, 16, 16, 1);
    display.drawBitmap(16 * 4, 16, hans_8, 16, 16, 1);
    display.drawBitmap(16 * 5, 16, hans_9, 16, 16, 1);
    display.display();//*显示
    delay(2000);//2s
    oled_flag=0;
}



/**********************************主界面*******************************************/
void oled_zhu()
{

    display.clearDisplay();
    display.drawBitmap(20 * 1, 0, hans_6, 16, 16, 1);//点餐系统
    display.drawBitmap(20 * 2, 0, hans_7, 16, 16, 1);
    display.drawBitmap(20 * 3, 0, hans_10, 16, 16, 1);
    display.drawBitmap(20 * 4, 0, hans_11, 16, 16, 1);

    display.drawBitmap(16 * 0, 48, hans_14, 16, 16, 1);//进入关机
    display.drawBitmap(16 * 1, 48, hans_15, 16, 16, 1);

    display.drawBitmap(16 * 6, 48, hans_16, 16, 16, 1);//Serial.println("c9");
    display.drawBitmap(16 * 7, 48, hans_17, 16, 16, 1);  //Serial.println("c10");
    display.display();//*显示
  
     
}

/****************************功能界面*************************************/
void Oled_mode(unsigned char md_flag)
{
    display.clearDisplay();

    display.drawBitmap(20 * 2, 0, hans_6, 16, 16, 1);//点餐
    display.drawBitmap(20 * 3, 0, hans_7, 16, 16, 1);
    
    display.drawBitmap(20 * 2, 16, hans_24, 16, 16, 1);//查询
    display.drawBitmap(20 * 3, 16, hans_25, 16, 16, 1);
    
    display.drawBitmap(20 * 2, 32, hans_26, 16, 16, 1);//呼叫
    display.drawBitmap(20 * 3, 32, hans_27, 16, 16, 1);

    display.drawBitmap(16 * 0, 48, hans_2, 16, 16, 1);//确定取消
    display.drawBitmap(16 * 1, 48, hans_3, 16, 16, 1);
    display.drawBitmap(16 * 6, 48, hans_4, 16, 16, 1);
    display.drawBitmap(16 * 7, 48, hans_5, 16, 16, 1);  
    
      display.setCursor(20 *4, 16*md_flag+5);        
      display.print("<");  
    display.display();//*显示
 
    

}


/***********************************菜单界面*********************
参数：ye：页面:0-1
xu：序号：0-3
**/
void Oled_cai(unsigned char ye,unsigned char xu)
{

  if(ye==0)  
  {   
     display.setTextSize(2);  //设置字体大小
    display.clearDisplay();
    display.drawBitmap(16 * 0, 0, hans_te, 16, 16, 1);//特色鱼头
    display.drawBitmap(16 * 1, 0, hans_se, 16, 16, 1);
    display.drawBitmap(16 * 2, 0, hans_yu, 16, 16, 1);
    display.drawBitmap(16 * 3, 0, hans_tou, 16, 16, 1);
    display.drawBitmap(16 * 6, 0, hans_38, 16, 16, 1);
    display.setCursor(16 *4-4, 0);        
    display.print(":");
    display.print(89);

    display.drawBitmap(16 * 0, 16, hans_fei, 16, 16, 1);//飞刀牛肉
    display.drawBitmap(16 * 1, 16, hans_dao, 16, 16, 1);
    display.drawBitmap(16 * 2, 16, hans_nui, 16, 16, 1);
    display.drawBitmap(16 * 3, 16, hans_rou, 16, 16, 1);
    display.drawBitmap(16 * 6, 16, hans_38, 16, 16, 1);
          display.setCursor(16 *4-4, 16);        
    display.print(":");
  display.print(38);

    display.drawBitmap(16 * 0, 32, hans_guo, 16, 16, 1);//锅包肉
    display.drawBitmap(16 * 1, 32, hans_bao, 16, 16, 1);
    display.drawBitmap(16 * 2, 32, hans_rou, 16, 16, 1);
    display.drawBitmap(16 * 6, 32, hans_38, 16, 16, 1);
    display.setCursor(16 *4-4, 32);        
    display.print(":");
display.print(26);

    display.drawBitmap(16 * 0, 48, hans_ba, 16, 16, 1);//八仙过海
    display.drawBitmap(16 * 1, 48, hans_xian, 16, 16, 1);
    display.drawBitmap(16 * 2, 48, hans_guoo, 16, 16, 1);
    display.drawBitmap(16 * 3, 48, hans_hai, 16, 16, 1);
    display.drawBitmap(16 * 6, 48, hans_38, 16, 16, 1);
        display.setCursor(16 *4-4, 48);        
    display.print(":");
    display.print(99);
  }
    else{
       display.setTextSize(2);  //设置字体大小
    display.clearDisplay();
    display.drawBitmap(16 * 0, 0, hans_shi, 16, 16, 1);//柿子鸡蛋
    display.drawBitmap(16 * 1, 0, hans_zi, 16, 16, 1);
    display.drawBitmap(16 * 2, 0, hans_ji, 16, 16, 1);
    display.drawBitmap(16 * 3, 0, hans_dan, 16, 16, 1);
    display.drawBitmap(16 * 6, 0, hans_38, 16, 16, 1);
        display.setCursor(16 *4-4, 0);        
    display.print(":");
    display.print(15);
    
    display.drawBitmap(16 * 0, 16, hans_ba1, 16, 16, 1);//拔丝紫薯
    display.drawBitmap(16 * 1, 16, hans_si, 16, 16, 1);
    display.drawBitmap(16 * 2, 16, hans_zie, 16, 16, 1);
    display.drawBitmap(16 * 3, 16, hans_shu, 16, 16, 1);
    display.drawBitmap(16 * 6, 16, hans_38, 16, 16, 1);
    display.setCursor(16 *4-4, 16);        
    display.print(":");
      display.print(20);
      
    display.drawBitmap(16 * 0, 32, hans_la, 16, 16, 1);//腊八排骨
    display.drawBitmap(16 * 1, 32, hans_ba, 16, 16, 1);
    display.drawBitmap(16 * 2, 32, hans_pai, 16, 16, 1);
    display.drawBitmap(16 * 3, 32, hans_gu, 16, 16, 1);
    display.drawBitmap(16 * 6, 32, hans_38, 16, 16, 1);    
    display.setCursor(16 *4-4, 32);        
    display.print(":");
    display.print(35);
    
    display.drawBitmap(16 * 0, 48, hans_shang, 16, 16, 1);//上汤牛肉
    display.drawBitmap(16 * 1, 48, hans_tang, 16, 16, 1);
    display.drawBitmap(16 * 2, 48, hans_nui, 16, 16, 1);
    display.drawBitmap(16 * 3, 48, hans_rou, 16, 16, 1);
    display.drawBitmap(16 * 6, 48, hans_38, 16, 16, 1);
    display.setCursor(16 *4-4, 48);        
    display.print(":");
    display.print(39);    
    }  

       display.setTextSize(1.5);  //设置字体大小
      display.setCursor(16*7+8, 16*xu+5);        
      display.print("<"); 

   display.display();//*显示
   
}
/***********************口味选择界面**************************************/
void Oled_taste(unsigned char kw_flag)
{
  display.setTextSize(2);  //设置字体大小
     display.clearDisplay();
    display.drawBitmap(20 * 1, 0, hans_28, 16, 16, 1);//口味选择
    display.drawBitmap(20 * 2, 0, hans_29, 16, 16, 1);
    display.drawBitmap(20 * 3, 0, hans_30, 16, 16, 1);
    display.drawBitmap(20 * 4, 0, hans_31, 16, 16, 1);

    display.drawBitmap(16 * 0, 16, hans_32, 16, 16, 1);//微辣
    display.drawBitmap(16 * 1, 16, hans_33, 16, 16, 1);
 
    display.drawBitmap(16 * 3, 16, hans_34, 16, 16, 1);//中
    display.drawBitmap(16 * 4, 16, hans_33, 16, 16, 1);
 
    display.drawBitmap(16 * 6, 16, hans_35, 16, 16, 1);//特辣
    display.drawBitmap(16 * 7, 16, hans_33, 16, 16, 1); 
    
        display.drawBitmap(0, 48, hans_40, 16, 16, 1);//数量
    display.drawBitmap(16, 48, hans_41, 16, 16, 1);     
    display.setCursor(32, 48);  
    display.print(":");     
    display.print(temp);  
    display.drawBitmap(64, 48, hans_39, 16, 16, 1);//份：
 
     
      display.setCursor(kw_flag*16, 35);        
      display.print("^");  
    display.display();//*显示

}


/***********************************查询界面*********************************/
void Oled_cha()
{ 
    display.clearDisplay();
    display.setTextSize(2);  //设置字体大小
    ge_fg=sever_date();//保存有效菜单
if(ge_fg==0)
{
  display.drawBitmap(20 * 1, 0, hans_18, 16, 16, 1);//已点菜单
  display.drawBitmap(20 * 2, 0, hans_19, 16, 16, 1);
  display.drawBitmap(20 * 3, 0, hans_20, 16, 16, 1);
  display.drawBitmap(20 * 4, 0, hans_21, 16, 16, 1);
  display.drawBitmap(16 * 3, 32, hans_23, 16, 16, 1);
  display.display();//*显示
  delay(3000);
  display.clearDisplay();
    oled_flag=1;
   display.display();//*更新显示
}
else   cha_task();
       
      

}


/******选择汉字***********************
*参数1：菜品id
*参数2：第几个字
*返回汉字   */
void hanzi_xz(unsigned char id,int wz)
{

  switch(id)
  {
    case 0:
         {
               display.drawBitmap(16 * 0, wz,hans_te, 16, 16, 1);
               display.drawBitmap(16 * 1, wz,hans_se, 16, 16, 1) ;
               display.drawBitmap(16 * 2, wz,hans_yu, 16, 16, 1);
               display.drawBitmap(16 * 3, wz,hans_tou, 16, 16, 1);
         
         }break;

    case 1:
         {

                display.drawBitmap(16 * 0, wz,hans_fei, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_dao, 16, 16, 1) ;
                display.drawBitmap(16 * 2, wz,hans_nui, 16, 16, 1);
                display.drawBitmap(16 * 3, wz,hans_rou, 16, 16, 1);               
        
         }break;

        case 2:
         {

                display.drawBitmap(16 * 0, wz,hans_guo, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_bao, 16, 16, 1) ;
                display.drawBitmap(16 * 2, wz,hans_rou, 16, 16, 1);
                 
         }break;

          case 3:
         {
                display.drawBitmap(16 * 0, wz,hans_ba, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_xian, 16, 16, 1) ;
                display.drawBitmap(16 * 2, wz,hans_guoo, 16, 16, 1);
                display.drawBitmap(16 * 3, wz,hans_hai, 16, 16, 1);
                    
         }break;

          case 4:
         {

                display.drawBitmap(16 * 0, wz,hans_shi, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_zi, 16, 16, 1) ;
                display.drawBitmap(16 * 2, wz,hans_ji, 16, 16, 1);
                display.drawBitmap(16 * 3, wz,hans_dan, 16, 16, 1); 
                       
         }break;

          case 5:
         {

                display.drawBitmap(16 * 0, wz,hans_ba1, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_si, 16, 16, 1) ;
                display.drawBitmap(16 * 2, wz,hans_zie, 16, 16, 1);
                display.drawBitmap(16 * 3, wz,hans_shu, 16, 16, 1);
                        
         }break;

          case 6:
         {

                display.drawBitmap(16 * 0, wz,hans_la, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_ba, 16, 16, 1);
                display.drawBitmap(16 * 2, wz,hans_pai, 16, 16, 1);
                display.drawBitmap(16 * 3, wz,hans_gu, 16, 16, 1);
                        
         }break;

          case 7:
         {

                display.drawBitmap(16 * 0, wz,hans_shang, 16, 16, 1);
                display.drawBitmap(16 * 1, wz,hans_tang, 16, 16, 1) ;
                display.drawBitmap(16 * 2, wz,hans_nui, 16, 16, 1);
                display.drawBitmap(16 * 3, wz,hans_rou, 16, 16, 1);
                       
         }break;
  }
}




//******************************查询函数**************/

void less_3(unsigned char ge_fg)
{

   int wz=0;
   display.setTextSize(2);  //设置字体大小
   display.clearDisplay();
   display.drawBitmap(20 * 1, 0, hans_18, 16, 16, 1);//已点菜单
   display.drawBitmap(20 * 2, 0, hans_19, 16, 16, 1);
   display.drawBitmap(20 * 3, 0, hans_20, 16, 16, 1);
   display.drawBitmap(20 * 4, 0, hans_21, 16, 16, 1);
    for(char i=0;i<ge_fg;i++)
    {
    //遍历去显示他们
        wz+=16;
        hanzi_xz(arr1[i].Id,wz); 
    display.drawBitmap(18 * 5, wz, hans_39, 16, 16, 1);//份
  display.setCursor(16 *4, wz);        
    display.print(":");
    //display.print(arr1[i].Id);//测试
    display.print(arr1[i].num);//数量 

    switch(arr1[i].kou) 
    {
      case 1: display.drawBitmap(16 * 7, wz, hans_32, 16, 16, 1);break;//微辣
      case 2: display.drawBitmap(16 * 7, wz, hans_34, 16, 16, 1);break;//中辣
      case 3: display.drawBitmap(16 * 7, wz, hans_35, 16, 16, 1);break;//特辣
    }
    } 
    display.display();//*显示  

}





void More_3()
{
     int wz_4=0;
    display.clearDisplay();    
    for(char i=3;i<ge_fg;i++)
    {
    hanzi_xz(arr1[i].Id,wz_4); 
    display.drawBitmap(18 * 5, wz_4, hans_39, 16, 16, 1);//份
    display.setCursor(16 *4, wz_4);        
    display.print(":");
    //display.print(arr1[i].Id);//测试
    display.print(arr1[i].num);//数量 
    switch(arr1[i].kou) 
    {
      case 1: display.drawBitmap(16 * 7, wz_4, hans_32, 16, 16, 1);break;//微辣
      case 2: display.drawBitmap(16 * 7, wz_4, hans_34, 16, 16, 1);break;//中辣
      case 3: display.drawBitmap(16 * 7, wz_4, hans_35, 16, 16, 1);break;//特辣
    }
       wz_4+=16; 
    } 
    display.display();//*更新显示 
}







//******************************查询函数**************/
void cha_task()
{

  if(ge_fg<=3)
  {
  less_3(ge_fg);
  }

  else{

   if(cha_fg==0) less_3(3);//先显示前三
    else More_3();//后显示后面
     }
}






/***********************************对应赋值菜品*************************************/
void cai_id()
{
   if(Ye==0)
   {
    switch(Xu) 
    {
    case 0:arr[0].num=temp;arr[0].kou=x;break;
    case 1:arr[1].num=temp;arr[1].kou=x;break;    
    case 2:arr[2].num=temp;arr[2].kou=x;break;
    case 3:arr[3].num=temp;arr[3].kou=x;break;
    }       
   }else {
       switch(Xu) 
    {
    case 0:arr[4].num=temp;arr[4].kou=x;break;
    case 1:arr[5].num=temp;arr[5].kou=x;break;    
    case 2:arr[6].num=temp;arr[6].kou=x;break;
    case 3:arr[7].num=temp;arr[7].kou=x;break;
    } 
   }
}


#endif
