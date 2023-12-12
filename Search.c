// ���ļ����ڴ�Ź��������ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'S_'��ͷ
//
// Test Status: Freeze
// Code Status: Freeze
//
// �����빦�ܶ�Ӧ��
// 
// ��ʼ��һ����������ͷ����
// TrainIndexNode* S_RequestTINode()
// return: NULL, ��Ӧͷ����ַ
// 
// ����VL_TI_DB�г����������ָ��
// TrainIndexNode* S_GetTIHeadPointer(char*)
// return: NULL, ��Ӧͷ���ָ��
// 
// ��ʼ��VL_TI_DB
// Status S_InitTIDB()
// return: NOSPACE, OK
//
// ��ʼ��VL_SI_DB
// Status S_InitSIDB()
// return: NOSPACE, OK
// 
// ��������Ϣ������������μ���ϵͳ��
// Status S_AddTrainToSearchDB(char*, StopName*) 
// input�����α�ţ�վ��
// return: OK, NOSPACE
//
// ���ݳ��α�ŷ���VL_Ti_Lib�µĳ��ν��
// SUB_TrainInfo* S_GetTrainNode(char*)
// input�����α��
// return����Ӧͷָ��, NULL
//
// �����ֻ��ŷ���VL_Or_Lib�µ��ֻ��Ž��
// PhoneOrder* S_GetPhoneOrder(char*)
// input���绰
// return����Ӧ����Ԫ�ؽ��ָ�루���򴴽�������Ԫ�ؽ�㣩, NULL�����ֳɽ�㣬Ҳ�޿ռ䴴����㣩
//

#include "F_Lib.h"
#include "V_Lib.h"

// ��ʼ������

// ��ʼ��һ����������ͷ����
// Freeze
TrainIndexNode* S_RequestTINode()
{
	int i; // ��������

	TrainIndexNode* node;
	node = (TrainIndexNode*)malloc(sizeof(struct TrainIndexNode));
	StationList* namelist;
	namelist = (StationList*)malloc(sizeof(struct StationList));

	if (!node || !namelist) return NULL; // �޿��ÿռ�

	namelist->StationName = "HeadNode";
	namelist->next = NULL;

	node->NodeKind = "H";
	node->TrainNum = "HeadNode";
	node->StationNameList = NULL;

	for (i = 0; i < 10; i++)
	{
		TrainIndexNode* subnode;
		subnode = (TrainIndexNode*)malloc(sizeof(struct TrainIndexNode));
		
		if (!subnode) return NULL; // �޿��ÿռ�

		// ��ʼ���ӿ������ͷ���
		subnode->NodeKind = "H";
		for (int j = 0; j < 10; j++) subnode->NumIndex[j] = NULL;
		subnode->TrainNum = "HeadNode";
		subnode->StationNameList = NULL;

		// �ӽ�����ָ������
		node->NumIndex[i] = subnode;
	}
	return node;
}

// ����VL_TI_DB�г����������ָ��
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
	return NULL; // ������ַ��������ڿ���������
}

// ��ʼ��VL_TI_DB
// Freeze
Status S_InitTIDB()
{
	TrainIndexDB* TopDB;
	TrainIndexNode* p;
	int i; // ѭ������
	TopDB = (TrainIndexDB*)malloc(sizeof(struct TrainIndexDB));
	if (!TopDB) return NOSPACE; // �޿��ÿռ�

	
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
	
	
	VL_TI_DB = TopDB; // ������ַ��ֵ��VL_TI_DB

	return OK;
}

// ��ʼ��VL_SI_DB
// Freeze
Status S_InitSIDB()
{
	StopIndexDB* TopNode;
	TopNode = (StopIndexDB*)malloc(sizeof(struct StopIndexDB));

	if (!TopNode) return NOSPACE; // �޿��ÿռ�

	// ͷ��㸳ֵ
	TopNode->NodeKind = "H";
	TopNode->StationName = "HeadNode";
	TopNode->TrainList = NULL;
	TopNode->next = NULL;

	// ����ַ���͸�VL_SI_DB
	VL_SI_DB = TopNode;

	return OK;
}

// ��ֵVL_Or_Lib������Ԫ�ص�ͷ���
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

// ���ݳ��α�ŷ���VL_Ti_Lib�µĳ��ν��
// output����Ӧͷָ��
// Freeze
SUB_TrainInfo* S_GetTrainNode(char* _TrainNum)
{
	char First = *_TrainNum; // ���α������ĸ
	SUB_TrainInfo* p, *q; // ����ָ��
	
	q = NULL; // qΪ����ֵ

	p = TM_Get_TiLib_HeadPointer(_TrainNum); // pָ���Ӧ�������ͷ���
	
	int Firnum = (int)*(_TrainNum + 1) - 48;
	p = p->FirstNum[Firnum]->next;

	while (p) // ����������Ϣ����
	{
		if (strcmp(p->TrainNum, _TrainNum) == 0)
		{
			q = p;
			break;
		}
		p = p->next;
	} // while (p)

	// ��ʱqΪ��ָ�룬���ڲ����Ͻ���RETURN���������Һ�����Ҫ����ֵ��������������q=NULLʱ�ķ���
	return q;
}	

