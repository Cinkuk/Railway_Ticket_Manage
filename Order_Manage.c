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
// 查询候补订单能否候补并操作
// Status OM_CheckWaitOrder(SearchWaitResult* SWR)
// output: OK（有候补订单并成功候补），EMPTY（无可以进行候补操作的订单）
// 
// 
//


#include "V_Lib.h"
#include "F_Lib.h"
#include <stdlib.h>
#include <string.h>


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

// 申请唯一的订单编号
char* OM_CreateOrderNum()
{
	int i; // 循环变量
	if (!VL_OrderID) // 编号池为空
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));

		if (!node) return NULL; // 无可用空间申请编号

		// 初始化为A000000001
		node->ID[0] = 65; // 65为ASCII的A
		for (int i = 1; i < 9; i++) node->ID[i] = 48; // 48为ASCII的0
		node->ID[9] = 1;
		node->next = NULL;
		return BF_Merge_Char(node->ID);
	}
	OrderSet* node;
	node = (OrderSet*)malloc(sizeof(struct OrderSet));
	if (!node) return NULL; // 无可用空间申请编号
	
	node->next = VL_OrderID;
	for (i = 0; i < 9; i++) node->ID[i] = node->next->ID[i]; // 复制前一张订单的编号
	VL_OrderID = node; // 插入为第一个结点
	
	node->ID[9] += 1;

	for (i = 9; i > 0; i--)
	{
		if (node->ID[i] > 57) // >0需进位
		{
			node->ID[i] = 0;
			node->ID[1 - 1] += 1;
		}
	}

	if (node->ID[0] > 90) return NULL; // 当前编号已超出最大值“Z999999999”

	return BF_Merge_Char(node->ID);
}

// 创建新的正式订单
// input：手机号、车次、出发站、到达站、订票张数
Status OM_New_F_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
{
	Order* p; // 订单信息结点
	OrderSet* t; // 订单编号池工作指针
	char* _OrderNum = (char*)malloc(sizeof(char)*STRLENGTH); // 订单编号
	SUB_TrainInfo* TrainNode; // 指向当前订单车次的车次信息头结点
	PhoneOrder* PhoneNode; // 指向总订单信息结点
	
	t = VL_OrderID;

	p = (Order*)malloc(sizeof(struct Order));

	if (!p) return NOSPACE; // 无可用空间

	PhoneOrderList* q; // 订单信息结点
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; //无可用空间

	// 申请订单编号和需要的结点地址
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrderNode(_phone);

	// TrainNode or PhoneNode为空结点或无可用空间建立订单编号_OrderNum
	if (!_OrderNum || !TrainNode || !PhoneNode) return NOSPACE; 

	// 结点赋值
	// 订单类型
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus =  "F";

	strcpy(p->OrderNum, _OrderNum); // 订单编号
	strcpy(p->TrainNum, _TrainNum); // 车次编号
	strcpy(p->phone, _phone); // 手机号

	// 出发站
	strcpy(p->Start, _LeaveStop);
	strcpy(q->LeaveStop, _LeaveStop);
	// 到达站
	strcpy(p->End, _ArriveStop);
	strcpy(q->ArriveStop, _ArriveStop);
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

	// 订单信息结点p存入订单编号池内
	while (t)
	{
		// t指向当前订单结点
		if (strcmp(t->ID, _OrderNum) == 0)
		{
			t->OrderKind = "F"; // 订单类型为正式订单
			t->OrderNode = p; // 将当前订单链接进订单池内
			break; // 退出循环
		}
		// t指向下一张订单
		t = t->next;
	}


	return OK;
}

// 创建新的候补订单
// input：手机号、车次、出发站、到达站、订票张数
Status OM_New_W_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
{
	WaitOrder* p; // 订单信息结点
	OrderSet* t; // 订单编号池工作指针
	char* _OrderNum = (char*)malloc(sizeof(char) * STRLENGTH); // 订单编号
	SUB_TrainInfo* TrainNode; // 指向当前订单车次的车次信息头结点
	PhoneOrder* PhoneNode; // 指向总订单信息结点
	
	t = VL_OrderID;

	p = (WaitOrder*)malloc(sizeof(struct WaitOrder));

	if (!p) return NOSPACE; // 无可用空间

	PhoneOrderList* q; // 订单信息结点
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; // 无可用空间

	// 申请订单编号和需要的结点地址
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrderNode(_phone);

	// TrainNode or PhoneNode为空结点或无可用空间建立订单编号_OrderNum
	if (!_OrderNum || !TrainNode || !PhoneNode) return NOSPACE; 

	// 结点赋值
	// 订单类型
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus = "W";

	strcpy(p->OrderNum, _OrderNum); // 订单编号
	strcpy(p->TrainNum, _TrainNum); // 车次编号
	strcpy(p->phone, _phone); // 手机号

	// 出发站
	strcpy(p->Start, _LeaveStop);
	strcpy(q->LeaveStop, _LeaveStop);
	// 到达站
	strcpy(p->End, _ArriveStop);
	strcpy(q->ArriveStop, _ArriveStop);
	
	// 票数
	p->TicketNum = _TicketSmount;
	q->TicketAmount = _TicketSmount;

	// 总订单结点指针链接
	// 链接同一手机号下的其他订单
	q->NextOrder = PhoneNode->OrderList->NextOrder;
	PhoneNode->OrderList->NextOrder = q;
	// 链接当前车次结点
	q->Train = TrainNode; // 指向当前车次结点
	q->CurrentWaitOrder =  TrainNode->TrainWaitOrder; // 指向当前车次候补订单头结点
	
	// 该车次下的候补订单结点中，链接本张订单的结点
	p->next = TrainNode->TrainWaitOrder->rear->next;
	TrainNode->TrainWaitOrder->rear->next = p;
	TrainNode->TrainWaitOrder->rear = p;
	
	// 订单信息结点p存入订单编号池内
	while (t)
	{
		// t指向当前订单结点
		if (strcmp(t->ID, _OrderNum) == 0)
		{
			t->OrderKind = "W"; // 订单类型为候补订单
			t->WaitOrderNode = p; // 将当前订单链接进订单池内
			break; // 退出循环
		}
		// t指向下一张订单
		t = t->next;
	}

	return OK;
}

// 查询候补订单能否候补并操作
Status OM_CheckWaitOrder(SearchWaitResult* SWR)
{

}
