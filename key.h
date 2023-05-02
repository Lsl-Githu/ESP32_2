#ifndef _key_h
#define _key_h
#include "oled.h"
#include "UART.h"
#define KEY1 digitalRead(15)
#define KEY2 digitalRead(4)
#define KEY3 digitalRead(5)
#define KEY4 digitalRead(18)


extern unsigned char Cmode;

extern char State;

void LED_Init();
void key_init();
unsigned char KEY_Scan(unsigned char mode);
void key_task();



void LED_Init()
{
    pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
}


/*********************************按键初始化*************************/
void key_init()
{
pinMode(15, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
pinMode(18, INPUT_PULLUP);

}

//***********************************按键扫描**********************************/
unsigned char KEY_Scan(unsigned char mode)
{   
  static unsigned char key_up=1;   /*按键按松开标志，key_up=1为无按键按下，key_up=0为有按键按下*/
  
  if(mode)key_up=1;    //支持连按     
  if(key_up && (KEY1==0||KEY2==0||KEY3==0||KEY4==0))     /*任意一个按键按下*/
  {
    delay(100);    //去抖动 
    key_up=0;        //有按键按下
         if(KEY1==0)return 1;             
    else if(KEY2==0)return 2;
    else if(KEY3==0)return 3;
    else if(KEY4==0)return 4;

  }
  else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1;  /*还是默认电平，说明无按键按下*/      
  return 0;
}



/******按键处理****************/
void key_task()
{

key_val=KEY_Scan(1);

//左按键处理
if((oled_flag==0 || oled_flag==5 || oled_flag==2 || oled_flag==3|| oled_flag==4 || oled_flag==8 ) && key_val==1) 
{
    key_val=0;
    if(oled_flag==0 && Cont_fh==0)oled_flag=1;
    else if(oled_flag==8){
       Cont++;
       if(Cont>=12 && Cont_fh==1){
         Cont=0;oled_flag=0;Cont_fh=0;
       }  
    }
  else if(oled_flag==4){State=1;oled_flag=9;}//上告
  else if(oled_flag==5) oled_flag=6;//确认呼叫
  else if(oled_flag==2) oled_flag=3;//进入口味数量选择
  else if(oled_flag==3)//口味选择点餐
  {
    if(feng_flag==0) 
    {
        if(kw==1) x=1;
        else if(kw==4) x=2;     
        else if(kw==7) x=3;          
        feng_flag=1; 
    }

      else  if(feng_flag==1 && temp!=0) 
        {
            feng_flag=0;
    //上告成功后才执行下面,保存数据这里先为1
       
              cai_id(); 
              temp=0;
              x=0;
              oled_flag=2;    
    /*    else{
                ///点餐失败
                oled_flag=7;    
                temp=0;
                x=0;
                oled_flag=2; 
             }*/
        }
  }
    
}




//右按键  
if( (oled_flag==0 || oled_flag==1 || oled_flag==2  || oled_flag==3 || oled_flag==4 || oled_flag==5 )&& key_val==3) //取消
{
    key_val=0;
  if(oled_flag==0){
    Cont++;
    if(Cont>=10){
      clean_date();//清空菜单
      Cont=0;
      Cont_fh=1;
      oled_flag=8;
    }
  }
  else if(oled_flag==1)oled_flag=0;  
  else if(oled_flag==3) {oled_flag=2; feng_flag=0;temp=0;}
  else oled_flag=1;
    
}  



//上按键
else if((oled_flag==1 || oled_flag==2 || oled_flag==3 || oled_flag==4) && key_val==2){ //上键
    key_val=0;
    if(oled_flag==1)   {if(Cmode>0)Cmode--;} 
   else if(oled_flag==2)   {
         if(Xu==0 && Ye==1)
         {Ye=!Ye;Xu=4;} 
          if(Ye==0 && Xu>0)  Xu--;
          else if(Ye==1 && Xu>0) {           
            Xu--;               
            }   
      } 
 else if(oled_flag==3 )    
{
 if(feng_flag==0){
  if(kw==1)kw=10;
  if(kw>1)kw-=3;
 }
 else{
    if(temp<9)temp++;   
 }
}

else if(oled_flag==4)
{
  cha_fg=0;
}


}


//下按键
else if((oled_flag==1 || oled_flag==2 || oled_flag==3 || oled_flag==4) && key_val==4) {//下键
    key_val=0;
   if(oled_flag==1){ if(Cmode<2)  Cmode++;}
 else  if(oled_flag==2) {
     Xu++;
    if(Xu==4) {Xu=0;Ye=!Ye;}    
   } 
 else if(oled_flag==3)    
{
  if(feng_flag==0)
  {
    kw+=3;
    if(kw==10)kw=1; 
  }
  else{
       if(temp>0)temp--;
  }
 
}

else if(oled_flag==4)
{
  cha_fg=1;
}

}
  

else if(oled_flag==1 && key_val==1 && (Cmode==0 || Cmode==1 || Cmode==2)) {//*功能选择
  key_val=0;
if(Cmode==0)  oled_flag=2;//进入点餐
if(Cmode==1)  oled_flag=4;//*进入查询
if(Cmode==2)  oled_flag=5;//进入呼叫
  }  
       
}



#endif
