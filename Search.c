// 本文件用于存放关于搜索的函数
// 所依赖的关键变量存放于Variables_Lib.c中
// 本文件的函数名以'S_'开头
//
// Test Status: Freeze
// Code Status: Freeze
//
// 函数与功能对应：
// 
// 初始化一个车次链表头链表
// TrainIndexNode* S_RequestTINode()
// return: NULL, 对应头结点地址
// 
// 返回VL_TI_DB中车次类别的入口指针
// TrainIndexNode* S_GetTIHeadPointer(char*)
// return: NULL, 对应头结点指针
// 
// 初始化VL_TI_DB
// Status S_InitTIDB()
// return: NOSPACE, OK
//
// 初始化VL_SI_DB
// Status S_InitSIDB()
// return: NOSPACE, OK
// 
// 将车次信息结点新增进车次检索系统中
// Status S_AddTrainToSearchDB(char*, StopName*) 
// input：车次编号，站点
// return: OK, NOSPACE
//
// 根据车次编号返回VL_Ti_Lib下的车次结点
// SUB_TrainInfo* S_GetTrainNode(char*)
// input：车次编号
// return：对应头指针, NULL
//
// 根据手机号返回VL_Or_Lib下的手机号结点
// PhoneOrder* S_GetPhoneOrder(char*)
// input：电话
// return：对应数据元素结点指针（无则创建该数据元素结点）, NULL（无现成结点，也无空间创建结点）
//

#include "F_Lib.h"
#include "V_Lib.h"

// 初始化部分

// 初始化一个车次链表头链表
// Freeze
TrainIndexNode* S_RequestTINode()
{
	int i; // 索引变量

	TrainIndexNode* node;
	node = (TrainIndexNode*)malloc(sizeof(struct TrainIndexNode));
	StationList* namelist;
	namelist = (StationList*)malloc(sizeof(struct StationList));

	if (!node || !namelist) return NULL; // 无可用空间

	namelist->StationName = "HeadNode";
	namelist->next = NULL;

	node->NodeKind = "H";
	node->TrainNum = "HeadNode";
	node->StationNameList = NULL;

	for (i = 0; i < 10; i++)
	{
		TrainIndexNode* subnode;
		subnode = (TrainIndexNode*)malloc(sizeof(struct TrainIndexNode));
		
		if (!subnode) return NULL; // 无可用空间

		// 初始化加快检索的头结点
		subnode->NodeKind = "H";
		for (int j = 0; j < 10; j++) subnode->NumIndex[j] = NULL;
		subnode->TrainNum = "HeadNode";
		subnode->StationNameList = NULL;

		// 子结点存入指针数组
		node->NumIndex[i] = subnode;
	}
	return node;
}

// 返回VL_TI_DB中车次类别的入口指针
// Freeze
TrainIndexNode* S_Get_TIDB_HeadPointer(char* First)
{
	switch (*First)
	{
	case 'G': return VL_TI_DB->G;
	case 'D': return VL_TI_DB->D;
	case 'C': return VL_TI_DB->C;
	case 'Z': return VL_TI_DB->Z;
	case 'T': return VL_TI_DB->T;
	case 'K': return VL_TI_DB->K;
	case 'Y': return VL_TI_DB->Y;
	case 'L': return VL_TI_DB->L;
	case 'S': return VL_TI_DB->S;
	case 'N': return VL_TI_DB->N;
	case 'P': return VL_TI_DB->P;
	}
	return NULL; // 传入的字符不存在于可用类型中
}

// 初始化VL_TI_DB
// Freeze
Status S_InitTIDB()
{
	TrainIndexDB* TopDB;
	TrainIndexNode* p;
	int i; // 循环变量
	TopDB = (TrainIndexDB*)malloc(sizeof(struct TrainIndexDB));
	if (!TopDB) return NOSPACE; // 无可用空间

	
	for (i = 0; i < 11; i++)
	{
		p = S_RequestTINode();
		switch (i)
		{
		case 0: {TopDB->G = p; break; }
		case 1: {TopDB->D = p; break; }
		case 2: {TopDB->C = p; break; }
		case 3: {TopDB->Z = p; break; }
		case 4: {TopDB->T = p; break; }
		case 5: {TopDB->K = p; break; }
		case 6: {TopDB->Y = p; break; }
		case 7: {TopDB->L = p; break; }
		case 8: {TopDB->S = p; break; }
		case 9: {TopDB->N = p; break; }
		case 10: {TopDB->P = p; break; }

		} // switch (i)
	} // for (i = 0; i < 11; i++)
	
	
	VL_TI_DB = TopDB; // 将结点地址赋值给VL_TI_DB

	return OK;
}

