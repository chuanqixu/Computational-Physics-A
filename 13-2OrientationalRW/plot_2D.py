import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
length = 50
width = 1
num_steps = 10000

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13_2OrientationRW\\13_2OrientationRW\\RW,length=%.1lf,width=%.1lf,num=%d.txt" % (length,width,num_steps), delimiter=',')

#绘图
plt.plot(data[:,1], data[:,2],c='red',linewidth=0.3)

#添加图相关描述
plt.xlabel("X")
plt.ylabel("Y")
plt.suptitle("Random Walk\nlength = %.1lf, width = %.1lf, num = %d" % (length, width, num_steps))

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13_2OrientationRW\\13_2OrientationRW\\RW2D,length=%.1lf,width=%.1lf,num=%d.jpg"%(length,width,num_steps)
plt.savefig(filename)

#显示图片
plt.show()