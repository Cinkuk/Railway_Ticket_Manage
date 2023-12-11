// ���ļ���ŵĺ��������û��Ĳ���
// ���ļ��ĺ�������'UF_'��ͷ
//
// Test Status: Undo
// Code Status: Working
//
// �����빦�ܶ�Ӧ��
//
// ��ѯ����������ء�Ŀ�ĵ�
// Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)
// ���룺����վ������վ�����ؽ���ṹ���ָ��
// return��OK, ERROR������վ�����ڣ�, NOSPACE, EMPTY���޿��ð�Σ�
// 
// ��ѯ����
// int UF_GetOrderInfo(char* _OrderNum, void* ResultPtr )
// input��������
// return��1:��ʽ������2���򲹶�����3���޴˶���
// 
// ��ѯ�ֻ����µĶ���
// PhoneOrderList* UF_GetPhoneOrder(char* _phone)
// input���ֻ���
// return�����ֻ����¶�����ͷ���ָ�룬NULL�������ڵ��ֻ���)
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
//Status UF_Delete_Order(char* OrderNum)
// input: ������
// output: OK, ERROR
// 
// 
// 
// 
//  
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
			if (!NEW_SR) return NOSPACE;
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
// input��������
// return��1:��ʽ������2���򲹶�����3���޴˶���
int UF_GetOrderInfo(char* _OrderNum, void* ResultPtr )
{
	OrderSet* p; // ����ָ��
	p = VL_OrderID;

	while (p) // ����������
	{
		if (strcmp(p->ID, _OrderNum) == 0) // ƥ�䵽����
		{
			if (strcmp(p->OrderKind, "F") == 0) // ��ʽ����
			{
				ResultPtr = p->OrderNode;
				return 1;
			}
			else if (strcmp(p->OrderKind, "W") == 0) // �򲹶���
			{
				ResultPtr = p->WaitOrderNode;
				return 2;
			}
		} // 	if (strcmp(p->ID, _OrderNum) == 0)

		p = p->next; // ��һ�ŵ�
	} // while (p)

	// ƥ�䲻������
	ResultPtr = NULL;
	return 3;
}

// ��ѯ�ֻ����µĶ���
// input���ֻ���
// return�����ֻ����¶�����ͷ���ָ�룬NULL�������ڵ��ֻ���)
PhoneOrderList* UF_GetPhoneOrder(char* _phone)
{
	PhoneOrder* p; // ����ָ��
	p = VL_Or_Lib->next; // ָ�򶩵����ݿ���Ԫ���

	while (p) // �����������ݿ�
	{
		if (strcmp(p->phone, _phone) == 0) // ƥ�䵽�ֻ���
		{
			return p->OrderList;
		}
		else // ��һ�ŵ�
			p = p->next;
	}

	// �޴��ֻ���
	return NULL;
}

// ����ʽ����
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
// input: ������
// output: OK, ERROR
Status UF_Delete_Order(char* OrderNum)
{
	
}

// ���ճ���ʱ���������
Status UF_LeaveTimeSort(SearchResult* CurRes)
{
	if (!CurRes->NextResult) return ERROR; // ��Ԫ���Ϊ��
	// ���㳤��
	int len = 0;
	SearchResult* p = CurRes->NextResult; // ����ָ��ָ����Ԫ���
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	BF_QuickSort(CurRes, 1, len, 0);

	return OK;
}


// ��������ʱ���������
Status UF_RunTimeSort(SearchResult* CurRes)
{
	if (!CurRes->NextResult) return ERROR; // ��Ԫ���Ϊ��
	// ���㳤��
	int len = 0;
	SearchResult* p = CurRes->NextResult; // ����ָ��ָ����Ԫ���
	while (p)
	{
		len++;
		p = p->NextResult;
	}
	BF_QuickSort(CurRes, 1, len, 1);

	return OK;
}