// 初始化VL_SI_DB
// Freeze
Status S_InitSIDB()
{
	StopIndexDB* TopNode;
	TopNode = (StopIndexDB*)malloc(sizeof(struct StopIndexDB));

	if (!TopNode) return NOSPACE; // 无可用空间

	// 头结点赋值
	TopNode->NodeKind = "H";
	TopNode->StationName = "HeadNode";
	TopNode->TrainList = NULL;
	TopNode->next = NULL;

	// 结点地址传送给VL_SI_DB
	VL_SI_DB = TopNode;

	return OK;
}

// 赋值VL_Or_Lib中数据元素的头结点
// Freeze
Status S_Fill_OrLib_HeadNode(PhoneOrderList* p)
{
	p->NodeKind = "H";
	p->OrderStatus = "HN";
	p->CurrentOrder = NULL;
	p->CurrentWaitOrder = NULL;
	p->Train = NULL;
	p->LeaveStop = p->ArriveStop = NULL;
	p->TicketAmount = 0;
	p->NextOrder = NULL;
	return OK;
}

// 根据车次编号返回VL_Ti_Lib下的车次结点
// output：对应头指针
// Freeze
SUB_TrainInfo* S_GetTrainNode(char* _TrainNum)
{
	char First = *_TrainNum; // 车次编号首字母
	SUB_TrainInfo* p, *q; // 工作指针
	
	q = NULL; // q为返回值

	p = TM_Get_TiLib_HeadPointer(_TrainNum); // p指向对应车次类别头结点
	
	int Firnum = (int)*(_TrainNum + 1) - 48;
	p = p->FirstNum[Firnum]->next;

	while (p) // 遍历车次信息链表
	{
		if (strcmp(p->TrainNum, _TrainNum) == 0)
		{
			q = p;
			break;
		}
		p = p->next;
	} // while (p)

	// 此时q为空指针，由于不符合进入RETURN的条件，且函数需要返回值，下面的语句用于q=NULL时的返回
	return q;
}	

// 根据手机号返回VL_Or_Lib下的手机号结点
// output：对应数据元素结点指针（无则创建该数据元素结点）
// Freeze
PhoneOrder* S_GetPhoneOrderNode(char* _phone)
{
	PhoneOrder* p, *PONode; // 工作指针
	PhoneOrderList* q; // 用于新建结点
	int i; // 循环变量

	p = VL_Or_Lib->next; // p指向订单链表首元结点

	while (p) // 遍历订单链表
	{
		if (strcmp(p->phone, _phone)==0) goto RETURN;
		else p = p->next;
	} // while (p)

	if (!p) // 订单链表中无此手机号结点，创建并返回
	{
		q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));
		if (!q) { goto RETURN; } // 无可用空间，返回空指针

		PONode = (PhoneOrder*)malloc(sizeof(struct PhoneOrder));
		if (!PONode) { goto RETURN; } // 无可用空间，返回空指针
		PONode->NodeKind = (char*)malloc(sizeof(char) * 3);
		PONode->phone = (char*)malloc(sizeof(char) * STRLENGTH);
		// 赋值头结点
		S_Fill_OrLib_HeadNode(q);
		PONode->NodeKind = "H";
		strcpy(PONode->phone, _phone);
		PONode->OrderList = q;
		PONode->next = NULL;

		// q插入为VL_Or_lib的首元结点
		p = VL_Or_Lib;
		PONode->next = p->next;
		p->next = PONode;

		// 返回头结点地址
		p = PONode;
		goto RETURN;
	}

	// 返回结点地址
RETURN:return p;
}

