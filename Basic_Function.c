// 本文件用于比较、提取字符等基础函数
// 本文件的函数名以'BF_'开头
//
// Test Status: Undo
// Code Status: Working
//
// 函数与功能对应：
// 
// 提取车次中的数字
// int BF_Get_Train_Number(chat* TrainNum)
// 返回值：对应的数字, -1（传入空值）
//
//

#include "V_Lib.h"
#include <stdlib.h>

// 提取车次中的数字
int BF_Get_Train_Number(char* TrainNum)
{
	int i = 0; // 循环变量
	int j = 1;
	int sum = 0; // 计算结果
	
	if (!TrainNum) return -1; // 传入值为空

	while (*(TrainNum + i) != '\0') // 计算字符串长度
	{
		i++;
	} // while (*(TrainNum + i) != '\0')

	while (j <= i) // 将编号中的的数字转换为整数
	{
		sum = sum * 10 + *(TrainNum + j);
		j++;
	} // while (j <= i)

	return sum;
}

// 传入10位字符数组，输出字符串
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
// KeyKind: 0:按照出发时间, 1:按照运行时间
int BF_Partition(SearchResult* A, int p, int r, int KeyKind)
{
	SearchResult* ptr; // 工作指针
	SearchResult* ptr_i, *ptr_j, *ptr_r, *temp; // 工作指针

	ptr = A->NextResult;
	int Index=0;

	int x; // pivot Value
	int i; // highest index into the low side

	while (ptr) // p指向第r个元素结点
	{
		Index++;
		if (Index == r) break; // 已指到
		else ptr = ptr->NextResult;
	}

	// 赋值x
	if (KeyKind == 0) // 按照出发时间
		x = (ptr->LeaveTime[0]) * 60 + (ptr->LeaveTime[1]);
	else if (KeyKind == 1) // 按照运行时间
		x = ptr->ToNextMin;
	
	i = p - 1;// 赋值i
	
	// 工作指针定位
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

	// 按照出发时间排序
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

	// 按照运行时间排序
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
