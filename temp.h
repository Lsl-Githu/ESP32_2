#ifndef _temp_h
#define _temp_h


char  sever_date();
void clean_date();
void CAI_listIinit();

/*unsigned char *name_shu[8]={"特色鱼头","飞刀牛肉","锅包肉","八仙过海",
"柿子鸡蛋","拔丝紫薯","腊八排骨","上汤牛肉"};*/






 struct menu
{
   //char *name;//菜名
   unsigned char num;//数量
   unsigned char  kou;//口味
   unsigned char Id;//编号
}arr[8],arr1[8];


/**********保存数据**************/
char  sever_date()
{
  char ge=0;//有效菜单个数
  for(char j=0;j<8;j++)
  {
     if(arr[j].num>0)
     {
       arr1[ge]=arr[j];
       ge++;
     }  
  }
    return ge;

}

/*******清除数据*****************/
void clean_date()
{
for(char i=0;i<8;i++)
{
  arr[i].num=0;
  arr1[i].num=0;  
}

}

void CAI_listIinit()
{
  /*初始化8个菜品参数：菜名、数量、口味、id*/
for(char i=0;i<8;i++)
{
   // arr[i].name=name_shu[i];
    arr[i].num=0;   
    arr[i].kou=0; 
    arr[i].Id=i;
}
}


#endif
