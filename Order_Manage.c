// ���ļ����ڴ�Ŷ�������ĺ���
// �������Ĺؼ����������Variables_Lib.c��
// ���ļ��ĺ�������'OM_'��ͷ
//
// Test Status: Undo
// Code Status: Working
//
// �����빦�ܶ�Ӧ:
// 
// ��ʼ��VL_Or_Lib
// OM_InitOrder()����ʼ��VL_Or_Lib
// ����ֵ��NOSPACE, OK
// 
//


#include "V_Lib.h"
#include <stdlib.h>
#include "F_Lib.h"

// ��ʼ��VL_Or_Lib
Status OM_InitOrder()
{
	// ����PhoneOrder���
	PhoneOrder* p;
	p = (struct PhoneOrder*)malloc(sizeof(struct PhoneOrder));
	if (!p) return NOSPACE; // �޿��ÿռ�
	VL_Or_Lib = p; // ����ɹ����ڴ��ַ��ֵ��VL_Or_Lib
	// ��ʼ������ֵ
	p->NodeKind = "H";
	p->phone = -1;
	p->OrderList = NULL;
	p->next = NULL;
	return OK; 
}



