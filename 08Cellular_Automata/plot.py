import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
num = num=10000
#n = 100 #n为指定的次数

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\08Cellular_Automata\\08Cellular_Automata\\num=%d.txt" % (num), delimiter=",")
x0s = []
y0s = []
x1s = []
y1s = []
ratio1 = data[512][0]
ratio2 = data[1025][0]

#设置画布大小
"""
fig=plt.figure(figsize=(5.12*1.418,5.12*1.422))
"""
fig = plt.figure(figsize=(12, 5.12))
ax1 = fig.add_subplot(1, 2, 1)
ax2 = fig.add_subplot(1, 2, 2)

#绘图
"""
#绘制指定次数时的图像
for x in range(512*(n-1), 512*n):
    for y in range(0, 512):
        if data[x][y] == 1:
            x0s.append(int(x)%512)
            y0s.append(y)
        #else:
        #    x1s.append(int(x)%512)
        #    y1s.append(y)
"""
#绘制单次图像
for x in range(0, 512):
    for y in range(0, 512):
        if data[x][y] == 1:
            x0s.append(x)
            y0s.append(y)
        else:
            x1s.append(x)
            y1s.append(y)
ax1.scatter(x1s, y1s, s=0.001, c='red')
ax1.scatter(x0s, y0s, s=0.001, c='white')

x0s = []
y0s = []
x1s = []
y1s = []
for x in range(513, 1025):
    for y in range(0, 512):
        if data[x][y] == 1:
            x0s.append(x)
            y0s.append(y)
        else:
            x1s.append(x)
            y1s.append(y)
ax2.scatter(x1s, y1s, s=0.001, c='red')
ax2.scatter(x0s, y0s, s=0.001, c='white')

"""
plt.scatter(x1s, y1s, s=0.001, c='white')
plt.scatter(x0s, y0s, s=0.001, c='red')
"""
#分别画白点在先和白点在后的图
"""
ax1.scatter(x1s, y1s, s=0.001, c='white')
ax1.scatter(x0s, y0s, s=0.001, c='red')

ax2.scatter(x0s, y0s, s=0.001, c='red')
ax2.scatter(x1s, y1s, s=0.001, c='white')
"""


#添加图相关描述
"""
plt.xlabel = ("X")
plt.ylabel = ("Y")
"""
ax1.xlabel = ("X")
ax1.ylabel = ("Y")
ax2.xlabel = ("X")
ax2.ylabel = ("Y")

#图片名称
plt.suptitle("Ising Model\nNum = %d" % (num))
ax1.set_title("Start: ratio = %.5f" % (ratio1))
ax2.set_title("End: ratio = %.5f" % (ratio2))

#保存图片
#plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\08Cellular_Automata\\08Cellular_Automata\\num=%d,n=%d.jpg" % (num,n))
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\08Cellular_Automata\\08Cellular_Automata\\num=%d.jpg" % (num))

#显示图片
plt.show()