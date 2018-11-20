import matplotlib.pyplot as plt
import numpy as np

#读取data.dat中数据到data中
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\11Integral\\11Integral\\1.txt", delimiter=",")

#读取相关参数
lnN = np.log10(data[:, 0])
error = np.log10(np.abs(data[:, 1]))

#画散点图
plt.scatter(lnN, error, s=10, c='r', label='Sampling')

#线性拟合
coefficient = np.polyfit(lnN, error, 1)  #一次多项式拟合，相当于线性拟合
p1 = np.poly1d(coefficient)
x = (1, 7)
y = p1(x)
plt.plot(x, y, label='Fit')

#添加图相关描述
plt.xlabel("ln N")
plt.ylabel("Error")
plt.legend()

#图片名称
plt.suptitle('Error - ln N\ny = %.5f x + %.5f ' % (coefficient[0], coefficient[1]))

#保存图片
plt.savefig('E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\11Integral\\11Integral\\1.jpg')

#显示图片
plt.show()