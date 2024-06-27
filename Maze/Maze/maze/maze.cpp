#include "maze.h"
extern ID3D12GraphicsCommandList* g_pd3dCommandList = nullptr;

MAZE::MAZE() :rows(0), cols(0)
{
	maze = nullptr;
}

MAZE::MAZE(int x1, int y1) : rows(x1), cols(y1)
{
	maze = new int* [rows+2];
	for (int i = 0; i < rows+2; i++)
		maze[i] = new int[cols+2];
	for (int i = 0; i < rows + 2; i++)
		for (int j = 0; j < cols + 2; j++)
			maze[i][j] = 1;
}

MAZE::MAZE(const MAZE& m)		// 拷贝构造函数
{
	for (int i = 0; i < rows + 2; i++)
	{
		delete[] maze[i];
		maze[i] = nullptr;
	}
	//delete[] maze;
	maze = nullptr;

	rows = m.rows;
	cols = m.cols;

	maze = new int* [rows + 2];
	for (int i = 0; i < rows + 2; i++)
		maze[i] = new int[cols + 2];
	for (int i = 0; i < rows + 2; i++)
		for (int j = 0; j < cols + 2; j++)
			maze[i][j] = 1;
}

MAZE::~MAZE()
{
	for (int i = 0; i < rows+2; i++)
	{
		delete[] maze[i];
		maze[i] = nullptr;
	}
	//delete[] maze;
	maze = nullptr;
	rows = 0;
	cols = 0;
	stack.stack_Destroy();
}

void MAZE::set_maze_boundary()	// 设置迷宫边界 为 1
{

	// 第一行 和 最后一行
	for (int j = 0; j < cols + 2; j++)
	{
		maze[0][j] = 1;
		maze[rows + 1][j] = 1;
	}
	// 第一列 和 最后一列
	for (int i = 0; i < rows+ 2; i++)
	{
		maze[i][0] = 1;
		maze[i][cols + 1] = 1;
	}
}

void MAZE::random_maze()
{
	srand(time(0));
	if (rows == 0 || cols == 0) {
		std::cout << "迷宫已空，没有空间!" << std::endl;
		exit(1);
	}
	if (maze) {
		for (int i = 0; i < rows + 2; i++)
			delete[] maze[i];
		maze = nullptr;
	}
	maze = new int* [rows + 2];
	for (int i = 0; i < rows + 2; i++)
		maze[i] = new int[cols + 2];
	for (int i = 1; i < rows + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
			maze[i][j] = rand() % 2;	// 随机生成 0 或 1
	}
	set_maze_boundary();
	maze[1][1] = 0;
	maze[rows][cols] = 0;
}

//void MAZE::DFS_maze()
//{
//	for (int i = 0; i < rows + 2; i++)
//		for (int j = 0; j < cols + 2; j++)
//			maze[i][j] = 1;
//
//	std::vector<std::pair<int, int>> direction = { {0,1}, {1,0},{0,-1},{-1,0} };
//	srand(time(0));
//	maze[1][1] = 0;
//	STACK ss;
//	ss.stack_Push({ 1,1,0 });
//
//	bool foundPath = false;
//
//	while (!ss.stack_Empty()) {
//		auto current = ss.stack_GetTop();
//		int  x = current.x;
//		int  y = current.y;
//
//		if (x == rows && y == cols)
//			foundPath = true;
//
//		std::vector<std::pair<int, int>> neighbors;	// 邻居节点
//		for (auto& dir : direction) {
//			int nx = x + dir.first * 2;
//			int ny = y + dir.second * 2;
//			if (isValid(nx, ny))
//			{
//				neighbors.push_back({ nx,ny});
//			}
//		}
//		if (!neighbors.empty()) {
//			auto next = neighbors[rand() % neighbors.size()];
//			int nx = next.first;
//			int ny = next.second;
//
//			maze[nx][ny] = 0;
//			maze[x + (nx - x) / 2][y + (ny - y) / 2] = 0;
//
//			ss.stack_Push({ nx,ny, 0 });
//		}
//		else {
//			ss.stack_Pop();
//		}
//	}
//
//
//	set_maze_boundary();		// 设置迷宫边框
//	maze[rows][cols] = 0;
//}

void MAZE::DFS_maze() {
        for (int i = 0; i < rows + 2; i++)
            for (int j = 0; j < cols + 2; j++)
                maze[i][j] = 1;

        std::vector<std::pair<int, int>> direction = { {0,1}, {1,0},{0,-1},{-1,0} };
        srand(time(0));
        maze[1][1] = 0;
        STACK ss;
        ss.stack_Push({ 1, 1, 0 });

        while (!ss.stack_Empty()) {
            auto current = ss.stack_GetTop();
            int x = current.x;
            int y = current.y;

            std::vector<std::pair<int, int>> neighbors;
            for (auto& dir : direction) {
                int nx = x + dir.first * 2;
                int ny = y + dir.second * 2;
                if (isValid(nx, ny)) {
                    neighbors.push_back({ nx, ny });
                }
            }
            if (!neighbors.empty()) {
                auto next = neighbors[rand() % neighbors.size()];
                int nx = next.first;
                int ny = next.second;

                maze[nx][ny] = 0;
                maze[x + (nx - x) / 2][y + (ny - y) / 2] = 0;

                ss.stack_Push({ nx, ny, 0 });
            } else {
                ss.stack_Pop();
            }
        }

        set_maze_boundary();
        maze[rows][cols] = 0;
    }

