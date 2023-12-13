// 本文件用于比较、提取字符等基础函数
// 本文件的函数名以'BF_'开头
//
// Test Status: Freeze
// Code Status: Freeze
//
// 函数与功能对应：
// 
// 提取车次中的数字
// int BF_Get_Train_Number(chat* TrainNum)
// 返回值：对应的数字, -1（传入空值）
//
// 传入10位字符数组，输出字符串
// char* BF_Merge_Char(char in[])
// 
// 传入字符串格式的数字，转换为数字
// int BF_StrToInt(char* inp)
//
// 传入时间，返回分钟总数
// int BF_StrToMin(char* time)
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
	ch = (char*)malloc(sizeof(char) * STRLENGTH);
	if (!ch) return NULL;
	int i;
	for (i = 0; i < 11; i++) *(ch + i) = in[i];
	return ch;
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

