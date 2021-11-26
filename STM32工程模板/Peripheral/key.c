#include "key.h"
/*多功能按键*/

/**********************************/
/*   判断单击和长按并返回按键状态  */
/********************************/
u8 key_driver(void)
{
	static u8 key_state =key_state_0,key_time = 0;
	u8 key_press,key_return = N_key;
	
	key_press = KEY1;  //读取KEY1电平
	switch(key_state)
	{
		case key_state_0:  //按键初始状态
			if(!key_press)key_state = key_state_1; //按键按下，状态转换到消抖
		break;
		case key_state_1:  //按键消抖
			if(!key_press)
		{
			key_time = 0; key_state=key_state_2; //按键消抖完成，按键任anxious
		}
		else 
			key_state=key_state_0;  //按键已抬起，转换到初始状态
		break;
		case key_state_2:  
		    if(key_press)
		{
			key_return=S_key;  //此时按键已抬起，则为单击，返回S_key
			key_state=key_state_0; //转换到初始状态
		}
		    else if(++key_time>=100) //按键为抬起，计时加10ms（本函数循环时间）
		{
			key_return=L_key;  //按下时间大于1s，则为长按，返回L_key
			key_state=key_state_3; //转换到案件释放装填
		}
		break;
		case key_state_3:  //等待按键释放
			if(key_press)  //若按键被释放
				key_state=key_state_0;  //状态转换为初始状态
			break;
	}
	return key_return;  //返回按键状态
}

/**************************************/
/* 引用key_driver，判断单机或双击      */
/*     本函数循环10ms调用一次         */
/************************************/
u8 key_read(void)
{
	static u8 key_m = key_state_0,key_times = 0;
	u8 key_return = N_key,key_temp;
	
	key_temp = key_driver();
	switch(key_m)
	{
		case key_state_0:
			if(key_temp == S_key)
			{
				key_times = 0;   //第一次单击，不返回，到下一个状态判断是否出现双击
				key_m=key_state_1;
			}
			else
				key_return = key_temp;  //对于无键，长按，返回对应标志位
			break;
		case key_state_1:
			if(key_temp == S_key)  //若又单击一次（间隔时间小于500ms）
			{
				key_return = D_key;  //返回双击
				key_m = key_state_0;  //回到初始初始状态
			}
			else
			{
				if(++key_times >= 50)    // 这里500ms内肯定读到的都是无键事件，因为长键>1000ms，在1s前低层返回的都是无键
				{
					key_return = S_key;    // 500ms内没有再次出现单键事件，返回上一次的单键事件
					key_m = key_state_0;   // 返回初始状态
				}
			}
			break;
	}
	return key_return;
}





