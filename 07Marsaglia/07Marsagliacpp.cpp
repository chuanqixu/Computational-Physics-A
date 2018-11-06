#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807随机数产生器最大随机数数量，一般要求小于210000000

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double u[NUM_16807]; //用来保存u的抽样
double v[NUM_16807]; //用来保存v的抽样

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
	int num, i, count = 0;
	double u_now, v_now, r2, x, y, z; //抽样中相关变量
	FILE *file = NULL;
	char filename[20] = {};

	printf("请输入随机数个数：");
	scanf("%d", &num);

	srand(time(NULL)); //设置随机种子

	//输出数据到文件中
	sprintf(filename, "num=%d.txt", num);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		while (count < num) {

			//用16807随机数产生器均匀地随机生成两组随机数，对应u与v的抽样
			RNG_16807(u, NUM_16807, rand());
			RNG_16807(v, NUM_16807, rand());

			for (i = 0; i<NUM_16807; i++) {
				//使16807产生的随机数在[-1,1]区间内重新分布
				u_now = -1 + 2 * u[i];
				v_now = -1 + 2 * v[i];
				r2 = u_now * u_now + v_now * v_now;
				if (r2 <= 1) {
					//计算对应点的x、y、z坐标
					x = 2 * u_now * sqrt(1 - r2);
					y = 2 * v_now * sqrt(1 - r2);
					z = 1 - 2 * r2;

					//输出x、y、z坐标到文件中
					fprintf(file, "%.10lf,%.10lf,%.10lf\n", x, y, z);

					count++; //计数加一
					if (count >= num) //当达到num时，程序退出
						break;
				}
			}
		}
		fclose(file);
	}
}