import matplotlib.pyplot as plt              
import numpy as np

#读取data.dat中数据到data中
data = np.loadtxt("data.dat", delimiter=",")

#求lambda的下限和上限
lambda_begin = data[0][0]
lambda_end = data[-1][0]
#求num，num为同一个lambda的x的最大的个数
j = 0
for i in range(0,len(data[:,0])):
    if data[i][0] == data[0][0]:
        j += 1
    else:
        break
num = j
#求step
step=data[j][0]-data[0][0]


#画散点图
plt.scatter(data[:, 0], data[:, 1],s=1)
#添加图相关描述
plt.xlabel("$\lambda$")
plt.ylabel("x")
plt.suptitle('$\lambda\in[%.3f,%.3f]\ Where\ Step=%.6f$\nEvery lambda has %d x at most' % (lambda_begin, lambda_end, step, num))
plt.xticks(list(np.arange(lambda_begin,lambda_end+step*100,step*1000)))

#显示图片
plt.show()
