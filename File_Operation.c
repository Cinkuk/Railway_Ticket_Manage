// 本文件用于对文件进行读写操作
// 本文件的函数名以'FO_'开头
//
// Test Status: Undo
// Code Status: Undo
//
// 函数与功能对应：
// 
// // 存盘
// Status SaveToHD()
// input: None
// return: OK, NOSPACE, ERROR（文件无法打开、被占用）
// 
// // 从磁盘读取
// Status LoadFromHD()
// input: None
// return: OK, ERROR(无此文件),EMPTY(磁盘空间不足) 
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

// 从磁盘读取
Status LoadFromHD()
{
	FILE* fp;
	char* filename = "TrainIN.txt";
	fp = fopen("TrainIN.txt", "r");

	int BlockBegin = 0; // 0：忽略之后的内容，1：记录之后的内容
	int coloum_index = 0; // 列号
	int row_index = 0; // 行号
	
	// 文件打开失败
	if (fp == NULL)
	{
		return ERROR;
	}

	// 读取每行的字符
	char line[LINELENGTH];
	char* token;

	// 创建变量存储每读取一个车次信息所需要的存储空间
	ReadTrain* ReadBlock, *p, *q;
	ReadBlock = (ReadTrain*)malloc(sizeof(ReadTrain));
	if (!ReadBlock) return ERROR; // 无可用空间
	ReadBlock->NextLine = NULL;

	// 逐行获取内容
	while (fgets(line, LINELENGTH, fp) != NULL)
	{
		// 每行读取内容所需的存储空间
		// 结构体
		ReadTrain* ReadLine;
		ReadLine = (ReadTrain*)malloc(sizeof(ReadTrain));
		if (!ReadLine) return ERROR; // 无可用空间
		// 字符串
		char* l1 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l2 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l3 = (char*)malloc(sizeof(char) * STRLENGTH);
		ReadLine->c1 = l1;
		ReadLine->c2 = l2;
		ReadLine->c3 = l3;

		// 获取逗号分隔的第一个字符串
		token = strtok(line, ",");
		// 判断是否需要自增行号
		if (BlockBegin == 1) row_index++;

		// 若该行非空
		while (token != NULL)
		{
			// 列号自增
			coloum_index++;

			// 判断token读取的字符串位置
			// 信息块开始
			if (strcmp(token, "BOT") == 0) BlockBegin = 1;
			
			// 信息块结束
			else if (strcmp(token, "EOT") == 0) BlockBegin = 0;

			// 逐列读取字符
			if (!(strcmp(token, "\n") == 0)) // 不是换行符
			{
				switch (coloum_index)
				{
				case 1: {strcpy(l1, token); break; }
				case 2: {strcpy(l2, token); break; }
				case 3: {strcpy(l3, token); break; }
				} // switch (coloum_index)
			} // if (!(strcmp(token, "\n") == 0))

			// 获取下一个由空格分隔的字符串
			token = strtok(NULL, ",");
		
		} // while (token != NULL)

		// 本行内容分隔获取完，重置列号
		row_index = 0;

		// 获取完本行信息，写入结构体，准备开始获取下一行
		p = ReadBlock;
		// p指向ReadBlock尾结点
		while (p)
		{
			// ReadLine插入到尾结点之后
			if (!(p->NextLine))
			{
				ReadLine->NextLine = NULL;
				p->NextLine = ReadLine;
				break;
			}
			p = p->NextLine;
		}

		// 判断是否为一个车次信息读取完毕
		// 1. BlockBegin=0, 2.ReadBlock至少读取了两行的信息
		if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)
		{
			// 创建新车次需要的空间变量

			
			// 空间变量赋值

			
			// 新增车次
			

			// 清空ReadBlock，重置ReadBlock的Next指针为NULL
			p = ReadBlock->NextLine; // p指向首元结点
			while (p)
			{
				q = p; // q指向需释放的结点
				p = p->NextLine; // p后移
				free(q); // 释放q
			} // while (p)
			ReadBlock->NextLine = NULL;

		} // if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)

	} // while (fgets(line, LINELENGTH, fp) != NULL)

	fclose(fp);
	return OK;
}



// 存盘
Status SaveToHD()
{

}
