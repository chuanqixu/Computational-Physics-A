import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
coefficient = 0
omega = 0
x = 1000
E = coefficient * np.sin(omega * x / 2) * np.sin(omega * (x + 1) / 2) / np.sin(omega / 2) if math.fabs(omega) > 1e-6 else 0
X_2 = x * (1 - coefficient ** 2 / 2) + coefficient ** 2 / 2 * np.sin(omega * x) * np.cos(omega * (x + 1)) / np.sin(omega) + coefficient ** 2 * (np.sin(omega * x / 2) * np.sin(omega * (x + 1) / 2) / np.sin(omega / 2))** 2 if math.fabs(omega) > 1e-6 else x
Var = X_2 - E ** 2
xs = np.arange(E - 3*np.sqrt(Var), E + 3*np.sqrt(Var), 0.01)

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13RandomWalk\\13RandomWalk\\end_x,c=%.1f,omega=%.2f.txt" % (coefficient, omega))

#绘图
plt.plot(xs, 1 / math.sqrt(2 * math.pi * Var) * np.exp(-(xs - E)** 2 / (2 * Var)), '--', label="Normal Distribution", c='blue')
plt.hist(data, density=True, bins=25, label='Sampling', color='red',edgecolor='white')

#添加图相关描述
plt.xlabel("x")
plt.ylabel("Counts")
plt.legend()
plt.suptitle("End Position\ncoefficient = %.1f, omega = %.2f" % (coefficient, omega))

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13RandomWalk\\13RandomWalk\\end_x,c=%.1f,omega=%.2f.jpg"%(coefficient,omega)
plt.savefig(filename)

#显示图片
plt.show()