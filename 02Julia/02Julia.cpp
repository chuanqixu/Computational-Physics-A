#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SMALL_RADIUS 0.0000001


int CountEscape(double x, double y, double x_c, double y_c, double small_radius, double large_radius, int num) {
	//该函数用来计算复平面上的点(x,y)需要多少次迭代才会到原点距离小于small_radius或大于large_radius
	//若还未迭代num次后距离小于small_radius，则返回0
	//若迭代num次距离处于(small_radius,large_radius)，则返回-2或者num
	//若还未迭代num次距离就大于large_radius，则返回距离大于large_radius时的迭代次数
	//x,y为点的实部与虚部
	//x_c,y_c为定义Julia集时C的实部与虚部
	//small_radius,large_radius为设定的最小距离和最大距离，认为小于small_radius就将到原点，大于large_radius就将逃逸
	//num为设定的最大迭代次数
	int count = 0, i; //count为逃逸次数
	double x_now = x, y_now = y; //x_now，y_now为迭代时现在的x，y值
	for (i = 0; i < num; i++) {
		//计算x，y
		x = (x_now * x_now - y_now * y_now) + x_c;
		y = 2 * x_now*y_now + y_c;
		count++; //迭代次数+1
		if ((x*x + y * y) < (small_radius*small_radius)) //若还未迭代num次后距离小于small_radius，则返回0
			return 0;
		if ((x*x + y * y) > (large_radius*large_radius)) //若还未迭代num次距离就大于large_radius，则返回距离大于large_radius时的迭代次数
			return count;
		x_now = x;
		y_now = y;
	}
	//return -2; //若迭代num次距离处于(small_radius,large_radius)，则返回-2
	return count; //若迭代num次距离处于(small_radius,large_radius)，则返回num
}



int main() {
	//相关变量声明
	double range, step; //实部虚部的范围
	//double x_low, x_high, y_low, y_high;
	double x_now, y_now; //现在的x与y
	double x_c, y_c, small_radius = SMALL_RADIUS, large_radius; //x_c,y_c为C的实部和虚部，small_radius和large_radius为判定的距离
	double error = 0.00001; //double型变量判定误差，为了使边界能够取到
	int count, num, i, j;

	/*
	printf("请输入x的范围：");
	scanf("%lf", &x_low);
	printf("请输入x的上限：");
	scanf("%lf", &x_high);
	printf("请输入y的下限：");
	scanf("%lf", &y_low);
	printf("请输入y的上限：");
	scanf("%lf", &y_high);
	*/

	//输入数据
	printf("请输入范围（推荐1.5）：");
	scanf("%lf", &range);
	printf("请输入步长（推荐0.01，步长太小将导致数据很大）：");
	scanf("%lf", &step);
	printf("请输入C的实部：");
	scanf("%lf", &x_c);
	printf("请输入C的虚部：");
	scanf("%lf", &y_c);
	//printf("请输入最小判定距离：");
	//scanf("%lf", &small_radius);
	printf("请输入逃逸距离：");
	scanf("%lf", &large_radius);
	printf("请输入最大迭代次数：");
	scanf("%d", &num);
	printf("\n程序正在运行中!\n");

	//打开文件
	FILE *p = fopen("data.txt", "w");
	if(!p)
		printf("Open failed\n"); //打开失败则返回
	
	else {
		//打印参数到文件中
		fprintf(p, "%lf %lf %d\n", range, step, num);
		fprintf(p, "%lf %lf %lf\n", x_c, y_c, large_radius);

		//遍历正方形区域中的点，并将点的坐标和迭代次数输入到文件中
		for (x_now = -range, i = 0; x_now - error < range; x_now = -range + i * step) {
			for (y_now = -range, j = 0; y_now - error < range; y_now = -range + j * step) {
				count = CountEscape(x_now, y_now, x_c, y_c, small_radius, large_radius, num);
				fprintf(p, "%lf %lf %d\n", x_now, y_now, count);
				j++;
			}
			i++;
		}

		printf("\n程序正在运行完毕，数据已经输入到data.dat中!\n");
	}

	fclose(p); //关闭文件
}