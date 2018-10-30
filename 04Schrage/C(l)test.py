import numpy as np
import matplotlib.pyplot as plt
import math

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\04Schrage\\04Schrage\\C(l)test,start=1000.txt",delimiter=',')

colors = ['green',
'purple',
'aqua',
'aquamarine',
'red',
'yellow',
'bisque',
'grey',
'magenta',
'blue']

num=[]
for n in range(0, len(data)):
    num.append(math.log(data[n, 0], 10))

#画折线图
for l in range(1,11):
    plt.plot(num, data[:, l], c=colors[l-1],label='l = %d'%l)
plt.plot((2,8),(0,0),'--',c='black')


#添加图相关描述
plt.xlabel("ln(N)")
plt.ylabel("C(l)")
plt.legend(loc='upper right')

#图片名称
plt.suptitle("C(l) Test")

#保存图片
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\04Schrage\\04Schrage\\C(l)test")

#显示图片
plt.show()