[TOC]

## 实验

### 实验设计
本实验分别使用了不同的方法对同一数据集进行IPv6地址扫描空间生成。

在Baseline中，我们使用```leftMostIndex```指标来进行空间划分；在Experiment中，我们使用```maxCovering```来进行空间划分，并使用```OutlierSeedDetection```方法剔除“异常”的种子。

两个划分过程均使用了```SpacePartition```方法，这个方法接受一个函数指针，来指定是基于```leftMostIndex```还是```maxCovering```划分。这个方法是基于广度优先遍历的，对于划分后规模大于 $\beta$ 的种子簇继续插入队列进行划分，小于 $\beta$ 的进行输出。

剔除“异常”种子的过程中，我们对种子计算了```weight```指标，对```weight```大于```threshold```的种子进行剔除。

最后，我们分别对两种方法中生成的种子簇进行聚合，生成地址空间，对于所有种子相同的半字节的维度，我们将其聚合成固定维，否则聚合成自由维，例如：

```
0.2a0107c8aacb0258505400fffec5f4af
1.2a0107c8aacb02710000000000000001
2.2a0107c8aacb027e10de51e8eb667583
3.2a0107c8aacb027f0000000000000001
4.2a0107c8aacb02b20000000000000001
5.2a0107c8aacb02ba505400fffee8eb27
6.2a0107c8aacb02c4505400fffe8312eb
```
我们将其聚合成：
```
2a0107c8aacb02***0**************
```

由于C++没有原生的大整数计算方法，所以我们使用Python对地址空间大小进行计算。在两个实验中，我们会两者指定相同的 $\beta$ 值，并不断改变 $\beta$ 和```threshold```，观察实验结果。

### 说明

