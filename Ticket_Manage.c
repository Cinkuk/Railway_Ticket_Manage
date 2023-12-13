// 本文件用于存放车票、车次管理的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'TM_'开头
//
// Test Status: Freeze
// Code Status: Freeze
//
// 函数与功能对应：
// 
// 申请SUB_TrainInfo类别的头结点，用于初始化FirstNum[]指针数组内的结点
// SUB_TrainInfo* TM_RequestSUBTrainHeadNode()
// 返回值：NULL（无可用空间）, 对应结点地址
// 
// 申请SUB_TrainInfo类别的头结点，用于初始化TOP_TrainInfo下的结点
// SUB_TrainInfo* TM_RequestNodeForTopNode()
// 返回值：NULL（无可用空间）, 对应结点地址
// 
// 初始化VL_Ti_Lib
// Status InitTicket()
// 返回值：OK, NOSPACE
// 
// 返回VL_Ti_Lib中对应车次开头的头指针
// SUB_TrainInfo * TM_Get_TiLib_HeadPointer(char*)
// 返回值：对应车次的SUB_TrainInfo指针, NULL（不存在）
// 
// 将车次信息结点依照升序插入到对应位置
// Status TM_InsertTrainNode (SUB_TrainInfo*)
// 返回值：ERROR（对应车次头结点不存在）, NPSPACE（对应的最小车次指针不存在且无空间进行分配）, OK
//
// 新增车次
// Status TM_NewTrain(char* , char* , StopName* , char* ,
//	                  LeaveTime* , int , int )
// 返回值：NOSPACE, OK
// 

#include "V_Lib.h"
#include "F_Lib.h"

// 车票操作数据库部分
// Freeze
// 申请SUB_TrainInfo类别的头结点，用于初始化FirstNum[]指针数组内的结点
SUB_TrainInfo* TM_RequestSUBTrainHeadNode()
{
	SUB_TrainInfo* q;
	q = (SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));

	if (!q) return NULL; // 无可用空间分配

	// 存入头结点信息
	q->NodeKind = "H";
	for (int i = 0; i < 10; i++) q->FirstNum[i] = NULL; 
	q->TrainNum = "HeadNode";
	q->Start = "HeadNode";
	q->Stop = NULL;
	q->End = "HeadNode";
	q->StationLeaveTime = NULL;
	q->OccupantQuota = 0;
	q->SurplusTicket = 0;
	q->TrainOrder = NULL;
	q->TrainWaitOrder = NULL;
	q->next = NULL;

	return q;
}

