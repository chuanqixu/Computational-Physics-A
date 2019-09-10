# Computational-Physics-A
This repository is my solution to the course: Computational Physics A (instructors: Prof. Zejun Ding and Prof. Xia Sun)

## Questions

### 01: Chaos

以 $x_{n+1} = \lambda sin(\pi x_{n})$ 为迭代方程：

(1)画出系统状态随参数$\lambda$的变化图，要求包括定值状态、倍周期分叉和混沌状态；

(2)列出各个倍周期分叉处的$\lambda$值，求相应的 Feigenbaum 常数。

### 02: Julia

在复平面上任选一个参数 $C=a+ib$，画出该 $C$ 值下的Julia集(图形可彩色，也可黑白或灰度)。

### 03: DLA

进行单中心DLA模型的模拟（可以用圆形边界，也可以用正方形边界），并用两种方法计算你模拟得到的DLA图形的分形维数，求分形维数时需要作出双对数图。

### 04: Schrage

用Schrage方法编写随机数子程序，用连续两个随机数作为点的坐标值绘出若干点的平面分布图。再用$\langle X^k \rangle$测试均匀性（取不同量级的$N$值，讨论偏差与$N$的关系）、$C(l)$测试其2维独立性（总点数$N>10^7$）

### 05: Fibonacci

用16807产生器测试随机数序列中满足关系$X_{n-1}<X_{n+1}<X_n$的比重。讨论Fibonacci延迟器中出现这种关系的比重。

### 06: DirectSampling

在球坐标系$(\rho,\ \theta,\ \phi)$下产生球面上均匀分布的随机坐标点，给出其直接抽样方法。

### 07: Marsaglia

对于球面上均匀分布的随机坐标点，给出它们在$(x, y)$平面上投影的几率分布函数。并由此验证Marsaglia抽样方法 $x=2u\sqrt{1-r^2},\ y=2v\sqrt{1-r^2},\ z=1-2r^2$ 确为球面上均匀分布的随机抽样。

### 08: Cellular_Automata

在$512\times 512$的二维正方形网格上，设置几个初始状态的自旋比例值，按照Q2规则Ising自旋动力学模型，模拟体系自旋状态随时间的演化，作图比较体系初始状态和平衡状态的分布。

### 09: Acceptance-rejection_Sampling

对两个函数线型（Gauss分布和Lorentz型分布），设其一为$p(x)$，另一为$F(x)$，用舍选法对$p(x)$抽样。将计算得到的归一化频数分布直方图与理论曲线$p(x)$进行比较，讨论差异。讨论抽样效率。

$Gaussian:\ exp(-\frac{x^2}{2})\ \ Lorentzian like:\ \frac{1}{1+x^4}$

### 10: Direct_and_A-R

对一个实验谱数值曲线$p(x)$ ，自设$F(x)$，分别用直接抽样和舍选法对$p(x)$抽样。比较原曲线和抽样得到的曲线并验证。讨论抽样效率。

### 11: Integral

用Monte Carlo方法计算如下定积分，并讨论有效数字位数。

$\int_0^2dx\sqrt{x+\sqrt{x}}$，

$\int_0^{9/10}dx\int_0^{4/5}dy\int_0^{9/10}dz\int_0^2du\int_0^{13/10}dv(6-x^2-y^2-z^2-u^2-v^2)$

### 12: Central_Limit_Theorem

自设若干个随机分布（相同或不同分布，它们有相同或不同的$\mu$和$\sigma^2$），通过Monte Carlo模拟，验证中心极限定理成立（$N =2、5、10$）。

### 13-1 RandomWalk

Monte Carlo方法研究正弦外力场$\propto \sin{wt}$中的随机行走。

### 13-2 OrientationalRW

研究有取向的布朗粒子（如纳米棒）的随机行走，计算取向的自相关函数：$C(t)=\langle u_x(t)u_x(0)\rangle$，其中$u_x$为取向单位矢量在$x$轴上的投影。

### 14: RandomWalk

数值研究$d\ (d=1,2,3)$维空间中随机行走返回原点的几率$P_d$，讨论它随步数$N$的变化关系$P_d(N)$，能否定义相关的指数值？

### 16: Percolation

推导三角格子点阵上座逾渗的重整化群变换表达式$p'=R(p)$，其中端－端连接的条件是3个格点中的2个是占据态，求临界点$p_c$与临界指数$\nu$，与正确值（表1.6.1.3-1）相比较。

### 17: Debate

请以学生C的身份参与相关概念的辩论。详细题目见报告。

### 18: MC

一篇应用MC方法研究聚苯乙烯小球自组装结构的研究论文“Formation of waferscale monolayer close packed polystyrene spheres template by thermally assisted selfassembly”在投稿某刊物后被审稿人拒稿，现在作者欲向刊物编辑申诉。请根据文章内容和审稿人评审意见，撰写申诉理由（你认为，作者在文中阐述的方法和概念以及审稿人的评论意见有哪些是合理的，哪些是需要修正的，或者哪些是需要进一步阐明的）。进一步，如果你是作者的话，你将如何进行该工作以及建立模型？

### 19: Metropolis

设体系的能量为$H=x^2/2\sigma_x^2+y^2/2\sigma_y^2$（以$kT$为单位），采用Metropolis抽样法计算$\langle x^2 \rangle,\langle y^2\rangle,\langle x^2+y^2\rangle$并与解析结果进行比较。抽样时在2维平面上依次标出Markov链点分布，从而形象地理解Markov链。

### 20: Demon

考虑一维经典粒子组成的理想气体，由于无相互作用，各粒子的能量不依赖于其位置，只需考虑它的动能，因此体系的构型即是各粒子速度坐标值的集合。给定粒子的质量、初始速度、总粒子数、总能、demon能，模拟足够多步后达到平衡时的粒子速度分布。微正则系综中没有定义温度，其数值由$\frac{1}{2}kT=\frac{1}{2}m\langle v^2\rangle$给出，求平衡时的温度值。
