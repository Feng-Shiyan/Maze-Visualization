#pragma once

#define MAX_SIZE 1000

typedef struct MYSTRUCT			// 三元组
{
	int x;
	int y;	// 坐标
	int dir;		// 下一点的方向	
}NODE;

class STACK 
{
private:
	NODE *data;	// 存储路径
	int top;	// 栈顶指针

public:
	STACK();		// 默认构造函数
	void stack_Destroy();				// 销毁栈
	bool stack_Empty();					// 判断栈是否为空
	void stack_Push(NODE elem);			// 压栈
	void stack_Pop(NODE &elem);					// 出栈
	NODE stack_Pop();
	NODE stack_GetTop();				// 获取栈顶元素
	void stack_dis();		// 输出栈的内容
	int get_top() { return top; };	// 返回 top 值
	NODE get_data(int i) { return data[i]; };	// 返回 data 值
	void stack_Clear();	// 清空栈
};


