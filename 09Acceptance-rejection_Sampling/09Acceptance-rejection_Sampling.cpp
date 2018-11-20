#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807随机数产生器最大随机数数量
#define PI 3.1415926
#define C 0.92153762 //计算得到的Lorentz Like分布满足抽样条件的最小系数
#define BLOCK 100 //直方图块数

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double xs[NUM_16807], ys[NUM_16807]; //用来保存随机数
double sample[NUM_16807]; //用来保存抽样数据
int counts[BLOCK] = { 0 }; //用来保存分段数据



 //16807随机数产生器：输入输入生成的随机数的数组x、随机数数量num和起始点start，将16807随机数产生器产生的随机数保存在一维数组中
void RNG_16807(double x[], int num, int start) {
	int i;
	x[0] = double(start) / m;

	//根据Schrage方法和16807随机数产生器产生随机数
	for (i = 1; i < num; i++) {
		start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m);
		x[i] = double(start) / m;
	}
}



//Lorentz-like 的累计函数
double CumulativeFunction(double x) {
	return ((2 * atan(1 + sqrt(2)*x) - 2 * atan(1 - sqrt(2)*x) + log((x*x + sqrt(2)*x + 1) / (x*x - sqrt(2)*x + 1))) / (4 * PI) + 1.0 / 2);
}



int main() {
	double x, y1, y2;
	int i, j, n, count, num;
	FILE *file = NULL;
	char filename[20] = {};

	printf("请输入随机数的个数：");
	scanf("%d", &num);

	srand(time(NULL)); //设置随机数种子

	//用16807随机数产生器产生随机数
	RNG_16807(xs, num, 1);
	RNG_16807(ys, num, rand());

	for (i = 0, count = 0; i < num; i++) {
		/*
		//用累计函数的反函数求的抽样（反函数具体选取在报告中）
		if (xs[i] < 0.005299474)
			continue;
		else
			if (xs[i] < 0.164117)
				x = log(xs[i] - 0.005299474) / 2.3;
			else
				if (xs[i] < 0.3651704)
					x = (xs[i] - 0.4858025) / 0.402107;
				else
					if (xs[i] < 0.6348296)
						x = (xs[i] - 0.5) / 0.449432;
					else
						if (xs[i] < 0.835883)
							x = (xs[i] - 0.5141975) / 0.402107;
						else
							if (xs[i] < 0.994700525)
								x = -log(0.994700525 - xs[i]) / 2.3;
							else
								continue;
		*/

		//离散化分布函数，并取对应的中点为x值
		for (j = 0; j < BLOCK; j++)
			if (CumulativeFunction(-3 + j * 6.0 / BLOCK) <= xs[i] && CumulativeFunction(-3 + (j + 1) * 6.0 / BLOCK) > xs[i]) {
				x = -3 + (j + 0.5)*6.0 / BLOCK;
				//计算当前抽样下的两个函数值
				y1 = exp(-x * x / 2) / sqrt(2 * PI);
				y2 = C / (1 + pow(x, 4));

				//舍选：当超过想要抽样的函数时舍弃，否则为抽样值
				if (y1 > y2*ys[i]) {
					sample[count] = x;
					count++;
				}
				break;
			}
				
		/*
		//计算当前抽样下的两个函数值
		y1 = exp(-x * x / 2) / sqrt(2 * PI);
		y2 = C / (1 + pow(x, 4));

		//舍选：当超过想要抽样的函数时舍弃，否则为抽样值
		if (y1 > y2*ys[i]) {
			sample[count] = x;
			count++;
		}
		*/
	}

	//将抽样得到的数打印到文件中
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n\n");
	else {
		fprintf(file, "%lf\n", double(count) / num); //将抽样效率打印到文件中
		fprintf(file, "%d\n", BLOCK); //将直方图块数打印到文件中
		for (i = 0; i < count; i++)
			fprintf(file, "%.10f\n", sample[i]); //将抽样坐标打印到文件中
		fclose(file);
	}

	//在命令行中打印抽样比
	printf("%lf\n", double(count) / num);
	system("pause");
}