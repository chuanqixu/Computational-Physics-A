#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>



int main() {
	int i, j, k, num_particles, num_steps, x_now, y_now, z_now, count, randomnumber;
	char filename[20] = {};
	FILE *file = NULL;

	//输入相关数据
	printf("请输入总的粒子数：");
	scanf("%d", &num_particles);
	printf("请输入总的步数：");
	scanf("%d", &num_steps);

	srand(time(NULL)); //设置随机数种子

	sprintf(filename, "data.txt"); //打印文件名
	file = fopen(filename, "w"); //打开文件
	if (!file)
		printf("Can't Open File!\n"); //打开失败提示
	else {
		printf("Steps\t\td = 1\t\td = 2\t\td = 3\n"); //打印

		for (i = 2; i <= num_steps; i+=2) { //循环步数，因为奇数次的步数概率为0，因此只算偶数次的
			printf("%d\t\t", i);
			fprintf(file, "%d,", i);
			

			//求d=1时的概率的代码
			for (j = 0, count = 0; j < num_particles; j++) { //循环粒子个数
				for (k = 1, x_now = 0; k <= i; k++) { //每个粒子随机行走，随机行走规则如下，或者在报告中写到
					randomnumber = rand() % 2;
					if (randomnumber == 0)
						x_now--;
					else
						x_now++;
				}
				if (x_now == 0) //回到原点时计数加一
					count++;
			}
			//打印数据到命令行和文件中
			printf("%.5lf\t\t", double(count) / num_particles);
			fprintf(file, "%.10lf,", double(count) / num_particles);


			//求d=2时的概率的代码
			for (j = 0, count = 0; j < num_particles; j++) { //循环粒子个数
				for (k = 1, x_now = 0, y_now = 0; k <= i; k++) { //每个粒子随机行走，随机行走规则如下，或者在报告中写到
					randomnumber = rand() % 4;
					if (randomnumber == 0)
						x_now--;
					else if (randomnumber == 1)
						x_now++;
					else if (randomnumber == 2)
						y_now--;
					else
						y_now++;
				}
				if (x_now == 0 && y_now == 0) //回到原点时计数加一
					count++;
			}
			//打印数据到命令行和文件中
			printf("%.5lf\t\t", double(count) / num_particles);
			fprintf(file, "%.10lf,", double(count) / num_particles);


			//求d=3时的概率的代码
			for (j = 0, count=0; j < num_particles; j++) { //循环粒子个数
				for (k = 1, x_now = 0, y_now = 0, z_now = 0; k <= i; k++) { //每个粒子随机行走，随机行走规则如下，或者在报告中写到
					randomnumber = rand() % 6;
					if (randomnumber == 0)
						x_now--;
					else if (randomnumber == 1)
						x_now++;
					else if (randomnumber == 2)
						y_now--;
					else if (randomnumber == 3)
						y_now++;
					else if (randomnumber == 4)
						z_now--;
					else
						z_now++;
				}	
				if (x_now == 0 && y_now == 0 && z_now == 0) //回到原点时计数加一
					count++;
			}
			//打印数据到命令行和文件中
			printf("%.5lf\n", double(count) / num_particles);
			fprintf(file, "%.10lf\n", double(count) / num_particles);
		}

		fclose(file); //关闭文件
	}
	system("pause");
}