#pragma once

#define MAX_SIZE 1000

typedef struct MYSTRUCT			// ��Ԫ��
{
	int x;
	int y;	// ����
	int dir;		// ��һ��ķ���	
}NODE;

class STACK 
{
private:
	NODE *data;	// �洢·��
	int top;	// ջ��ָ��

public:
	STACK();		// Ĭ�Ϲ��캯��
	void stack_Destroy();				// ����ջ
	bool stack_Empty();					// �ж�ջ�Ƿ�Ϊ��
	void stack_Push(NODE elem);			// ѹջ
	void stack_Pop(NODE &elem);					// ��ջ
	NODE stack_Pop();
	NODE stack_GetTop();				// ��ȡջ��Ԫ��
	void stack_dis();		// ���ջ������
	int get_top() { return top; };	// ���� top ֵ
	NODE get_data(int i) { return data[i]; };	// ���� data ֵ
	void stack_Clear();	// ���ջ
};


