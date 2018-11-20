#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 30000000 //16807随机数产生器最大随机数数量

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double x[NUM_16807], y[NUM_16807], z[NUM_16807], u[NUM_16807], v[NUM_16807]; //用来保存随机数



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
	int i,  num;
	char filename[20] = {};
	double f,  x_now, y_now, z_now, u_now, v_now;
	FILE *file = NULL;

	printf("\n\n\t积分值为：\n\n");

	srand(time(NULL)); //设置随机种子
	
	//计算第一个积分
	printf("\t第一个积分值为：\n\n");
	printf("\tNum\t\tIntegral\t\terror\n");
	sprintf(filename, "1.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (num = 10; num < NUM_16807; num *= 2) { //循环随机点个数
			if(num<10000000)
				printf("%\t%d\t\t", num);
			else
				printf("%\t%d\t", num);
			RNG_16807(x, num, rand()); //16807随机数产生器产生随机数
			for (i = 0, f = 0; i < num; i++) {
				x_now = 2 * x[i]; //计算抽样的x
				f += sqrt(x_now + sqrt(x_now)); //求f的和
			}
			//打印数据到命令行和文件中
			printf("%.7f\t\t%.5f\n", f * 2 / num, f * 2 / num - 2.6895213);
			fprintf(file, "%d,%.7f\n", num, f * 2 / num - 2.6895213);
		}

		fclose(file);
	}


	//计算第二个积分
	printf("\n\n\t第二个积分值为：\n\n");
	printf("\tNum\t\tIntegral\t\terror\n");
	sprintf(filename, "2.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (num = 10; num < NUM_16807; num *= 2) { //循环随机点个数
			if (num<10000000)
				printf("%\t%d\t\t", num);
			else
				printf("%\t%d\t", num);

			//16807随机数产生器产生随机数
			RNG_16807(x, num, rand());
			RNG_16807(y, num, rand());
			RNG_16807(z, num, rand());
			RNG_16807(u, num, rand());
			RNG_16807(v, num, rand());

			for (i = 0, f = 0; i < num; i++) {
				//计算抽样的值
				x_now = 0.9 * x[i];
				y_now = 0.8 * y[i];
				z_now = 0.9 * z[i];
				u_now = 2 * u[i];
				v_now = 1.3 * v[i];

				f += 6 - x_now * x_now - y_now * y_now - z_now * z_now - u_now * u_now - v_now * v_now; //求f的和
			}
			//打印数据到命令行和文件中
			printf("%.7f\t\t%.5e\n", f * 1.6848 / num, f * 1.6848 / num - 5.6440800);
			fprintf(file, "%d,%.7f\n", num, f * 1.6848 / num - 5.6440800);
		}

		fclose(file);
	}
	

	printf("\n\n");
	system("pause");
}