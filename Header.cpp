#include "Header.h"

bool lose = 0;
bool exitConfirm = 0;
bool rightMovable = 1;
bool leftMovable = 1;
bool upMovable = 1;
bool downMovable = 1;
bool restartConfirm = 0;

int getoperation(int arr[][4])
{
	isrightmovable(arr);
	isleftmovable(arr);
	isupmovable(arr);
	isdownmovable(arr);
	printgrid(arr);
		if (!leftMovable && !rightMovable && !upMovable && !downMovable) {
			lose = 1;
		}

	char ch;
	while (ch = getch()) {//按ESC即退出

		switch (ch)
		{
		case 0x1b: 
			if(exitConfirm)
				return -1;
			exitConfirm = 1;
			printgrid(arr);
			break;
		case -32:
			exitConfirm = 0;
			switch (ch = getch())
			{
			case 72:  return 1;//UP
			case 80:  return 2;//DOWN
			case 75:  return 3;//LEFT
			case 77:  return 4;//RIGHT
			case -123: return 9;//F11
			case -122: return 0;//F12
			default: return -9;
			}
		default: 
			exitConfirm = 0;
			return -9;
		}

	}
	return -2;//no operation.
}
//打印网格
void printgrid(int arr[4][4]) {
	//cout << "haha" << endl;
	system("cls");
	for (int i = 0; i != 4; i++) {
		for (int j = 0; j != 4; j++)
			cout <<setw(6)<< arr[i][j];
		cout << endl;
	}
	if (restartConfirm) {
		cout << endl << "    Press again to restart." << endl << endl;
	}
	/*else
		printgrid(arr);*/
	if(lose)
		cout << endl << "           You lose" << endl << endl;
	if (exitConfirm)
		cout << endl << "     Press again to exit." << endl << endl;

//##############################################
	cout << " Right movable: " << boolalpha << rightMovable << endl;
	cout << " Left movable: " << boolalpha << leftMovable << endl;
	cout << " Up movable: " << boolalpha << upMovable << endl;
	cout << " Down movable: " << boolalpha << downMovable << endl;
//##############################################

}
//初始化网格
void gridinit(int arr[4][4]) {
	cout << "haha" << endl;
	for (int i = 0; i != 4; i++) {
		for (int j = 0; j != 4; j++)
			arr[i][j] = 0;
		cout << "runned " << i+1 << " times" << endl;
	}
	int count = 0, x, y;
	while (count != 2)
	{
		x = rand() % 4;
		y = rand() % 4;
		//cout << x << " " << y << endl;
		if (arr[x][y] == 0) {
			arr[x][y] = 2;
			count++;
		}
	}
}


//******************************************************
//                 获取移动命令，调用移动函数
//******************************************************

void gridmanip(int arr[][4], int operation)
{
		switch (operation) {
		case 0:
			if (restartConfirm) {
				gridinit(arr);
				restartConfirm = 0;
				lose = 0;
			}
			else {
				restartConfirm = 1;
			}
			break;
		case 1: //UP
			if (!lose && upMovable) {
				moveup(arr);
			}
			restartConfirm = 0;
			break;
		case 2: //DOWN
			if(!lose && downMovable){
				movedown(arr);
			}
			restartConfirm = 0;
			break;
		case 3: //LEFT
			if(!lose && leftMovable){
				moveleft(arr);
			}
			restartConfirm = 0;
			break;
		case 4: //RIGHT
			if (!lose && rightMovable) {
				moveright(arr);
			}
			restartConfirm = 0;
			break;
		default:
			restartConfirm = 0;
			break;
		}

		/*if (restartConfirm) {
			cout << endl << "    Press again to restart." << endl;
		}
		else
			printgrid(arr);*/
	
}

//******************************************************
//                 向四个方向移动的具体方法
//******************************************************

