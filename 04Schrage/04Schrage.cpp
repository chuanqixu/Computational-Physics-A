#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double x[210000000];

int main() {
	int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
	int start = 1, num = 0, now; //start是起始点，num是点的个数，now是现在迭代的数
	double schrage = double(start) / m; //schrage是迭代到现在的数（归一化后）
	double xk = 0, difference, coefficient; //xk是x的k阶距，difference是计算的x的k阶距与理论值的差别，coefficient是相关系数
	int menu, i, k;

	printf("16807产生器\n\n");
	printf("1：单个N值下的16807随机数产生器产生二维坐标点\n");
	printf("2：x的k阶距检验数据生成\n");
	printf("3：C(l)测试二维独立性数据生成\n\n");
	printf("请输入需要的功能：");
	scanf("%d", &menu);

	switch (menu) {
	case 1: {
		//输入相关数据
		printf("请输入点的个数：");
		scanf("%d", &num);
		printf("请输入起始值：");
		scanf("%d", &start);
		schrage = double(start) / m; //double要设置

		//打开文件
		char filename[50] = {};
		sprintf(filename, "num=%d,start=%d.txt", num, start);
		FILE *p = fopen(filename, "w");
		//打开失败则报错
		if (!p)
			printf("Open Fail!");
		else
			//循环输出点的坐标
			for (i = 0; i < num; i++) {
				fprintf(p, "%.18lf,", schrage); //输入当前点的横坐标
				start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m); //根据Schrage方法和16807随机数产生器计算下一个随机数
				schrage = double(start) / m;
				fprintf(p, "%.18lf\n", schrage); //将下一个随机数生成纵坐标
			}

		fclose(p);
	}//要添加花括号
		break;

	case 2: {
		//打开文件
		printf("\n请输入起始值：");
		scanf("%d", &start);
		char filename[50] = {};
		sprintf(filename, "xk test,start=%d.txt",start);
		FILE *p = fopen(filename, "w");
		//打开失败则报错
		if (!p)
			printf("Open Fail!");
		else {		
			printf("\n   Num\t\tk=1\t\tk=2\t\tk=3\t\tk=4\t\tk=5");
			//设置不同的Num数
			for (num = 100; num <= 210000000; num *= 2) {
				fprintf(p, "%d,", num);
				printf("\n   %-10d\t", num);
				//重置初始值
				now = start;
				schrage = double(start) / m;
				x[0] = schrage;

				//根据Schrage方法和16807随机数产生器产生随机数
				for (i = 1; i < num; i++) {
					now = (a*(now%q) - r * (now / q) >= 0) ? (a*(now%q) - r * (now / q)) : (a*(now%q) - r * (now / q) + m); 
					schrage = double(now) / m;
					x[i] = schrage;
				}

				//求不同k值下的k阶距与理论值的区别
				for (k = 1; k <= 5; k ++) {
					xk = 0;
					//求k阶距
					for (i = 0; i < num; i++)
						xk += pow(x[i], k);
					xk = xk / num;
					//求与理论值的区别
					difference = 1 / (double(k) + 1)- xk; //要设置double
					if (k < 5)
						fprintf(p, "%.18lf,", difference);
					else
						fprintf(p, "%.18lf\n", difference);
					printf("%.6lf\t", difference);
				}
			}
		}
		printf("\n\n");
		system("pause");
	}
		break;

	case 3: {
		int l;
		double mean, square_mean, l_mean, coefficient;

		printf("\n请输入起始值：");
		scanf("%d", &start);
		//打开文件
		char filename[50] = {};
		sprintf(filename, "C(l)test,start=%d.txt",start);
		FILE *p = fopen(filename, "w");
		//打开失败则报错
		if (!p)
			printf("Open Fail!");
		else {
			printf("\n   Num\t\tl=1     l=2     l=3     l=4     l=5     l=6     l=7     l=8     l=9     l=10");

			//设置不同的Num值
			for (num = 100; num <= 210000000; num *= 2) {
				printf("\n   %-10d\t", num);
				fprintf(p, "%d,", num);
				//重置初始值
				now = start;
				schrage = double(start) / m;
				x[0] = schrage;
				mean = schrage;
				square_mean = pow(schrage, 2);

				//根据Schrage方法和16807随机数产生器产生随机数
				for (i = 1; i < num; i++) {
					now = (a*(now%q) - r * (now / q) >= 0) ? (a*(now%q) - r * (now / q)) : (a*(now%q) - r * (now / q) + m);
					schrage = double(now) / m;
					x[i] = schrage;
					mean += schrage;
					square_mean += pow(schrage, 2);
				}
				//求平均值与方均值
				mean = mean / num;
				square_mean = square_mean / num;

				//求不同l下的C(l)
				for (l = 1; l <= 10; l++) {
					l_mean = 0;
					for (i = 0; i + l < num; i++) 
						l_mean += x[i] * x[i + l];
					l_mean = l_mean / (num - l);
					coefficient = (l_mean - pow(mean, 2)) / (square_mean - pow(mean, 2));
					if (l != 10)
						fprintf(p, "%.18lf,", coefficient);
					else
						fprintf(p, "%.18lf\n", coefficient);
					printf("%.4lf\t", coefficient);
				}
			}
		}
		printf("\n\n");
		system("pause");
	}
		break;

	default:
		break;
	}
}