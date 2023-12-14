// 本文件用于存放订单管理的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'OM_'开头
//
// Test Status: Finished
// Code Status: Freeze
//
// 函数与功能对应:
// 
// 初始化VL_Or_Lib
// Status OM_InitOrder()
// 返回值：NOSPACE, OK
// 
// // 初始化订单池
// Status OM_InitOrderID()
// 
// 创建唯一的订单编号
// char* OM_CreateOrderNum()
// return: 订单编号字符串指针
// 
// 获取下一张订单的编号
// char* OM_NextOrderNum()
//
// 创建新的正式订单
// Status OM_New_F_Order(char* _phone, char* _TrainNum,
//	                     char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input：手机号、车次、出发站、到达站、订票张数
// return: NOSPACE, OK, ERROR
//
// 创建新的候补订单
// Status OM_New_W_Order(char* _phone, char* _TrainNum,
//	                    char* _LeaveStop, char* _ArriveStop, int _TicketSmount)
// input：手机号、车次、出发站、到达站、订票张数
// return: NOSPACE, OK
//
// 查询候补订单能否候补并操作
// Status OM_CheckWaitOrder(SearchWaitResult* SWR)
// output: OK（有候补订单并成功候补），EMPTY（无可以进行候补操作的订单）
// 


#include "V_Lib.h"
#include "F_Lib.h"


// 初始化VL_Or_Lib
// Freeze
Status OM_InitOrder()
{
	// 申请PhoneOrder结点
	PhoneOrder* p;
	p = (struct PhoneOrder*)malloc(sizeof(struct PhoneOrder));
	if (!p) return NOSPACE; // 无可用空间
	// 初始化变量值
	p->NodeKind = "H";
	p->phone = NULL;
	p->OrderList = NULL;
	p->next = NULL;

	VL_Or_Lib = p; // 分配成功的内存地址赋值给VL_Or_Lib
	return OK; 
}

// 初始化订单池
// Freeze
Status OM_InitOrderID()
{
	VL_OrderID = (OrderSet*)malloc(sizeof(OrderSet));
	if (!VL_OrderID) return NOSPACE;
	memset(VL_OrderID, 0, sizeof(OrderSet));
	return OK;

}

// 申请唯一的订单编号
// Freeze
char* OM_CreateOrderNum()
{
	int i; // 循环变量
	if (!(VL_OrderID->next)) // 编号池为空
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));
		if (!node) return NULL; // 无可用空间申请编号
		memset(node, 0, sizeof(OrderSet));
		node->OrderKind = (char*)malloc(sizeof(char) * 5);

		// 初始化为A000000001
		node->ID[0] = 65; // 65为ASCII的A
		for (int i = 1; i < 9; i++) node->ID[i] = 48; // 48为ASCII的0
		node->ID[9] = 49;
		node->ID[10] = '\0';

		node->next = VL_OrderID->next;
	    VL_OrderID->next = node;
		
		return BF_Merge_Char(node->ID);
	}
	else
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));
		if (!node) return NULL; // 无可用空间申请编号
		memset(node, 0, sizeof(OrderSet));
		node->OrderKind = (char*)malloc(sizeof(char) * 5);
	
		for (i = 0; i <= 10; i++) node->ID[i] = VL_OrderID->next->ID[i]; // 复制前一张订单的编号
		node->next = VL_OrderID->next;
		VL_OrderID->next = node; // 插入为第一个结点

		node->ID[9] += 1;

		for (i = 9; i > 0; i--)
		{
			if (node->ID[i] > 57) // >0需进位
			{
				node->ID[i] = 48;
				node->ID[i - 1] += 1;
			}
		}

		if (node->ID[0] > 90) return NULL; // 当前编号已超出最大值“Z999999999”


		return BF_Merge_Char(node->ID);
	}
}

