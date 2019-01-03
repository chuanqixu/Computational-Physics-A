#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>



int main() {
	int N = 1000000, M = 100000, i;
	double sigma_x, sigma_y, step, x0, y0, x_now, y_now, r, sum_x2 = 0, sum_y2 = 0, sum_xy2 = 0;
	char filename[50] = {};
	FILE *file = NULL;

	//输入相关数据
	printf("请输入sigma_x：");
	scanf("%lf", &sigma_x);
	printf("请输入sigma_y：");
	scanf("%lf", &sigma_y);
	printf("请输入步长：");
	scanf("%lf", &step);
	printf("请输入起始横坐标：");
	scanf("%lf", &x0);
	printf("请输入起始纵坐标：");
	scanf("%lf", &y0);

	srand(time(NULL)); //设置随机数种子

	for (i = 0; i < M; i++) {
		//随机生成下个位置的坐标并计算比值r
		x_now = x0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
		y_now = y0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
		r = exp(-0.5*(x_now * x_now / (sigma_x*sigma_x) + y_now * y_now / (sigma_y*sigma_y) - (x0 * x0 / (sigma_x*sigma_x) + y0 * y0 / (sigma_y*sigma_y))));

		//r>1时直接选择当前位置到序列中
		if (r > 1) {
			x0 = x_now;
			y0 = y_now;
		}
		//r<=1时，重新抽取[0,1]上的随机数，若小于r，则选择当前位置到序列中；否则位置不变
		else
			if (double(rand() % RAND_MAX) / RAND_MAX < r) {
				x0 = x_now;
				y0 = y_now;
			}
	}

	sprintf(filename, "sx=%.1lf,sy=%.1lf,step=%.1lf.txt", sigma_x, sigma_y, step);
	//sprintf(filename, "error.txt");
	file = fopen(filename, "w");
	if (!file)
		printf("Can't Open File!\n");
	else {
		for (i = 0; i < N - M; i++) {
			//随机生成下个位置的坐标
			x_now = x0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
			y_now = y0 + 2 * (double(rand()) / RAND_MAX - 0.5)*step;
			r = exp(-0.5*(x_now * x_now / (sigma_x*sigma_x) + y_now * y_now / (sigma_y*sigma_y) - (x0 * x0 / (sigma_x*sigma_x) + y0 * y0 / (sigma_y*sigma_y))));

			//r>1时直接选择当前位置到序列中
			if (r > 1) {
				x0 = x_now;
				y0 = y_now;
			}
			//r<=1时，重新抽取[0,1]上的随机数，若小于r，则选择当前位置到序列中；否则位置不变
			else
				if (double(rand() % RAND_MAX) / RAND_MAX < r) {
					x0 = x_now;
					y0 = y_now;
				}
			//输出当前坐标到文件中
			fprintf(file, "%.6lf,%.6lf\n", x0, y0);

			//计算x^2,y^2,x^2+y^2
			sum_x2 += x0 * x0;
			sum_y2 += y0 * y0;
			sum_xy2 += x0 * x0 + y0 * y0;
			//fprintf(file, "%.6lf,%.6lf,%.6lf\n", sum_x2 / (i + 1) - sigma_x * sigma_x, sum_y2 / (i + 1) - sigma_y * sigma_y, sum_xy2 / (i + 1) - sigma_x * sigma_x - sigma_y * sigma_y);
		}
		//输出计算的均值到文件中
		fprintf(file, "%.6lf,%.6lf\n%.6lf,0", sum_x2 / (N - M), sum_y2 / (N - M), sum_xy2 / (N - M));
		
		//关闭文件
		fclose(file);
	}
	printf("\n<x^2>=%.6lf\n<y^2>=%.6lf\n<x^2+y^2>=%.6lf\n", sum_x2 / (N - M), sum_y2 / (N - M), sum_xy2 / (N - M));
	system("pause");
}