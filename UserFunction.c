// ���ļ���ŵĺ��������û��Ĳ���
// ���ļ��ĺ�������'UF_'��ͷ
//
// Test Status: Finished
// Code Status: Freeze
//
// �����빦�ܶ�Ӧ��
//
// ��ѯ����������ء�Ŀ�ĵ�
// SearchResulr* UF_SearchStop(char* _Leave, char* _Arrive)
// ���룺����վ������վ�����ؽ���ṹ���ָ��
// return��OK, ERROR������վ�����ڣ�, NOSPACE, EMPTY���޿��ð�Σ�
// 
// ��ѯ����
// OrderSet* UF_GetOrderInfo(char* _OrderNum)
// input��������
// return��1:��ʽ������2���򲹶�����3���޴˶���
// 
// ����ʽ����
// Status UF_New_F_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
//	                     int _TicketNum, char* _phone)
// input: ���Σ�����վ������վ������Ʊ�����ֻ���
// output: OK, ERROR, NOSPACE
// 
// �º򲹶���
// Status UF_New_W_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
//	                     int _TicketNum, char* _phone)
// input: ���Σ�����վ������վ������Ʊ�����ֻ���
// output: OK, ERROR, NOSPACE
// 
// ɾ������
// Status UF_Delete_Order(char* OrderNum)
// input: ������
// output: OK, ERROR
// 
// ���ճ���ʱ���������
// SearchResult* UF_LeaveTimeSort(SearchResult* CurRes)
//
// ��������ʱ���������
// SearchResult* UF_RunTimeSort(SearchResult* CurRes)
//
// ���յ���ʱ���������
// SearchResult* UF_ArriveTimeSort(SearchResult* CurRes)
// 
// ��ȡ�ֻ����µĶ������
// PhoneOrder* UF_GetPhoneOrderNode(char* phone)
//

#include "F_Lib.h"
#include "V_Lib.h"


