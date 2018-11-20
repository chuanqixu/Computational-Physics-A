import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib
from mpl_toolkits.mplot3d import Axes3D

#输入文件想要打印的图片的数据文件信息
num=10000

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\06DirectSampling\\06DirectSampling\\num=%d.txt" % (num), delimiter=",")
x = data[:, 0]
y = data[:, 1]
z = data[:, 2]

#绘图
ax = plt.subplot(111, projection='3d')
ax.scatter(x,y,z,s=0.1)
#plt.scatter(x, y,s=0.1)

#添加图相关描述
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
#plt.xlabel("X")
#plt.ylabel("Y")

#图片名称
plt.suptitle("Direct Sampling, Num=%d" % (num))

#保存图片
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\06DirectSampling\\06DirectSampling\\num=%d.jpg" % (num))
#plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\06DirectSampling\\06DirectSampling\\num=%d,project.jpg" % (num))

#显示图片
plt.show()