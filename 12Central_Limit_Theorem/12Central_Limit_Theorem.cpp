#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_16807 100000 //16807随机数产生器最大随机数数量
#define N 10 

int a = 16807, m = 2147483647, r = m % a, q = m / a; //相关参数设置
double x[N][NUM_16807]; //用来保存随机数
int Ns[3] = { 2,5,10 };


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
	int i, j, k;
	double x_now, E, Var;
	char filename[20] = {};
	FILE *file = NULL;

	srand(time(NULL)); //设置种子

	for (i = 0; i < 3; i++) {
		for (j = 0; j < Ns[i]; j++)
			RNG_16807(x[j], NUM_16807, rand()); //产生随机数
		
		//0-1分布
		E = 0.5, Var = 0.25;
		sprintf(filename, "01,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //遍历随机数
				for (x_now = 0, j = 0; j<Ns[i]; j++) //遍历Xi
					if (x[j][k]<= 0.5)
						x_now += 0;
					else
						x_now += 1;
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //打印到文件中
			}
			fclose(file);
		}
		


		//二项分布
		E = 2.5, Var = 1.25;
		sprintf(filename, "binom,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //遍历随机数
				for (x_now = 0, j = 0; j < Ns[i]; j++) //遍历Xi
					if (x[j][k] <= 1.0 / 32)
						x_now += 0;
					else if (x[j][k] <= 6.0 / 32)
						x_now += 1;
					else if (x[j][k] <= 16.0 / 32)
						x_now += 2;
					else if (x[j][k] <= 26.0 / 32)
						x_now += 3;
					else if (x[j][k] <= 31.0 / 32)
						x_now += 4;
					else
						x_now += 5;
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //打印到文件中
			}
			fclose(file);
		}


		
		//均匀分布
		E = 1, Var = 1.0/3;
		sprintf(filename, "uni,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //遍历随机数
				for (x_now = 0, j = 0; j < Ns[i]; j++) //遍历Xi
					x_now += 2 * x[j][k];
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //打印到文件中
			}
			fclose(file);
		}
		



		//指数分布
		E = 1, Var = 1;
		sprintf(filename, "expo,%d.txt", Ns[i]);
		file = fopen(filename, "w");
		if (!file)
			printf("Can't Open File!");
		else {
			for (k = 0; k < NUM_16807; k++) { //遍历随机数
				for (x_now = 0, j = 0; j < Ns[i]; j++) //遍历Xi
					x_now += -log(1 - x[j][k]);
				fprintf(file, "%.5f\n", (x_now / Ns[i] - E) / (sqrt(Var / Ns[i]))); //打印到文件中
			}
			fclose(file);
		}
	}
}