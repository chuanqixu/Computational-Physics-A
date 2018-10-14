#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GENERATE_PARTICLE_RANGE 400 //产生新粒子的边界
#define EDGE 500 //粒子最大边界，大于此边界的时候重新产生粒子
#define PICTURE_RANGE 800 //图片大小
#define INCREAMENT 50
#define COEFFICIENT_BOXCOUNT 15
#define COEFFICIENT_SANDBOX 9

int middle = PICTURE_RANGE / 2; //图片的中心
static unsigned char particles[PICTURE_RANGE][PICTURE_RANGE] = { 0 }; //表示粒子的二维数组。数组元素为1表示该处有粒子，为0表示该出无粒子



//随机行走函数，只在上下左右四个方向上行走
void RandomWalk(int *x, int *y) {
	int walk = rand() % 4; //随机产生0、1、2、3四个数中的一个，分别代表向上、下、左、右四个方向走

	//随机行走
	switch (walk) {
	case 0:
		(*y)++;
		break;
	case 1:
		(*y)--;
		break;
	case 2:
		(*x)--;
		break;
	case 3:
		(*x)++;
		break;
	}
}



//在产生粒子的正方形边界上的四条边上随机产生一个新粒子
void GenerateParticle(int *x, int *y,int generate_particle_range) {
	int side = rand() % 4; //随机产生0、1、2、3四个数中的一个，分别代表上、下、左、右四条边
	int coordinate = rand() % generate_particle_range; //随机产生四条边上的一个坐标点

	//随机产生新粒子
	switch (side) {
	case 0:
		*x = middle - generate_particle_range / 2 + coordinate;
		*y = middle + generate_particle_range / 2;
		break;
	case 1:
		*x = middle - generate_particle_range / 2 + coordinate;
		*y = middle - generate_particle_range / 2;
		break;
	case 2:
		*x = middle - generate_particle_range / 2;
		*y = middle - generate_particle_range / 2 + coordinate;
		break;
	case 3:
		*x = middle + generate_particle_range / 2;
		*y = middle - generate_particle_range / 2 + coordinate;
		break;
	}
}



//判断是否需要重新产生一个新粒子
//当粒子的坐标超出图片边界或者聚集到已经生成的团簇上，则需要重现产生一个新粒子；否则则不需要产生新粒子
//当不需要产生新粒子时返回0；当粒子聚集到已经生成的团簇上时返回1；当粒子超出边界时返回2
int NeedNewParticle(int x, int y, unsigned char particles[PICTURE_RANGE][PICTURE_RANGE], int *num,int edge) {
	//当粒子超出边界时，需要产生新粒子，返回2
	if (x<middle - edge / 2 || x>middle + edge / 2 || y<middle - edge / 2 || y>middle + edge / 2)
		return 2;
	//当粒子聚集到已经生成的团簇上时，团簇中的粒子数+1。需要产生新粒子，返回1
	if (particles[x - 1][y] == 1 || particles[x + 1][y] == 1 || particles[x][y - 1] == 1 || particles[x][y + 1] == 1
		|| particles[x - 1][y - 1] == 1 || particles[x - 1][y + 1] == 1 || particles[x + 1][y - 1] == 1 || particles[x + 1][y + 1] == 1
		) {
		particles[x][y] = 1;
		(*num)++;
		return 1;
	}
	//目前不是以上两种情况，不需要新粒子，返回0
	return 0;
}



//盒计数法
int BoxCount(unsigned char particles[PICTURE_RANGE][PICTURE_RANGE], int r, int range) {
	int x, y, i, j, count = 0, flag = 0;
	for (x = middle - range / 2; x <= middle + range / 2; x += r) {
		for (y = middle - range / 2; y <= middle + range / 2; y += r) {
			for (i = x; i < x + r && x <= middle + range / 2; i++) {
				for (j = y; j < y + r && y <= middle + range / 2; j++) {
					if (particles[i][j] == 1) {
						flag = 1;
						count++;
						break;
					}
				}
				if (flag == 1)
					break;
			}
			if (flag == 1)
				flag = 0;
		}
	}
	return count;
}



