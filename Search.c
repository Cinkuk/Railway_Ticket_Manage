// ���ļ����ڴ�Ź��������ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'S_'��ͷ
//
// Test Status: Undo
// Code Status: Working
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
SUB_TrainInfo* S_GetTrainNode(char* _TrainNum)
{
	char First = *_TrainNum; // ���α������ĸ
	SUB_TrainInfo* p, *q; // ����ָ��
	int i = 0; // ѭ������
	
	q = NULL; // qΪ����ֵ

	if (!(p = TM_Get_TiLib_HeadPointer(_TrainNum))); // pָ���Ӧ�������ͷ���
	return NULL; // ��Ӧ���ͷ��㲻����

	p = p->next;
	while (p) // ����������Ϣ����
	{
		// ���α�Ÿ�ʽΪһλ��ĸ+4λ����
		// ��λ�Ƚϳ�������
		for (i = 0; i <= 5; i++) 
		{
			// ������λ�ȽϾ���ͬ
			// �˳�whileѭ�������ص�ַ
			if (*(p->TrainNum + i) == '\0' && *(_TrainNum + i) == '\0')
			{
				q = p;
				goto RETURN;
			}
			else if (*(p->TrainNum + i) == *(_TrainNum + i)); // ��ǰλ��ͬ���Ƚ���һλ
			else // ��ǰλ��ͬ��pָ����һλ�����ֱȽ���ֹ
			{
				p = p->next;
				break;
			}
		} // for (i = 1; i <= 4; i++) 
	} // while (p)

	// ֻ���ҵ�ƥ����Ż᷵�ض�Ӧָ�룬��������ؿ�ָ��
RETURN: return q;

	// ��ʱqΪ��ָ�룬���ڲ����Ͻ���RETURN���������Һ�����Ҫ����ֵ��������������q=NULLʱ�ķ���
	return q;
}	

// �����ֻ��ŷ���VL_Or_Lib�µ��ֻ��Ž��
// output����Ӧ����Ԫ�ؽ��ָ�루���򴴽�������Ԫ�ؽ�㣩
PhoneOrder* S_GetPhoneOrderNode(char* _phone)
{
	PhoneOrder* p, *PONode; // ����ָ��
	PhoneOrderList* q; // �����½����
	int i; // ѭ������

	p = VL_Or_Lib->next; // pָ�򶩵�������Ԫ���

	while (p) // ������������
	{
		for (i = 0; i <= 11; i++) // �ֻ���Ϊ11λ
		{
			// �ֻ�����λ�ȽϾ���ͬ
			// �˳�whileѭ�������ص�ַ
			if (*(p->phone + i) == '\0' && *(_phone + i) == '\0') // �ֻ���λ�ȽϾ���ͬ
			{
				goto RETURN;
			}
			else if (*(p->phone + i) == *(_phone + i)); // ��ǰλ��ͬ���Ƚ���һλ
			else // ��ǰλ��ͬ��pָ����һ��㣬���ֱȽ���ֹ
			{
				p = p->next;
				break;
			}
		} // for (i = 0; i <= 11; i++) 
	} // while (p)

	if (!p) // �����������޴��ֻ��Ž�㣬����������
	{
		q = (PhoneOrderList*)malloc(sizeof(struct PhoneOrderList));
		if (!q) { goto RETURN; } // �޿��ÿռ䣬���ؿ�ָ��

		PONode = (PhoneOrder*)malloc(sizeof(struct PhoneOrder));
		if (!PONode) { goto RETURN; } // �޿��ÿռ䣬���ؿ�ָ��
		
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
		_SID = VL_SI_DB->next ; // ָ����Ԫ���
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
				NewTrainNum->next = _SID->TrainList->next;
				_SID->TrainList->next = NewTrainNum;
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
				NewSID->StationName - NewSN;

				// ��ֵͷ���
				strcpy(NewSID->NodeKind, "E");
				strcpy(NewSID->StationName, psn->name);
				// վ����ͷ�ڵ���복��
				NewTrainNum->next = NewSID->TrainList->next;
				NewSID->TrainList->next = NewTrainNum;

				// ����Ϊ���ݿ�β���
				NewSID->next = _SID->next;
				_SID->next = NewSID;

			} // else if (!(_SID->next)) 
			
			_SID = _SID->next; // ��Ѱ���ݿ���һ��վ����
		} // while (_SID)
		// ������һ��;��վ��
		psn = psn->next;
	}
	
	return OK;
}