void moveright(int arr[][4]) {

	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 3; j != 0; j--) {//列游标
			//从右向左寻找相同数字，若当前位置数字为零，则跳过当前位置，继续查看下一位置。
			if (arr[i][j] == 0)
				continue;
			//当前数字不为零，从当前数字左一位开始继续向左找，遇到不同数字即停止，遇到相同数字则将
			//当前位置乘二，将这个相同数字置零，并退回到列游标处。
			for (int k = j-1; k != -1; k--) {
				if (arr[i][k] != 0 && arr[i][k] != arr[i][j])
					break;
				if (arr[i][j] == arr[i][k]) {
					arr[i][j] *= 2;
					arr[i][k] = 0;
					break;
				}
			}
		}
	}
	printgrid(arr);
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 3; (j != -1); j--) {//列游标
			if (arr[i][j] != 0) {
				int k = 0;
				for (k = j + 1; (k < 4) && (arr[i][k] == 0); k++);
				if (k - 1 != j) {
					arr[i][k - 1] = arr[i][j];
					arr[i][j] = 0;
				}
			}
		}
	}
	//给非零处新增2。
	newelement(arr);
}
void moveleft(int arr[][4]) {
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 0; j != 4; j++) {//列游标
			//从左向右寻找相同数字，若当前位置数字为零，则跳过当前位置，继续查看下一位置。
			if (arr[i][j] == 0)
				continue;
			//当前数字不为零，从当前数字右一位开始继续向右找，遇到不同数字即停止，遇到相同数字则将
			//当前位置乘二，将这个相同数字置零，并退回到列游标处。
			for (int k = j + 1; k != 4; k++) {
				if (arr[i][k] != 0 && arr[i][k] != arr[i][j])
					break;
				if (arr[i][j] == arr[i][k]) {
					arr[i][j] *= 2;
					arr[i][k] = 0;
					break;
				}
			}
		}
	}
	printgrid(arr);
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 0; j != 4; j++) {//列游标
			if (arr[i][j] != 0) {
				int k = 0;
				for (k = j - 1; (k > -1) && (arr[i][k] == 0); k--);
				if (k + 1 != j) {
					arr[i][k + 1] = arr[i][j];
					arr[i][j] = 0;
				}
			}
		}
	}
	//给非零处新增2。
	newelement(arr);
}
void movedown(int arr[][4]) {
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 3; i != -1; i--) {//行游标
			//从下向上寻找相同数字，若当前位置数字为零，则跳过当前位置，继续查看下一位置。
			if (arr[i][j] == 0)
				continue;
			//当前数字不为零，从当前数字上方一位开始继续向上找，遇到不同数字即停止，遇到相同数字则将
			//当前位置乘二，将这个相同数字置零，并退回到列游标处。
			for (int k = i - 1; k != -1; k--) {
				if (arr[k][j] != 0 && arr[k][j] != arr[i][j])
					break;
				if (arr[i][j] == arr[k][j]) {
					arr[i][j] *= 2;
					arr[k][j] = 0;
					//cout << k << " , " << j << " 置零" << endl;
					break;
				}
			}
		}
	}
	//getch();
	printgrid(arr);
	//从下向上逐位移动
	for (int j = 0; j != 4; j++) {//列游标
		//cout << j << "列:" << endl;
		for (int i = 3; i != -1; i--) {//行游标
			if (arr[i][j] != 0) {
				//cout << " " << i << " 行不为零" << endl;
				int k = 0;
				for (k = i + 1; (k < 4) && (arr[k][j] == 0); k++);
				//cout << "  from " << i << " to " << k - 1 << endl;
				if (k - 1 != i) {
					arr[k-1][j] = arr[i][j];
					arr[i][j] = 0;
				//cout << "yidongzhong" << i << " , " << j << " 置零" << endl;
				}
			}
		}
	}
	//给非零处新增2。
	newelement(arr);
}
void moveup(int arr[][4]) {
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 0; i != 4; i++) {//行游标
			//从上向下寻找相同数字，若当前位置数字为零，则跳过当前位置，继续查看下一位置。
			if (arr[i][j] == 0)
				continue;
			//当前数字不为零，从当前数字下方一位开始继续向下找，遇到不同数字即停止，遇到相同数字则将
			//当前位置乘二，将这个相同数字置零，并退回到列游标处。
			for (int k = i + 1; k != 4; k++) {
				if (arr[k][j] != 0 && arr[k][j] != arr[i][j])
					break;
				if (arr[i][j] == arr[k][j]) {
					arr[i][j] *= 2;
					arr[k][j] = 0;
					break;
				}
			}
		}
	}
	printgrid(arr);
	//从上向下逐位移动
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 0; i != 4; i++) {//行游标
			if (arr[i][j] != 0) {
				int k = 0;
				for (k = i - 1; (k > -1) && (arr[k][j] == 0); k--);
				if (k + 1 != i) {
					arr[k + 1][j] = arr[i][j];
					arr[i][j] = 0;
				}
			}
		}
	}
	//给非零处新增2。
	newelement(arr);
}

