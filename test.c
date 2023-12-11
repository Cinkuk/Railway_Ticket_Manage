#include "V_Lib.h"
#include "F_Lib.h"

static void TrainInfoTraverse();
static void DisplayTrainInfoNode(SUB_TrainInfo*);
static void DisplaySearchResult(SearchResult*);
void main()
{	

	TM_InitTicket();
	OM_InitOrder();
	OM_InitOrderID();

#if 0
	// TEST BF_Merge_Char
	char a[10] = { 'A','5','6','0','0','0','0','5','9'};
	char b[10] = { 'A','5','6','0','0','0','0','5','9','0'};
	printf("%s\n", BF_Merge_Char(a));
	printf("%s\n", BF_Merge_Char(b));
#endif

#if 0
	// TEST BF_Get_Train_Num
	char* a = "D7523";
	char* b = "K12";
	printf("%d\n", BF_Get_Train_Number(a));
	printf("%d\n", BF_Get_Train_Number(b));
#endif

#if 0
	// TEST OM_CreateOrderNum
	printf("%s", OM_CreateOrderNum());
#endif

#if 0
	// TEST BE_StrToInt
	char* a = "1253";
	char* b = "01258";
	char* c = "0";
	char* d = "10";
	printf("%d\n", BF_StrToInt(a));
	printf("%d\n", BF_StrToInt(b));
	printf("%d\n", BF_StrToInt(c));
	printf("%d\n", BF_StrToInt(d));
#endif

#if 0
	// TEST BF_StrToMin
	char* a = "00:00";
	char* b = "15:47"; // 947
	char* c = "09:52"; // 592
	char* d = "22.16"; // 1336
	printf("%d\n", BF_StrToMin(a));
	printf("%d\n", BF_StrToMin(b));
	printf("%d\n", BF_StrToMin(c));
	printf("%d\n", BF_StrToMin(d));
#endif


	S_InitSIDB();
	S_InitTIDB();
	FO_LoadTrainFromHD();

#if 0
	TrainInfoTraverse();
#endif


	SearchResult* SR, *p;
	SR=UF_SearchStop("上海虹桥", "无锡东");
	p = UF_RunTimeSort(SR);
	//p = UF_LeaveTimeSort(SR);
	DisplaySearchResult(p);


#if 0
	OM_New_F_Order("13712345678", "D3802", "云浮东", "普者黑", 8);
	OM_New_F_Order("13712345678", "D3802", "广州南", "大理", 500);
	printf("%d", OM_New_F_Order("13712345649", "D3802", "广州南", "大理", 500));
	OM_New_W_Order("13712345680", "D3802", "广州南", "昆明", 1);
	OM_New_W_Order("13712345681", "D3802", "佛山西", "昆明南", 1);
#endif

#if 0
	OM_InitOrderID();
	printf("NO.1: %s\n", OM_CreateOrderNum());
	printf("NO.2: %s\n", OM_CreateOrderNum());
	printf("NO.3: %s\n", OM_CreateOrderNum());
	printf("NO.4: %s\n", OM_CreateOrderNum());
	printf("NO.5: %s\n", OM_CreateOrderNum());
	printf("NO.6: %s\n", OM_CreateOrderNum());
	printf("NO.7: %s\n", OM_CreateOrderNum());
	printf("NO.8: %s\n", OM_CreateOrderNum());
	printf("NO.9: %s\n", OM_CreateOrderNum());
	printf("NO.10: %s\n", OM_CreateOrderNum());
	printf("NO.11: %s\n", OM_CreateOrderNum());
	printf("\n");
#endif
	
#if 0
	OM_InitOrderID();
	int i = 1;
	int j = 0;
	char* s = (char*)malloc(sizeof(char) * 15);
	while (True)
	{
		s = OM_CreateOrderNum();
		printf("NO.%015d:\t%s\n", i++, s);
		if (strcmp(s, "Z999999999")==0)
		{
			s = OM_CreateOrderNum();
			printf("NO.%035d:\t%s\n", i++, s);
			s = OM_CreateOrderNum();
			printf("NO.%015d:\t%s\n", i++, s);
			s = OM_CreateOrderNum();
			printf("NO.%015d:\t%s\n", i++, s);
			s = OM_CreateOrderNum();
			printf("NO.%015d:\t%s\n", i++, s);
			return;
		}
	}
#endif	
}

void TrainInfoTraverse()
{
	TOP_TrainInfo* p;
	p = VL_Ti_Lib;
	int i = 0;
	while (i < 11)
	{
		switch (i)
		{
		case 0: {printf("\nNO.G Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->G); break; }
		case 1: {printf("\nNO.D Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->D); break; }
		case 2: {printf("\nNO.C Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->C); break; }
		case 3: {printf("\nNO.Z Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->Z); break; }
		case 4: {printf("\nNO.T Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->T); break; }
		case 5: {printf("\nNO.K Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->K); break; }
		case 6: {printf("\nNO.Y Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->Y); break; }
		case 7: {printf("\nNO.L Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->L); break; }
		case 8: {printf("\nNO.S Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->S); break; }
		case 9: {printf("\nNO.N Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->N); break; }
		case 10: {printf("\nNO.P Train Infomation belowing:\n\n"); DisplayTrainInfoNode(p->P); break; }
		}
		i++;
	}
}

static void DisplayTrainInfoNode(SUB_TrainInfo* TN)
{
	StopName* SN, *p;
	LeaveTime* LT;
	int i = 1;
	p = TN;
	
	while (i<10)
	{
		TN = TN->FirstNum[i]->next; 
		while (TN)
		{
			SN = TN->Stop->next;
			LT = TN->StationLeaveTime->next;
			
			printf("\n车次：%s\n", TN->TrainNum);
			printf("始发站：%s\n", TN->Start);
			printf("终到站：%s\n", TN->End);
			printf("乘员定额：%d\n", TN->OccupantQuota);
			printf("余票数量：%d\n\n", TN->SurplusTicket);

			printf("途径站点如下：\n");
			while (SN)
			{
				printf("%-10s\t", SN->name);
				SN = SN->next;
			}
			printf("\n\n各站点\t发车时间\t区间运行时长\n");
			while (LT)
			{
				printf("%-10s\t%02d:%02d\t%d\n", LT->name, LT->hour, LT->min, LT->ToNextMin);
				LT = LT->next;
			}
			TN = TN->next;
			printf("\n---------------------------------------------------------------------------------------------\n");
		}
		i++;
		TN = p;
	}

}

void DisplaySearchResult(SearchResult* SR)
{
	SearchResult* p = SR->NextResult;
	printf("查询到从%s到%s的班次如下：\n\n", p->Leave, p->Arrive);
	printf("\t%-10s\t|\t%-15s\t|\t%-15s\t|\t%s\n", "班次", "出发时间", "到达时间", "余票"); // 运行时间
	while (p)
	{
		printf("\t%-10s\t|\t%02d:%02d\t|\t%02d:%02d\t|\t%d\n", p->TrainNum, p->LeaveTime[0], p->LeaveTime[1], (p->LeaveTime[0] * 60 + p->LeaveTime[1] + p->ToNextMin) / 60, (p->LeaveTime[0] * 60 + p->LeaveTime[1] + p->ToNextMin) % 60, p->TrainNode->SurplusTicket);
		p = p->NextResult;
	}
}
