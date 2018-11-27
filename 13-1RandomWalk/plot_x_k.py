import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
type = 1
N = 100000
coefficient = 0.1
omega = 0.05

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13RandomWalk\\13RandomWalk\\particles=%d,c=%.1f,omega=%.2f.txt" % (N, coefficient, omega), delimiter=',')
steps = data[:, 0]
x = np.arange(0, 1000, 1)
y_1 = coefficient * np.sin(omega * x / 2) * np.sin(omega * (x + 1) / 2) / np.sin(omega / 2) if omega != 0 else np.zeros(1000)
y_2 = x * (1 - coefficient ** 2 / 2) + coefficient ** 2 / 2 * np.sin(omega * x) * np.cos(omega * (x + 1)) / np.sin(omega) + coefficient ** 2 * (np.sin(omega * x / 2) * np.sin(omega * (x + 1) / 2) / np.sin(omega / 2))** 2 if omega != 0 else x
x_1 = data[:,1]
x_2 = data[:,2]

#绘图
if type == 1:
    plt.plot(x, y_1, '--', label='Theoretical')
    plt.scatter(steps, x_1, s=5, color='red',label='Sampling')
    title = '$<x^1>$ - N\n'
    plt.ylabel("$<x^1>$")
elif type == 2:
    plt.plot(x, y_2, '--', label='Theoretical')
    plt.scatter(steps, x_2, s=5, color='red',label='Sampling')
    title = '$<x^2>$ - N\n'
    plt.ylabel("$<x^2>$")
plt.suptitle(title + "Particles = %d" % (N))

#添加图相关描述
plt.xlabel("N")
plt.legend()

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13RandomWalk\\13RandomWalk\\"+str(type)+","+str(N)+",c=%.1f,omega=%.2f.jpg"%(coefficient,omega)
plt.savefig(filename)

#显示图片
plt.show()