// ���ļ����ڱȽϡ���ȡ�ַ��Ȼ�������
// ���ļ��ĺ�������'BF_'��ͷ
//
// Test Status: Undo
// Code Status: Working
//
// �����빦�ܶ�Ӧ��
// 
// ��ȡ�����е�����
// int BF_Get_Train_Number(chat* TrainNum)
// ����ֵ����Ӧ������, -1�������ֵ��
//
//

#include "V_Lib.h"
#include <stdlib.h>

// ��ȡ�����е�����
int BF_Get_Train_Number(char* TrainNum)
{
	int i = 0; // ѭ������
	int j = 1;
	int sum = 0; // ������
	
	if (!TrainNum) return -1; // ����ֵΪ��

	while (*(TrainNum + i) != '\0') // �����ַ�������
	{
		i++;
	} // while (*(TrainNum + i) != '\0')

	while (j <= i) // ������еĵ�����ת��Ϊ����
	{
		sum = sum * 10 + *(TrainNum + j);
		j++;
	} // while (j <= i)

	return sum;
}

// ����10λ�ַ����飬����ַ���
char* BF_Merge_Char(char in[])
{
	char* ch;
	ch = (char*)malloc(sizeof(char) * STRLENGTH);
	if (!ch) return NULL;
	int i;
	for (i = 0; i < 10; i++) *(ch + i) = in[i];
	return ch;
}

// Partition for QuickSort
// KeyKind: 0:���ճ���ʱ��, 1:��������ʱ��
int BF_Partition(SearchResult* A, int p, int r, int KeyKind)
{
	SearchResult* ptr; // ����ָ��
	SearchResult* ptr_i, *ptr_j, *ptr_r, *temp; // ����ָ��

	ptr = A->NextResult;
	int Index=0;

	int x; // pivot Value
	int i; // highest index into the low side

	while (ptr) // pָ���r��Ԫ�ؽ��
	{
		Index++;
		if (Index == r) break; // ��ָ��
		else ptr = ptr->NextResult;
	}

	// ��ֵx
	if (KeyKind == 0) // ���ճ���ʱ��
		x = (ptr->LeaveTime[0]) * 60 + (ptr->LeaveTime[1]);
	else if (KeyKind == 1) // ��������ʱ��
		x = ptr->ToNextMin;
	
	i = p - 1;// ��ֵi
	
	// ����ָ�붨λ
	ptr = A->NextResult;
	Index = 0;
	while (ptr)
	{
		Index++;

		if (Index == r) ptr_r = ptr;
		else if (Index == p - 1) ptr_i = ptr;
		else if (Index = p) ptr_j = ptr;

		else ptr = ptr->NextResult;
	}

	// ���ճ���ʱ������
	if (KeyKind == 0)
	{
		for (int j = p; j <= r - 1; j++)
		{
			// if A[j] <= x
			if ((ptr_j->LeaveTime[0] * 60 + ptr_j->LeaveTime[1]) <= x)
			{	
				// i++
				i++;
				ptr_i = ptr_i->NextResult;
				// exchange A[j] with A[i]
				temp = ptr_j;
				ptr_j - ptr_i;
				ptr_i = temp;
			

			} // if ((ptr_j->LeaveTime[0] * 60 + ptr_j->LeaveTime[1]) <= x)

			// j point to next
			// imitate for j = p to r-1
			ptr_j = ptr_j->NextResult;

		} // for (int j = p; j <= r - 1; j++)
		
		// exchange A[i+1] with A[r]

		// ptr_i point to i+1
		ptr_i = ptr_i->NextResult;
		// exchange 
		temp = ptr_j;
		ptr_j - ptr_i;
		ptr_i = temp;
		
		return (++i);
	} // 	if (KeyKind == 0)

	// ��������ʱ������
	else if (KeyKind == 1)
	{
		for (int j = p; j <= r - 1; j++)
		{
			// if A[j] <= x
			if ((ptr_j->ToNextMin) <= x)
			{	
				// i++
				i++;
				ptr_i = ptr_i->NextResult;
				// exchange A[j] with A[i]
				temp = ptr_j;
				ptr_j - ptr_i;
				ptr_i = temp;
			

			} // if ((ptr_j->LeaveTime[0] * 60 + ptr_j->LeaveTime[1]) <= x)

			// j point to next
			// imitate for j = p to r-1
			ptr_j = ptr_j->NextResult;

		} // for (int j = p; j <= r - 1; j++)
		
		// exchange A[i+1] with A[r]

		// ptr_i point to i+1
		ptr_i = ptr_i->NextResult;
		// exchange 
		temp = ptr_j;
		ptr_j - ptr_i;
		ptr_i = temp;
		
		return (++i);
	} // 	if (KeyKind == 1)
	
}

// QuickSort
void BF_QuickSort(SearchResult* A, int p, int r, int KeyKind)
{
	int q;
	if (p < r)
	{
		q = BF_Partition(A, p, r, KeyKind);
		BF_QuickSort(A, p, q - 1, KeyKind);
		BF_QuickSort(A, q + 1, r, KeyKind);
	}
}
