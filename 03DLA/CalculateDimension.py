import matplotlib.pyplot as plt
import numpy as np

#读取数据
data_Boxcount = np.loadtxt("Boxcount.txt", delimiter=',')
data_Sandbox = np.loadtxt("Sandbox.txt", delimiter=",")

#读取相关参数
num = data_Sandbox[-2][0]
generate_particle_range = data_Sandbox[-2][1]
edge = data_Sandbox[-1][0]
picture_range = data_Sandbox[-1][1]

plt.figure(figsize=(5,10))

#对盒计数法求得的点线性拟合
X_Boxcount = np.log(data_Boxcount[0:-2, 0])
Y_Boxcount = np.log(data_Boxcount[0:-2, 1])
coefficient_Boxcount = np.polyfit(X_Boxcount, Y_Boxcount, 1)
fit_Boxcount = np.poly1d(coefficient_Boxcount)

#对Sanbox法求得的点线性拟合
X_Sandbox = np.log(data_Sandbox[0:-2, 0])
Y_Sandbox = np.log(data_Sandbox[0:-2, 1])
coefficient_Sandbox = np.polyfit(X_Sandbox, Y_Sandbox, 1)
fit_Sandbox = np.poly1d(coefficient_Sandbox)

#画盒计数散点图与拟合直线
ax1 = plt.subplot(211)
plt.plot(X_Boxcount, Y_Boxcount, '.', label='Boxcount Points')
plt.plot(X_Boxcount, fit_Boxcount(X_Boxcount), c='r', label='Linear Fit')
plt.legend(loc=4)
ax1.set_title('Boxcount for %d Particles\nf(x) = %f x + %f' %(num, fit_Boxcount[1], fit_Boxcount[0]))

#画Sanbox散点图与拟合直线
ax2 = plt.subplot(212)
plt.plot(X_Sandbox, Y_Sandbox, '.',label='Sandbox Pointsr')
plt.plot(X_Sandbox, fit_Sandbox(X_Sandbox), c='r',label='Linear Fit')
plt.legend(loc=4)
ax2.set_title('Sandbox for %d Particles\nf(x) = %f x + %f' % (num, fit_Sandbox[1], fit_Sandbox[0]))

#添加图相关描述
plt.xlabel("ln(r)")
plt.ylabel("ln(N)")

#图片名称
#plt.suptitle('Sandbox for %d Particles\nf(x) = %f x + %f' % (num, fit_Sandbox[1], fit_Sandbox[0]))

#保存图片
plt.savefig('%dCalculateDimension.jpg' % num)

#显示图片
plt.show()