// 获取下一张订单的编号
// Freeze
char* OM_NextOrderNum()
{
	int i; // 循环变量
	if (!(VL_OrderID->next)) // 编号池为空
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));
		if (!node) return NULL; // 无可用空间申请编号
		memset(node, 0, sizeof(OrderSet));
		node->OrderKind = (char*)malloc(sizeof(char) * 5);

		// 初始化为A000000001
		node->ID[0] = 65; // 65为ASCII的A
		for (int i = 1; i < 9; i++) node->ID[i] = 48; // 48为ASCII的0
		node->ID[9] = 49;
		node->ID[10] = '\0';
		return BF_Merge_Char(node->ID);
	}
	else
	{
		OrderSet* node;
		node = (OrderSet*)malloc(sizeof(struct OrderSet));
		if (!node) return NULL; // 无可用空间申请编号
		memset(node, 0, sizeof(OrderSet));
		node->OrderKind = (char*)malloc(sizeof(char) * 5);
	
		for (i = 0; i <= 10; i++) node->ID[i] = VL_OrderID->next->ID[i]; // 复制前一张订单的编号

		node->ID[9] += 1;

		for (i = 9; i > 0; i--)
		{
			if (node->ID[i] > 57) // >0需进位
			{
				node->ID[i] = 48;
				node->ID[i - 1] += 1;
			}
		}

		if (node->ID[0] > 90) return NULL; // 当前编号已超出最大值“Z999999999”
		return BF_Merge_Char(node->ID);
	}
}

// 创建新的正式订单
// Freeze
// input：手机号、车次、出发站、到达站、订票张数
Status OM_New_F_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketAmount)
{
	Order* p; // 订单信息结点
	OrderSet* t; // 订单编号池工作指针
	char* _OrderNum = (char*)malloc(sizeof(char)*STRLENGTH); // 订单编号
	SUB_TrainInfo* TrainNode; // 指向当前订单车次的车次信息头结点
	PhoneOrder* PhoneNode; // 指向总订单信息结点
	

	p = (Order*)malloc(sizeof(struct Order));

	if (!p) return NOSPACE; // 无可用空间

	PhoneOrderList* q; // 订单信息结点
	q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));

	if (!q) return NOSPACE; //无可用空间

	// 申请订单编号和需要的结点地址
	_OrderNum = OM_CreateOrderNum();
	TrainNode = S_GetTrainNode(_TrainNum);
	PhoneNode = S_GetPhoneOrderNode(_phone);

	if (!TrainNode) return ERROR; // 无此班次

	// TrainNode or PhoneNode为空结点或无可用空间建立订单编号_OrderNum
	if (!_OrderNum || !PhoneNode) return NOSPACE; 

	// 判断是否能够购票
	if (TrainNode->SurplusTicket < _TicketAmount) return ERROR;

	// 结点赋值

	p->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	p->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	p->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	p->End = (char*)malloc(sizeof(char) * STRLENGTH);


	q->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	q->OrderStatus = (char*)malloc(sizeof(char) * STRLENGTH);
	q->LeaveStop = (char*)malloc(sizeof(char) * STRLENGTH);
	q->ArriveStop = (char*)malloc(sizeof(char) * STRLENGTH);
	q->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);

	// 订单类型
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus =  "F";

	strcpy(p->OrderNum, _OrderNum); // 订单编号
	strcpy(q->OrderNum, _OrderNum);
	strcpy(p->TrainNum, _TrainNum); // 车次编号
	strcpy(p->phone, _phone); // 手机号

	// 出发站
	strcpy(p->Start, _LeaveStop);
	strcpy(q->LeaveStop, _LeaveStop);
	// 到达站
	strcpy(p->End, _ArriveStop);
	strcpy(q->ArriveStop, _ArriveStop);
	// 票数
	p->TicketNum = _TicketAmount;
	q->TicketAmount = _TicketAmount;
	// 改余票
	TrainNode->SurplusTicket -= _TicketAmount;

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

	q->CurrentWaitOrder = NULL;

	t = VL_OrderID->next;
	// 订单信息结点p存入订单编号池内
	while (t)
	{
		
		// t指向当前订单结点
		if (strcmp(BF_Merge_Char(t->ID),BF_Merge_Char(_OrderNum)) == 0)
		{
			strcpy(t->OrderKind, "F"); // 订单类型为正式订单
			t->OrderNode = p; // 将当前订单链接进订单池内
			t->WaitOrderNode = NULL;
			break; // 退出循环
		}
		// t指向下一张订单
		t = t->next;
	}


	return OK;
}

