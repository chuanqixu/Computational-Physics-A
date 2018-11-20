import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
num=100000

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\09Acceptance-rejection_Sampling\\09Acceptance-rejection_Sampling\\num=%d.txt" % (num), delimiter=",")
rate = data[0]
block = int(data[1])
x = np.arange(-3.0, 3.0, 0.001)
y1 = math.sqrt(1.0 / (2 * math.pi)) * np.exp(-x ** 2 / 2)
y2 = np.array(0.92153762 / (1 + x ** 4))

#绘图
plt.plot(x, y1, color='red',label='Gaussian')
#plt.plot(x, y2, color='blue', label='Lorentzian Like')
plt.hist(data[2:],bins=block,density=True,range=(-3,3),label='Sampling',edgecolor='black')

#添加图相关描述
plt.xlabel("X")
plt.ylabel("Y")
plt.legend()

#图片名称
plt.suptitle("Acceptance-rejection Sampling\nNum=%d, accept=%.5f" % (num, rate))

#保存图片
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\09Acceptance-rejection_Sampling\\09Acceptance-rejection_Sampling\\num=%d.jpg" % (num))

#显示图片
plt.show()