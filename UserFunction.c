// 本文件存放的函数面向用户的操作
// 本文件的函数名以'UF_'开头
//
// Test Status: Finished
// Code Status: Freeze
//
// 函数与功能对应：
//
// 查询，输入出发地、目的地
// SearchResulr* UF_SearchStop(char* _Leave, char* _Arrive)
// 输入：出发站，到达站，返回结果结构体空指针
// return：OK, ERROR（出发站不存在）, NOSPACE, EMPTY（无可用班次）
// 
// 查询订单
// OrderSet* UF_GetOrderInfo(char* _OrderNum)
// input：订单号
// return：1:正式订单，2：候补订单，3：无此订单
// 
// 下正式订单
// Status UF_New_F_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
//	                     int _TicketNum, char* _phone)
// input: 车次，出发站，到达站，订购票数，手机号
// output: OK, ERROR, NOSPACE
// 
// 下候补订单
// Status UF_New_W_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
//	                     int _TicketNum, char* _phone)
// input: 车次，出发站，到达站，订购票数，手机号
// output: OK, ERROR, NOSPACE
// 
// 删除订单
// Status UF_Delete_Order(char* OrderNum)
// input: 订单号
// output: OK, ERROR
// 
// 按照出发时间递增排序
// SearchResult* UF_LeaveTimeSort(SearchResult* CurRes)
//
// 按照运行时间递增排序
// SearchResult* UF_RunTimeSort(SearchResult* CurRes)
//
// 按照到达时间递增排序
// SearchResult* UF_ArriveTimeSort(SearchResult* CurRes)
// 
// 获取手机号下的订单结点
// PhoneOrder* UF_GetPhoneOrderNode(char* phone)
//

#include "F_Lib.h"
#include "V_Lib.h"


