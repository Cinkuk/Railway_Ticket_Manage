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

# include "V_Lib.h"

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
	int i;
	for (i = 0; i < 10; i++) *(ch + i) = in[i];
	return ch;
}