// 创建新的候补订单
// Freeze
// input：手机号、车次、出发站、到达站、订票张数
Status OM_New_W_Order(char* _phone, char* _TrainNum,
	char* _LeaveStop, char* _ArriveStop, int _TicketAmount)
{
	WaitOrder* p; // 订单信息结点
	OrderSet* t; // 订单编号池工作指针
	char* _OrderNum = (char*)malloc(sizeof(char) * STRLENGTH); // 订单编号
	SUB_TrainInfo* TrainNode; // 指向当前订单车次的车次信息头结点
	PhoneOrder* PhoneNode; // 指向总订单信息结点

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
	 
	p->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	p->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	p->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	p->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	p->End = (char*)malloc(sizeof(char) * STRLENGTH);


	q->NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);
	q->OrderStatus = (char*)malloc(sizeof(char) * STRLENGTH);
	q->LeaveStop = (char*)malloc(sizeof(char) * STRLENGTH);
	q->ArriveStop = (char*)malloc(sizeof(char) * STRLENGTH); 
	q->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH); 
	
	// 订单类型
	p->NodeKind = "E";
	q->NodeKind = "E";
	q->OrderStatus = "W";

	strcpy(p->OrderNum, _OrderNum); // 订单编号
	strcpy(q->OrderNum, _OrderNum);
	strcpy(p->TrainNum, _TrainNum); // 车次编号
	strcpy(p->phone, _phone); // 手机号

	// 出发站
	strcpy(p->Start, _LeaveStop);
	strcpy(q->LeaveStop, _LeaveStop);
	// 到达站
	strcpy(p->End, _ArriveStop);
	strcpy(q->ArriveStop, _ArriveStop);
	
	// 票数
	p->TicketNum = _TicketAmount;
	q->TicketAmount = _TicketAmount;

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

	q->CurrentOrder = NULL;
	
	t = VL_OrderID->next;
	// 订单信息结点p存入订单编号池内
	while (t)
	{
		// t指向当前订单结点
		if (strcmp(BF_Merge_Char(t->ID),BF_Merge_Char(_OrderNum)) == 0)
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
// Freeze
Status OM_CheckWaitOrder()
{
	// 工作指针
	OrderSet* CurID = VL_OrderID->next;
	OrderSet* ChangedID;
	PhoneOrder* PhOrderNode; // 订单数据库的手机号结点
	PhoneOrderList* pre_PhOrder, * PhOrder; // 订单数据库手机号订单的前一个订单结点，对应对应订单结点
	SUB_TrainInfo* TrainNode; // 车次结点
	WaitOrder* WTrainNode, * pre_WTrainNode; // 车次数据库中的候补订单结点，订单前一个结点

	// 用于插入的订单结点
	Order* NewTOrder;
	PhoneOrderList* NewPOrder;

	// 订单信息
	char* OrderNum, * TrainNum, * phone, * Start, * end, * NodeKind;
	int TicketNum;


	// 遍历订单池
	while (CurID)
	{
		// 当前订单为正式订单
		if (strcmp(CurID->OrderKind, "F") == 0) CurID = CurID->next;

		// 当前订单为候补订单
		else if (strcmp(CurID->OrderKind, "W") == 0)
		{
			// 记录车次号
			TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
			if (!TrainNum) return NOSPACE;
			memset(TrainNum, 0, sizeof(char) * STRLENGTH);
			strcpy(TrainNum, CurID->WaitOrderNode->TrainNum);

			// 定位车次结点
			TrainNode = S_GetTrainNode(TrainNum);

			// 判断余票是否充足
			// 不足，释放内存，扫描下一张订单
			if (TrainNode->SurplusTicket < CurID->WaitOrderNode->TicketNum)
			{
				CurID = CurID->next;
				continue;
			}
			// 足够，进入候补
			else if (TrainNode->SurplusTicket >= CurID->WaitOrderNode->TicketNum)
			{
				// 进入车次候补订单结点
				pre_WTrainNode = TrainNode->TrainWaitOrder->rear->next; // 进入头节点节点

				// 按照顺位判断
				while (strcmp(pre_WTrainNode->next->NodeKind, "H") != 0)
				{
					// 下一顺位所需票数大于余票，进入下一顺位
					if (pre_WTrainNode->next->TicketNum > TrainNode->SurplusTicket)
						pre_WTrainNode = pre_WTrainNode->next;
					
					// 下一顺位所需票数小于余票，进入候补处理
					else if (pre_WTrainNode->next->TicketNum <= TrainNode->SurplusTicket)
					{
						// 车次数据库结点定位
						WTrainNode = pre_WTrainNode->next;

						// 记录订单其他信息
						OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
						phone = (char*)malloc(sizeof(char) * STRLENGTH);
						Start = (char*)malloc(sizeof(char) * STRLENGTH);
						end = (char*)malloc(sizeof(char) * STRLENGTH);
						NodeKind = (char*)malloc(sizeof(char) * STRLENGTH);

						if (!OrderNum || !phone || !Start || !end || !NodeKind) return NOSPACE;
						memset(OrderNum, 0, sizeof(char) * STRLENGTH);
						memset(phone, 0, sizeof(char) * STRLENGTH);
						memset(Start, 0, sizeof(char) * STRLENGTH);
						memset(end, 0, sizeof(char) * STRLENGTH);
						memset(NodeKind, 0, sizeof(char) * STRLENGTH);

						strcpy(OrderNum, WTrainNode->OrderNum);
						strcpy(TrainNum, WTrainNode->TrainNum);
						strcpy(phone, WTrainNode->phone);
						strcpy(Start, WTrainNode->Start);
						strcpy(end, WTrainNode->End);
						strcpy(NodeKind, "E");
						TicketNum = WTrainNode->TicketNum;

						// 写入新结点
						NewTOrder = (Order*)malloc(sizeof(Order));
						if (!NewTOrder) return NOSPACE;
						memset(NewTOrder, 0, sizeof(Order));
						NewTOrder->NodeKind = NodeKind;
						NewTOrder->OrderNum = OrderNum;
						NewTOrder->TrainNum = TrainNum;
						NewTOrder->phone = phone;
						NewTOrder->Start = Start;
						NewTOrder->End = end;
						NewTOrder->TicketNum = TicketNum;

						NewPOrder = (PhoneOrderList*)malloc(sizeof(PhoneOrderList));
						if (!NewPOrder) return NOSPACE;
						memset(NewPOrder, 0, sizeof(Order));
						char* OrderStatus = (char*)malloc(sizeof(char) * STRLENGTH);
						if (!OrderStatus) return NOSPACE;
						memset(OrderStatus, 0, sizeof(char) * STRLENGTH);
						strcpy(OrderStatus, "F");

						NewPOrder->NodeKind = NodeKind;
						NewPOrder->OrderStatus = OrderStatus;
						NewPOrder->OrderNum = OrderNum;
						NewPOrder->LeaveStop = Start;
						NewPOrder->ArriveStop = end;
						NewPOrder->TicketAmount = TicketNum;
						NewPOrder->CurrentWaitOrder = NULL;
						// 车次数据库删除候补结点
						pre_WTrainNode->next = WTrainNode->next;
						if (strcmp(pre_WTrainNode->next->NodeKind, "H") == 0) TrainNode->TrainWaitOrder->rear = pre_WTrainNode->next;
				
						// 加入车次数据库正式订单结点
						NewTOrder->next = TrainNode->TrainOrder->next;
						TrainNode->TrainOrder->next = NewTOrder;
	

						// 在订单池中定位结点
						ChangedID = VL_OrderID->next;
						while (strcmp(BF_Merge_Char(ChangedID->ID), OrderNum) != 0)
							ChangedID = ChangedID->next;
				
						// 在订单数据库中定位候补结点
						PhOrderNode = VL_Or_Lib->next;
						while (strcmp(PhOrderNode->phone, phone) != 0)
							PhOrderNode = PhOrderNode->next;
						pre_PhOrder = PhOrderNode->OrderList;
						while (strcmp(pre_PhOrder->NextOrder->OrderNum, OrderNum) != 0)
							pre_PhOrder = pre_PhOrder->NextOrder;
						PhOrder = pre_PhOrder->NextOrder;
				
						// 删除候补接单
						pre_PhOrder->NextOrder = PhOrder->NextOrder;

						// 加入正式订单结点
						NewPOrder->NextOrder = PhOrderNode->OrderList->NextOrder;
						PhOrderNode->OrderList->NextOrder = NewPOrder;

						// 链接车次结点和订单结点
						NewPOrder->Train = TrainNode;
						NewPOrder->CurrentOrder = TrainNode->TrainOrder;

						// 修改订单池结点指向和信息
						char* NewOrderKind = (char*)malloc(sizeof(char) * STRLENGTH);
						strcpy(NewOrderKind, "F");
						ChangedID->OrderKind = NewOrderKind;
						ChangedID->WaitOrderNode = NULL;
						ChangedID->OrderNode = NewTOrder;

						// 重入头节点检查下一顺位
						pre_WTrainNode = TrainNode->TrainWaitOrder->rear->next;

					} // else if (pre_WTrainNode->next->TicketNum <= TrainNode->SurplusTicket)
				} // while (strcmp(pre_WTrainNode->next->NodeKind, "H") != 0)

				// 扫描订单池下一结点
				CurID = CurID->next;


			} // else if (TrainNode->SurplusTicket >= CurID->WaitOrderNode->TicketNum)

		} // else if (strcmp(CurID->OrderKind, "W") == 0)
		
	} // while (VL_OrderID)

	return OK;
} // END Function

