import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
N = 5
type = 'add'
filename = "E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\12Central_Limit_Theorem\\12Central_Limit_Theorem\\"+type+","+str(N)+".txt"

#读取数据
data = np.loadtxt(filename)
rate = data[0]
#block = int(np.max(data) - np.min(data))
x = np.arange(-5.0, 5.0, 0.001)
y1 = math.sqrt(1.0 / (2 * math.pi)) * np.exp(-x ** 2 / 2)

#绘图
plt.plot(x, y1, color='red',label='Gaussian')
plt.hist(data,bins=100,density=True,range=(-5,5),label='Sampling',edgecolor='white')

#添加图相关描述
plt.xlabel("X")
plt.ylabel("Y")
plt.legend()

#图片名称
if type == '01':
    title = 'Zero-One Distribution\n'
elif type == 'binom':
    title = 'Binomial Distribution\n'
elif type == 'uni':
    title = 'Unitary Distribution\n'
elif type == 'norm':
    title = 'Normal Distribution\n'
elif type == 'expo':
    title = 'Expotential Distribution\n'
elif type == 'add' :
    title = 'Normal + Expotential\n'
plt.suptitle(title + "N=%d" % (N))

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\12Central_Limit_Theorem\\12Central_Limit_Theorem\\"+type+","+str(N)+".jpg"
plt.savefig(filename)

#显示图片
plt.show()