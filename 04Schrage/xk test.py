import numpy as np
import matplotlib.pyplot as plt
import math

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\04Schrage\\04Schrage\\xk test,start=1999.txt",delimiter=',')

colors = ['r', 'y', 'b', 'g', 'pink']
num=[]
for n in range(0, len(data)):
    num.append(math.log(data[n, 0], 10))

#画折线图
for k in range(1,6):
    plt.plot(num, data[:, k], c=colors[k - 1],label='k = %d'%k)
plt.plot((2,8),(0,0),'--',c='black')


#添加图相关描述
plt.xlabel("ln(N)")
plt.ylabel("Difference")
plt.legend()

#图片名称
plt.suptitle("<x^k> Test")

#保存图片
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\04Schrage\\04Schrage\\xk test")

#显示图片
plt.show()