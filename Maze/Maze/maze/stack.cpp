#include "stack.h"
#include <iostream>

// Ĭ�Ϲ��캯��
STACK::STACK() : top(-1)
{
	data = new NODE[MAX_SIZE];
	for (int t = 0; t < MAX_SIZE; t++)
	{
		data[t].x = 0;
		data[t].y = 0;
		data[t].dir = 0;
	}
}

// ����ջ
void STACK::stack_Destroy()
{
	top == -1;
	delete data;
}

// �ж�ջ�Ƿ�Ϊ��
bool STACK::stack_Empty()
{
	return top == -1;
}

// ѹջ
void STACK::stack_Push(NODE elem)
{
	if (top >= MAX_SIZE)
	{
		std::cout << "ջ�Ѿ��� !" << std::endl;
		return;
	}
	else {
		top++;
		data[top] = elem;
	}
}

// ��ջ
void STACK::stack_Pop(NODE& elem)
{
	if (stack_Empty())
	{
		std::cout << "ջ�Ѿ��գ�" << std::endl;
	}
	elem = data[top];
	data[top] = { 0, 0, 0 };
	top--;
}

NODE STACK::stack_Pop()
{
	if (stack_Empty())
	{
		std::cout << "ջ�Ѿ��գ�" << std::endl;
	}
	return data[top--];
}

// ��ȡջ��Ԫ��
NODE STACK::stack_GetTop()
{
	if (stack_Empty())
	{
		std::cout << "ջ�Ѿ��գ�" << std::endl;

	}
	return data[top];
}

void STACK::stack_dis()		// ���ջ������
{
	for (int i = 0; i <= top; i++)
	{
		std::cout << "( " << data[i].x << ", "
			<< data[i].y << ", " << data[i].dir << ") " << std::endl;
	}

}

void STACK::stack_Clear()	// ���ջ
{
	stack_Destroy();
	data = new NODE[MAX_SIZE];
	for (int t = 0; t < MAX_SIZE; t++)
	{
		data[t].x = 0;
		data[t].y = 0;
		data[t].dir = 0;
	}
}