#pragma once
#include "stack.h"
#include "iostream"
#include "../imgui/imgui_impl_dx12.h"
#include "../imgui/imgui.h"
#include <vector>


class MAZE
{
private:
	int rows, cols;	// 迷宫矩阵的长和宽
	int** maze;		// 存储迷宫
	STACK stack;	// 存储路径
	std::string path;	// 存储路径

	bool isValid(int x, int y) {
		return (x >= 0 && x <= rows + 1 && y >= 0 && y <= cols + 1 && maze[x][y] == 1);
	}

public:
	MAZE();
	MAZE(int x1, int y1);
	MAZE(const MAZE&);		// 拷贝构造函数
	~MAZE();

	void set_maze_boundary();	// 设置迷宫边界 为 1
	void random_maze();		// 随机数随机生成迷宫
	void DFS_maze();		// DFS 生成迷宫

	bool DFS();			// 找到路径
	void path_dis();	// 输出找到的路径

	void set_rows(int r);	// 设置 rows
	void set_cols(int c);	// 设置 cols
	void clear_maze();		// 清空迷宫
	void set_maze(int** m, int row, int col);	// 设置maze
	void set_maze(int maze_x, int maze_y);
	void dis_maze();		// 显示迷宫
	void render_maze();		// 绘制迷宫
};