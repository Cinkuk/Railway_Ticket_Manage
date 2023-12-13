// ���ļ����ڴ�ų�Ʊ�����ι���ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'TM_'��ͷ
//
// Test Status: Freeze
// Code Status: Freeze
//
// �����빦�ܶ�Ӧ��
// 
// ����SUB_TrainInfo����ͷ��㣬���ڳ�ʼ��FirstNum[]ָ�������ڵĽ��
// SUB_TrainInfo* TM_RequestSUBTrainHeadNode()
// ����ֵ��NULL���޿��ÿռ䣩, ��Ӧ����ַ
// 
// ����SUB_TrainInfo����ͷ��㣬���ڳ�ʼ��TOP_TrainInfo�µĽ��
// SUB_TrainInfo* TM_RequestNodeForTopNode()
// ����ֵ��NULL���޿��ÿռ䣩, ��Ӧ����ַ
// 
// ��ʼ��VL_Ti_Lib
// Status InitTicket()
// ����ֵ��OK, NOSPACE
// 
// ����VL_Ti_Lib�ж�Ӧ���ο�ͷ��ͷָ��
// SUB_TrainInfo * TM_Get_TiLib_HeadPointer(char*)
// ����ֵ����Ӧ���ε�SUB_TrainInfoָ��, NULL�������ڣ�
// 
// ��������Ϣ�������������뵽��Ӧλ��
// Status TM_InsertTrainNode (SUB_TrainInfo*)
// ����ֵ��ERROR����Ӧ����ͷ��㲻���ڣ�, NPSPACE����Ӧ����С����ָ�벻�������޿ռ���з��䣩, OK
//
// ��������
// Status TM_NewTrain(char* , char* , StopName* , char* ,
//	                  LeaveTime* , int , int )
// ����ֵ��NOSPACE, OK
// 

#include "V_Lib.h"
#include "F_Lib.h"

// ��Ʊ�������ݿⲿ��
// Freeze
// ����SUB_TrainInfo����ͷ��㣬���ڳ�ʼ��FirstNum[]ָ�������ڵĽ��
SUB_TrainInfo* TM_RequestSUBTrainHeadNode()
{
	SUB_TrainInfo* q;
	q = (SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));

	if (!q) return NULL; // �޿��ÿռ����

	// ����ͷ�����Ϣ
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