bool MAZE::DFS()
{
	const int incX[4] = { 0, 1, 0, -1 };
	const int incY[4] = { 1, 0, -1, 0 };	// 节点 rows 和 cols 的增量，表示下一步方向

	int x, y, direction;		// x,y 表示当前所在路径，direction表示当前的下一步的方向
	NODE temp = { 1, 1, -1 };		// 存储出栈时的数据，初始数据为起始位置(1,1)，默认方向 0
	int next_rows, next_cols;		// 下一步所到的位置
	stack.stack_Push(temp);	
	
	while (!stack.stack_Empty())
	{
		stack.stack_Pop(temp);
		x = temp.x;
		y = temp.y;
		direction = temp.dir + 1;

		while (direction < 4)	// 默认四个方向 0，1，2，3
		{
			next_rows = x + incX[direction];
			next_cols = y + incY[direction];
			if (0 == maze[next_rows][next_cols])  // 当前路径的下一步路径可走
			{
				temp = { x, y, direction };
				
				
				stack.stack_Push(temp);		// 记录可走路径
				maze[x][y] = -1;	// 将已经走过的节点置为 -1， 表示不可走
				x = next_rows;
				y = next_cols;
				//maze[next_rows][next_cols] = -1;

				if (rows == x && cols == y)	// 到达出口
					return true;
				else
					direction = 0;
			}
			else
				direction++;
		}
	}
	return false;
}

void MAZE::path_dis()		// 输出找到的路径
{
	std::cout << "该迷宫可以走通 ！" << std::endl;
	stack.stack_dis();
	// stack.stack_Clear();
	//stack.stack_Clear();
}


void MAZE::set_rows(int r)	// 设置 rows
{
	rows = r;
}

void MAZE::set_cols(int c)// 设置 cols
{
	cols = c;
}

void MAZE::clear_maze()
{
	if (maze != nullptr)
	{
		for (int i = 0; i < rows + 2; i++)
		{
			delete[] maze[i];
		}
		//delete[] maze;
		maze = nullptr;
		rows = 0;
		cols = 0;
	}
}

void MAZE::set_maze(int** m, int row, int col)	// 设置maze
{
	if (nullptr == m || row <= 0 || col <= 0)
	{
		std::cout << "Invalid maze data or size." << std::endl;
		return;
	}
	clear_maze();	// 清空迷宫数据
	
	// 重新分配迷宫数据
	rows = row - 2;			// 自定义迷宫包含边界，需要减 2
	cols = col - 2;
	maze = new int* [cols + 2];
	for (int i = 0; i < rows + 2; i++)
	{
		maze[i] = new int[cols+2];
		for (int j = 0; j < cols+2; j++)
		{
			(maze[i])[j] = (m[i])[j];
		}
	}
}

void MAZE::set_maze(int maze_x, int maze_y)
{
	set_rows(maze_x);
	set_cols(maze_y);

	maze = new int* [rows+2];
	for (int i = 0; i < rows+2; i++)
		maze[i] = new int[cols+2];
	for (int i = 0; i < rows + 2; i++)
		for (int j = 0; j < cols + 2; j++)
			maze[i][j] = 1;
}

void MAZE::dis_maze()		// 显示迷宫
{
	for (int i = 0; i < rows + 2; i++)
	{
		for (int j = 0; j < cols + 2; j++)
		{
			std::cout << maze[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//void MAZE::render_maze()		// 绘制迷宫
//{
//	
//	//ImGui::Begin(u8"Maze visualization");
//	float cell_size = 20.0f;		// 每个单元格的大小
//	
//	ImDrawList* draw_list = ImGui::GetWindowDrawList();
//	ImVec2 p = ImGui::GetCursorPos();
//
//	for (int i = 0; i < rows+2; ++i)
//	{
//		for (int j = 0; j < cols + 2; j++)
//		{
//			ImU32 color = (maze[i][j] == 1) ? IM_COL32(0, 0, 0, 255) : IM_COL32(255, 255, 255, 255);
//			ImVec2 cell_min = ImVec2(p.x + j * cell_size, p.y + i * cell_size);
//			ImVec2 cell_max = ImVec2(p.x + (j + 1) * cell_size, p.y + (i + 1) * cell_size);
//			draw_list->AddRectFilled(cell_min, cell_max, color);
//
//			// 添加白色边框
//			ImU32 border_color = IM_COL32(128, 128, 128, 255);
//			draw_list->AddRect(cell_min, cell_max, border_color);
//		}
//	}
//
//	//ImGui::End();
//}

void MAZE::render_maze() // 绘制迷宫
{
    ImGui::Begin(u8"Maze visualization"); // 确保窗口上下文
    float cell_size = 20.0f; // 每个单元格的大小

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos(); // 使用GetCursorScreenPos获取屏幕空间坐标

    for (int i = 0; i < rows + 2; ++i)
    {
        for (int j = 0; j < cols + 2; j++)
        {
            ImU32 color = (maze[i][j] == 1) ? IM_COL32(0, 0, 0, 255) : IM_COL32(255, 255, 255, 255);
            ImVec2 cell_min = ImVec2(p.x + j * cell_size, p.y + i * cell_size);
            ImVec2 cell_max = ImVec2(p.x + (j + 1) * cell_size, p.y + (i + 1) * cell_size);
            draw_list->AddRectFilled(cell_min, cell_max, color);

            // 添加白色边框
            ImU32 border_color = IM_COL32(128, 128, 128, 255);
            draw_list->AddRect(cell_min, cell_max, border_color);
        }
    }

    ImGui::End(); // 确保窗口上下文结束
}
