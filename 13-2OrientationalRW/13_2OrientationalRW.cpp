#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

double lengths[4] = { 1,4,25,50 }; //用来保存矩形长度
double widths[4] = { 1,1,25,1 }; //用来保存矩形宽度



int main() {
	int i, j, k, n, num_steps, num_particles;
	double length, width, step, x_now, y_now, theta_now, rn, r_2, Ct;
	char filename[50];
	FILE *file = NULL;
	
	printf("请输入矩形长：");
	scanf("%lf", &length);
	printf("请输入矩形宽：");
	scanf("%lf", &width);
	printf("请输入一次的步长长度：");
	scanf("%lf", &step);
	printf("请输入粒子总数：");
	scanf("%d", &num_particles);
	printf("请输入随机行走次数：");
	scanf("%d", &num_steps);
	
	srand(time(NULL));



	//显示随机行走示意图
	sprintf(filename, "RW,length=%.1lf,width=%.1lf,num=%d.txt", length, width, num_steps); //文件名
	file = fopen(filename, "w"); //打开文件
	if (!file)
		printf("Can’t Open File!\n"); //打开失败提示
	else {
		x_now = 0, y_now = 0, theta_now = 0; //初始化
		fprintf(file, "%d,%.10lf, %.10lf, %.10lf\n", 0, x_now, y_now, theta_now); //将初始数据输入到文件中
		for (i = 0; i < num_steps; i++) {
			rn = double(rand()) / RAND_MAX; //rn为判断哪条边受力的随机数

			//四种受力的情况。若初始状态矩形的边沿着x和y轴，则以下四种情况分别是下、上、左、右四条边的受力情况
			//每步随机行走的坐标和角度变化的具体分析在报告中
			if (rn < length / (2 * (length + width))) {
				x_now -= step / sqrt(length)*sin(theta_now);
				y_now += step / sqrt(length)*cos(theta_now);
				theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
			}
			else if (rn < length / (length + width)) {
				x_now += step / sqrt(length)*sin(theta_now);
				y_now -= step / sqrt(length)*cos(theta_now);
				theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
			}
			else if (rn < (length + 0.5*width) / (length + width)) {
				x_now += step / sqrt(width)*cos(theta_now);
				y_now += step / sqrt(width)*sin(theta_now);
				theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
			}
			else {
				x_now -= step / sqrt(width)*cos(theta_now);
				y_now -= step / sqrt(width)*sin(theta_now);
				theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
			}
			fprintf(file, "%d,%.10lf, %.10lf, %.10lf\n", i, x_now, y_now, theta_now); //输出每步随机行走后的坐标和角度到文件中
		}
		fclose(file); //关闭文件
	}
	

	
	//计算2阶距和自相关函数
	sprintf(filename, "RC.txt"); //文件名
	file = fopen(filename, "w"); //打开文件
	if (!file)
		printf("Can’t Open File!\n"); //打开失败提示
	else {
		for (n = 0; n < 4; n++) { //设置不同的矩形长度和宽度
			length = lengths[n];
			width = widths[n];
			for (i = 1; i <= 100; i ++) {//遍历步数
				for (j = 0, r_2 = 0, Ct = 0; j < num_particles; j++) { //遍历不同的粒子
					for (k = 0, x_now = 0, y_now = 0, theta_now = 0; k < i; k++) { //每个粒子的随机行走
						rn = double(rand()) / RAND_MAX; //rn为判断哪条边受力的随机数

						//四种受力的情况。若初始状态矩形的边沿着x和y轴，则以下四种情况分别是下、上、左、右四条边的受力情况
						//每步随机行走的坐标和角度变化的具体分析在报告中
						if (rn < length / (2 * (length + width))) {
							x_now -= step / sqrt(length)*sin(theta_now);
							y_now += step / sqrt(length)*cos(theta_now);
							theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
						}
						else if (rn < length / (length + width)) {
							x_now += step / sqrt(length)*sin(theta_now);
							y_now -= step / sqrt(length)*cos(theta_now);
							theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*length*sqrt(length)*step / (pow(length, 3) + pow(width, 3));
						}
						else if (rn < (length + 0.5*width) / (length + width)) {
							x_now += step / sqrt(width)*cos(theta_now);
							y_now += step / sqrt(width)*sin(theta_now);
							theta_now -= 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
						}
						else {
							x_now -= step / sqrt(width)*cos(theta_now);
							y_now -= step / sqrt(width)*sin(theta_now);
							theta_now += 6 * (double(rand()) / RAND_MAX - 0.5)*width*sqrt(width)*step / (pow(length, 3) + pow(width, 3));
						}
					}
					r_2 += x_now * x_now + y_now * y_now; //对离原点距离的平方求和
					Ct += cos(theta_now); //计算自相关函数中的累加部分
				}
				fprintf(file, "%d,%.10lf,%.10lf\n", i, r_2 / num_particles, Ct/num_particles); //输出每步的2阶距和自相关函数
			}
		}
		
		fclose(file); //关闭文件
	}
}