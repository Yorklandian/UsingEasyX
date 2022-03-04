# UsingEasyX
使用EasyX图形API，用lua封装实现了几个操作图像的函数

如果在机器上运行可能要先安装EasyX的库，安装见官网https://docs.easyx.cn/zh-cn/setup

存在的问题：
  1 调用API旋转后会把一部分图片截丢，所以矩形图片旋转几次后就会变成圆形
  2 SlideTo实现时没有调整旋转，而是直接滑动过去
  
  注：
  lua中调用SlideTo，给出的坐标是像素坐标，速度最大为1，速度为1时进行瞬移。 
