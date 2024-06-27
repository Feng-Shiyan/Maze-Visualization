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

MAZE::MAZE(const MAZE& m)		// �������캯��
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

void MAZE::set_maze_boundary()	// �����Թ��߽� Ϊ 1
{

	// ��һ�� �� ���һ��
	for (int j = 0; j < cols + 2; j++)
	{
		maze[0][j] = 1;
		maze[rows + 1][j] = 1;
	}
	// ��һ�� �� ���һ��
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
		std::cout << "�Թ��ѿգ�û�пռ�!" << std::endl;
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
			maze[i][j] = rand() % 2;	// ������� 0 �� 1
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
//		std::vector<std::pair<int, int>> neighbors;	// �ھӽڵ�
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
//	set_maze_boundary();		// �����Թ��߿�
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
	const int incY[4] = { 1, 0, -1, 0 };	// �ڵ� rows �� cols ����������ʾ��һ������

	int x, y, direction;		// x,y ��ʾ��ǰ����·����direction��ʾ��ǰ����һ���ķ���
	NODE temp = { 1, 1, -1 };		// �洢��ջʱ�����ݣ���ʼ����Ϊ��ʼλ��(1,1)��Ĭ�Ϸ��� 0
	int next_rows, next_cols;		// ��һ��������λ��
	stack.stack_Push(temp);	
	
	while (!stack.stack_Empty())
	{
		stack.stack_Pop(temp);
		x = temp.x;
		y = temp.y;
		direction = temp.dir + 1;

		while (direction < 4)	// Ĭ���ĸ����� 0��1��2��3
		{
			next_rows = x + incX[direction];
			next_cols = y + incY[direction];
			if (0 == maze[next_rows][next_cols])  // ��ǰ·������һ��·������
			{
				temp = { x, y, direction };
				
				
				stack.stack_Push(temp);		// ��¼����·��
				maze[x][y] = -1;	// ���Ѿ��߹��Ľڵ���Ϊ -1�� ��ʾ������
				x = next_rows;
				y = next_cols;
				//maze[next_rows][next_cols] = -1;

				if (rows == x && cols == y)	// �������
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

void MAZE::path_dis()		// ����ҵ���·��
{
	std::cout << "���Թ�������ͨ ��" << std::endl;
	stack.stack_dis();
	// stack.stack_Clear();
	//stack.stack_Clear();
}


void MAZE::set_rows(int r)	// ���� rows
{
	rows = r;
}

void MAZE::set_cols(int c)// ���� cols
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

void MAZE::set_maze(int** m, int row, int col)	// ����maze
{
	if (nullptr == m || row <= 0 || col <= 0)
	{
		std::cout << "Invalid maze data or size." << std::endl;
		return;
	}
	clear_maze();	// ����Թ�����
	
	// ���·����Թ�����
	rows = row - 2;			// �Զ����Թ������߽磬��Ҫ�� 2
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

void MAZE::dis_maze()		// ��ʾ�Թ�
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

//void MAZE::render_maze()		// �����Թ�
//{
//	
//	//ImGui::Begin(u8"Maze visualization");
//	float cell_size = 20.0f;		// ÿ����Ԫ��Ĵ�С
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
//			// ��Ӱ�ɫ�߿�
//			ImU32 border_color = IM_COL32(128, 128, 128, 255);
//			draw_list->AddRect(cell_min, cell_max, border_color);
//		}
//	}
//
//	//ImGui::End();
//}

void MAZE::render_maze() // �����Թ�
{
    ImGui::Begin(u8"Maze visualization"); // ȷ������������
    float cell_size = 20.0f; // ÿ����Ԫ��Ĵ�С

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos(); // ʹ��GetCursorScreenPos��ȡ��Ļ�ռ�����

    for (int i = 0; i < rows + 2; ++i)
    {
        for (int j = 0; j < cols + 2; j++)
        {
            ImU32 color = (maze[i][j] == 1) ? IM_COL32(0, 0, 0, 255) : IM_COL32(255, 255, 255, 255);
            ImVec2 cell_min = ImVec2(p.x + j * cell_size, p.y + i * cell_size);
            ImVec2 cell_max = ImVec2(p.x + (j + 1) * cell_size, p.y + (i + 1) * cell_size);
            draw_list->AddRectFilled(cell_min, cell_max, color);

            // ��Ӱ�ɫ�߿�
            ImU32 border_color = IM_COL32(128, 128, 128, 255);
            draw_list->AddRect(cell_min, cell_max, border_color);
        }
    }

    ImGui::End(); // ȷ�����������Ľ���
}
