// 本文件用于对文件进行读写操作
// 本文件的函数名以'FO_'开头
//
// Test Status: Finished
// Code Status: Freeze
//
// 函数与功能对应：
//
// 从磁盘读取车次
// Status FO_LoadTrainFromHD() 
// return: ERROR（文件打开失败）, NOSPACE（没有内存读入文件）, OK
// 

#include "F_Lib.h"
#include "V_Lib.h"

// 从磁盘读取车次
// freeze
Status FO_LoadTrainFromHD()
{
	FILE* fp;
	char* filename = "TrainDB.csv";
	fp = fopen(filename, "r");

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
	if (!ReadBlock) return NOSPACE; // 无可用空间
	ReadBlock->NextLine = NULL;

	// 逐行获取内容
	while (fgets(line, LINELENGTH, fp) != NULL)
	{
		// 每行读取内容所需的存储空间
		// 结构体
		ReadTrain* ReadLine;
		ReadLine = (ReadTrain*)malloc(sizeof(ReadTrain));
		if (!ReadLine) return NOSPACE; // 无可用空间
		// 字符串
		char* l1 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l2 = (char*)malloc(sizeof(char) * STRLENGTH);
		char* l3 = (char*)malloc(sizeof(char) * STRLENGTH);
		ReadLine->c1 = l1;
		ReadLine->c2 = l2;
		ReadLine->c3 = l3;
		ReadLine->NextLine = NULL;

		// 获取逗号分隔的第一个字符串
		token = strtok(line, ",");

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
		coloum_index = 0;

		// 获取完本行信息，写入结构体，准备开始获取下一行
		p = ReadBlock;
		// p指向ReadBlock尾结点
		// 若本行为车次内容，存储
		if (!(strcmp(ReadLine->c1, "BOT") == 0) && !(strcmp(ReadLine->c1, "EOT") == 0))
		{
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
			} // while (p)
		} // if (!(strcmp(ReadLine->c1, "BOT") == 0) && !(strcmp(ReadLine->c1, "EOT")))

		// 判断是否为一个车次信息读取完毕，读取完毕则创建新车次
		// 1. BlockBegin=0, 2.ReadBlock至少读取了两行的信息
		if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)
		{
			// 创建新车次需要的空间变量
			char* _TrainNum = (char*)malloc(sizeof(char) * STRLENGTH);
			char* _Start = (char*)malloc(sizeof(char) * STRLENGTH);
			char* _End = (char*)malloc(sizeof(char) * STRLENGTH);
			int _Occupant;
			int _SurplusTicket;
			StopName* _StopList = (StopName*)malloc(sizeof(StopName));
			StopName* NewS, *ps;
			LeaveTime* _LeaveTime = (LeaveTime*)malloc(sizeof(LeaveTime));
			LeaveTime* NewL, *pl;
			int time = 0;
			// 空间变量赋值
			strcpy(_TrainNum, ReadBlock->NextLine->c1); // _TrainNum
			_Occupant = BF_StrToInt(ReadBlock->NextLine->c2); // _Occupant
			_SurplusTicket = BF_StrToInt(ReadBlock->NextLine->c3); // SurplusTicket
			strcpy(_Start, ReadBlock->NextLine->NextLine->c1); // _Start

			_StopList->next = NULL;
			_LeaveTime->next = NULL;
			// 遍历读取的数据存入对应结构中
			p = ReadBlock->NextLine->NextLine;
			while (p)
			{
				// 新结点
				NewS = (StopName*)malloc(sizeof(StopName));
				NewL = (LeaveTime*)malloc(sizeof(LeaveTime));
				char* NewStopName = (char*)malloc(sizeof(char) * STRLENGTH);
				strcpy(NewStopName, p->c1);
				NewS->name = NewL->name = NewStopName; // BOTH.name
				// 如果为最后一站
				if (!(p->NextLine))
				{
					_End = p->c1;
					NewL->hour = NewL->min = NewL->hour = -1;
				}
				else
				{
					NewL->ToNextMin = BF_StrToInt(p->c3); // LeaveTime.ToNextTime
					time = BF_StrToMin(p->c2);
					NewL->hour = time / 60;
					NewL->min = time % 60;
				}
				NewL->next = NULL;
				NewS->next = NULL;
				
				// NewS插入为尾结点
				ps = _StopList;
				while (ps)
				{
					if (!(ps->next))
					{
						ps->next = NewS;
						break;
					}
					ps = ps->next;
				}
				// NewL插入为尾结点
				pl = _LeaveTime;
				while (pl)
				{
					if (!(pl->next))
					{
						pl->next = NewL;
						break;
					}
					pl = pl->next;
				}
				p = p->NextLine;
			} // while (p)
			// 新增车次
			TM_NewTrain(_TrainNum, _Start, _StopList, _End, _LeaveTime, _Occupant, _SurplusTicket);
			S_AddTrainToSearchDB(_TrainNum, _StopList);

			// 清空ReadBlock，重置ReadBlock的Next指针为NULL
			p = ReadBlock->NextLine; // p指向首元结点
			while (p)
			{
				q = p; // q指向需释放的结点
				p = p->NextLine; // p后移
				free(q); // 释放q
			} // while (p)
			ReadBlock->NextLine = NULL;

			// 释放其他可释放的内存
			free(_TrainNum);
			free(_Start);
			free(_End);

		} // if (BlockBegin == 0 && ReadBlock->NextLine->NextLine)

	} // while (fgets(line, LINELENGTH, fp) != NULL)

	fclose(fp);
	return OK;
}

