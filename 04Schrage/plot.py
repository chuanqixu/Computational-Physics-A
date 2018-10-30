import numpy as np
import matplotlib.pyplot as plt

#输入文件想要打印的图片的数据文件信息
num =1000000
start = 1

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\04Schrage\\04Schrage\\num=%d,start=%d.txt" % (num, start), delimiter=",")

#画散点图
plt.scatter(data[:, 0], data[:, 1], s=2, c='r')

#添加图相关描述
plt.xlabel("X")
plt.ylabel("Y")

#图片名称
plt.suptitle("num= % d, start= % d" % (num, start))

#保存图片
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\04Schrage\\04Schrage\\num=%d,start=%d.jpg" % (num, start))

#显示图片
plt.show()