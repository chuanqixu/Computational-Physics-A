import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

plt.figure(figsize=(8,6))

#输入文件想要打印的图片的数据文件信息
start = 0
p = 1
q = 2

#读取数据
#data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\05Fibonacci\\05Fibonacci\\16807,start=%d.txt" % (start), delimiter=",")
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\05Fibonacci\\05Fibonacci\\Fibonacci,%d,%d.txt" % (p, q), delimiter=",")

colors = ['green',
'purple',
'aqua',
'aquamarine',
'red',
'yellow',
'bisque',
'grey',
'magenta',
'blue',
'pink']
num=[]
for n in range(1, len(data)):
    num.append(math.log(data[n, 0], 10))

#画单start折线图
#plt.plot(num, data[:, 1])

#画多start折线图
for k in range(1,len(data[0])):
    plt.plot(num, data[1:, k], c=colors[k - 1], label='start = %d' % (data[0, k]))

#plt.plot((2, 8), (1 / 6, 1 / 6), '--')
#plt.plot((2, 7), (1 / 6, 1 / 6), '--')

#添加图相关描述
plt.xlabel("ln(N)")
plt.ylabel("Count")
plt.legend(loc=2,ncol=2)

#图片名称
#plt.suptitle("16807_RNG,start=%d" % (start))
#plt.suptitle("16807_RNG, Multi-Start")
plt.suptitle("Finonacci_RNG, Multi-Start")

#保存图片
#plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\05Fibonacci\\05Fibonacci\\16807,start=%d.jpg" % (start))
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\05Fibonacci\\05Fibonacci\\Fibonacci,%d,%d.jpg" % (p,q))

#显示图片
plt.show()