// 查询，输入出发地、目的地
// Freeze
// return：返回结果指针, NULL
SearchResult* UF_SearchStop(char* _Leave, char* _Arrive)
{
	StopIndexDB* LeaveStop; // 工作指针

	int FindLeaveStop = 0; // 0：未找到出发站，1：已找到
	int i = 0; // 循环变量

	char* CurTrain = (char*)malloc(sizeof(char) * STRLENGTH); //当前车次编号
	char* CurStop = (char*)malloc(sizeof(char) * STRLENGTH); // 当前遍历到的站点名

	int Index_L = 0; // 出发站点在车次中的顺序序号
	int Index_A =0; // 终点站在车次中的顺序序号
	int Index = 1; // 当前遍历到的站点的顺序序号

	int _LeaveTime[2] = { 0,0 }; // 出发时间，数组0：小时，数组1：分钟
	int _ArriveTime[2] = { 0,0 }; // 到达时间，数组0：小时，数组1：分钟
	int _ToNextTime=0; // 出发站到终点站的时间

	SUB_TrainInfo* CurTrainNode; // 当前车次的结点
	LeaveTime* CurStopList; // 当前站点

	SearchResult* NEW_SR;

	// 返回结果指针
	// 为SR分配空间，无可用空间则返回空指针
	SearchResult* SR = (SearchResult*)malloc(sizeof(SearchResult));
	if (!SR) return NULL;
	// 填充头结点信息
	SR->TrainNum = SR->Leave = SR->Arrive = "HeadNode";
	SR->TrainNode = NULL;
	for (int j = 0; j < 2; j++) { SR->LeaveTime[j] = SR->ArriveTime[j] = 0; }
	SR->ToNextMin = 0;
	SR->NextResult = NULL;

	LeaveStop = VL_SI_DB->next; // 指向首元结点

	// 遍历站点检索车次的数据库寻找出发站
	while (LeaveStop && FindLeaveStop == 0) // 站点检索车次的数据库未遍历完，未找到出发站
	{
		if(strcmp(LeaveStop->StationName, _Leave)==0)
		{
			// 找到出发站
			FindLeaveStop = 1;
			// 退出查找出发站循环
			break;
		} // if
		// 当前站点不匹配出发站，工作指针移到下一站点
		LeaveStop = LeaveStop->next;
	} // 	while (LeaveStop && FindLeaveStop == 0)

	// 出发站不存在
	if (FindLeaveStop == 0) return NULL; 

	// 出发站存在，遍历经过出发站的全部车次
	TrainNumList* _TrainList = LeaveStop->TrainList;
	FindLeaveStop = 0;
	while (_TrainList) // 车次未遍历完
	{
		_ToNextTime = 0;
		CurTrain = _TrainList->CurNum; // 暂存当前车次编号
		CurTrainNode = S_GetTrainNode(CurTrain);
		CurStopList = CurTrainNode->StationLeaveTime->next;
		
		// 遍历途径站点
		while (CurStopList)
		{
			CurStop = CurStopList->name;
			
			// 站点与出发站相同
			if (strcmp(CurStop, _Leave) == 0)
			{
				Index_L = Index;
				_LeaveTime[0] = CurStopList->hour;
				_LeaveTime[1] = CurStopList->min;

				FindLeaveStop = 1;
			}

			
			
			// 站点与终点站相同
			if (strcmp(CurStop, _Arrive) == 0)
			{
				Index_A = Index;
				_ArriveTime[0] = CurStopList->hour;
				_ArriveTime[1] = CurStopList->min;
				break;

			}

			// 记录出发站到当前车站所经过的总时间
			if (FindLeaveStop == 1) _ToNextTime += CurStopList->ToNextMin;

			// 比较下一个站点
			CurStopList = CurStopList->next; // 指向下一站点

			// 遍历序号自增
			Index++;
		} // while (CurStopList)

		// 出发站和终点站均找到
		// 运行顺序为出发站前往终点站
		// 将查找结果写入搜寻结果中
		if (Index_L != 0 && Index_A != 0 &&
			Index_L < Index_A)
		{
			// 为SR分配空间，无可用空间则返回空指针
			NEW_SR = (SearchResult*)malloc(sizeof(SearchResult));
			if (!NEW_SR) return NULL;
			NEW_SR->TrainNum = CurTrain; // 车次编号
			NEW_SR->Leave = _Leave; // 出发地
			NEW_SR->Arrive = _Arrive; // 到达地
			// 出发时间
			NEW_SR->LeaveTime[0] = _LeaveTime[0];
			NEW_SR->LeaveTime[1] = _LeaveTime[1];
			// 到达时间
			NEW_SR->ArriveTime[0] = _ArriveTime[0];
			NEW_SR->ArriveTime[1] = _ArriveTime[1];
			NEW_SR->ToNextMin = _ToNextTime; // 总运行时间
			NEW_SR->TrainNode = CurTrainNode;
			// NEW_SR插入到SR首元结点
			NEW_SR->NextResult = SR->NextResult;
			SR->NextResult = NEW_SR;
		}

		
		
		// 重置搜索记录变量
		FindLeaveStop = 0;
		Index_L = 0;
		Index_A = 0;
		Index = 1;
		_LeaveTime[0] = _LeaveTime[1] = 0;
		_ArriveTime[0] = _ArriveTime[1] = 0;
		_ToNextTime = 0;
			
		
		// 查找该站点的下一班车次
		_TrainList = _TrainList->next;
	} // while (_TrainList)

	// 无可用车次
	if (!SR->NextResult) return NULL;
	
	// 查找成功
	else return SR;
} // Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)

// 查询订单
// Freeze
// input：订单号
// return：1:正式订单，2：候补订单，3：无此订单
OrderSet* UF_GetOrderInfo(char* _OrderNum)
{
	OrderSet* p; // 工作指针
	p = VL_OrderID;

	while (p) // 遍历订单池
	{
		if (strcmp(BF_Merge_Char(p->ID), _OrderNum) == 0) // 匹配到订单
		{
			return p;
		} // 	if (strcmp(p->ID, _OrderNum) == 0)

		p = p->next; // 下一张单
	} // while (p)

	// 匹配不到订单
	return NULL;
}

// 下正式订单
// Freeze
// input: 车次，出发站，到达站，订购票数，手机号
// output: OK, ERROR, NOSPACE
Status UF_New_F_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
	int _TicketNum, char* _phone)
{
	int ReturnStatus;
	ReturnStatus = OM_New_F_Order(_phone, _TrainNum, _Leave, _Arrive, _TicketNum);
	if (ReturnStatus == OK) return OK;
	else return ERROR;
}

