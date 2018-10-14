import matplotlib.pyplot as plt
import numpy as np

#读取data.dat中数据到data中
data = np.loadtxt("data.txt", delimiter=" ")

#从文件中读取相应参数
xyrange=data[0][0]
step = data[0][1]
num = data[0][2]
x_c = data[1][0]
y_c = data[1][1]
large_radius = data[1][2]

#画散点图
Julia = plt.scatter(data[2:, 0], data[2:, 1], s=1, c=data[2:, 2])

#添加图相关描述
plt.xlabel("Re(Z)")
plt.ylabel("Im(Z)")
plt.suptitle('C = %.3f + i %.3f\nStep = %.3f. Maximum Iterations = %d. Radius = %.1f' %
             (x_c, y_c, step, num, large_radius))
cbar = plt.colorbar(Julia)
cbar.ax.set_ylabel('Iterations')

#显示图片
plt.show()