// ����SUB_TrainInfo����ͷ��㣬���ڳ�ʼ��TOP_TrainInfo�µĽ��
// Freeze
SUB_TrainInfo* TM_RequestNodeForTopNode()
{
		// ����SUB_TrainInfo���
		SUB_TrainInfo* q;
		q = (struct SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
		if (!q) return NULL; // �޿��ÿռ����
		// ����StopName���
		StopName* sn;
		sn = (struct StopName*)malloc(sizeof(struct StopName));
		if (!sn) return NULL; // �޿��ÿռ����
		// ����LeaveTime���
		LeaveTime* lt;
		lt = (struct LeaveTime*)malloc(sizeof(struct LeaveTime));
		if (!lt) return NULL; // �޿��÷���ռ�
		// ��ʼ��sn�����Ϣ
		sn->name = "HeadNode";
		sn->next = NULL;
		// ��ʼ��lt�����Ϣ
		lt->name = "HeadNode";
		lt->hour = 0; lt->min = 0; lt->ToNextMin = 0;
		lt->next = NULL;
		// ��ʼ��SUB_TrainInfo�����Ϣ
		q->NodeKind = "H";
		// FirstNumָ���������ͷ���
		for (int i = 0; i < 10; i++)
		{
			q->FirstNum[i] = TM_RequestSUBTrainHeadNode();
			if (!(q->FirstNum[i])) return NULL; // �޿��ÿռ����
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

// ��ʼ��VL_Ti_Lib
// Freeze
Status TM_InitTicket()
{
	int index; // ѭ������

	// ����ռ�洢������Ϣ�ṹ��
	TOP_TrainInfo* p;
	p = (struct TOP_TrainInfo*)malloc(sizeof(struct TOP_TrainInfo));
	if (!p) return NOSPACE; // �޿��ÿռ����

	// �����ʼ��VL_Ti_Lib�µĽ��
	for (index = 0; index < 11; index++)
	{
		// ����SUB_TrainInfo���
		SUB_TrainInfo* q;
		q = TM_RequestNodeForTopNode();
		if (!q) return NOSPACE; // �޿��ÿռ�

		// ��SUB_TrainInfo��㸳ֵ��TOP�е�ָ�����
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

	VL_Ti_Lib = p; // ��ֵ��ʼ��VL_Ti_Lib

	return OK;

} // Status InitTicket()

// ����VL_Ti_Lib�ж�Ӧ���ο�ͷ��ͷָ��
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
	return NULL; // ������ַ��������ڿ���������
}

// ��������Ϣ�������������뵽��Ӧλ��
// Freeze
Status TM_InsertTrainNode(SUB_TrainInfo* NT)
{
	int NewNum = BF_Get_Train_Number(NT->TrainNum); //  NT������ֵ
	SUB_TrainInfo* p; // ����ָ�룬����ָ���Ӧ��������£��뵱ǰ�������ֿ�ͷ��ͬ����С���ν��
	int PNum, NextNum; // ���pָ���㳵����ֵ��p��һ��㳵����ֵ
	int HNum; // ���α�����ֲ������λ
	p = TM_Get_TiLib_HeadPointer(NT->TrainNum); // ָ���Ӧ��������ͷ���

	if (!p) return ERROR; // Ŀ���㲻����

	HNum = (int)*(NT->TrainNum + 1)-48;
	p = p->FirstNum[HNum]; // ָ���Ӧ�������λ��ͷ���

	// Ŀ���㲻���ڣ�����ͷ���󣬽�NT������ͷ���֮��
	if (!p)
	{
		p = TM_Get_TiLib_HeadPointer(NT->TrainNum); // ָ�����ͷ
		p->FirstNum[HNum] = TM_RequestSUBTrainHeadNode();
		if (!(p->FirstNum[HNum])) return NOSPACE; // �޿��ÿռ����

		p->FirstNum[HNum] = NT; // ��NT��ֵ��ָ�������Ӧλ��
		NT->next = NULL;
		return OK;
	}
	
	// Ŀ������ڣ����бȽ�
	while (p)
	{
		// ͷ�����޽��
		if (!(p->next))
		{
			p->next = NT; // NT���뵽ͷ���֮��NT->next�ѳ�ʼ��ΪNULL
			return OK;
		} // if (!(p->next))

		// ͷ�����н��
		else
		{
			while (p->next)
			{
				PNum = BF_Get_Train_Number(p->TrainNum); // ���㵱ǰ���ĳ�������
				NextNum=PNum = BF_Get_Train_Number(p->next->TrainNum); // ����p->next���ĳ�������
				// NT����p, p->next֮��
				if (PNum < NewNum && NewNum < NextNum)
				{
					// NT����p��p->next�м�
					NT->next = p->next;
					p->next = NT;
				} // 
				// pΪβ��㣬NT>p
				else if (NextNum == -1 && NewNum > PNum)
				{
					// NT��Ϊ�µ�β���
					NT->next = NULL;
					p->next = NT;
				}
				// �������㣬p����
				else p = p->next;
			} // while (p)
		} // else
	}
	return OK;
}

// �������ν���������Ϣϵͳ�У������޸ĵ����ݿ⣩
// Freeze
// input�����α�š�ʼ��վ��;��վ���յ�վ��_LeaveTime(��վ�㷢��ʱ�䡢��վ�����е���һվ��ʱ��)����Ա�����Ʊ����
// output��NOSPACE���޿��ÿռ䣬ERROR����Ӧ����ͷ��㲻���ڣ�OK������
Status TM_NewTrain(char* _TrainNum, char* _Start, StopName* _Stop, char* _End,
	LeaveTime* _LeaveTime, int _OccuQuota, int _SurpTick)
{
	SUB_TrainInfo* NT, *p; // NTΪ�½��ָ�룬pΪ����ָ��
	Order* OrNode; // ����ʽ����ͷ���
	WaitOrder* WaOrNode; // �º򲹶���ͷ���
	NT = (SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
	if (!NT) return NOSPACE; // �޿��ÿռ�
	
	// ����𳵴ε�ͷָ�벻����
	if (!(p = TM_Get_TiLib_HeadPointer(_TrainNum)))
	{
		SUB_TrainInfo* q;
		q = TM_RequestNodeForTopNode();
		if (!q) return NOSPACE; // �޿��ÿռ�������Դ���ͷ���

		switch (*_TrainNum) // �½���ͷ��㸳ֵ��VL_Ti_Lib��Ӧ���
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

		p = TM_Get_TiLib_HeadPointer(_TrainNum); // ���¶�λp��ָ��

	} // if (!(p = TM_GetHeadPointer(*_TrainNum)))

	// д�복����Ϣ��NT
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
	
	// ��ʽ����ͷ���
	// ��ʼ����ʽ����ͷ���
	OrNode = (Order*)malloc(sizeof(Order));
	if (!OrNode) return NOSPACE; //�޿��ÿռ�
	OrNode->NodeKind = (char*)malloc(sizeof(char) * 2);
	OrNode->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	OrNode->End = (char*)malloc(sizeof(char) * STRLENGTH);

	// ��ֵ
	OrNode->NodeKind = "H";
	// �����ַ�����ֵΪ��
	OrNode->OrderNum = OrNode->TrainNum = OrNode->phone = OrNode->Start = OrNode->End = '\0';
	OrNode->TicketNum = -1;
	OrNode->next = NULL;

	// �򲹶���ͷ���
	// ��ʼ���򲹶���ͷ���
	WaOrNode = (WaitOrder*)malloc(sizeof(WaitOrder));
	if (!WaOrNode) return NOSPACE; //�޿��ÿռ�
	WaOrNode->NodeKind = (char*)malloc(sizeof(char) * 2);
	WaOrNode->OrderNum = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->phone = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->Start = (char*)malloc(sizeof(char) * STRLENGTH);
	WaOrNode->End = (char*)malloc(sizeof(char) * STRLENGTH);

	// ��ֵ
	WaOrNode->NodeKind = "H";
	// �����ַ�����ֵΪ��
	WaOrNode->OrderNum = WaOrNode->TrainNum = WaOrNode->phone = WaOrNode->Start = WaOrNode->End = '\0';
	WaOrNode->TicketNum = -1;
	// βָ��ָ��ͷ��㣬nextָ��ͷ���
	WaOrNode->rear = WaOrNode;
	WaOrNode->next = WaOrNode;

	// ͷ��㸳ֵ
	NT->TrainOrder = OrNode;
	NT->TrainWaitOrder = WaOrNode;

	NT->next = NULL;

	// ���³��ν����뵽VL_Ti_lib�У������¶�Ӧ�������ͷ������Ϣ
	TM_InsertTrainNode(NT);

	return OK;
}


