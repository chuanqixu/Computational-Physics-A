#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define OPERATOR + //Fibonacci延迟产生器操作符：可以是+、-、*、XOR
#define NUM_16807 210000000 //16807随机数产生器最大随机数数量，一般要求小于210000000
#define NUM_FIBONACCI  20000000 //Fibonacci生成器最大随机数数量，一般要求小于20000000，否则long long数组长度太大
#define START_NUM 10 //定义起始点start的个数


int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double x[NUM_16807]; //用来保存随机数
long long I[NUM_FIBONACCI]; //用来保存Fibonacci延迟器n小于p或q时的整数数据
int starts[START_NUM]; //用来保存起始值start的数组

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


//Fibonacci延迟产生器：输入输入生成的随机数的数组x、随机数数量num和延迟整数对p、q，将Fibonacci延迟产生器产生的随机数保存在一维数组中
//Fibonacci延迟产生器的初始数列由start为起始点的16807随机数产生器产生
void RNG_Fibonacci(long long I[], double x[], int num,int start, int Fibonacci_p, int Fibonacci_q) {
	int i;
	
	I[0] = start;
	x[0] = double(start) / m;

	//根据Schrage方法和16807随机数产生器产生Fibonacci初始数列
	for (i = 1; i < (Fibonacci_p < Fibonacci_q ? Fibonacci_q : Fibonacci_p); i++) {
		start = (a*(start%q) - r * (start / q) >= 0) ? (a*(start%q) - r * (start / q)) : (a*(start%q) - r * (start / q) + m);
		I[i] = start;
		x[i] = double(start) / m;
	}

	//Fibonacci延迟产生器
	for (; i < num; i++) {
		I[i] = (I[i - Fibonacci_p] OPERATOR I[i - Fibonacci_q]) % m;
		x[i] = double(I[i]) / m;
	}
}


//Count函数：输入生成的随机数的数组x与随机数数量num，返回满足关系x[i - 1] < x[i + 1] < x[i]的比重
double Count(double x[], int num) {
	int i, count = 0;
	for (i = 1; i < num - 1; i++)
		if (x[i - 1] < x[i + 1] && x[i + 1] < x[i]) //满足关系则计数+1
			count++;
	return (double(count) / (num - 2)); //要设置double
}



int main() {
	int start = 1, num = 1;//起始值
	int i, Fibonacci_p = 0, Fibonacci_q = 0; //分别为循环变量i，Fibonacci延迟p、q
	char filename[50] = {}; //文件名
	FILE *file = NULL;

	srand(time(NULL)); //添加一个随机种子，为以后使用

	//输入相关数据
	//printf("请输入点的个数（需要小于2*10^7）：");
	//scanf("%d", &num);
	printf("请输入起始值：");
	scanf("%d", &start);
	printf("请输入Fibonacci延迟产生器延迟p：");
	scanf("%d", &Fibonacci_p);
	printf("请输入Fibonacci延迟产生器延迟q：");
	scanf("%d", &Fibonacci_q);

	
	//16807随机数产生器单个起始值的数据输出
	sprintf(filename, "16807,start=%d.txt", start);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		printf("\n\n   16807随机数产生器中所占比重\n\n");

		//不同随机数个数下输出16807随机数产生器中所占比重
		for (num = 100; num < NUM_16807; num *= 2) { //循环随机数个数
			RNG_16807(x, num, start);
			printf("   N = %-10d\tCount = %f\n", num, Count(x, num));
			fprintf(file, "%d,%.15f\n", num, Count(x, num));
		}
	}
	
	
	//16807随机数产生器多个起始值的数据输出，起始值由随机数随机产生
	sprintf(filename, "16807,start=0.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else{
		//相关打印
		printf("\n\n   16807随机数产生器中所占比重\n\n");
		printf("      Num\t\t");
		fprintf(file, "1,"); //无意义，只是为了python读取数据时能够直接用numpy函数读取，要满足数据为矩阵

		//随机生成起始点数值并打印
		for (i = 0; i < START_NUM; i++) {
			start = rand();
			starts[i] = start;

			if (i != START_NUM - 1) {
				printf("%d\t", start);
				fprintf(file, "%d,", start);
			}
			else {
				printf("%d\n\n", start);
				fprintf(file, "%d\n", start);
			}
		}

		//16807随机数产生器产生随机数，同时打印在控制台与输出到文件中
		for (num = 100; num < NUM_16807; num *= 2) { //循环随机数个数N
			fprintf(file, "%d,", num);
			printf("   N = %-10d\t", num);

			for (i = 0; i < START_NUM; i++) { //循环起始点
				RNG_16807(x, num, starts[i]);
				if (i != START_NUM - 1) {
					printf("%.4f\t", Count(x, num));
					fprintf(file, "%.15f,", Count(x, num));
				}
				else {
					printf("%.4f\n", Count(x, num));
					fprintf(file, "%.15f\n", Count(x, num));
				}
			}
		}
		printf("\n");
	}
	

	
	//Fibonacci延迟器多个起始值的数据输出

	//随机生成p，q，若不需要则注释掉
	//Fibonacci_p = rand();
	//Fibonacci_q = rand();

	sprintf(filename, "4Fibonacci,%d,%d.txt", Fibonacci_p, Fibonacci_q);
	file = fopen(filename, "w");
	if (!file)
		printf("Open File Fail!\n");
	else {
		//相关打印
		printf("\n\n   Fibonacci随机数产生器中所占比重\n\n");
		printf("   p = %d, q = %d\n\n", Fibonacci_p, Fibonacci_q);
		printf("      Num\t\t");
		fprintf(file, "1,"); //无意义，只是为了python读取数据时能够直接用numpy函数读取，要满足数据为矩阵

		//随机生成起始点数值并打印
		for (i = 0; i < START_NUM; i++) {
			start = rand();
			starts[i] = start;

			if (i != START_NUM - 1) {
				printf("%d\t", start);
				fprintf(file, "%d,", start);
			}
			else {
				printf("%d\n\n", start);
				fprintf(file, "%d\n", start);
			}
		}
		
		//Fibonacci延迟器产生随机数，同时打印在控制台与输出到文件中
		for (num = 100; num < NUM_FIBONACCI; num *= 2) { //循环随机数个数N
			fprintf(file, "%d,", num);
			printf("   N = %-10d\t", num);

			for (i = 0; i < START_NUM; i++) { //循环起始点
				RNG_Fibonacci(I, x, num, starts[i], Fibonacci_p, Fibonacci_q);
				if (i != START_NUM - 1) {
					printf("%.4f\t", Count(x, num));
					fprintf(file, "%.15f,", Count(x, num));
				}
				else {
					printf("%.4f\n", Count(x, num));
					fprintf(file, "%.15f\n", Count(x, num));
				}
			}
		}
		printf("\n");
	}
	

	system("pause");
}