//Sandbox法
int Sandbox(unsigned char particles[PICTURE_RANGE][PICTURE_RANGE], int r) {
	int x, y, count = 0;
	for (x = middle - r / 2; x <= middle + r / 2; x++) {
		for (y = middle - r / 2; y <= middle + r / 2; y++)
			if (particles[x][y] == 1)
				count++;
	}
	return count;
}



//主函数
int main() {
	//声明变量
	//依次为粒子现在的横、纵坐标，最大粒子数，当前粒子数，产生粒子的边界范围，粒子允许的最大距离，粒子的状态，图片的大小
	int x_now, y_now, maxnum, num, generate_particle_range, edge, flag;

	//初始时中心设置一个粒子，初始粒子数为1
	particles[middle][middle] = 1;
	num = 1;
	//设定初始值
	generate_particle_range = GENERATE_PARTICLE_RANGE;
	edge = EDGE;
	printf("计算分形维数时，请先在源代码中选择合适的参数(用来控制盒计数法和Sandbox法选取的大小范围)！\n\n");
	printf("请输入团簇的最大粒子数(建议小于10000)：");
	scanf("%d", &maxnum);

	srand(time(NULL)); //随机数生成种子

	//打开文件，打开失败则报错
	FILE *p = fopen("data.txt", "w");
	if (!p)
		printf("Open File Fail!\n");

	else {
		//输入起始点
		fprintf(p, "%d,%d\n", middle, middle);

		//当前粒子数小于最大粒子数的时候运行。否则结束程序
		while (num < maxnum) {
			//产生新粒子与判断新粒子状态
			GenerateParticle(&x_now, &y_now, generate_particle_range);
			flag = NeedNewParticle(x_now, y_now, particles, &num, edge);

			//当不需要产生新粒子时，随机行走一步并判断新的位置的粒子状态。一直循环直至需要产生新粒子
			while (flag == 0) {
				RandomWalk(&x_now, &y_now);
				flag = NeedNewParticle(x_now, y_now, particles, &num, edge);
			}

			//当需要产生新粒子是因为粒子聚集到团簇上时，输入粒子当前坐标到文件中
			if (flag == 1) {
				fprintf(p, "%d,%d\n", x_now, y_now);
				
				//如果团簇边界到达产生新粒子的边界，则将产生新粒子的边界扩大。当边界超过图片大小时就退出
				if (abs(x_now - middle) > generate_particle_range / 2 || abs(y_now - middle) > generate_particle_range / 2) {
					generate_particle_range += INCREAMENT;
					edge += INCREAMENT;
					if (edge > PICTURE_RANGE)
						break;
				}
				
			}
		}
		//输入相关数据和初始点到文件中
		fprintf(p, "%d,%d\n", num, generate_particle_range);
		fprintf(p, "%d,%d\n", edge, PICTURE_RANGE);
		fclose(p); //关闭文件
	}

	int r;

	//打开文件，打开失败则报错
	p = fopen("Boxcount.txt", "w");
	if (!p)
		printf("Open File Fail!\n");

	else {
		for (r = 8; r <= PICTURE_RANGE / COEFFICIENT_BOXCOUNT; r += 4) {
			fprintf(p, "%d,%d\n", r, BoxCount(particles, r, generate_particle_range));
		}
		//输入相关数据和初始点到文件中
		fprintf(p, "%d,%d\n", num, generate_particle_range);
		fprintf(p, "%d,%d\n", edge, PICTURE_RANGE);
		fclose(p); //关闭文件
	}

	//打开文件，打开失败则报错
	p = fopen("Sandbox.txt", "w");
	if (!p)
		printf("Open File Fail!\n");

	else {
		for (r = PICTURE_RANGE / 50; r <= generate_particle_range - COEFFICIENT_SANDBOX * INCREAMENT; r += PICTURE_RANGE / 50) {
			fprintf(p, "%d,%d\n", r, Sandbox(particles, r));
		}
		//输入相关数据和初始点到文件中
		fprintf(p, "%d,%d\n", num, generate_particle_range);
		fprintf(p, "%d,%d\n", edge, PICTURE_RANGE);
		fclose(p); //关闭文件
	}
}