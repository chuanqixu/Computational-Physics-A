import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib

#输入文件想要打印的图片的数据文件信息
type = '1ln'

#读取数据
data = np.loadtxt("E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\14RandomWalk\\14RandomWalk\\data.txt", delimiter=',')
x = []
y = []

#图片名称
if type == '0':
    title = '$P_d(N)$ - N'
    plt.scatter(data[:, 0], data[:, 1], s=5, c='r', label='d=1')
    plt.scatter(data[:, 0], data[:, 2], s=5, c='g', label='d=2')
    plt.scatter(data[:, 0], data[:, 3], s=5, c='b', label='d=3')
    plt.ylabel("$P_d(N)$")
elif type == '1':
    title = '$P_d(N)$ - N (d=1)'
    for i in range(2, 102, 2):
        x.append(i)
        y.append(np.math.factorial(i) * np.power(0.5, i) / (np.math.factorial(i / 2) * np.math.factorial(i / 2)))
    plt.plot(x, y, c='r', label="Theoretical")
    plt.scatter(data[:, 0], data[:, 1], c='b', label="Random Walk")
    plt.ylabel("$P_d(N)$")
elif type == '1ln':
    plt.xlabel("lnN")
    k, b = np.polyfit(np.log(data[:, 0]), np.log(data[:, 1]), 1)
    xs = np.arange(0.5, 5.5, 1)
    ys = k * xs + b
    plt.plot(xs, ys, c='green', label='Fitted Curve')
    title = 'ln$P_d(N)$ - lnN (d=1)\nFitted Curve: y = %.3f x + %.3f'%(k,b)
    for i in range(2, 102, 2):
        x.append(i)
        y.append(np.math.factorial(i) * np.power(0.5, i) / (np.math.factorial(i / 2) * np.math.factorial(i / 2)))
    plt.plot(np.log(x), np.log(y), c='r', label="Theoretical")
    plt.scatter(np.log(data[:, 0]), np.log(data[:, 1]), s=10, c='b', label="Random Walk")
    plt.ylabel("ln$P_d(N)$")
elif type == '2':
    title = '$P_d(N)$ - N (d=2)'
    for i in range(2, 102, 2):
        x.append(i)
        s = 0
        for j in range(0, int(i / 2) + 1):
            s += np.math.factorial(i) * 0.25 ** i / (np.math.factorial(j) * np.math.factorial(i / 2 - j))** 2
        y.append(s)
    plt.plot(x, y, c='r', label="Theoretical")
    plt.scatter(data[:, 0], data[:, 2], c='b', label="Random Walk")
    plt.ylabel("$P_d(N)$")
elif type == '2ln':
    plt.xlabel("lnN")
    k, b = np.polyfit(np.log(data[:, 0]), np.log(data[:, 2]), 1)
    xs = np.arange(0.5, 5.5, 1)
    ys = k * xs + b
    plt.plot(xs, ys, c='green', label='Fitted Curve')
    title = 'ln$P_d(N)$ - lnN (d=2)\nFitted Curve: y = %.3f x + %.3f'%(k,b)
    for i in range(2, 102, 2):
        x.append(i)
        s = 0
        for j in range(0, int(i / 2) + 1):
            s += np.math.factorial(i) * 0.25 ** i / (np.math.factorial(j) * np.math.factorial(i / 2 - j))** 2
        y.append(s)
    plt.plot(np.log(x), np.log(y), c='r', label="Theoretical")
    plt.scatter(np.log(data[:, 0]), np.log(data[:, 2]), s=10, c='b', label="Random Walk")
    plt.ylabel("ln$P_d(N)$")
elif type == '3':
    title = '$P_d(N)$ - N (d=3)'
    for i in range(2, 102, 2):
        x.append(i)
        s = 0
        for j in range(0, int(i / 2) + 1):
            for k in range(0, int(i / 2) - j + 1):
                s += np.math.factorial(i) * (1.0 / 6)**i / (np.math.factorial(j) * np.math.factorial(k) * np.math.factorial(i / 2 - j - k))** 2
        y.append(s)
    plt.plot(x, y, c='r', label="Theoretical")
    plt.scatter(data[:, 0], data[:, 3], s=10, c='b', label="Random Walk")
    plt.ylabel("$P_d(N)$")
elif type == '3ln':
    plt.xlabel("lnN")
    k, b = np.polyfit(np.log(data[:, 0]), np.log(data[:, 3]), 1)
    xs = np.arange(0.5, 5.5, 1)
    ys = k * xs + b
    plt.plot(xs, ys, c='green', label='Fitted Curve')
    title = 'ln$P_d(N)$ - lnN (d=3)\nFitted Curve: y = %.3f x + %.3f'%(k,b)
    for i in range(2, 102, 2):
        x.append(i)
        s = 0
        for j in range(0, int(i / 2) + 1):
            for k in range(0, int(i / 2) - j + 1):
                s += np.math.factorial(i) * (1.0 / 6)**i / (np.math.factorial(j) * np.math.factorial(k) * np.math.factorial(i / 2 - j - k))** 2
        y.append(s)
    plt.plot(np.log(x), np.log(y), c='r', label="Theoretical")
    plt.scatter(np.log(data[:, 0]), np.log(data[:, 3]), s=10, c='b', label="Random Walk")
    plt.ylabel("ln$P_d(N)$")
plt.suptitle(title)
plt.legend()

#保存图片
filename="E:\\中科大学习文件\\大三秋季学期\\计算物理\\作业\\14RandomWalk\\14RandomWalk\\"+type+".jpg"
plt.savefig(filename)

#显示图片
plt.show()