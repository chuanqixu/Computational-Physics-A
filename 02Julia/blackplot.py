import matplotlib.pyplot as plt
import numpy as np

#读取data.dat中数据到data中
data = np.loadtxt("data.txt", delimiter=" ")
xyrange = data[0][0]
step = data[0][1]
num = data[0][2]
x_c = data[1][0]
y_c = data[1][1]
large_radius = data[1][2]

#dataplot记录处于Julia set中的点，当迭代次数是num时就认为处于Julia集中
dataplot = []
for i in range(2,len(data)):
    if data[i][2] == num:
        dataplot.append([data[i, 0], data[i, 1]])

#画散点图
dataplot = np.array(dataplot)
if len(dataplot) != 0:
    plt.scatter(dataplot[:, 0], dataplot[:, 1], s=1, c='b')

#添加图相关描述
plt.xlabel("Re(z)")
plt.ylabel("Im(z)")
plt.suptitle('C = %.3f + i %.3f\nStep = %.3f. Maximum Iteration = %d. Radius = %.1f' %
             (x_c, y_c, step, num, large_radius))

#显示图片
plt.show()