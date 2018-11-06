#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 1000000 //16807随机数产生器最大随机数数量
#define PI 3.1415926 //PI的大小

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double Random1[NUM_16807]; //用来保存theta的抽样
double Random2[NUM_16807]; //用来保存phi的抽样

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



void main() {
	int num, i;
	double sin_theta, cos_theta, phi, x, y, z; //抽样中相关变量
	FILE *file = NULL;
	char filename[20] = {};

	printf("请输入随机数个数：");
	scanf("%d", &num);

	//用16807随机数产生器均匀地随机生成两组随机数，对应theta与phi的抽样
	srand(time(NULL)); //设置随机种子
	RNG_16807(Random1, num, rand());
	RNG_16807(Random2, num, rand());

	//输出数据到文件中
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		for (i = 0; i < num; i++) {
			//简单抽样下变换到theta与phi
			cos_theta = 1 - 2*Random1[i];
			phi = 2 * PI*Random2[i];

			//计算对应点的x、y、z坐标
			x = sqrt(1 - pow(cos_theta, 2))*cos(phi);
			y = sqrt(1 - pow(cos_theta, 2))*sin(phi);
			z = cos_theta;

			//输出x、y、z坐标到文件中
			fprintf(file, "%.15lf,%.15lf,%.15lf\n", x, y, z);
		}
		fclose(file);
	}
}