import matplotlib.pyplot as plt
import numpy as np

#读取data.dat中数据到data中
data = np.loadtxt("data.txt", delimiter=",")

#读取相关参数
num = data[-2][0]
generate_particle_range = data[-2][1]
edge=data[-1][0]
picture_range=data[-1][1]

#画散点图
plt.scatter(data[0, 0], data[0, 1], s=2,c='r')
plt.scatter(data[1:-2, 0], data[1:-2, 1],s=0.5)

#添加图相关描述
plt.xlabel("X")
plt.ylabel("Y")

#下面注释的两行是x、y轴范围，对于粒子数较小的情况，可以用下面被注释的范围让图片变大
#plt.xlim(picture_range / 2 - generate_particle_range / 2,picture_range / 2 + generate_particle_range / 2)
#plt.ylim(picture_range / 2 - generate_particle_range / 2,picture_range / 2 + generate_particle_range / 2)

#当图片较大时，用下面两行作为x、y轴范围
plt.xlim(0, picture_range)
plt.ylim(0, picture_range)

#图片名称
plt.suptitle('%d Particles in Aggregation'%num)

#保存图片
plt.savefig('%dParticles.jpg' % num)

#显示图片
plt.show()