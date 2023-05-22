# DigitRecongnition
---
特征包括高亮块个数和位置
|数字  |高亮块个数|
|----- |---------|
|0     |   6	|
|1     |   2	|
|2     |   5	|
|3     |   5	|
|4	   |   4	|
|5     |   5	|
|6     |   6	|
|7     |   3	|
|8     |   7	|
|9     |   6	|

## 预处理
1. 灰度处理
2. 高斯模糊
3. 二值化处理

## 提取中心点
1. 首先是提取识别到每个管,用矩形框出来
2. 找到每个矩形的中心点
3. 找到最中间的那个数码管中心点
## 提取特征向量
1. 对各个中点进行标记,
标记时是以中心点作为参考点,在x和y方向上分别判断
例如序号为0的数码管会被标记为[middle,middle]
序号为1的数码管会被标记为[UP,Left]
2. 提取特征向量

9-1 太亮需要提高高斯模糊
9-2 太暗需要降低高斯模糊