// 将车次信息结点新增进车次检索系统中
// Freeze
// input：车次编号，站点
Status S_AddTrainToSearchDB(char* _TrainNum, StopName* _StopName)
{
	// 工作指针
	TrainIndexNode* _TIN;
	StopIndexDB* _SID;
	StopName* psn = _StopName->next;
	_TIN = S_Get_TIDB_HeadPointer(_TrainNum);

	////
	// 分配内存空间
	
	// StationList
	StationList* SL = (StationList*)malloc(sizeof(StationList));
	StationList* psl;

	if (!SL) return NOSPACE; // 无可用空间
	SL->next = NULL;

	// TrainIndexNode
	TrainIndexNode* TIN = (TrainIndexNode*)malloc(sizeof(TrainIndexNode));
	char* TIN_NK = (char*)malloc(sizeof(char) * 3);
	char* TIN_TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);

	if (!TIN || !TIN_NK || !TIN_TrainNum) return NOSPACE;
	TIN->NextTrain = NULL;
	TIN->NodeKind = TIN_NK;
	TIN->TrainNum = TIN_TrainNum;

	// TrainNumList
	TrainNumList* TNL = (TrainNumList*)malloc(sizeof(TrainNumList));
	char* CurNum = (char*)malloc(sizeof(char) * STRLENGTH);

	if (!TNL || !CurNum) return NOSPACE;
	TNL->next = NULL;

	// StopIndexDB
	StopIndexDB* SID = (StopIndexDB*)malloc(sizeof(StopIndexDB));
	char* SID_NK = (char*)malloc(sizeof(char) * 3);
	char* SID_SN = (char*)malloc(sizeof(char) * STRLENGTH);

	if (!SID || !SID_NK || !SID_SN) return NOSPACE;
	SID->next = NULL;
	
	////
	// Process 
	// 将_StopName转换为StationList*
	psl = SL;
	while (psn)
	{
		// 申请新站点空间
		StationList* New_SL = (StationList*)malloc(sizeof(StationList));
		New_SL->StationName = (char*)malloc(sizeof(char) * STRLENGTH);

		if (!New_SL || !New_SL->StationName) return NOSPACE;
		
		// 记录站点名称
		strcpy(New_SL->StationName, psn->name);

		// 置空指针域
		New_SL->next = NULL;

		// New_SL 插入为SL尾结点
		while (psl)
		{
			if (!psl->next)
			{
				psl->next = New_SL;
				break;
			}
			psl = psl->next;
		}

		psn=psn->next; // psn后移

	}
	

	// 将车次数据加入VL_TI_DB;
	// 结点类型
	strcpy(TIN_NK, "E");
	// 用于加快检索的指针数组在此节点中无用，全部置空
	for (int i = 0; i < 10; i++) TIN->NumIndex[i] = NULL;
	// 车次编号
	strcpy(TIN_TrainNum, _TrainNum);
	// 本车次站点
	TIN->StationNameList = SL;
	
	// 将TIN置于VL_TI_DB对应位置的头结点
	// 获取车次首位数字
	int Firnum = (int)*(_TrainNum + 1) - 48;
	// _TIN已经指向首字母开头的头结点，下一步需要指向首位数字开头的头结点
	_TIN = _TIN->NumIndex[Firnum];
	// 插入为头结点
	TIN->NextTrain = _TIN->NextTrain;
	_TIN->NextTrain = TIN;
	// 加入VL_TI_DB完成


	// 遍历站点，将车次加入VL_SI_DB
	psn = _StopName->next; // 指向途径站点首元结点
	while (psn) // 站点列表未遍历完
	{
		_SID = VL_SI_DB ; 
		// 创建新车次结点
		TrainNumList* NewTrainNum = (TrainNumList*)malloc(sizeof(TrainNumList));
		if (!NewTrainNum) return NOSPACE;
		memset(NewTrainNum, 0, sizeof(TrainNumList));
		char* _CurNum = (char*)malloc(sizeof(char) * STRLENGTH);
		if (!_CurNum) return NOSPACE;
		strcpy(_CurNum, _TrainNum);
		NewTrainNum->CurNum = _CurNum;

		// 寻找VL_SI_DB中是否有本途径站点的结点
		while (_SID) // 未遍历完
		{
			// 找到途径站点结点
			if (strcmp(_SID->StationName, psn->name) == 0) 
			{
				// 插入为车次列表首元结点
				if (!(_SID->TrainList)) _SID->TrainList = NewTrainNum;
				else
				{
					NewTrainNum->next = _SID->TrainList->next;
					_SID->TrainList->next = NewTrainNum;
				}
				break;
				
			} // if (strcmp(_SID->StationName, psn->name) == 0) 

			// 遍历到最后结点，且途径站点不存在，创建为头结点
			else if (!(_SID->next)) 
			{
				StopIndexDB* NewSID=(StopIndexDB*)malloc(sizeof(StopIndexDB));
				if (!NewSID) return NOSPACE;
				memset(NewSID, 0, sizeof(StopIndexDB));

				char* NewNK = (char*)malloc(sizeof(char) * 3);
				if (!NewNK) return NOSPACE;
				memset(NewNK, 0, sizeof(char) * 3);

				char* NewSN = (char*)malloc(sizeof(char) * STRLENGTH);
				if (!NewSN) return NOSPACE;
				memset(NewSN, 0, sizeof(char) * STRLENGTH);

				NewSID->NodeKind = NewNK;
				NewSID->StationName = NewSN;

				// 赋值头结点
				strcpy(NewSID->NodeKind, "E");
				strcpy(NewSID->StationName, psn->name);
				// 站点结点头节点加入车次
				NewSID->TrainList = NewTrainNum;

				// 插入为数据库尾结点
				NewSID->next = _SID->next;
				_SID->next = NewSID;

				break;

			} // else if (!(_SID->next)) 
			
			_SID = _SID->next; // 搜寻数据库下一个站点结点
		} // while (_SID)
		// 遍历下一个途径站点
		psn = psn->next;
	}
	
	return OK;
}



