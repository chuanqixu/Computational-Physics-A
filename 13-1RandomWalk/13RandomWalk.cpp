#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 10000000 //16807随机数产生器最大随机数数量
#define COEFFICIENT 0.0 //电场影响作用
#define OMEGA 0.0 //电场力中的omega

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double x[NUM_16807]; //用来保存随机数
int randomwalk[5][1000]; //用来保存显示随机行走的粒子坐标


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



//返回向电场正方向的概率
double p_right(int n, double coefficient, double omega) {
	return (double(1 + coefficient* sin(omega*n)) / 2);
}



int main() {
	int i, j, x_now, num_particles, num_steps;
	double x_1, x_2, coefficient, omega;
	char filename[40] = {};
	FILE *file = NULL;

	//输入相关数据
	printf("请输入总的粒子数：");
	scanf("%d", &num_particles);
	printf("请输入电场力的影响效果：");
	scanf("%lf", &coefficient);
	printf("请输入电场力中的omega：");
	scanf("%lf", &omega);

	srand(time(NULL)); //设置随机数种子


	
	//打印随机行走示意图程序，只显示5个粒子,每个粒子行走100步
	sprintf(filename, "Random_Walk,c=%.1lf,omega=%.2lf.txt", coefficient, omega);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		//粒子进行随机行走
		for (i = 0; i < 5; i++) { //遍历num_particles个粒子
			x_now = 0; //起始坐标置0
			RNG_16807(x, 1000, rand()); //用16807随机数产生器产生随机数
			for (j = 0; j < 1000; j++) { //进行随机行走：大于向右的概率时，坐标+1，否则坐标-1。随机数产生器为系统自带的产生器
				randomwalk[i][j] = x_now;
				if (double(rand()) / RAND_MAX <= p_right(j, coefficient, omega))
					x_now++;
				else
					x_now--;
			}
		}
		
		//打印数据到文件中
		for (j = 0; j < 1000; j++)
			for (i = 0; i < 5; i++)  //遍历粒子
				//打印这个粒子每步所在的坐标到文件中
				if (i != 4)
					fprintf(file, "%d,", randomwalk[i][j]);
				else
					fprintf(file, "%d\n", randomwalk[i][j]);

		fclose(file);
	}
	

	
	//打印x的1阶距与2阶距程序
	sprintf(filename, "particles=%d,c=%.1f,omega=%.2f.txt", num_particles, coefficient, omega);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (num_steps = 10; num_steps <= 1000; num_steps += 10) { //设置不同的步长
			for (i = 0, x_1 = 0, x_2 = 0; i < num_particles; i++) { //遍历num_particles个粒子
				x_now = 0; //起始坐标置0

				/*
				RNG_16807(x, num_steps, rand()); //用16807随机数产生器产生随机数
				
				for (j = 0; j < num_steps; j++) //进行随机行走：大于向右的概率时，坐标+1，否则坐标-1。随机数产生器为16807
					if (x[j] <= p_right(j, coefficient, omega))
						x_now++;
					else
						x_now--;
				*/

				for (j = 0; j < num_steps; j++) //进行随机行走：大于向右的概率时，坐标+1，否则坐标-1。随机数产生器为系统自带的产生器
					if (double(rand()) / RAND_MAX <= p_right(j, coefficient, omega))
						x_now++;
					else
						x_now--;
				
				x_1 += double(x_now); //对x的1次方累加
				x_2 += double(x_now) * double(x_now); //对x的二次方累加
			}
			fprintf(file, "%d,%.5f,%.5f\n", num_steps, x_1 / num_particles, x_2 / num_particles); //打印步数、x的1阶距和x的2阶距到文件中
		}
		fclose(file);
	}
	



	//验证分布为正态分布程序
	sprintf(filename, "end_x,c=%.1lf,omega=%.2lf.txt", coefficient, omega);
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		//粒子进行随机行走
		for (i = 0; i < num_particles; i++) { //遍历num_particles个粒子
			x_now = 0; //起始坐标置0
			RNG_16807(x, 1000, rand()); //用16807随机数产生器产生随机数
			for (j = 0; j < 1000; j++) { //进行随机行走：大于向右的概率时，坐标+1，否则坐标-1。随机数产生器为系统自带的产生器
				if (double(rand()) / RAND_MAX <= p_right(j, coefficient, omega))
					x_now++;
				else
					x_now--;
			}
			fprintf(file, "%d\n", x_now);
		}
		fclose(file);
	}
}