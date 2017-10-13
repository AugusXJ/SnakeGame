# 贪吃蛇小游戏（Greedy Snake）
---------------------------------------

这个小游戏代码大概1000行左右，用C++面向对象知识和一些控制台的API共同完成，算是对C++知识的一个小练习，继承多态和模板功能用的不是很熟练，代码里只试着用了一下。 游戏可扩充的地方也很多，比如多条蛇多食物等等。

## 功能说明
就是经典的贪吃蛇游戏。

1. 游戏构造
在控制台中建立一个坐标系，对坐标点设置对象，所以对任意组件的操作最终归为对点的操作。

2. 动画的生成
使用`sleep(int)`函数使得画面产生一个延时，从而产生动画的视觉效果。

3. 与玩家的交互
我使用的是`_kbhit()`函数来判断是否有键盘输入，并用`_getch()`来获得键盘的输入。从而实现交互。

## 类
### Controller类
游戏的核心部分，各个画面的编写：SelectInterface（选择画面），GameInterface（游戏画面）。算是游戏的整体框架。
- `speed` --> 游戏速度
- `score` --> player得分
- `color` --> 颜色
- `key` --> 选择的难度

### Snake类
也就是player实际操作对象，完成蛇的吃食物，移动，撞击判断，死亡判断等等功能。
- `snake` --> 双向队列，保存Point对象
- `direct` --> 蛇的方向
- `shape` --> 用`●`来表示蛇
- `color` --> 绿色表示蛇的颜色

### Point类
画面表现形式的基类，因为需要在控制台输出，所以每个Point具有坐标属性，也就是控制台的位置。
- `x,y` --> 坐标值
- `shape` --> 待输出的字符
- `color` --> 输出颜色
- `ChangePos(int, int)` --> 改变位置
- `Crash(Point&)` --> 撞击判断


### Food类
用随机器在地图中随机生成食物，属于Point类的派生类。

### Window类
设置控制台的窗口大小，以及与控制台API的一些借口函数，更便于游戏开发中使用。