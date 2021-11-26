#include "key.h"
/*�๦�ܰ���*/

/**********************************/
/*   �жϵ����ͳ��������ذ���״̬  */
/********************************/
u8 key_driver(void)
{
	static u8 key_state =key_state_0,key_time = 0;
	u8 key_press,key_return = N_key;
	
	key_press = KEY1;  //��ȡKEY1��ƽ
	switch(key_state)
	{
		case key_state_0:  //������ʼ״̬
			if(!key_press)key_state = key_state_1; //�������£�״̬ת��������
		break;
		case key_state_1:  //��������
			if(!key_press)
		{
			key_time = 0; key_state=key_state_2; //����������ɣ�������anxious
		}
		else 
			key_state=key_state_0;  //������̧��ת������ʼ״̬
		break;
		case key_state_2:  
		    if(key_press)
		{
			key_return=S_key;  //��ʱ������̧����Ϊ����������S_key
			key_state=key_state_0; //ת������ʼ״̬
		}
		    else if(++key_time>=100) //����Ϊ̧�𣬼�ʱ��10ms��������ѭ��ʱ�䣩
		{
			key_return=L_key;  //����ʱ�����1s����Ϊ����������L_key
			key_state=key_state_3; //ת���������ͷ�װ��
		}
		break;
		case key_state_3:  //�ȴ������ͷ�
			if(key_press)  //���������ͷ�
				key_state=key_state_0;  //״̬ת��Ϊ��ʼ״̬
			break;
	}
	return key_return;  //���ذ���״̬
}

/**************************************/
/* ����key_driver���жϵ�����˫��      */
/*     ������ѭ��10ms����һ��         */
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
				key_times = 0;   //��һ�ε����������أ�����һ��״̬�ж��Ƿ����˫��
				key_m=key_state_1;
			}
			else
				key_return = key_temp;  //�����޼������������ض�Ӧ��־λ
			break;
		case key_state_1:
			if(key_temp == S_key)  //���ֵ���һ�Σ����ʱ��С��500ms��
			{
				key_return = D_key;  //����˫��
				key_m = key_state_0;  //�ص���ʼ��ʼ״̬
			}
			else
			{
				if(++key_times >= 50)    // ����500ms�ڿ϶������Ķ����޼��¼�����Ϊ����>1000ms����1sǰ�Ͳ㷵�صĶ����޼�
				{
					key_return = S_key;    // 500ms��û���ٴγ��ֵ����¼���������һ�εĵ����¼�
					key_m = key_state_0;   // ���س�ʼ״̬
				}
			}
			break;
	}
	return key_return;
}