// 下候补订单
// Freeze
// input: 车次，出发站，到达站，订购票数，手机号
// output: OK, ERROR, NOSPACE
Status UF_New_W_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
	int _TicketNum, char* _phone)
{
	int ReturnStatus;
	ReturnStatus = OM_New_W_Order(_phone, _TrainNum, _Leave, _Arrive, _TicketNum);
	if (ReturnStatus == OK) return OK;
	else return ERROR;
}

// 删除订单
// Freeze
// input: 订单号
// output: OK, ERROR
Status UF_Delete_Order(char* OrderNum)
{
	// 工作信息
	char* phone;
	int Kind; // 0：正式订单，1：候补
	char* TrainNum; // 车次
	// 工作指针
	OrderSet* IDNode, * pre_IDNode; // 订单池中的订单结点，前一个结点
	PhoneOrder * PhOrderNode; // 订单数据库中的订单结点
	PhoneOrderList* pre_PhOrder, * PhOrder; // 订单数据库对应手机号中的前一个订单结点，对应订单结点
	SUB_TrainInfo* TrainNode; // 车次结点

	// 用于正式订单
	Order* TrainOrderNode, *pre_TrainOrderNode; // 车次数据库中的订单结点，订单之前一个结点
	
	// 用于候补订单
	WaitOrder* WTrainNode, * pre_WTrainNode; // 车次数据库中的候补订单结点，订单之前一个结点

	// 在订单池中定位
	pre_IDNode = VL_OrderID;
	// pre_IDNode下一个结点是目标结点
	while (strcmp(BF_Merge_Char(pre_IDNode->next->ID), OrderNum) != 0)
	{
		pre_IDNode = pre_IDNode->next;
	}
	IDNode = pre_IDNode->next;

	// 订单类型
	Kind = (strcmp(IDNode->OrderKind, "F") == 0) ? 0 : 1;

	// 保存手机号
	if (Kind == 0)	phone = IDNode->OrderNode->phone;
	else if (Kind == 1) phone = IDNode->WaitOrderNode->phone;
	// 保存车次
	if (Kind == 0) TrainNum = IDNode->OrderNode->TrainNum;
	else if (Kind == 1) TrainNum = IDNode->WaitOrderNode->TrainNum;

	// 获取订单数据库对应手机号结点
	PhOrderNode = S_GetPhoneOrderNode(phone);
	pre_PhOrder = PhOrderNode->OrderList;

	// 获取车次结点
	TrainNode = S_GetTrainNode(TrainNum);

	//////
	// 处理

	// 正式订单
	if (Kind==0)
	{
		// 订单池链表删除目标结点
		pre_IDNode->next = IDNode->next;
		
		// 处理车次数据库
		// 定位车次订单结点
		pre_TrainOrderNode = TrainNode->TrainOrder; 
		while (strcmp(pre_TrainOrderNode->next->OrderNum, OrderNum) != 0)
		{
			pre_TrainOrderNode = pre_TrainOrderNode->next;
		}
		TrainOrderNode = pre_TrainOrderNode->next;
		// 车次数据库链表删除
		pre_TrainOrderNode->next = TrainOrderNode->next;
		
		// 处理订单数据库
		// 定位订单数据库订单结点
		while (strcmp(pre_PhOrder->NextOrder->OrderNum, OrderNum) != 0)
		{
			pre_PhOrder = pre_PhOrder->NextOrder;
		}
		PhOrder = pre_PhOrder->NextOrder;
		// 订单数据库中删除
		pre_PhOrder->NextOrder = PhOrder->NextOrder;
	}
	// 候补订单
	else if (Kind==1)
	{
		// 订单池链表删除目标结点
		pre_IDNode->next = IDNode->next;

		// 处理车次数据库
		// 定位车次订单结点
		pre_WTrainNode = TrainNode->TrainWaitOrder->rear->next;
		while (strcmp(pre_WTrainNode->next->OrderNum, OrderNum) != 0)
		{
			pre_WTrainNode = pre_WTrainNode->next;
		}
		WTrainNode = pre_WTrainNode->next;
		// 车次数据库中删除
		pre_WTrainNode->next = WTrainNode->next;

		// 处理订单数据库
		// 定位订单结点
		while (strcmp(pre_PhOrder->NextOrder->OrderNum, OrderNum) != 0)
		{
			pre_PhOrder = pre_PhOrder->NextOrder;
		}
		PhOrder = pre_PhOrder->NextOrder;
		// 订单数据库中删除
		pre_PhOrder->NextOrder = PhOrder->NextOrder;
	}

	return OK;

}

