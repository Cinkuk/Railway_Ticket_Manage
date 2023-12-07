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
// return����Ӧͷָ��
//
// �����ֻ��ŷ���VL_Or_Lib�µ��ֻ��Ž��
// PhoneOrder* S_GetPhoneOrder(char*)
// input���绰
// return����Ӧ����Ԫ�ؽ��ָ�루���򴴽�������Ԫ�ؽ�㣩
//

#include "F_Lib.h"
#include "V_Lib.h"
#include <stdlib.h>

// ��ʼ������

// ��ʼ��һ����������ͷ����
TrainIndexNode* S_RequestTINode()
{
	int i; // ��������

	TrainIndexNode* node;
	node = (TrainIndexNode*)mallooc(sizeof(struct TrainIndexNode));
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
		subnode = (TrainIndexNode*)mallooc(sizeof(struct TrainIndexNode));
		
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
TrainIndexNode* S_GetTIHeadPointer(char* First)
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

// ��������Ϣ������������μ���ϵͳ��
// input�����α�ţ�վ��
Status S_AddTrainToSearchDB(char* _TrainNum, StopName* _StopName)
{
	
}

// ���ݳ��α�ŷ���VL_Ti_Lib�µĳ��ν��
// output����Ӧͷָ��
SUB_TrainInfo* S_GetTrainNode(char* _TrainNum)
{

}

// �����ֻ��ŷ���VL_Or_Lib�µ��ֻ��Ž��
// output����Ӧ����Ԫ�ؽ��ָ�루���򴴽�������Ԫ�ؽ�㣩
PhoneOrder* S_GetPhoneOrder(char* _phone)
{

}