// ��ѯ����������ء�Ŀ�ĵ�
// Freeze
// return�����ؽ��ָ��, NULL
SearchResult* UF_SearchStop(char* _Leave, char* _Arrive)
{
	StopIndexDB* LeaveStop; // ����ָ��

	int FindLeaveStop = 0; // 0��δ�ҵ�����վ��1�����ҵ�
	int i = 0; // ѭ������

	char* CurTrain = (char*)malloc(sizeof(char) * STRLENGTH); //��ǰ���α��
	char* CurStop = (char*)malloc(sizeof(char) * STRLENGTH); // ��ǰ��������վ����

	int Index_L = 0; // ����վ���ڳ����е�˳�����
	int Index_A =0; // �յ�վ�ڳ����е�˳�����
	int Index = 1; // ��ǰ��������վ���˳�����

	int _LeaveTime[2] = { 0,0 }; // ����ʱ�䣬����0��Сʱ������1������
	int _ArriveTime[2] = { 0,0 }; // ����ʱ�䣬����0��Сʱ������1������
	int _ToNextTime=0; // ����վ���յ�վ��ʱ��

	SUB_TrainInfo* CurTrainNode; // ��ǰ���εĽ��
	LeaveTime* CurStopList; // ��ǰվ��

	SearchResult* NEW_SR;

	// ���ؽ��ָ��
	// ΪSR����ռ䣬�޿��ÿռ��򷵻ؿ�ָ��
	SearchResult* SR = (SearchResult*)malloc(sizeof(SearchResult));
	if (!SR) return NULL;
	// ���ͷ�����Ϣ
	SR->TrainNum = SR->Leave = SR->Arrive = "HeadNode";
	SR->TrainNode = NULL;
	for (int j = 0; j < 2; j++) { SR->LeaveTime[j] = SR->ArriveTime[j] = 0; }
	SR->ToNextMin = 0;
	SR->NextResult = NULL;

	LeaveStop = VL_SI_DB->next; // ָ����Ԫ���

	// ����վ��������ε����ݿ�Ѱ�ҳ���վ
	while (LeaveStop && FindLeaveStop == 0) // վ��������ε����ݿ�δ�����꣬δ�ҵ�����վ
	{
		if(strcmp(LeaveStop->StationName, _Leave)==0)
		{
			// �ҵ�����վ
			FindLeaveStop = 1;
			// �˳����ҳ���վѭ��
			break;
		} // if
		// ��ǰվ�㲻ƥ�����վ������ָ���Ƶ���һվ��
		LeaveStop = LeaveStop->next;
	} // 	while (LeaveStop && FindLeaveStop == 0)

	// ����վ������
	if (FindLeaveStop == 0) return NULL; 

	// ����վ���ڣ�������������վ��ȫ������
	TrainNumList* _TrainList = LeaveStop->TrainList;
	FindLeaveStop = 0;
	while (_TrainList) // ����δ������
	{
		_ToNextTime = 0;
		CurTrain = _TrainList->CurNum; // �ݴ浱ǰ���α��
		CurTrainNode = S_GetTrainNode(CurTrain);
		CurStopList = CurTrainNode->StationLeaveTime->next;
		
		// ����;��վ��
		while (CurStopList)
		{
			CurStop = CurStopList->name;
			
			// վ�������վ��ͬ
			if (strcmp(CurStop, _Leave) == 0)
			{
				Index_L = Index;
				_LeaveTime[0] = CurStopList->hour;
				_LeaveTime[1] = CurStopList->min;

				FindLeaveStop = 1;
			}

			
			
			// վ�����յ�վ��ͬ
			if (strcmp(CurStop, _Arrive) == 0)
			{
				Index_A = Index;
				_ArriveTime[0] = CurStopList->hour;
				_ArriveTime[1] = CurStopList->min;
				break;

			}

			// ��¼����վ����ǰ��վ����������ʱ��
			if (FindLeaveStop == 1) _ToNextTime += CurStopList->ToNextMin;

			// �Ƚ���һ��վ��
			CurStopList = CurStopList->next; // ָ����һվ��

			// �����������
			Index++;
		} // while (CurStopList)

		// ����վ���յ�վ���ҵ�
		// ����˳��Ϊ����վǰ���յ�վ
		// �����ҽ��д����Ѱ�����
		if (Index_L != 0 && Index_A != 0 &&
			Index_L < Index_A)
		{
			// ΪSR����ռ䣬�޿��ÿռ��򷵻ؿ�ָ��
			NEW_SR = (SearchResult*)malloc(sizeof(SearchResult));
			if (!NEW_SR) return NULL;
			NEW_SR->TrainNum = CurTrain; // ���α��
			NEW_SR->Leave = _Leave; // ������
			NEW_SR->Arrive = _Arrive; // �����
			// ����ʱ��
			NEW_SR->LeaveTime[0] = _LeaveTime[0];
			NEW_SR->LeaveTime[1] = _LeaveTime[1];
			// ����ʱ��
			NEW_SR->ArriveTime[0] = _ArriveTime[0];
			NEW_SR->ArriveTime[1] = _ArriveTime[1];
			NEW_SR->ToNextMin = _ToNextTime; // ������ʱ��
			NEW_SR->TrainNode = CurTrainNode;
			// NEW_SR���뵽SR��Ԫ���
			NEW_SR->NextResult = SR->NextResult;
			SR->NextResult = NEW_SR;
		}

		
		
		// ����������¼����
		FindLeaveStop = 0;
		Index_L = 0;
		Index_A = 0;
		Index = 1;
		_LeaveTime[0] = _LeaveTime[1] = 0;
		_ArriveTime[0] = _ArriveTime[1] = 0;
		_ToNextTime = 0;
			
		
		// ���Ҹ�վ�����һ�೵��
		_TrainList = _TrainList->next;
	} // while (_TrainList)

	// �޿��ó���
	if (!SR->NextResult) return NULL;
	
	// ���ҳɹ�
	else return SR;
} // Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)

