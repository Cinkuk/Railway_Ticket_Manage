// 本文件用于存放订单管理的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'OM_'开头
//
// Test Status: Undo
// Code Status: Working
//
// 函数与功能对应:
// 
// 初始化VL_Or_Lib
// OM_InitOrder()：初始化VL_Or_Lib
// 返回值：NOSPACE, OK
// 
// 创建唯一的订单编号
// char* OM_CreateOrderNum()
// return: 订单编号字符串指针
//
//
// 创建新的正式订单
// Status OM_New_F_Order(char* _phone, char* _TrainNum,
//	                     char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input：手机号、车次、出发站、到达站、订票张数
// return: NOSPACE, OK
//
// 创建新的候补订单
//Status OM_New_W_Order(char* _phone, char* _TrainNum,
//	                    char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input：手机号、车次、出发站、到达站、订票张数
// return: NOSPACE, OK
//
//


#include "V_Lib.h"
#include <stdlib.h>
#include "F_Lib.h"

// 初始化VL_Or_Lib
Status OM_InitOrder()
{
	// 申请PhoneOrder结点
	PhoneOrder* p;
	p = (struct PhoneOrder*)malloc(sizeof(struct PhoneOrder));
	if (!p) return NOSPACE; // 无可用空间
	// 初始化变量值
	p->NodeKind = "H";
	p->phone = -1;
	p->OrderList = NULL;
	p->next = NULL;

	VL_Or_Lib = p; // 分配成功的内存地址赋值给VL_Or_Lib
	return OK; 
}

// 创建唯一的订单编号
char* OM_CreateOrderNum()
{

}

// 创建新的正式订单
// input：手机号、车次、出发站、到达站、订票张数
Status OM_New_F_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
{
	Order* p;
	char* _OrderNum;
	SUB_TrainInfo* TrainNode;
	PhoneOrder* PhoneNode;

	p = (Order*)malloc(sizeof(struct Order));

	if (!p) return NOSPACE; // 无可用空间

	PhoneOrderList* q; // 总订单结点
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; //无可用空间

	// 申请订单编号和需要的结点地址
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrder(_phone);

	// 结点赋值
	// 订单类型
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus =  "F";

	p->OrderNum = _OrderNum; // 订单编号
	p->TrainNum = _TrainNum; // 车次编号
	p->phone = _phone; // 手机号

	// 出发站
	p->Start = _LeaveStop;
	q->LeaveStop = _LeaveStop;
	// 到达站
	p->End = _ArriveStop;
	q->ArriveStop = _ArriveStop;
	// 票数
	p->TicketNum = _TicketSmount;
	q->TicketAmount = _TicketSmount;

	// 总订单结点指针链接
	// 链接同一手机号下的其他订单
	q->NextOrder = PhoneNode->OrderList->NextOrder;
	PhoneNode->OrderList->NextOrder = q;
	// 链接当前车次结点
	q->Train = TrainNode; // 指向当前车次结点
	q->CurrentOrder = TrainNode->TrainOrder; // 指向当前车次订单	
	// 该车次下的订单结点中，链接本张订单的结点
	p->next = TrainNode->TrainOrder->next;
	TrainNode->TrainOrder->next = p;

	return OK;
}

// 创建新的候补订单
// input：手机号、车次、出发站、到达站、订票张数
Status OM_New_W_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
{
	WaitOrder* p;
	char* _OrderNum;
	SUB_TrainInfo* TrainNode;
	PhoneOrder* PhoneNode;

	p = (WaitOrder*)malloc(sizeof(struct WaitOrder));

	if (!p) return NOSPACE; // 无可用空间

	PhoneOrderList* q; // 总订单结点
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; // 无可用空间

	// 申请订单编号和需要的结点地址
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrder(_phone);

	// 结点赋值
	// 订单类型
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus = "W";

	p->OrderNum = _OrderNum; // 订单编号
	p->TrainNum = _TrainNum; // 车次编号
	p->phone = _phone; // 手机号

	// 出发站
	p->Start = _LeaveStop;
	q->LeaveStop = _LeaveStop;
	// 到达站
	p->End = _ArriveStop;
	q->ArriveStop = _ArriveStop;
	// 票数
	p->TicketNum = _TicketSmount;
	q->TicketAmount = _TicketSmount;

	// 总订单结点指针链接
	// 链接同一手机号下的其他订单
	q->NextOrder = PhoneNode->OrderList->NextOrder;
	PhoneNode->OrderList->NextOrder = q;
	// 链接当前车次结点
	q->Train = TrainNode; // 指向当前车次结点
	q->CurrentOrder =  TrainNode->TrainWaitOrder; // 指向当前车次候补订单头结点
	
	// 该车次下的候补订单结点中，链接本张订单的结点
	p->next = TrainNode->TrainWaitOrder->rear->next;
	TrainNode->TrainWaitOrder->rear = p;

	return OK;
}


