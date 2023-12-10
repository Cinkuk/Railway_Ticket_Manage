// ���ļ����ڶ��ļ����ж�д����
// ���ļ��ĺ�������'FO_'��ͷ
//
// Test Status: Undo
// Code Status: Undo
//
// �����빦�ܶ�Ӧ��
// 
// // ����
// Status SaveToHD()
// input: None
// return: OK, NOSPACE, ERROR���ļ��޷��򿪡���ռ�ã�
// 
// // �Ӵ��̶�ȡ
// Status LoadFromHD()
// input: None
// return: OK, ERROR(�޴��ļ�),EMPTY(���̿ռ䲻��) 
// 
// 
// 
// 
// 
//  

#include "F_Lib.h"
#include "V_Lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �Ӵ��̶�ȡ
Status LoadFromHD()
{
	FILE* fp;
	char* filename = "TrainIN.txt";
	fp = fopen("TrainIN.txt", "r");

	int BlockBegin = 0; // 0������֮������ݣ�1����¼֮�������
	int coloum_index = 0; // �к�
	int row_index = 0; // �к�
	
	// �ļ���ʧ��
	if (fp == NULL)
	{
		return ERROR;
	}

	// ��ȡÿ�е��ַ�
	char line[LINELENGTH];
	char* token;

	// ���������洢ÿ��ȡһ��������Ϣ����Ҫ�Ĵ洢�ռ�
	ReadTrain* ReadBlock, *p, *q;
	ReadBlock = (ReadTrain*)malloc(sizeof(ReadTrain));
	if (!ReadBlock) return ERROR; // �޿��ÿռ�
	ReadBlock->NextLine = NULL;

	// ���л�ȡ����
	while (fgets(line, LINELENGTH, fp) != NULL)
	{
		// ÿ�ж�ȡ��������Ĵ洢�ռ�
		// �ṹ��
		ReadTrain* ReadLine;
		ReadLine = (ReadTrain*)malloc(sizeof(ReadTrain));
		if (!ReadLine) return ERROR; // �޿��ÿռ�
		// �ַ���
		char* l1 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l2 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l3 = (char*)malloc(sizeof(char) * STRLENGTH);
		ReadLine->c1 = l1;
		ReadLine->c2 = l2;
		ReadLine->c3 = l3;

		// ��ȡ���ŷָ��ĵ�һ���ַ���
		token = strtok(line, ",");
		// �ж��Ƿ���Ҫ�����к�
		if (BlockBegin == 1) row_index++;

		// �����зǿ�
		while (token != NULL)
		{
			// �к�����
			coloum_index++;

			// �ж�token��ȡ���ַ���λ��
			// ��Ϣ�鿪ʼ
			if (strcmp(token, "BOT") == 0) BlockBegin = 1;
			
			// ��Ϣ�����
			else if (strcmp(token, "EOT") == 0) BlockBegin = 0;

			// ���ж�ȡ�ַ�
			if (!(strcmp(token, "\n") == 0)) // ���ǻ��з�
			{
				switch (coloum_index)
				{
				case 1: {strcpy(l1, token); break; }
				case 2: {strcpy(l2, token); break; }
				case 3: {strcpy(l3, token); break; }
				} // switch (coloum_index)
			} // if (!(strcmp(token, "\n") == 0))

			// ��ȡ��һ���ɿո�ָ����ַ���
			token = strtok(NULL, ",");
		
		} // while (token != NULL)

		// �������ݷָ���ȡ�꣬�����к�
		row_index = 0;

		// ��ȡ�걾����Ϣ��д��ṹ�壬׼����ʼ��ȡ��һ��
		p = ReadBlock;
		// pָ��ReadBlockβ���
		while (p)
		{
			// ReadLine���뵽β���֮��
			if (!(p->NextLine))
			{
				ReadLine->NextLine = NULL;
				p->NextLine = ReadLine;
				break;
			}
			p = p->NextLine;
		}

		// �ж��Ƿ�Ϊһ��������Ϣ��ȡ���
		// 1. BlockBegin=0, 2.ReadBlock���ٶ�ȡ�����е���Ϣ
		if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)
		{
			// �����³�����Ҫ�Ŀռ����

			
			// �ռ������ֵ

			
			// ��������
			

			// ���ReadBlock������ReadBlock��Nextָ��ΪNULL
			p = ReadBlock->NextLine; // pָ����Ԫ���
			while (p)
			{
				q = p; // qָ�����ͷŵĽ��
				p = p->NextLine; // p����
				free(q); // �ͷ�q
			} // while (p)
			ReadBlock->NextLine = NULL;

		} // if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)

	} // while (fgets(line, LINELENGTH, fp) != NULL)

	fclose(fp);
	return OK;
}



// ����
Status SaveToHD()
{

}