// ��ѯ����
// Freeze
// input��������
// return��1:��ʽ������2���򲹶�����3���޴˶���
OrderSet* UF_GetOrderInfo(char* _OrderNum)
{
	OrderSet* p; // ����ָ��
	p = VL_OrderID;

	while (p) // ����������
	{
		if (strcmp(BF_Merge_Char(p->ID), _OrderNum) == 0) // ƥ�䵽����
		{
			return p;
		} // 	if (strcmp(p->ID, _OrderNum) == 0)

		p = p->next; // ��һ�ŵ�
	} // while (p)

	// ƥ�䲻������
	return NULL;
}

// ����ʽ����
// Freeze
// input: ���Σ�����վ������վ������Ʊ�����ֻ���
// output: OK, ERROR, NOSPACE
Status UF_New_F_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
	int _TicketNum, char* _phone)
{
	int ReturnStatus;
	ReturnStatus = OM_New_F_Order(_phone, _TrainNum, _Leave, _Arrive, _TicketNum);
	if (ReturnStatus == OK) return OK;
	else return ERROR;
}

// �º򲹶���
// Freeze
// input: ���Σ�����վ������վ������Ʊ�����ֻ���
// output: OK, ERROR, NOSPACE
Status UF_New_W_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
	int _TicketNum, char* _phone)
{
	int ReturnStatus;
	ReturnStatus = OM_New_W_Order(_phone, _TrainNum, _Leave, _Arrive, _TicketNum);
	if (ReturnStatus == OK) return OK;
	else return ERROR;
}

// ɾ������
// Freeze
// input: ������
// output: OK, ERROR
Status UF_Delete_Order(char* OrderNum)
{
	// ������Ϣ
	char* phone;
	int Kind; // 0����ʽ������1����
	char* TrainNum; // ����
	// ����ָ��
	OrderSet* IDNode, * pre_IDNode; // �������еĶ�����㣬ǰһ�����
	PhoneOrder * PhOrderNode; // �������ݿ��еĶ������
	PhoneOrderList* pre_PhOrder, * PhOrder; // �������ݿ��Ӧ�ֻ����е�ǰһ��������㣬��Ӧ�������
	SUB_TrainInfo* TrainNode; // ���ν��

	// ������ʽ����
	Order* TrainOrderNode, *pre_TrainOrderNode; // �������ݿ��еĶ�����㣬����֮ǰһ�����
	
	// ���ں򲹶���
	WaitOrder* WTrainNode, * pre_WTrainNode; // �������ݿ��еĺ򲹶�����㣬����֮ǰһ�����

	// �ڶ������ж�λ
	pre_IDNode = VL_OrderID;
	// pre_IDNode��һ�������Ŀ����
	while (strcmp(BF_Merge_Char(pre_IDNode->next->ID), OrderNum) != 0)
	{
		pre_IDNode = pre_IDNode->next;
	}
	IDNode = pre_IDNode->next;

	// ��������
	Kind = (strcmp(IDNode->OrderKind, "F") == 0) ? 0 : 1;

	// �����ֻ���
	if (Kind == 0)	phone = IDNode->OrderNode->phone;
	else if (Kind == 1) phone = IDNode->WaitOrderNode->phone;
	// ���泵��
	if (Kind == 0) TrainNum = IDNode->OrderNode->TrainNum;
	else if (Kind == 1) TrainNum = IDNode->WaitOrderNode->TrainNum;

	// ��ȡ�������ݿ��Ӧ�ֻ��Ž��
	PhOrderNode = S_GetPhoneOrderNode(phone);
	pre_PhOrder = PhOrderNode->OrderList;

	// ��ȡ���ν��
	TrainNode = S_GetTrainNode(TrainNum);

	//////
	// ����

	// ��ʽ����
	if (Kind==0)
	{
		// ����������ɾ��Ŀ����
		pre_IDNode->next = IDNode->next;
		
		// ���������ݿ�
		// ��λ���ζ������
		pre_TrainOrderNode = TrainNode->TrainOrder; 
		while (strcmp(pre_TrainOrderNode->next->OrderNum, OrderNum) != 0)
		{
			pre_TrainOrderNode = pre_TrainOrderNode->next;
		}
		TrainOrderNode = pre_TrainOrderNode->next;
		// �������ݿ�����ɾ��
		pre_TrainOrderNode->next = TrainOrderNode->next;
		
		// ���������ݿ�
		// ��λ�������ݿⶩ�����
		while (strcmp(pre_PhOrder->NextOrder->OrderNum, OrderNum) != 0)
		{
			pre_PhOrder = pre_PhOrder->NextOrder;
		}
		PhOrder = pre_PhOrder->NextOrder;
		// �������ݿ���ɾ��
		pre_PhOrder->NextOrder = PhOrder->NextOrder;
	}
	// �򲹶���
	else if (Kind==1)
	{
		// ����������ɾ��Ŀ����
		pre_IDNode->next = IDNode->next;

		// ���������ݿ�
		// ��λ���ζ������
		pre_WTrainNode = TrainNode->TrainWaitOrder->rear->next;
		while (strcmp(pre_WTrainNode->next->OrderNum, OrderNum) != 0)
		{
			pre_WTrainNode = pre_WTrainNode->next;
		}
		WTrainNode = pre_WTrainNode->next;
		// �������ݿ���ɾ��
		pre_WTrainNode->next = WTrainNode->next;

		// ���������ݿ�
		// ��λ�������
		while (strcmp(pre_PhOrder->NextOrder->OrderNum, OrderNum) != 0)
		{
			pre_PhOrder = pre_PhOrder->NextOrder;
		}
		PhOrder = pre_PhOrder->NextOrder;
		// �������ݿ���ɾ��
		pre_PhOrder->NextOrder = PhOrder->NextOrder;
	}

	return OK;

}

