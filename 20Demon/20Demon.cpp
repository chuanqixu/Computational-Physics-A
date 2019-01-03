#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define MAX_NUM_PARTICLES 1000000
double m = 1;
double vs[MAX_NUM_PARTICLES] = { 0 };



int main() {
	int i, N=10000000, M=100000, num, n, steps, i_now;
	double xi, step, E_d = 0, v_now, H = 0, delta_H, sum1 = 0, sum2 = 0;
	char filename[20] = {};
	FILE *file = NULL;

	//输入相关数据
	printf("请输入总的粒子数：");
	scanf("%d", &num);
	printf("请输入步长：");
	scanf("%lf", &step);
	/*
	printf("请输入demon的初始能量：");
	scanf("%lf", &E_d);
	*/
	srand(time(NULL)); //设置随机数种子

	//初始化速度数组为1，同时计算能量
	for (i = 0; i < num; i++) {
		vs[i] = 0;
		H += m / 2 * (vs[i] * vs[i]);
	}
	
	//热化阶段
	for (i = 0; i < M; i++) {
		i_now = rand() % num; //选取第i_now个粒子
		v_now = vs[i_now] + (2 * double(rand()) / RAND_MAX - 1)*step; //第i_now个粒子的速度进行改变
		delta_H = m / 2 * (v_now*v_now - vs[i_now] * vs[i_now]); //系综的能量进行改变

		if (delta_H < 0) { //系综能量减少则接受此次尝试
			vs[i_now] = v_now; //改变速度
			H = H + delta_H; //改变能量
			E_d = E_d - delta_H; //改变demon能量
		}
		else
			if (E_d > delta_H) {
				vs[i_now] = v_now; //改变速度
				H = H + delta_H; //改变能量
				E_d = E_d - delta_H; //改变demon能量
			}
	}

	//进行达到平衡态的过程，同时将demon的能量输入到文件中
	//sprintf(filename, "T.txt");
	sprintf(filename, "demon_energy.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		//进行达到平衡态的过程
		for (i = 0; i < N - M; i++) {
			i_now = rand() % num; //选取第i_now个粒子
			v_now = vs[i_now] + (2 * double(rand()) / RAND_MAX - 1)*step; //第i_now个粒子的速度进行改变
			delta_H = m / 2 * (v_now*v_now - vs[i_now] * vs[i_now]); //系综的能量进行改变

			if (delta_H < 0) { //系综能量减少则接受此次尝试
				vs[i_now] = v_now; //改变速度
				H = H + delta_H; //改变能量
				E_d = E_d - delta_H; //改变demon能量
			}
			else
				if (E_d > delta_H) {
					vs[i_now] = v_now; //改变速度
					H = H + delta_H; //改变能量
					E_d = E_d - delta_H; //改变demon能量
				}
			//fprintf(file, "%.6lf\n", 2 * H / num);
			fprintf(file, "%.6lf\n", E_d);
		}

		fclose(file);
	}

	//打印速度数据到文件中
	sprintf(filename, "vs.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0; i < num; i++) {
			fprintf(file, "%.6lf\n", vs[i]);
			sum1 += vs[i];
			sum2 += vs[i] * vs[i];
		}
		fprintf(file, "%.6lf\n%.6lf\n%.6lf", sum1 / num, sum2 / num, sum2 / num - sum1 * sum1 / (num*num));
			
		fclose(file);
	}
}