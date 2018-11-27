import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
lengths = list((1, 4, 25, 50))
widths = list((1, 1, 25, 1))

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13_2OrientationRW\\13_2OrientationRW\\RC.txt", delimiter=',')

#绘图
for i in range(0,4):
    plt.scatter(data[100 * i:100 * (i + 1), 0], data[100 * i:100 * (i + 1), 1], s=10, label='a=%d, b=%d' % (lengths[i], widths[i]))

#添加图相关描述
plt.xlabel("N")
plt.ylabel("$<R^2>$")
plt.legend()
plt.suptitle("$<R^2>$ - N")

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\13_2OrientationRW\\13_2OrientationRW\\R2.jpg"
plt.savefig(filename)

#显示图片
plt.show()