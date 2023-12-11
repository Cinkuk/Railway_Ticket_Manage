// 本文件用于比较、提取字符等基础函数
// 本文件的函数名以'BF_'开头
//
// Test Status: Working
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
#include "F_Lib.h"

// 提取车次中的数字
// freeze
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

	while (j < i) // 将编号中的的数字转换为整数
	{
		sum = sum * 10 + (int)*(TrainNum + j) - 48;
		j++;
	} // while (j <= i)

	return sum;
}

// 传入10位字符数组，输出字符串
// freeze
char* BF_Merge_Char(char in[])
{
	char* ch;
	ch = (char*)malloc(sizeof(char) * 10);
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
	SearchResult* ptr_i, *ptr_j, *ptr_r, *temp1, *temp2, *ptr_2; // 工作指针

	ptr = A->NextResult;
	int Index=0;

	int x; // pivot Value
	int i; // highest index into the low side

	
	i = p - 1;// 赋值i
	
	// 工作指针定位
	ptr = A->NextResult;
	Index = 0;
	while (ptr)
	{
		Index++;

		if (Index == r) ptr_r = ptr;
		else if (Index == p - 1) ptr_i = ptr;
		else if (Index == p) ptr_j = ptr;

		ptr = ptr->NextResult;
	}

	// 赋值x
	if (KeyKind == 0) // 按照出发时间
		x = (ptr_r->LeaveTime[0]) * 60 + (ptr_r->LeaveTime[1]);
	else if (KeyKind == 1) // 按照运行时间
		x = ptr_r->ToNextMin;
	
	ptr = A->NextResult;

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
				if (i == 1) ptr_i = ptr;
				else ptr_i = ptr_i->NextResult;

				// exchange A[j] with A[i]
				if (i != j)
				{
					temp1 = ptr_i; temp2 = ptr_j;
					ptr = A->NextResult;
					ptr_2 = A->NextResult;
					while (ptr) // ptr->next is ptr_i
					{
						if (ptr->NextResult == ptr_i) break;
						ptr = ptr->NextResult;
					}
					while (ptr_2) // ptr_2->next is ptr_j
					{
						if (ptr_2->NextResult == ptr_j) break;
						ptr_2 = ptr_2->NextResult;
					}
					ptr->NextResult = ptr_i->NextResult;
					ptr_2->NextResult = ptr_j->NextResult;
					temp1->NextResult = ptr_2->NextResult; ptr_2->NextResult = temp1;
					temp2->NextResult = ptr->NextResult; ptr->NextResult = temp2;
				}

			

			} // if ((ptr_j->LeaveTime[0] * 60 + ptr_j->LeaveTime[1]) <= x)

			// j point to next, means j++
			// imitate for j = p to r-1
			ptr_j = ptr_j->NextResult;

		} // for (int j = p; j <= r - 1; j++)
		

		// exchange A[r] with A[i+1]
		// ptr_i point to i+1
		if (r != (i + 1))
		{
			ptr_i = ptr_i->NextResult;
			temp1 = ptr_i; temp2 = ptr_r;
			ptr = A->NextResult;
			ptr_2 = A->NextResult;
			while (ptr) // ptr->next is ptr_i
			{
				if (ptr->NextResult == ptr_i) break;
				ptr = ptr->NextResult;
			}
			while (ptr_2) // ptr_2->next is ptr_r
			{
				if (ptr_2->NextResult == ptr_r) break;
				ptr_2 = ptr_2->NextResult;
			}
			ptr->NextResult = ptr_i->NextResult;
			ptr_2->NextResult = ptr_r->NextResult;
			temp1->NextResult = ptr_2->NextResult; ptr_2->NextResult = temp1;
			temp2->NextResult = ptr->NextResult; ptr->NextResult = temp2;
		}

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
				if (i == 1) ptr_i = ptr;
				else ptr_i = ptr_i->NextResult;

				// exchange A[j] with A[i]
				if (i != j)
				{
					temp1 = ptr_i; temp2 = ptr_j;
					ptr = A->NextResult;
					ptr_2 = A->NextResult;
					while (ptr) // ptr->next is ptr_i
					{
						if (ptr->NextResult == ptr_i) break;
						ptr = ptr->NextResult;
					}
					while (ptr_2) // ptr_2->next is ptr_j
					{
						if (ptr_2->NextResult == ptr_j) break;
						ptr_2 = ptr_2->NextResult;
					}
					ptr->NextResult = ptr_i->NextResult;
					ptr_2->NextResult = ptr_j->NextResult;
					temp1->NextResult = ptr_2->NextResult; ptr_2->NextResult = temp1;
					temp2->NextResult = ptr->NextResult; ptr->NextResult = temp2;
				}
											

			} // if ((ptr_j->ToNextMin) <= x)

			// j point to next
			// imitate for j = p to r-1
			ptr_j = ptr_j->NextResult;

		} // for (int j = p; j <= r - 1; j++)
		
		// exchange A[r] with A[i+1]
		// ptr_i point to i+1
		if (r != (i + 1))
		{
			ptr_i = ptr_i->NextResult;
			temp1 = ptr_i; temp2 = ptr_r;
			ptr = A->NextResult;
			ptr_2 = A->NextResult;
			while (ptr) // ptr->next is ptr_i
			{
				if (ptr->NextResult == ptr_i) break;
				ptr = ptr->NextResult;
			}
			while (ptr_2) // ptr_2->next is ptr_r
			{
				if (ptr_2->NextResult == ptr_r) break;
				ptr_2 = ptr_2->NextResult;
			}
			ptr->NextResult = ptr_i->NextResult;
			ptr_2->NextResult = ptr_r->NextResult;
			temp1->NextResult = ptr_2->NextResult; ptr_2->NextResult = temp1;
			temp2->NextResult = ptr->NextResult; ptr->NextResult = temp2;
		}
		return (++i);
	} // 	if (KeyKind == 1)
	
}

// QuickSort
SearchResult* BF_QuickSort(SearchResult* A, int p, int r, int KeyKind)
{
	int q;
	if (p < r)
	{
		q = BF_Partition(A, p, r, KeyKind);
		BF_QuickSort(A, p, q - 1, KeyKind);
		BF_QuickSort(A, q + 1, r, KeyKind);
	}
	return A;

}

// 传入字符串格式的数字，转换为数字
// freeze
int BF_StrToInt(char* inp)
{
	int i = 0;
	int sum = 0; // 结果
	// 字符串未遍历完
	while (*(inp + i) != '\0')
	{
		sum = sum * 10 + (int)*(inp + i++) - 48;
	}
	return sum;
}

// 传入时间，返回分钟总数
// freeze
int BF_StrToMin(char* time)
{
	int i = 0;
	int sum_h = 0;
	int sum_m = 0;
	int hour_flag = 0; // 0: hour, 1:min
	while (*(time + i) != '\0')
	{
		if (48 <= *(time + i) && *(time + i) <= 57) // time为数字
		{
			if (hour_flag == 0) sum_h = sum_h * 10 + (int)*(time + i) - 48;
			else if (hour_flag == 1) sum_m = sum_m * 10 + (int)*(time + i) - 48;
			i++;
		}
		else // time为分隔符号
		{
			hour_flag = 1;
			i++;
		}
	}
	return sum_h * 60 + sum_m;
}