//******************************************************
//                 能否移动的判断函数
//******************************************************

void isrightmovable(int arr[][4]){
	bool isZeroExist = 0;
	bool isDuplicationExist = 0;
	//搜索有效0
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 0; j != 4; j++) {//列游标
			if (arr[i][j] != 0) {
				for (int k = j + 1; k != 4; k++) {
					if (arr[i][k] == 0) {
						isZeroExist = 1;
					}
				}
			}
		}
	}
	//搜索有效重复
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 3; j != 0; j--) {//列游标
			if (arr[i][j] == 0)
				continue;
			for (int k = j - 1; k != -1; k--) {
				if (arr[i][k] == 0)
					continue;
				else if (arr[i][k] != arr[i][j])
					break;
				else
					isDuplicationExist = 1;
			}
		}
	}
	if (isZeroExist || isDuplicationExist)
		rightMovable = 1;
	else
		rightMovable = 0;
}
void isleftmovable(int arr[][4]){
	bool isZeroExist = 0;
	bool isDuplicationExist = 0;
	//搜索有效0
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 3; j != -1; j--) {//列游标
			if (arr[i][j] != 0) {
				for (int k = j - 1; k != -1; k--) {
					if (arr[i][k] == 0) {
						isZeroExist = 1;
					}
				}
			}
		}
	}
	//搜索有效重复
	for (int i = 0; i != 4; i++) {//行游标
		for (int j = 0; j != 3; j++) {//列游标
			if (arr[i][j] == 0)
				continue;
			for (int k = j + 1; k != 4; k++) {
				if (arr[i][k] == 0)
					continue;
				else if (arr[i][k] != arr[i][j])
					break;
				else
					isDuplicationExist = 1;
			}
		}
	}
	if (isZeroExist || isDuplicationExist)
		leftMovable = 1;
	else
		leftMovable = 0;
}
void isupmovable(int arr[][4]){
	bool isZeroExist = 0;
	bool isDuplicationExist = 0;
	//搜索有效0
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 3; i != -1; i--) {//行游标
			if (arr[i][j] != 0) {
				for (int k = i - 1; k != -1; k--) {
					if (arr[k][j] == 0) {
						isZeroExist = 1;
					}
				}
			}
		}
	}
	//搜索有效重复
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 0; i != 4; i++) {//行游标
			if (arr[i][j] == 0)
				continue;
			for (int k = i + 1; k != 4; k++) {
				if (arr[k][j] == 0)
					continue;
				else if (arr[k][j] != arr[i][j])
					break;
				else
					isDuplicationExist = 1;
			}
		}
	}
	if (isZeroExist || isDuplicationExist)
		upMovable = 1;
	else
		upMovable = 0;
}

void isdownmovable(int arr[][4]){
	bool isZeroExist = 0;
	bool isDuplicationExist = 0;
	//搜索有效0
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 0; i != 4; i++) {//行游标
			if (arr[i][j] != 0) {
				for (int k = i + 1; k != 4; k++) {
					if (arr[k][j] == 0) {
						isZeroExist = 1;
					}
				}
			}
		}
	}
	//搜索有效重复
	for (int j = 0; j != 4; j++) {//列游标
		for (int i = 3; i != -1; i--) {//行游标
			if (arr[i][j] == 0)
				continue;
			for (int k = i - 1; k != -1; k--) {
				if (arr[k][j] == 0)
					continue;
				else if (arr[k][j] != arr[i][j])
					break;
				else
					isDuplicationExist = 1;
			}
		}
	}
	if (isZeroExist || isDuplicationExist)
		downMovable = 1;
	else
		downMovable = 0;
}

//每走一步，给网格增添一个数字
void newelement(int arr[][4]) {
	int Zero = 0, fourAva = 0;
	for (int i = 0; i != 4; i++)
		for (int j = 0; j != 4; j++) {
			if (arr[i][j] == 0)
				Zero++;
			if (arr[i][j] == 4)
				fourAva = 1;
		}
	int count = 0, x, y;
	if (Zero)
	{
		while (!count) {
			x = rand() % 4;
			y = rand() % 4;
			//cout << x << " " << y << endl;
			if (arr[x][y] == 0 && !fourAva) {
				arr[x][y] = 2;
				count++;
			}
			else if(arr[x][y] == 0 && fourAva)
			{
				//规定出现4的概率为0.1
				arr[x][y] = ((rand() % 10 == 9) ? 4 : 2);
				count++;
			}
		}
	}
}