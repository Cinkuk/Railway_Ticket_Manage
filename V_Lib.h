// 此头文件用于记录用于可在项目中共用的变量名和结构体名
//
// Code Status: Undo
// 此头文件用于记录用于可在项目中共用的变量名、结构体、常量
//
// Code Status: Working

//////////
// 编译指令
// 防止结构体重复定义
#pragma once
// 允许使用strcpy
#define _CRT_SECURE_NO_WARNINGS


//////////
// 常量
// 状态和错误信息
#define OK 1
#define ERROR 0
#define OVERFLOW -10
#define EMPTY -11
#define NOSPACE -12

// 布尔值
#define True 1
#define False 0

// 长度常量
#define STATIONNAME 20
#define STRLENGTH 30

//////////
// 返回值类型
typedef int Status;
typedef int Bool;

//////////
// 结构体
// 存储途径站点名字的链式串
typedef struct StopName {
	 char* name;

	struct StopName* next; // 下一站点名字
}StopName;

// 存储各个站点发车时间和运行时长信息
typedef struct LeaveTime {
	char* name; // 站点名称
	int hour; // 发车时间小时
	int min; // 发车时间分钟
	int ToNextMin; // 运行至下一站点所需时间

	struct LeaveTime* next; // 下一站点信息
}LeaveTime;

// 单一订单信息链表
// 每一车次的订单信息链表独立
typedef struct Order {
	char* NodeKind; // 节点类别，H:头结点，E：数据元素结点
	char* OrderNum; // 订单编号
	char* TrainNum; // 车次
	char* phone; // 手机号
	char* Start; // 出发站
	char* End; // 终点站
	int TicketNum; // 订购车票张数

	struct Order* next; // 下一份订单
}Order;

// 候补订单信息
// 循环链表
typedef struct WaitOrder {
	char* NodeKind; // 节点类别，H:头结点，E：数据元素结点
	char* OrderNum; // 订单编号
	char* TrainNum; // 车次
	char* phone; // 手机号
	char* Start; // 出发站
	char* End; // 终点站
	int TicketNum; // 订购车票张数

	struct WaitOrder* rear; // 候补订单尾指针，无候补时指向头结点
	struct WaitOrder* next;
}WaitOrder;

// 存储车次信息
// 该链表按照车次数字递增排序
typedef struct SUB_TrainInfo {
	char* NodeKind; // 结点类别，H：头节点，E：数据元素结点
	// 定义十位的指针数组
	// 用于存放指向以1-9开头的车次数字最小的车次的指针，用于加快检索，弃用第0位
	struct SUB_TrainInfo* FirstNum[10];
	char* TrainNum; // 车次
	char* Start; // 始发站
	StopName* Stop; // 途经站
	char* End; // 终到站
	LeaveTime*  StationLeaveTime; // 各站点发车时间和运行时长信息
	int OccupantQuota; // 乘员定额
	int SurplusTicket; // 余票数量

	Order *TrainOrder; // 关于该车次的订单
	WaitOrder *TrainWaitOrder; // 关于该车次的候补订单

	struct SUB_TrainInfo* next; // 下一车次
}SUB_TrainInfo;

// 实际用作车票信息管理
// 以运营时速区分车次开头，共11种开头
typedef struct TOP_TrainInfo {
	SUB_TrainInfo* G;
	SUB_TrainInfo* D;
	SUB_TrainInfo* C;
	SUB_TrainInfo* Z;
	SUB_TrainInfo* T;
	SUB_TrainInfo* K;
	SUB_TrainInfo* Y;
	SUB_TrainInfo* L;
	SUB_TrainInfo* S;
	SUB_TrainInfo* N; // 此类别的车次号为纯数字
	SUB_TrainInfo* P;
}TOP_TrainInfo;

// 用于链接同一手机号下的所有订单
typedef struct PhoneOrderList {
	char* NodeKind; // 结点类别，H：头结点，E：数据元素结点
	char* OrderStatus; // 订单状态，F：正式订单，W：候补订单
	Order* CurrentOrder; // 指向当前正式订单结点
	WaitOrder* CurrentWaitOrder; // 指向当前候补订单结点
	SUB_TrainInfo* Train; // 指向当前车次结点
	char* LeaveStop; // 出发站
	char* ArriveStop; // 到达站
	int TicketAmount; // 订购票数

	struct PhoneOrderList* NextOrder; // 同一手机号的下一订单
}PhoneOrderList;

// 用于存储手机号对应的订单号
typedef struct PhoneOrder {
	char* NodeKind; // 结点类别，H：头结点，E：数据元素结点
	char* phone; // 手机号
	PhoneOrderList* OrderList; // 当前手机号下的全部订单

	struct PhoneOrder* next; // 下一手机号
}PhoneOrder;

// 用于检索的数据库
// 以车次搜索站点
//
// 站点名链表 
typedef struct StationList
{
	char* StationName; // 本站名称
	struct StationList* next; // 下一站
}StationList;

//车次链表
typedef struct TrainIndexNode
{
	char* NodeKind; // 结点类型，H：头结点，E：数据元素结点
	struct TrainIndexNode* NumIndex[10]; // 首位数字加快检索的指针数组
	char* TrainNum; // 车次编号
	StationList* StationNameList; // 按行进方向存放的所有站点
}TrainIndexNode;

// 数据库结构体
typedef struct TrainIndexDB
{
	TrainIndexNode* G;
	TrainIndexNode* D;
	TrainIndexNode* C;
	TrainIndexNode* Z;
	TrainIndexNode* T;
	TrainIndexNode* K;
	TrainIndexNode* Y;
	TrainIndexNode* L;
	TrainIndexNode* S;
	TrainIndexNode* N;
	TrainIndexNode* P;
}TrainIndexDB;

// 订单编号池
typedef struct OrderSet
{
	// 订单编号格式为一位字母+9位数字
	char ID[10];
	char OrderKind; // 订单类别，F:正式订单，W：候补订单
	Order* OrderNode;
	WaitOrder* WaitOrderNode;
	struct OrderSet* next;
}OrderSet;


// 以站点搜索车次
//
// 车次编号列表
typedef struct TrainNumList
{
	// 不设头结点
	char* CurNum; // 该结点车次编号
	struct TrainNumList* next;
}TrainNumList;

// 站点编号列表
typedef struct StopIndexDB
{
	char* NodeKind; // 结点类型，H：头结点，E：数据元素结点
	char* StationName; // 站点名字
	TrainNumList* TrainList; // 车次列表
	struct StopIndexDB* next; // 下一站点
}StopIndexDB;

// 搜寻结果
typedef struct SearchResult
{
	// 设头结点
	char* TrainNum;  // 车次编号
	char* Leave; // 出发地
	char* Arrive; // 到达地
	int LeaveTime[2]; // 出发时间
	int ToNextMin;
	int ArriveTime[2]; // 到达时间

	SUB_TrainInfo* TrainNode; // 车次信息结点

	struct SearchResult* NextResult;
}SearchResult;

// 候补订单查询返回结果
typedef struct SearchWaitResult
{
	Order* TransOrder; // 转为正式订单的订单结点
	struct SearchWaitResult* next;
}SearchWaitResult;

//////////
// 变量
extern TOP_TrainInfo* VL_Ti_Lib; // 将车票车次变量在项目中共用
extern PhoneOrder* VL_Or_Lib; // 将订单信息变量在项目中共用
extern TrainIndexDB* VL_TI_DB; // 车次检索站点的数据库
extern StopIndexDB* VL_SI_DB; // 站点检索车次的数据库
extern OrderSet* VL_OrderID; // 订单编号池
