import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
num=1

#读取数据
data1 = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\10Direct_and_A-R\\10Direct_and_A-R\\data.TXT", delimiter='\t')
data2 = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\10Direct_and_A-R\\10Direct_and_A-R\\direct_num=%d.txt" % (num))
data3 = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\10Direct_and_A-R\\10Direct_and_A-R\\ra_num=%d.txt" % (num))
energy = data1[:, 0]
count = data1[:, 1]
sum = np.sum(count)
rate = count / sum
efficiency = data3[-1]

#绘图
plt.bar(energy, rate, label='Original', width=1)
#plt.plot((2900, 2994, 2994, 3013), (0.015, 0.015, 0.100, 0.100),':', color='red', label='f(x)')
plt.hist(data2, bins=114, density=True, range=(2899.5,3013.5),label='Sampling', edgecolor='red', color='red',histtype='step')
#plt.hist(data3[:-1], bins=114, density=True, range=(2899.5,3013.5),label='Sampling', edgecolor='red', color='red',histtype='step')




#添加图相关描述
plt.xlabel('Energy/eV')
plt.ylabel('Counts')
plt.legend()

#图片名称
#plt.suptitle("Acceptance-rejection Curve")
plt.suptitle("Direct Sampling\nNum = %d" % num)
#plt.suptitle("Rejection-acceptance Sampling\nNum = %d, efficiency = %.5f" % (num, efficiency))



#保存图片
plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\10Direct_and_A-R\\10Direct_and_A-R\\direct_num=%d.jpg" % (num))
#plt.savefig("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\10Direct_and_A-R\\10Direct_and_A-R\\ra_num=%d.jpg" % (num))

#显示图片
plt.show()