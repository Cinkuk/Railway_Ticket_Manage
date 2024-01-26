### 课程大作业：使用C语言编写的模拟火车订票系统

只做了command窗口版本，没做图形界面，有一定的健壮性

### 实现的功能
1、订票

2、通过手机号或订单号查询订单

3、退票

4、支持订单候补

5、支持购买同一车次符合行进方向的任意两个站点的车票

6、从文件读入车次信息

7、结果排序

### 没做
1、中转购票

2、购买到达时间与出发时间不在同一天的车票

3、将订单信息存入文件


### 数据库
数据库为TrainDB.csv，内容格式如下

每班车次的信息格式：

|BOT| | | |
|------|-------|----|----|
|车次号|乘员定额|余票|,|
|首发站|本站出发时间|到下一站的时间|,|
|第二站|本站出发时间|到下一站的时间|,|
|以此类推|||,|
|终到站|END|END|,|
|EOT|||

BOT、END、EOT、“,”为位置标识符，用于读取文件的函数依据此分割车次信息并录入数据库

### 文件结构
main.c: 主函数文件

Display.c: 控制界面显示

F_Lib.h: 存储可被外部文件调用的函数声明

V_Lib.h: 存储常量定义、结构体定义、数据库变量外部声明

Variables_Lib.h: 定义并存放数据库变量

Basic_Function.c: 存放简单操作的基础函数

File_Operation.c: 定义文件进行交互的函数

Order_Manager.c: 存放有关订单管理的函数

Search.c: 存放有关搜索的函数

Ticket_Manage.c: 存放有关于管理车次信息的函数

UserFunction.c: 存放面向用户操作的函数

### 运行效果

### 主界面
![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/a344d168-6468-44c8-a1c4-bd2cf0e05ba2)

### 订票
![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/8acdc9fe-48c1-43bc-bf50-0d929fef445a)

![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/dc21e0aa-4a0c-452a-9528-354151b5c302)

![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/2e26e4dc-a7a5-4824-9290-6a570a07e18a)

![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/05463ef9-0bff-4b87-8cdd-0824d8251735)

### 查询订单
![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/dfbc62b6-2329-494e-9110-a7d1cdf383ee)

![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/208ca388-022d-4d66-89d9-b314d170c33a)

### 退票
![image](https://github.com/Cinkuk/Railway_Ticket_Manage/assets/108922408/60afed53-5b00-4e4d-9f8a-a1998e75ef32)


