#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807随机数产生器最大随机数数量
#define N 114 //总的点数

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double xs[NUM_16807], ys[NUM_16807]; //用来保存随机数
int energy[N], count[N]; //用来保存读取的数据
double p[N]; //用来抽取随机变量




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



int main() {
	FILE *file = NULL;
	int i, j, num, sum, ra_count, xi;
	char filename[20] = {};

	//输入抽样点的个数
	printf("请输入抽样点的个数：");
	scanf("%d", &num);
	

	srand(time(NULL)); //设置随机种子

	//用16807随机数产生器产生随机种子
	RNG_16807(xs, num, rand());
	RNG_16807(ys, num, rand());

	//读取data.TXT中的数据，并且保存数据到energy和count数组中
	file = fopen("data.TXT", "r");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0, sum = 0; i < N; i++) {
			fscanf(file, "%d", &energy[i]); //保存对应的能量到数组中
			fscanf(file, "%d", &count[i]); //保存该能量下的计数到数组中
			sum += count[i]; //计算总计数
		}
		fclose(file);
	}
	


	//直接抽样法

	//保存累计函数的值到数组p中
	for (i = 0; i < N; i++)
		if (i != 0)
			p[i] = p[i - 1] + double(count[i]) / sum;
		else
			p[i] = double(count[i]) / sum;

	//保存直接抽样得到的能量到文件中
	sprintf(filename, "direct_num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0; i < num; i++) //循环随机数
			for (j = 0; j < N; j++) //循环离散分布
				if (xs[i] <= p[j]) { //当随机数小于i处的累计函数时，将该点能量保存到文件中，且进行下一个随机点的循环
					fprintf(file, "%d\n", energy[j]);
					break;
				}
		fclose(file);
	}
	


	//舍选抽样法

	//保存舍选法得到的能量到文件中
	sprintf(filename, "ra_num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0, ra_count = 0; i < num; i++) {//循环随机数
			if (xs[i] <= 141.0 / 341) {
				xi = energy[int(xs[i] * 682 / 3)];
				if (0.015*ys[i] <= double(count[xi - 2900]) / sum) {
					fprintf(file, "%d\n", xi);
					ra_count++;
				}
			}
			else {
				xi = energy[94 + int((xs[i] - 141.0 / 341) * 341 / 10)];
				if (0.100*ys[i] <= double(count[xi - 2900]) / sum) {
					fprintf(file, "%d\n", xi);
					ra_count++;
				}
			}
		}
		fprintf(file, "%f", double(ra_count) / num);
		fclose(file);
	}
}