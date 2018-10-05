#include<iostream>
#include <string>
using namespace std;

typedef struct Position {
	int x, y, dir;															//位置x,y和前进方向direction
	Position* nextP;

	Position() {
		dir = x = y = -1;
		nextP = NULL;
	}
}*pos;
//-----------链表栈-----------------
typedef class LinkStark {

private:
	pos top;																//上一步位置
	int length;																//步数

public:
	LinkStark(pos entrance) {												//建立栈并加入起点位置
		top = entrance;
		length = 1;
	}
	~LinkStark() {
		delete top;
	}
	pos getTop() {
		return top;
	}
	int getLength() {
		return length;
	}
	void push(pos);
	void pop();
	bool empty() {															//栈的判空
		return top == NULL;
	}
}*StarkNode;

void LinkStark::push(pos in) {												//入栈操作
	in->nextP = top;
	top = in;
	length++;
}

void LinkStark::pop() {														//出栈
	pos out = top;
	top = top->nextP;
	delete out;
	length--;
}

bool reachExit(StarkNode path, pos exit) {									//判断是否到达终点
	return path->getTop()->x == exit->x&&path->getTop()->y == exit->y;
}
//---------建立迷宫-----------------
int** setMize() {
	int m, n;
	cout << "输入迷宫大小（m,n）" << endl;
	cin >> m >> n;
	int**maze = new int*[m + 2];
	for (int i = 0; i <= m + 1; i++) {
		maze[i] = new int[n + 2];
	}

	for (int i = 0; i <= m + 1; i++)
		for (int j = 0; j <= n + 1; j++) {
			cout << "请输入" << "(" << i << "," << j
				<< ") 处状态.0表示通路,1表示墙,在i等于0或" << m + 1
				<< "及j等于0或" << n + 1 << "时，请输入1" << endl;
			cin >> maze[i][j];
		}

	return maze;
}
//---------寻找迷宫路径---------------
StarkNode findPath(int** maze) {
	pos ent = new Position;																//入口
	pos exit = new Position;															//出口
	bool flag;																			//前进标志
	int i;
	cout << "请输入入口位置以及出口位置:(x,y)" << endl;
	cout << "entrance : " ;
	cin >> ent->x >> ent->y;
	cout << "exit : " ;
	cin >> exit->x >> exit->y;
	maze[ent->x][ent->y] = 2;
	maze[exit->x][exit->y] = 0;

	StarkNode path = new LinkStark(ent); 
	while (!reachExit(path, exit)) {													//未到达出口时一直执行
		flag = false;

		for (i = 1; i <= 4; i++) {														//按照上右下左4个方向的顺序前进
			pos step = new Position;
			switch (i)
			{
			case 1: {
				step->y = path->getTop()->y;
				step->x = path->getTop()->x - 1;
				break;
			}
			case 2: {
				step->y = path->getTop()->y + 1;
				step->x = path->getTop()->x;
				break;
			}
			case 3: {
				step->y = path->getTop()->y;
				step->x = path->getTop()->x + 1;
				break;
			}
			case 4: {
				step->y = path->getTop()->y - 1;
				step->x = path->getTop()->x;
				break;
			}
			}

			if (maze[step->x][step->y] == 0) {									//如果下一位置没走过就加入栈并标记为走过，否则进行下一个方向
				path->getTop()->dir = i;
				path->push(step);
				flag = true;
				maze[step->x][step->y] = 2;
				break;
			}
			else { delete step; }
		}
		if (!flag) {															//如果保留原地，则回到上一步
			path->pop();
		}
		if (path->empty()) {													//栈为空则表示没有通路
			cout << "没有通路" << endl;
			return NULL;
		}
	}
	cout << "到达终点" << endl;

	delete exit;
	return path;
}
int main() {
	int** maze = setMize();
	StarkNode path = findPath(maze);
//-----换栈以将原栈倒置------
	if (path) {
		pos top = new Position;												
		top->x = path->getTop()->x;
		top->y = path->getTop()->y;
		top->nextP = path->getTop()->nextP;

		StarkNode box = new LinkStark(top);									//建立新栈，用来储存从入口到出口的路径

		int theLength = path->getLength();
		path->pop();
		for (int i = 1; i < theLength; i++) {								
			top = new Position;
			top->x = path->getTop()->x;
			top->y = path->getTop()->y;
			top->nextP = path->getTop()->nextP;
			top->dir = path->getTop()->dir;
			box->push(top);
			path->pop();
		}

		cout << "路径：";
		for (int i = 1; i < theLength; i++) {								//输出路径
			cout << "(" << box->getTop()->x << "," << box->getTop()->y << "," << box->getTop()->dir << ") --> ";
			box->pop();
		}
		cout << "(" << box->getTop()->x << "," << box->getTop()->y << ",-"  << ")"<<endl;
		delete box;
	}
	else {
		cout << "迷宫不通" << endl;
	}

	delete path;
	system("pause");
	return 0;
}
