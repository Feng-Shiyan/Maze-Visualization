#pragma once
#include "stack.h"
#include "iostream"
#include "../imgui/imgui_impl_dx12.h"
#include "../imgui/imgui.h"
#include <vector>


class MAZE
{
private:
	int rows, cols;	// �Թ�����ĳ��Ϳ�
	int** maze;		// �洢�Թ�
	STACK stack;	// �洢·��
	std::string path;	// �洢·��

	bool isValid(int x, int y) {
		return (x >= 0 && x <= rows + 1 && y >= 0 && y <= cols + 1 && maze[x][y] == 1);
	}

public:
	MAZE();
	MAZE(int x1, int y1);
	MAZE(const MAZE&);		// �������캯��
	~MAZE();

	void set_maze_boundary();	// �����Թ��߽� Ϊ 1
	void random_maze();		// �������������Թ�
	void DFS_maze();		// DFS �����Թ�

	bool DFS();			// �ҵ�·��
	void path_dis();	// ����ҵ���·��

	void set_rows(int r);	// ���� rows
	void set_cols(int c);	// ���� cols
	void clear_maze();		// ����Թ�
	void set_maze(int** m, int row, int col);	// ����maze
	void set_maze(int maze_x, int maze_y);
	void dis_maze();		// ��ʾ�Թ�
	void render_maze();		// �����Թ�
};