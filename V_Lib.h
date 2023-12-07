// 此头文件用于记录用于可在项目中共用的变量名和结构体名
//
// Code Status: Undo
// 此头文件用于记录用于可在项目中共用的变量名、结构体、常量
//
// Code Status: Working

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
	char NodeKine; // 节点类别，H:头结点，E：数据元素结点
	char* OrderNum; // 订单编号
	char* TrainNum; // 车次
	int phone; // 手机号
	char* Start; // 出发站
	char* End; // 终点站
	int TicketNum; // 订购车票张数

	struct Order* next; // 下一份订单
}Order;

// 候补订单信息
// 循环链表
typedef struct WaitOeder {
	char NodeKine; // 节点类别，H:头结点，E：数据元素结点
	char *OrderNum; // 订单编号
	char *TrainNum; // 车次
	int phone; // 手机号
	char* Start; // 出发站
	char* End; // 终点站
	int TicketNum; // 订购车票张数

	struct WaitOrder* rear; // 候补订单尾指针，无候补时指向头结点
}WaitOrder;

// 存储车次信息
// 该链表按照车次数字递增排序
typedef struct SUB_TrainInfo {
	char NodeKind; // 结点类别，H：头节点，E：数据元素结点
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
	char NodeKind; // 结点类别，H：头结点，E：数据元素结点
	char OrderStatus; // 订单状态，F：正式订单，W：候补订单
	Order* CurrentOrder; // 指向当前订单结点或候补订单结点
	SUB_TrainInfo* Train; // 指向当前车次结点

	struct PhoneOrderList* NextOrder; // 同一手机号的下一订单
}PhoneOrderList;

// 用于存储手机号对应的订单号
typedef struct PhoneOrder {
	char NodeKind; // 结点类别，H：头结点，E：数据元素结点
	char* phone; // 手机号
	PhoneOrderList* OrderList; // 当前手机号下的全部订单

	struct PhoneOrder* next; // 下一手机号
}PhoneOrder;

//////////
// 变量
extern TOP_TrainInfo* VL_Ti_Lib; // 将车票车次变量在项目中共用
extern PhoneOrder* VL_Or_Lib; // 将订单信息变量在项目中共用