// 按照出发时间递增排序
// Freeze
SearchResult* UF_LeaveTimeSort(SearchResult* CurRes)
{

	if (!CurRes) return ERROR; 
	int len = 0;
	SearchResult* p = CurRes->NextResult ; // 工作指针指向首元结点
	SearchResult* r, *r_n, *curh, *temp;

	// 计算长度
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	
	if (len == 1) return CurRes;

	// 断开第一和第二个元素
	r = CurRes->NextResult;
	curh = CurRes->NextResult->NextResult;
	r->NextResult = NULL;

	// r_n为比较元素
	r = CurRes;
	r_n = r->NextResult;

	while (curh)
	{
		while (r_n != NULL && (curh->LeaveTime[0]*60+curh->LeaveTime[1]) >= (r_n->LeaveTime[0]*60+r_n->LeaveTime[1]))
		{
			r = r->NextResult;
			r_n = r_n->NextResult;
		}
		temp = curh;
		curh = curh->NextResult;
		r->NextResult = temp;
		temp->NextResult = r_n;
		r = CurRes;
		r_n = r->NextResult;

	}

	return CurRes;
}

// 按照运行时间递增排序
// Freeze
SearchResult* UF_RunTimeSort(SearchResult* CurRes)
{
	if (!CurRes) return ERROR; 
	int len = 0;
	SearchResult* p = CurRes->NextResult ; // 工作指针指向首元结点
	SearchResult* r, *r_n, *curh, *temp;

	// 计算长度
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	
	if (len == 1) return CurRes;

	// 断开第一和第二个元素
	r = CurRes->NextResult;
	curh = CurRes->NextResult->NextResult;
	r->NextResult = NULL;

	// r_n为比较元素
	r = CurRes;
	r_n = r->NextResult;

	while (curh)
	{
		while (r_n != NULL && curh->ToNextMin >= r_n->ToNextMin)
		{
			r = r->NextResult;
			r_n = r_n->NextResult;
		}
		temp = curh;
		curh = curh->NextResult;
		r->NextResult = temp;
		temp->NextResult = r_n;
		r = CurRes;
		r_n = r->NextResult;

	}

	return CurRes;
}

// 按照到达时间递增排序
// Freeze
SearchResult* UF_ArriveTimeSort(SearchResult* CurRes)
{

	if (!CurRes) return ERROR; 
	int len = 0;
	SearchResult* p = CurRes->NextResult ; // 工作指针指向首元结点
	SearchResult* r, *r_n, *curh, *temp;

	// 计算长度
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	
	if (len == 1) return CurRes;

	// 断开第一和第二个元素
	r = CurRes->NextResult;
	curh = CurRes->NextResult->NextResult;
	r->NextResult = NULL;

	// r_n为比较元素
	r = CurRes;
	r_n = r->NextResult;

	while (curh)
	{
		while (r_n != NULL && (curh->ArriveTime[0]*60+curh->ArriveTime[1]) >= (r_n->ArriveTime[0]*60+r_n->ArriveTime[1]))
		{
			r = r->NextResult;
			r_n = r_n->NextResult;
		}
		temp = curh;
		curh = curh->NextResult;
		r->NextResult = temp;
		temp->NextResult = r_n;
		r = CurRes;
		r_n = r->NextResult;

	}

	return CurRes;
}

// 获取手机号下的订单结点
// Freeze
PhoneOrder* UF_GetPhoneOrderNode(char* phone)
{
	return S_GetPhoneOrderNode(phone);
}