// �����ֻ��ŷ���VL_Or_Lib�µ��ֻ��Ž��
// output����Ӧ����Ԫ�ؽ��ָ�루���򴴽�������Ԫ�ؽ�㣩
// Freeze
PhoneOrder* S_GetPhoneOrderNode(char* _phone)
{
	PhoneOrder* p, *PONode; // ����ָ��
	PhoneOrderList* q; // �����½����
	int i; // ѭ������

	p = VL_Or_Lib->next; // pָ�򶩵�������Ԫ���

	while (p) // ������������
	{
		if (strcmp(p->phone, _phone)==0) goto RETURN;
		else p = p->next;
	} // while (p)

	if (!p) // �����������޴��ֻ��Ž�㣬����������
	{
		q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));
		if (!q) { goto RETURN; } // �޿��ÿռ䣬���ؿ�ָ��

		PONode = (PhoneOrder*)malloc(sizeof(struct PhoneOrder));
		if (!PONode) { goto RETURN; } // �޿��ÿռ䣬���ؿ�ָ��
		PONode->NodeKind = (char*)malloc(sizeof(char) * 3);
		PONode->phone = (char*)malloc(sizeof(char) * STRLENGTH);
		// ��ֵͷ���
		S_Fill_OrLib_HeadNode(q);
		PONode->NodeKind = "H";
		strcpy(PONode->phone, _phone);
		PONode->OrderList = q;
		PONode->next = NULL;

		// q����ΪVL_Or_lib����Ԫ���
		p = VL_Or_Lib;
		PONode->next = p->next;
		p->next = PONode;

		// ����ͷ����ַ
		p = PONode;
		goto RETURN;
	}

	// ���ؽ���ַ
RETURN:return p;
}

// ��������Ϣ������������μ���ϵͳ��
// Freeze
// input�����α�ţ�վ��
Status S_AddTrainToSearchDB(char* _TrainNum, StopName* _StopName)
{
	// ����ָ��
	TrainIndexNode* _TIN;
	StopIndexDB* _SID;
	StopName* psn = _StopName->next;
	_TIN = S_Get_TIDB_HeadPointer(_TrainNum);

	////
	// �����ڴ�ռ�
	
	// StationList
	StationList* SL = (StationList*)malloc(sizeof(StationList));
	StationList* psl;

	if (!SL) return NOSPACE; // �޿��ÿռ�
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
	// ��_StopNameת��ΪStationList*
	psl = SL;
	while (psn)
	{
		// ������վ��ռ�
		StationList* New_SL = (StationList*)malloc(sizeof(StationList));
		New_SL->StationName = (char*)malloc(sizeof(char) * STRLENGTH);

		if (!New_SL || !New_SL->StationName) return NOSPACE;
		
		// ��¼վ������
		strcpy(New_SL->StationName, psn->name);

		// �ÿ�ָ����
		New_SL->next = NULL;

		// New_SL ����ΪSLβ���
		while (psl)
		{
			if (!psl->next)
			{
				psl->next = New_SL;
				break;
			}
			psl = psl->next;
		}

		psn=psn->next; // psn����

	}
	

	// ���������ݼ���VL_TI_DB;
	// �������
	strcpy(TIN_NK, "E");
	// ���ڼӿ������ָ�������ڴ˽ڵ������ã�ȫ���ÿ�
	for (int i = 0; i < 10; i++) TIN->NumIndex[i] = NULL;
	// ���α��
	strcpy(TIN_TrainNum, _TrainNum);
	// ������վ��
	TIN->StationNameList = SL;
	
	// ��TIN����VL_TI_DB��Ӧλ�õ�ͷ���
	// ��ȡ������λ����
	int Firnum = (int)*(_TrainNum + 1) - 48;
	// _TIN�Ѿ�ָ������ĸ��ͷ��ͷ��㣬��һ����Ҫָ����λ���ֿ�ͷ��ͷ���
	_TIN = _TIN->NumIndex[Firnum];
	// ����Ϊͷ���
	TIN->NextTrain = _TIN->NextTrain;
	_TIN->NextTrain = TIN;
	// ����VL_TI_DB���


	// ����վ�㣬�����μ���VL_SI_DB
	psn = _StopName->next; // ָ��;��վ����Ԫ���
	while (psn) // վ���б�δ������
	{
		_SID = VL_SI_DB ; 
		// �����³��ν��
		TrainNumList* NewTrainNum = (TrainNumList*)malloc(sizeof(TrainNumList));
		if (!NewTrainNum) return NOSPACE;
		memset(NewTrainNum, 0, sizeof(TrainNumList));
		char* _CurNum = (char*)malloc(sizeof(char) * STRLENGTH);
		if (!_CurNum) return NOSPACE;
		strcpy(_CurNum, _TrainNum);
		NewTrainNum->CurNum = _CurNum;

		// Ѱ��VL_SI_DB���Ƿ��б�;��վ��Ľ��
		while (_SID) // δ������
		{
			// �ҵ�;��վ����
			if (strcmp(_SID->StationName, psn->name) == 0) 
			{
				// ����Ϊ�����б���Ԫ���
				if (!(_SID->TrainList)) _SID->TrainList = NewTrainNum;
				else
				{
					NewTrainNum->next = _SID->TrainList->next;
					_SID->TrainList->next = NewTrainNum;
				}
				break;
				
			} // if (strcmp(_SID->StationName, psn->name) == 0) 

			// ����������㣬��;��վ�㲻���ڣ�����Ϊͷ���
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

				// ��ֵͷ���
				strcpy(NewSID->NodeKind, "E");
				strcpy(NewSID->StationName, psn->name);
				// վ����ͷ�ڵ���복��
				NewSID->TrainList = NewTrainNum;

				// ����Ϊ���ݿ�β���
				NewSID->next = _SID->next;
				_SID->next = NewSID;

				break;

			} // else if (!(_SID->next)) 
			
			_SID = _SID->next; // ��Ѱ���ݿ���һ��վ����
		} // while (_SID)
		// ������һ��;��վ��
		psn = psn->next;
	}
	
	return OK;
}



