// ���ļ����ڱȽϡ���ȡ�ַ��Ȼ�������
// ���ļ��ĺ�������'BF_'��ͷ
//
// Test Status: Freeze
// Code Status: Freeze
//
// �����빦�ܶ�Ӧ��
// 
// ��ȡ�����е�����
// int BF_Get_Train_Number(chat* TrainNum)
// ����ֵ����Ӧ������, -1�������ֵ��
//
// ����10λ�ַ����飬����ַ���
// char* BF_Merge_Char(char in[])
// 
// �����ַ�����ʽ�����֣�ת��Ϊ����
// int BF_StrToInt(char* inp)
//
// ����ʱ�䣬���ط�������
// int BF_StrToMin(char* time)
//

#include "V_Lib.h"
#include "F_Lib.h"

// ��ȡ�����е�����
// freeze
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

	while (j < i) // ������еĵ�����ת��Ϊ����
	{
		sum = sum * 10 + (int)*(TrainNum + j) - 48;
		j++;
	} // while (j <= i)

	return sum;
}

// ����10λ�ַ����飬����ַ���
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

// �����ַ�����ʽ�����֣�ת��Ϊ����
// freeze
int BF_StrToInt(char* inp)
{
	int i = 0;
	int sum = 0; // ���
	// �ַ���δ������
	while (*(inp + i) != '\0')
	{
		sum = sum * 10 + (int)*(inp + i++) - 48;
	}
	return sum;
}

// ����ʱ�䣬���ط�������
// freeze
int BF_StrToMin(char* time)
{
	int i = 0;
	int sum_h = 0;
	int sum_m = 0;
	int hour_flag = 0; // 0: hour, 1:min
	while (*(time + i) != '\0')
	{
		if (48 <= *(time + i) && *(time + i) <= 57) // timeΪ����
		{
			if (hour_flag == 0) sum_h = sum_h * 10 + (int)*(time + i) - 48;
			else if (hour_flag == 1) sum_m = sum_m * 10 + (int)*(time + i) - 48;
			i++;
		}
		else // timeΪ�ָ�����
		{
			hour_flag = 1;
			i++;
		}
	}
	return sum_h * 60 + sum_m;
}