原项目[地址](https://github.com/Lab-ANT/6Forest)，本项目[地址](https://github.com/uminomanimani/6ForestCpp/)。

#### 需求
```
Python >= 3.8
C++ >= 11
```

#### 构建项目
如果您使用的编译器是g++，那么需要在编译的时候指定```-std=c++11```选项，即：
```bash
g++ -std=c++11 -o main *.cpp
```
如果编译器是clang++，那么需要指定```-std=c++14```：
```bash
clang++ -std=c++14 -o main *.cpp
```
在使用cmake编译时，也需要在```CMakeLists.txt```中指定相应的标准，例如指定C++11标准：
```cmake
set(CMAKE_CXX_STANDARD 11)
```

#### 执行代码
请确保可执行文件，```seeds```文件以及```evaluate.py```文件在同一文件夹下。在该文件夹下执行：
```bash
./main & python ./evaluate.py
```
会在同一目录下生成```Baseline.txt```以及```Experiment.txt```文件。```evaluate.py```会根据这两者计算生成的扫描空间的大小并进行比较。

### 结果

我们分别设置```threshold```（这个数值是一个浮点数）为2、4、6、8、10直到18， $\beta$ 为8、16、32直到256来进行测试。实验结果如下：

<html>
<head>
    <meta charset="utf-8" />
</head>

<body>
    <table>
        <tr>
            <td colspan="2" t="z" id="sjs-A1"></td>
            <td rowspan="2" t="s" id="sjs-C1">Baseline</td>
            <td rowspan="2" t="s" id="sjs-D1">Experiment</td>
        </tr>
        <tr>
            <td t="s" id="sjs-A2">beta</td>
            <td t="s" id="sjs-B2">threshold</td>
        </tr>
        <tr>
            <td rowspan="9" t="n" id="sjs-A3">8</td>
            <td t="n" id="sjs-B3">2</td>
            <td rowspan="9" t="n" id="sjs-C3">6.938E+32</td>
            <td t="n" id="sjs-D3">9.744E+26</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B4">4</td>
            <td t="n" id="sjs-D4">9.239E+28</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B5">6</td>
            <td t="n" id="sjs-D5">3.247E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B6">8</td>
            <td t="n" id="sjs-D6">3.453E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B7">10</td>
            <td t="n" id="sjs-D7">3.659E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B8">12</td>
            <td t="n" id="sjs-D8">6.906E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B9">14</td>
            <td t="n" id="sjs-D9">6.933E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B10">16</td>
            <td t="n" id="sjs-D10">6.934E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B11">18</td>
            <td t="n" id="sjs-D11">6.935E+32</td>
        </tr>
        <tr>
            <td rowspan="5" t="n" id="sjs-A12">16</td>
            <td t="n" id="sjs-B12">2</td>
            <td rowspan="5" t="n" id="sjs-C12">2.126E+33</td>
            <td t="n" id="sjs-D12">4.794E+30</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B13">4</td>
            <td t="n" id="sjs-D13">2.831E+31</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B14">6</td>
            <td t="n" id="sjs-D14">4.151E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B15">8</td>
            <td t="n" id="sjs-D15">7.844E+32</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B16">10</td>
            <td t="n" id="sjs-D16">1.130E+33</td>
        </tr>
        <tr>
            <td rowspan="5" t="n" id="sjs-A17">32</td>
            <td t="n" id="sjs-B17">2</td>
            <td rowspan="5" t="n" id="sjs-C17">1.850E+34</td>
            <td t="n" id="sjs-D17">5.591E+33</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B18">4</td>
            <td t="n" id="sjs-D18">5.981E+33</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B19">6</td>
            <td t="n" id="sjs-D19">1.156E+34</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B20">8</td>
            <td t="n" id="sjs-D20">1.195E+34</td>
        </tr>
        <tr>
            <td t="n" id="sjs-B21">10</td>
            <td t="n" id="sjs-D21">1.230E+34</td>
        </tr>
        <tr>
            <td t="n" id="sjs-A22">64</td>
            <td t="n" id="sjs-B22">8</td>
            <td t="n" id="sjs-C22">4.587E+34</td>
            <td t="n" id="sjs-D22">3.895E+34</td>
        </tr>
        <tr>
            <td t="n" id="sjs-A23">128</td>
            <td t="n" id="sjs-B23">8</td>
            <td t="n" id="sjs-C23">5.658E+34</td>
            <td t="n" id="sjs-D23">4.999E+34</td>
        </tr>
        <tr>
            <td t="n" id="sjs-A24">256</td>
            <td t="n" id="sjs-B24">8</td>
            <td t="n" id="sjs-C24">2.058E+35</td>
            <td t="n" id="sjs-D24">2.047E+35</td>
        </tr>
    </table>
</body>
</html>

不难看出，在 $\beta$ 固定的情况下，随着```threshold```的增长，Experiment组的划分空间会发生明显膨胀，并且Experiment越来越接近Baseline。这是因为，从直观上来说```threshold```指定了对被筛选的种子的“宽容度”，```threshold```越小，特征与其他种子越不相似的种子会更容易被剔除，而```threshold```越大，算法对种子的特征会越不敏感，对通过的种子会越宽容。

而在```threshold```固定的情况下，增加 $\beta$ 的值，同样会造成两组扫描空间的急剧上升。这是因为， $\beta$ 指定了```SpacePartition```对种子簇停止划分的临界值，该值越大，那么停止搜索的时候种子簇大小越大。种子簇越大，那么不同特征的种子在簇中出现的概率也越大，这增加了自由维出现的概率。

最后，在小 $\beta$ 和```threshold```的情况下（如 $\beta = 8$ ，threshold=4），使用```maxCovering```指标和```OutlierSeedDetection```方法对种子簇进行划分会显著减少自由维的数量，这使得待搜索的空间大大减少。因此，在实际应用中，我们可以指定一个合适的 $\beta$ 和```threshold```来满足扫描需要。

### 鸣谢

这项工作是在@马立开、@周芝丹、@段海岳 以及@李志扬 的共同努力下完成的。
