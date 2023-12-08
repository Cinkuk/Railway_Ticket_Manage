// ���ļ���ŵĺ��������û��Ĳ���
// ���ļ��ĺ�������'UF_'��ͷ
//
// Test Status: Undo
// Code Status: Undo
//
// �����빦�ܶ�Ӧ��
//
// ��ѯ����������ء�Ŀ�ĵ�
// Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)
// ���룺����վ������վ�����ؽ���ṹ���ָ��
// return��OK, ERROR������վ�����ڣ�, NOSPACE, EMPTY���޿��ð�Σ�
// 
// ��ѯ����
// PhoneOrderList* UF_GetOrderInfo(char* _OrderNum)
// input��������
// return��PhoneOrderLIst* ���ָ��, NULL(�����ڵĶ���)
// 
// ��ѯ�ֻ����µĶ���
// PhoneOrderList* UF_GetPhoneOrder(char* _phone)
// input��������
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
//Status UF_New_W_Order(char* OrderNum)
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ��ѯ����������ء�Ŀ�ĵ�
// return��OK, ERROR������վ�����ڣ�, NOSPACE, EMPTY���޿��ð�Σ�
Status UF_SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)
{
	StopIndexDB* LeaveStop; // ����ָ��

	int FindLeaveStop = 0; // 0��δ�ҵ�����վ��1�����ҵ�
	int i = 0; // ѭ������

	char* CurTrain; //��ǰ���α��
	char* CurStop; // ��ǰ��������վ����

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
	if (!(SR = (SearchResult*)malloc(sizeof(SearchResult)))) return NOSPACE;
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
		while (*(LeaveStop->StationName + i) == *(_Leave + i) &&
			i != 0) // ��Ҫƥ����ַ����ǿգ���λƥ�����
		{
			i++;
		} // while
		// ��Ҫƥ����ַ�����ȫ��ͬ�ҷǿգ��ҵ�����վ
		if (*(LeaveStop->StationName + i) == '\0' &&
			*(_Leave + i) == '\0' && i != 0)
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
	if (FindLeaveStop == 0) return ERROR; 

	// ����վ���ڣ�������������վ��ȫ������
	TrainNumList* _TrainList = LeaveStop->TrainList;
	FindLeaveStop = 0;
	while (_TrainList) // ����δ������
	{
		CurTrain = _TrainList->CurNum; // �ݴ浱ǰ���α��
		CurTrainNode = S_GetTrainNode(CurTrain);
		CurStopList = CurTrainNode->StationLeaveTime;
		
#if 0
		// �Ƚϳ���վ���յ�վ�복�θ�վ��
		// ����վ�복���յ�վ���
		if (strcmp(_Leave, CurTrainNode->Start) == 0)
		{
			Index_L = Index;
			
			Index++;
		}
#endif

		CurStop = CurStopList->name;
		// ����;��վ��
		while (CurStopList)
		{
			// ��¼����վ����ǰ��վ����������ʱ��
			if (FindLeaveStop == 1) _ToNextTime += 60 * CurStopList->hour + CurStopList->min;

			// վ�������վ��ͬ
			if (strcmp(CurStop, _Leave) == 0)
			{
				Index_L = Index;
				_LeaveTime[0] = CurStopList->hour;
				_LeaveTime[1] = CurStopList->min;

				FindLeaveStop = 1;
			}
			
			// վ�����յ�վ��ͬ
			else if (strcmp(CurStop, _Arrive) == 0)
			{
				Index_A = Index;
				_ArriveTime[0] = CurStopList->hour;
				_ArriveTime[1] = CurStopList->min;

			}

			// ������ͬ���Ƚ���һ��վ��
			CurStopList = CurStopList->next; // ָ����һվ��
			CurStop = CurStopList->name; // ��¼��ǰվ������

			// �����������
			Index++;
		} // while (CurStopList)

#if 0
		// �յ�վ���յ�վ��ͬ
		if (strcmp(_Leave, CurTrainNode->End) == 0) Index_A = Index;
#endif
		
		// ����վ���յ�վ���ҵ�
		// ����˳��Ϊ����վǰ���յ�վ
		// �����ҽ��д����Ѱ�����
		if (Index_L != 0 && Index_A != 0 &&
			Index_L < Index_A)
		{
			// ΪSR����ռ䣬�޿��ÿռ��򷵻ؿ�ָ��
			if (!(NEW_SR = (SearchResult*)malloc(sizeof(SearchResult)))) return NULL;
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

		else
		{
			// ����������¼����
			FindLeaveStop = 0;
			Index_L = Index_A = Index = 0;
			_LeaveTime[0] = _LeaveTime[1] = 0;
			_ArriveTime[0] = _ArriveTime[1] = 0;
			_ToNextTime = 0;
			
			// ���Ҹ�վ�����һ�೵��
			_TrainList = _TrainList->next;
		}
	} // while (_TrainList)

	// �޿��ó���
	if (!SR->NextResult) return EMPTY;
	
	// ���ҳɹ�
	else return OK;
} // Status SearchStop(char* _Leave, char* _Arrive, SearchResult* SR)

// ��ѯ����
// input��������
// return��PhoneOrderLIst* ���ָ��, NULL(�����ڵĶ���)
PhoneOrderList* UF_GetOrderInfo(char* _OrderNum)
{

}


// ��ѯ�ֻ����µĶ���
// input��������
// return�����ֻ����¶�����ͷ���ָ�룬NULL�������ڵ��ֻ���)
PhoneOrderList* UF_GetPhoneOrder(char* _phone)
{

}

// ����ʽ����
// input: ���Σ�����վ������վ������Ʊ�����ֻ���
// output: OK, ERROR, NOSPACE
Status UF_New_F_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
	int _TicketNum, char* _phone)
{

}

// �º򲹶���
// input: ���Σ�����վ������վ������Ʊ�����ֻ���
// output: OK, ERROR, NOSPACE
Status UF_New_W_Order(char* _TrainNum, char* _Leave, char* _Arrive, 
	int _TicketNum, char* _phone)
{

}

// ɾ������
// input: ������
// output: OK, ERROR
Status UF_New_W_Order(char* OrderNum)
{

}



