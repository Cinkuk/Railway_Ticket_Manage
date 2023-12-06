// ���ļ����ڴ�ų�Ʊ�����ι���ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'TM_'��ͷ
//
// Test Status: Undo
// Code Status: Working
//
// �����빦�ܶ�Ӧ��
// 
// ��ʼ��VL_Ti_Lib
// Status InitTicket()
// ����ֵ��OK, NOSPACE
// 
// ����VL_Ti_Lib�ж�Ӧ���ο�ͷ��ͷָ��
// SUB_TrainInfo * GetHeadPointer(char)
// ����ֵ����Ӧ���ε�SUB_TrainInfoָ��
// 
// ��������
// Status NewTrain()
// ����ֵ��NOSPACE, OK
// 
//

#include "V_Lib.h"
#include <stdlib.h>

// ��ʼ��VL_Ti_Lib
Status TM_InitTicket()
{
	// ���ܵ��쳣��
	// p q sn lt�޿��ÿռ����

	int index; // ѭ������

	// ����ռ�洢������Ϣ�ṹ��
	TOP_TrainInfo* p;
	p = (struct TOP_TrainInfo*)malloc(sizeof(struct TOP_TrainInfo));
	if (!p) return NOSPACE; // �޿��ÿռ����
	VL_Ti_Lib = p; // ��ֵ��ʼ��VL_Ti_Lib

	// �����ʼ��VL_Ti_Lib�µĽ��
	for (index = 0; index < 11; index++)
	{
		// ����SUB_TrainInfo���
		SUB_TrainInfo* q;
		q = (struct SUB_TrainInfo*)malloc(sizeof(struct SUB_TrainInfo));
		if (!q) return NOSPACE; // �޿��ÿռ����
		// ����StopName���
		StopName* sn;
		sn = (struct StopName*)malloc(sizeof(struct StopName));
		if (!sn) return NOSPACE; // �޿��ÿռ����
		// ����LeaveTime���
		LeaveTime* lt;
		lt = (struct LeaveTime*)malloc(sizeof(struct LeaveTime));
		if (!lt) return NOSPACE; // �޿��÷���ռ�
		// ��ʼ��sn�����Ϣ
		sn->name = "HeadNode";
		sn->next = NULL;
		// ��ʼ��lt�����Ϣ
		lt->name = "HeadNode";
		lt->hour = 0; lt->min = 0; lt->ToNextMin = 0;
		lt->next = NULL;
		// ��ʼ��SUB_TrainInfo�����Ϣ
		q->NodeKind = "H";
		// FirstNumָ�������ÿ�
		for (int i = 0; i < 10; i++) q->FirstNum[i] = NULL;

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
	return OK;

} // Status InitTicket()

//����VL_Ti_Lib�ж�Ӧ���ο�ͷ��ͷָ��
SUB_TrainInfo* TM_GetHeadPointer(char FirstC)
{
	switch (FirstC)
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
}

// ��������
Status NewTrain()
{

}

