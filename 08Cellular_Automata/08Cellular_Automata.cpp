
//0代表自旋向上，1代表自旋向下

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define LENGTH 512
#define RATIO 0.12

char Spins[LENGTH][LENGTH] = { 0 }; //保存自旋状态的二维数组
int a = 16807, m = 2147483647, r = m % a, q = m / a; //16807随机数产生器相关参数设置


//随机初始化网格
void InitSpins(char Spins[LENGTH][LENGTH], int start, double ratio) {
	int x, y;
	double now = double(start) / m;

	//用随机数初始化网格
	for (x = 0; x < LENGTH; x++)
		for (y = 0; y < LENGTH; y++) {
			//若随机数小于RATIO则自旋向上，否则自旋向下
			if (now < ratio)
				Spins[x][y] = 0;
			else
				Spins[x][y] = 1;

			//16807随机数产生器：输入输入生成的随机数的数组x、随机数数量num和起始点start，将16807随机数产生器产生的随机数保存在一维数组中
			start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m);
			now = double(start) / m;
		}
}



//判断(x,y)处自旋是否要翻转，如果要反转，则返回1，否则返回0。边界条件为周期条件
int WhetherFlip(char Spins[LENGTH][LENGTH], int x, int y) {
	int a = y + 1, b = y - 1, c = x - 1, d = x + 1; //代表上、下、左、右四个位置的坐标
	int count0 = 0, count1 = 0; //代表邻居中为0的个数和为1的个数

	//用周期边界条件重置上、下、左、右的坐标
	if (y == 511)
		a = 0;
	if (y == 0)
		b = 511;
	if (x == 0)
		c = 511;
	if (x == 511)
		d = 0;

	//计算邻居中为0的个数和为1的个数
	count0 = 4 - Spins[x][a] - Spins[x][b] - Spins[c][y] - Spins[d][y];
	count1 = 4 - count0;

	//若邻居中为0的个数等于为1的个数，则表明自旋翻转，返回1，否则返回0
	if (count0 == count1)
		return 1;
	else
		return 0;
}



/*
//判断(x,y)处自旋是否要翻转，如果要反转，则返回1，否则返回0。边界条件为定值条件
int WhetherFlip(char Spins[LENGTH][LENGTH], int x, int y) {
	int a = y + 1, b = y - 1, c = x - 1, d = x + 1; //代表上、下、左、右四个位置的坐标
	int count0 = 0, count1 = 0; //代表邻居中为0的个数和为1的个数

	//用定值边界条件重置上、下、左、右的坐标
	if (y == 511)
		a = 0;
	else
		a = Spins[x][y + 1];
	if (y == 0)
		b = 0;
	else
		b = Spins[x][y - 1];
	if (x == 0)
		c = 0;
	else
		c = Spins[x - 1][y];
	if (x == 511)
		d = 0;
	else
		d = Spins[x + 1][y];

	//计算邻居中为0的个数和为1的个数
	count0 = 4 - a - b - c - d;
	count1 = 4 - count0;

	//若邻居中为0的个数等于为1的个数，则表明自旋翻转，返回1，否则返回0
	if (count0 == count1)
		return 1;
	else
		return 0;
}
*/



//对网格按Q2规则进行一次自旋翻转
void Flip(char Spins[LENGTH][LENGTH]) {
	int x, y, flag;

	//对偶数子格进行翻转
	flag = 0;
	for (x = 0; x < LENGTH; x++) {
		for (y = flag; y < LENGTH; y += 2)
			if (WhetherFlip(Spins, x, y) == 1)
				Spins[x][y] = 1 - Spins[x][y];
		flag = 1 - flag;
	}

	//对奇数数子格进行翻转
	flag = 1;
	for (x = 0; x < LENGTH; x++) {
		for (y = flag; y < LENGTH; y += 2)
			if (WhetherFlip(Spins, x, y) == 1)
				Spins[x][y] = 1 - Spins[x][y];
		flag = 1 - flag;
	}
}



//统计自旋向上的粒子所占的比例
double Calculate(char Spins[LENGTH][LENGTH]) {
	int x, y, count = 0;

	//遍历网格，自旋向上则计数加一
	for (x = 0; x < LENGTH; x++)
		for (y = 0; y < LENGTH; y++)
			if (Spins[x][y] == 0)
				count++;
	return (double(count) / (512 * 512));
}



int main() {
	int num, i, x, y;
	double ratio = RATIO;
	FILE *file = NULL;
	char filename[20] = {};

	//计时程序设置
	clock_t start, finish;
	double totaltime;
	start = clock();

	//输入相关数值
	printf("请输入起始自旋向上所占比例：");
	scanf("%lf", &ratio);
	printf("请输入最大次数：");
	scanf("%d", &num);

	srand(time(NULL)); //设置随机种子
	InitSpins(Spins, rand(), ratio); //初始化网格

	//输出数据到文件中
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		//打印并输出起始状态的数据
		ratio = Calculate(Spins);
		printf("   %.10f\n", ratio);
		for (x = 0; x < LENGTH; x++)
			for (y = 0; y < LENGTH; y++)
				if (y != LENGTH - 1)
					fprintf(file, "%d,", Spins[x][y]);
				else
					fprintf(file, "%d\n", Spins[x][y]);
		for (x = 0; x<LENGTH; x++)
			if (x != LENGTH - 1)
				fprintf(file, "%.10f,", ratio);
			else
				fprintf(file, "%d\n", ratio);

		//进行翻转
		for (i = 0; i < num; i++) {
			Flip(Spins);
			//每次翻转后的数据都输出（可以不需要）
			/*
			for (x = 0; x < LENGTH; x++)
				for (y = 0; y < LENGTH; y++)
					if (y != LENGTH - 1)
						fprintf(file, "%d,", Spins[x][y]);
					else
						fprintf(file, "%d\n", Spins[x][y]);			
			*/
			ratio = Calculate(Spins);
			printf("   %.10f\n", ratio);
		}

		//打印并输出终止状态
		for (x = 0; x < LENGTH; x++)
			for (y = 0; y < LENGTH; y++)
				if (y != LENGTH - 1)
					fprintf(file, "%d,", Spins[x][y]);
				else
					fprintf(file, "%d\n", Spins[x][y]);
		for(x=0;x<LENGTH;x++)
			if (x != LENGTH - 1)
				fprintf(file, "%.10f,", ratio);
			else
				fprintf(file, "%d\n", ratio);

		fclose(file);
	}
	/*
	for (i = 0; i < LENGTH; i++) {
		for (j = 0; j < LENGTH; j++)
			printf("%d", Spins[i][j]);
			printf("\n");
		}
	*/

	//打印总耗时
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n   总共耗时：%f  seconds\n\n", totaltime);

	system("pause");
}