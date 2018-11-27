import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
coefficient = 0.1
omega = 0.05

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13RandomWalk\\13RandomWalk\\Random_Walk,c=%.1f,omega=%.2f.txt" % (coefficient, omega), delimiter=',')
steps = np.arange(0,1000,1)

#绘图
for i in range(0, 5):
    plt.scatter(steps, data[:,i], s=5,label="Particle%d" % (i + 1))

#添加图相关描述
plt.xlabel("N")
plt.ylabel("x")
plt.legend()
plt.suptitle("Random Walk\ncoefficient = %.1f, omega = %.2f" % (coefficient, omega))

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13RandomWalk\\13RandomWalk\\Random_Walk,c=%.1f,omega=%.2f.jpg"%(coefficient,omega)
plt.savefig(filename)

#显示图片
plt.show()