// ���ճ���ʱ���������
// Freeze
SearchResult* UF_LeaveTimeSort(SearchResult* CurRes)
{

	if (!CurRes) return ERROR; 
	int len = 0;
	SearchResult* p = CurRes->NextResult ; // ����ָ��ָ����Ԫ���
	SearchResult* r, *r_n, *curh, *temp;

	// ���㳤��
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	
	if (len == 1) return CurRes;

	// �Ͽ���һ�͵ڶ���Ԫ��
	r = CurRes->NextResult;
	curh = CurRes->NextResult->NextResult;
	r->NextResult = NULL;

	// r_nΪ�Ƚ�Ԫ��
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

// ��������ʱ���������
// Freeze
SearchResult* UF_RunTimeSort(SearchResult* CurRes)
{
	if (!CurRes) return ERROR; 
	int len = 0;
	SearchResult* p = CurRes->NextResult ; // ����ָ��ָ����Ԫ���
	SearchResult* r, *r_n, *curh, *temp;

	// ���㳤��
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	
	if (len == 1) return CurRes;

	// �Ͽ���һ�͵ڶ���Ԫ��
	r = CurRes->NextResult;
	curh = CurRes->NextResult->NextResult;
	r->NextResult = NULL;

	// r_nΪ�Ƚ�Ԫ��
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

// ���յ���ʱ���������
// Freeze
SearchResult* UF_ArriveTimeSort(SearchResult* CurRes)
{

	if (!CurRes) return ERROR; 
	int len = 0;
	SearchResult* p = CurRes->NextResult ; // ����ָ��ָ����Ԫ���
	SearchResult* r, *r_n, *curh, *temp;

	// ���㳤��
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	
	if (len == 1) return CurRes;

	// �Ͽ���һ�͵ڶ���Ԫ��
	r = CurRes->NextResult;
	curh = CurRes->NextResult->NextResult;
	r->NextResult = NULL;

	// r_nΪ�Ƚ�Ԫ��
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

// ��ȡ�ֻ����µĶ������
// Freeze
PhoneOrder* UF_GetPhoneOrderNode(char* phone)
{
	return S_GetPhoneOrderNode(phone);
}

