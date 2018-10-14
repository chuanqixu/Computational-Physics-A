#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// 一、初值设定：
#define X0 0.5 //x的初值
#define LAMBDA0 0.6 //lambda起始值
#define LAMBDA_LIMIT 0.9 //lambda终值
#define STEP 0.00001 //lambda步长值
#define N 100000 //保存lambda的数组长度，要大于 lambda取值范围 / step
#define ITERATION 10000 //初始的函数迭代次数
#define NUM 100 //ITERATION次后后开始的迭代次数
#define ERROR 0.00001 //两个double类型数据大小误差
#define PI 3.1415926 //PI的值
#define FUNCTION(x,lambda) ( (lambda)*sin(PI*(x)) ) //需要求混沌的函数

//定义名为sq线性表类型，用来保存x的值
typedef struct sq {
	double x;
	sq *next = NULL;
} sq;

//求混沌的函数
double function(double x, double lambda) {
	return (FUNCTION(x, lambda));
}





// 二、主函数
int main() {
	//相关变量声明
	double x = X0;
	double lambda = LAMBDA0;
	double lambda_limit = LAMBDA_LIMIT;
	double step = STEP;
	double lambda_now; //lambda_now用来保存循环中当前的lambda值
	int iteration = ITERATION;
	int num = NUM;
	double error = ERROR;
	//value[i]为一个sq型链表的头指针
	//线性表中数据保存lambda = LAMBDA0 + i*STEP迭代ITERATION次后再迭代NUM次的NUM个x值
	sq* value[N] = { NULL };
	//unique_lambda[i]为一个sq型链表的头指针
	//线性表中数据保存lambda = LAMBDA0 + i*STEP中唯一的x值，即value[i]中不重复的x值
	sq* unique_lambda[N] = { NULL };
	//Feigenbaum用来保存倍周期分叉时的lambda
	double Feigenbaum[10] = { 0 };
	sq *end = NULL, *q = NULL;
	int i, j, count, flag = 1;

	//手动输入数据
	//本步骤可省略，可通过程序内部的define直接设置
	printf("请输入lambda起始值（推荐%lf）：",lambda);
	scanf("%lf", &lambda);
	printf("请输入lambda终止值（推荐%lf）：",lambda_limit);
	scanf("%lf", &lambda_limit);
	printf("请输入步长（推荐%lf）：",step);
	scanf("%lf", &step);
	printf("请输入每个lambda值最大拥有的x值数（推荐%d）：",num);
	scanf("%d", &num);
	printf("\n程序正在运行中！\n");

	//（1）for循环用来产生数组value
	for (i = 0, lambda_now = lambda; lambda_now < lambda_limit; lambda_now = lambda + i * step, i++) {
		x = X0;

		//初始迭代ITERATION次
		for (j = 0; j < iteration; j++)
			x = function(x, lambda_now);
		//value[i]为空时，创建头指针
		x = function(x, lambda_now);
		value[i] = (sq*)malloc(sizeof(sq));
		value[i]->x = x;
		value[i]->next = NULL;
		end = value[i];
		//继续迭代(NUM-1)次，并将得到的x连接成value[i]的链表
		for (j = 0; j < num - 1; j++) {
			x = function(x, lambda_now);
			//value[i]不为空时，在链表尾部插入x
			end->next = (sq*)malloc(sizeof(sq));
			end->next->x = x;
			end->next->next = NULL;
			end = end->next;
		}
	}



	//（2）打开文件data.dat，并将得到的(lambda,x)打印到data.dat中
	FILE *p = fopen("data.dat", "w");
	//检测是否成功打开  
	if (p == NULL)
		printf("Open failed\n");

	else {
		//遍历value[i]链表，将(lambda_now,x)打印到data.dat中
		for (i = 0; value[i] != NULL; i++) {
			lambda_now = lambda + step * i;
			//打印(lambda_now,x)
			for (end = value[i]; end != NULL; end = end->next) {
				fprintf(p, "%lf,", lambda_now);
				fprintf(p, "%lf\n", end->x);
			}
		}
	}

	//释放指针
	fclose(p);



	//（3）for循环用来产生数组unique_lambda
	for (i = 0, lambda_now = lambda; lambda_now < lambda_limit; lambda_now = lambda + i * step, i++) {
		//将value[i]第一个值输入到unique_lambda[i]中
		end = value[i];
		q = (sq*)malloc(sizeof(sq));
		q->x = end->x;
		q->next = NULL;
		unique_lambda[i] = q;
		//遍历value
		for (end = end->next; end != NULL; end = end->next) {
			//当value中x值与第一个相差大于ERROR时，将x插入到unique_lambda[i]尾部
			if (fabs(end->x - value[i]->x) > error) {
				q->next = (sq*)malloc(sizeof(sq));
				q->next->x = end->x;
				q->next->next = NULL;
				q = q->next;
			}
			//当value中x值与第一个相差小于ERROR时，跳出循环
			else
				break;
		}
	}



	/*
	本步可以省略，本步的目的是为了检查数据
	//（4）打开文件unique value.txt，并将得到的(lambda,x1,x2,x3,...)打印到unique value.txt中
	p = fopen("unique value.txt", "w");
	//检测是否成功打开
	if (p == NULL)
		printf("Open failed\n");

	else {
		//遍历unique_lambda[i]链表，将(lambda,x1,x2,x3,...)打印到unique value.txt中
		for (i = 0; unique_lambda[i] != NULL; i++) {
			lambda_now = lambda + step * i;
			//打印lambda
			fprintf(p, "%lf", lambda_now);
			//打印x
			for (end = unique_lambda[i]; end != NULL; end = end->next)
				fprintf(p, ",%lf", end->x);
			fprintf(p, "\n"); //每行结束换行  
		}
	}

	fclose(p);//释放指针
	*/


	//（5）打开文件Feigenbaum.txt，并将得到的(lambda,count)打印到Feigenbaum.txt中，count是不同的x值的个数
	p = fopen("Feigenbaum.txt", "w");
	//检测是否成功打开  
	if (p == NULL)
		printf("Open failed\n");
	
	else {
		//遍历unique_lambda[i]链表，将(lambda,count)打印到Feigenbaum.txt中
		for (i = 0, j = 0; unique_lambda[i] != NULL; i++) {
			lambda_now = lambda + i * step;
			count = 1;
			//计unique_lambda[i]中元素个数
			for (end = unique_lambda[i]->next; end != NULL; end = end->next)
				count++;
			//当出现新的倍周期点时，将(lambda,count)打印到Feigenbaum.txt中
			if (count != flag) {
				fprintf(p, "%lf,", lambda_now);
				fprintf(p, "%d\n", count);
				flag = count;
				//保存lambda到Feigenbaum中
				Feigenbaum[j] = lambda_now;
				j++;
			}
			if (j >= 7)
				break;
		}
	}

	//释放指针 
	fclose(p);



	//（6）打印Feigenbaum常数
	printf("\nFeigenbaum常数计算：\nlambda\t\t倍周期分叉\tFeigenbaum常数\n\n");
	printf("%lf\t1->2\n\n", Feigenbaum[0]);
	for (i = 1; i < 6; i++) {
		printf("%lf\t%d->%d\t\t%lf\n\n", Feigenbaum[i], int(pow(2, i)), int(pow(2, i + 1)), (Feigenbaum[i] - Feigenbaum[i - 1]) / (Feigenbaum[i + 1] - Feigenbaum[i]));
	}



	printf("\n程序运行完毕，数据输出到文件中！\n\n按任意键结束");
	getchar();
	getchar();
}