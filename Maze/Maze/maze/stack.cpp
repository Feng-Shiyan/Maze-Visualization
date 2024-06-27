#include "stack.h"
#include <iostream>

// 默认构造函数
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

// 销毁栈
void STACK::stack_Destroy()
{
	top == -1;
	delete data;
}

// 判断栈是否为空
bool STACK::stack_Empty()
{
	return top == -1;
}

// 压栈
void STACK::stack_Push(NODE elem)
{
	if (top >= MAX_SIZE)
	{
		std::cout << "栈已经满 !" << std::endl;
		return;
	}
	else {
		top++;
		data[top] = elem;
	}
}

// 出栈
void STACK::stack_Pop(NODE& elem)
{
	if (stack_Empty())
	{
		std::cout << "栈已经空！" << std::endl;
	}
	elem = data[top];
	data[top] = { 0, 0, 0 };
	top--;
}

NODE STACK::stack_Pop()
{
	if (stack_Empty())
	{
		std::cout << "栈已经空！" << std::endl;
	}
	return data[top--];
}

// 获取栈顶元素
NODE STACK::stack_GetTop()
{
	if (stack_Empty())
	{
		std::cout << "栈已经空！" << std::endl;

	}
	return data[top];
}

void STACK::stack_dis()		// 输出栈的内容
{
	for (int i = 0; i <= top; i++)
	{
		std::cout << "( " << data[i].x << ", "
			<< data[i].y << ", " << data[i].dir << ") " << std::endl;
	}

}

void STACK::stack_Clear()	// 清空栈
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