// 申请SUB_TrainInfo类别的头结点，用于初始化TOP_TrainInfo下的结点
// Freeze
SUB_TrainInfo* TM_RequestNodeForTopNode()
{
		// 申请SUB_TrainInfo结点
		SUB_TrainInfo* q;
		q = (struct SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
		if (!q) return NULL; // 无可用空间分配
		// 申请StopName结点
		StopName* sn;
		sn = (struct StopName*)malloc(sizeof(struct StopName));
		if (!sn) return NULL; // 无可用空间分配
		// 申请LeaveTime结点
		LeaveTime* lt;
		lt = (struct LeaveTime*)malloc(sizeof(struct LeaveTime));
		if (!lt) return NULL; // 无可用分配空间
		// 初始化sn结点信息
		sn->name = "HeadNode";
		sn->next = NULL;
		// 初始化lt结点信息
		lt->name = "HeadNode";
		lt->hour = 0; lt->min = 0; lt->ToNextMin = 0;
		lt->next = NULL;
		// 初始化SUB_TrainInfo结点信息
		q->NodeKind = "H";
		// FirstNum指针数组存入头结点
		for (int i = 0; i < 10; i++)
		{
			q->FirstNum[i] = TM_RequestSUBTrainHeadNode();
			if (!(q->FirstNum[i])) return NULL; // 无可用空间分配
			q->FirstNum[i]->NodeKind = "H";

		}

		q->TrainNum = "HeadNode";
		q->Start = "HeadNode";
		q->Stop = sn;
		q->End = "HeadNode";
		q->StationLeaveTime = lt;
		q->OccupantQuota = 0;
		q->SurplusTicket = 0;
		q->TrainOrder = NULL;
		q->TrainWaitOrder = NULL;
		q->next = NULL;

		return q;
}

// 初始化VL_Ti_Lib
// Freeze
Status TM_InitTicket()
{
	int index; // 循环变量

	// 申请空间存储车次信息结构体
	TOP_TrainInfo* p;
	p = (struct TOP_TrainInfo*)malloc(sizeof(struct TOP_TrainInfo));
	if (!p) return NOSPACE; // 无可用空间分配

	// 逐个初始化VL_Ti_Lib下的结点
	for (index = 0; index < 11; index++)
	{
		// 申请SUB_TrainInfo结点
		SUB_TrainInfo* q;
		q = TM_RequestNodeForTopNode();
		if (!q) return NOSPACE; // 无可用空间

		// 将SUB_TrainInfo结点赋值给TOP中的指针变量
		switch (index)
		{
		case 0: {p->G = q; break; }
		case 1: {p->D = q; break; }
		case 2: {p->C = q; break; }
		case 3: {p->Z = q; break; }
		case 4: {p->T = q; break; }
		case 5: {p->K = q; break; }
		case 6: {p->Y = q; break; }
		case 7: {p->L = q; break; }
		case 8: {p->S = q; break; }
		case 9: {p->N = q; break; }
		case 10: {p->P = q; break; }
		} // switch
	
	} // for (index = 0; index < 11; index++)

	VL_Ti_Lib = p; // 赋值初始化VL_Ti_Lib

	return OK;

} // Status InitTicket()

// 返回VL_Ti_Lib中对应车次开头的头指针
// Freeze
SUB_TrainInfo* TM_Get_TiLib_HeadPointer(char* FirstC)
{
	switch (*FirstC)
	{
	case 'G': return VL_Ti_Lib->G;
	case 'D': return VL_Ti_Lib->D;
	case 'C': return VL_Ti_Lib->C;
	case 'Z': return VL_Ti_Lib->Z;
	case 'T': return VL_Ti_Lib->T;
	case 'K': return VL_Ti_Lib->K;
	case 'Y': return VL_Ti_Lib->Y;
	case 'L': return VL_Ti_Lib->L;
	case 'S': return VL_Ti_Lib->S;
	case 'N': return VL_Ti_Lib->N;
	case 'P': return VL_Ti_Lib->P;
	}
	return NULL; // 传入的字符不存在于可用类型中
}

// 将车次信息结点依照升序插入到对应位置
// Freeze
Status TM_InsertTrainNode(SUB_TrainInfo* NT)
{
	int NewNum = BF_Get_Train_Number(NT->TrainNum); //  NT车次数值
	SUB_TrainInfo* p; // 工作指针，最终指向对应车次类别下，与当前车次数字开头相同的最小车次结点
	int PNum, NextNum; // 存放p指向结点车次数值，p下一结点车次数值
	int HNum; // 车次编号数字部分最高位
	p = TM_Get_TiLib_HeadPointer(NT->TrainNum); // 指向对应车次类别的头结点

	if (!p) return ERROR; // 目标结点不存在

	HNum = (int)*(NT->TrainNum + 1)-48;
	p = p->FirstNum[HNum]; // 指向对应数字最高位的头结点

	// 目标结点不存在，新增头结点后，将NT链接在头结点之后
	if (!p)
	{
		p = TM_Get_TiLib_HeadPointer(NT->TrainNum); // 指向类别开头
		p->FirstNum[HNum] = TM_RequestSUBTrainHeadNode();
		if (!(p->FirstNum[HNum])) return NOSPACE; // 无可用空间分配

		p->FirstNum[HNum] = NT; // 将NT赋值给指针数组对应位置
		NT->next = NULL;
		return OK;
	}
	
	// 目标结点存在，进行比较
	while (p)
	{
		// 头结点后无结点
		if (!(p->next))
		{
			p->next = NT; // NT插入到头结点之后，NT->next已初始化为NULL
			return OK;
		} // if (!(p->next))

		// 头结点后有结点
		else
		{
			while (p->next)
			{
				PNum = BF_Get_Train_Number(p->TrainNum); // 计算当前结点的车次数字
				NextNum=PNum = BF_Get_Train_Number(p->next->TrainNum); // 计算p->next结点的车次数字
				// NT介于p, p->next之间
				if (PNum < NewNum && NewNum < NextNum)
				{
					// NT插入p和p->next中间
					NT->next = p->next;
					p->next = NT;
				} // 
				// p为尾结点，NT>p
				else if (NextNum == -1 && NewNum > PNum)
				{
					// NT成为新的尾结点
					NT->next = NULL;
					p->next = NT;
				}
				// 均不满足，p后移
				else p = p->next;
			} // while (p)
		} // else
	}
	return OK;
}

// 新增车次结点进车次信息系统中（用于修改的数据库）
// Freeze
// input：车次编号、始发站、途经站、终到站、_LeaveTime(各站点发车时间、各站点运行到下一站点时间)、乘员定额、余票数量
// output：NOSPACE：无可用空间，ERROR：对应车次头结点不存在，OK：正常
Status TM_NewTrain(char* _TrainNum, char* _Start, StopName* _Stop, char* _End,
	LeaveTime* _LeaveTime, int _OccuQuota, int _SurpTick)
{
	SUB_TrainInfo* NT, *p; // NT为新结点指针，p为工作指针
	Order* OrNode; // 新正式订单头结点
	WaitOrder* WaOrNode; // 新候补订单头结点
	NT = (SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
	if (!NT) return NOSPACE; // 无可用空间
	
	// 该类别车次的头指针不存在
	if (!(p = TM_Get_TiLib_HeadPointer(_TrainNum)))
	{
		SUB_TrainInfo* q;
		q = TM_RequestNodeForTopNode();
		if (!q) return NOSPACE; // 无可用空间可申请以创建头结点

		switch (*_TrainNum) // 新建的头结点赋值给VL_Ti_Lib对应入口
		{
			case 'G': {VL_Ti_Lib->G = q; break; }
			case 'D': {VL_Ti_Lib->D = q; break; }
			case 'C': {VL_Ti_Lib->C = q; break; }
			case 'Z': {VL_Ti_Lib->Z = q; break; }
			case 'T': {VL_Ti_Lib->T = q; break; }
			case 'K': {VL_Ti_Lib->K = q; break; }
			case 'Y': {VL_Ti_Lib->Y = q; break; }
			case 'L': {VL_Ti_Lib->L = q; break; }
			case 'S': {VL_Ti_Lib->S = q; break; }
			case 'N': {VL_Ti_Lib->N = q; break; }
			case 'P': {VL_Ti_Lib->P = q; break; }
		} // switch

		p = TM_Get_TiLib_HeadPointer(_TrainNum); // 重新定位p的指向

	} // if (!(p = TM_GetHeadPointer(*_TrainNum)))

	// 写入车次信息进NT
	NT->NodeKind = (char*)malloc(sizeof(char) * 3);
	strcpy(NT->NodeKind, "E");
	NT->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	strcpy(NT->TrainNum, _TrainNum);
	NT->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	strcpy(NT->Start, _Start);
	NT->Stop = _Stop;
	NT->End = (char*)malloc(sizeof(char) * STRLENGTH);
	strcpy(NT->End, _End);
	NT->StationLeaveTime = _LeaveTime;
	NT->OccupantQuota = _OccuQuota;
	NT->SurplusTicket = _SurpTick;
	
	// 正式订单头结点
	// 初始化正式订单头结点
	OrNode = (Order*)malloc(sizeof(Order));
	if (!OrNode) return NOSPACE; //无可用空间
	OrNode->NodeKind = (char*)malloc(sizeof(char) * 2);
	OrNode->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->End = (char*)malloc(sizeof(char) * STRLENGTH);

	// 赋值
	OrNode->NodeKind = "H";
	// 所有字符串赋值为空
	OrNode->OrderNum = OrNode->TrainNum = OrNode->phone = OrNode->Start = OrNode->End = '\0';
	OrNode->TicketNum = -1;
	OrNode->next = NULL;

	// 候补订单头结点
	// 初始化候补订单头结点
	WaOrNode = (WaitOrder*)malloc(sizeof(WaitOrder));
	if (!WaOrNode) return NOSPACE; //无可用空间
	WaOrNode->NodeKind = (char*)malloc(sizeof(char) * 2);
	WaOrNode->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->End = (char*)malloc(sizeof(char) * STRLENGTH);

	// 赋值
	WaOrNode->NodeKind = "H";
	// 所有字符串赋值为空
	WaOrNode->OrderNum = WaOrNode->TrainNum = WaOrNode->phone = WaOrNode->Start = WaOrNode->End = '\0';
	WaOrNode->TicketNum = -1;
	// 尾指针指向本头结点，next指向本头结点
	WaOrNode->rear = WaOrNode;
	WaOrNode->next = WaOrNode;

	// 头结点赋值
	NT->TrainOrder = OrNode;
	NT->TrainWaitOrder = WaOrNode;

	NT->next = NULL;

	// 将新车次结点插入到VL_Ti_lib中，并更新对应车次类别头结点的信息
	TM_InsertTrainNode(NT);

	return OK;
}


