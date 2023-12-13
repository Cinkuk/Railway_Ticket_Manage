// 本文件为主函数，用于调用各模块并实现与用户的交互
//
// Test Status: Undo
// Code Status: Undo


#include "V_Lib.h"
#include "F_Lib.h"

void main()
{
	S_InitSIDB();
	S_InitTIDB();
	TM_InitTicket();
	OM_InitOrder();
	OM_InitOrderID();
	FO_LoadTrainFromHD();

	while (True)
	{
		
		char command;
		while (True)
		{
			system("cls");
			printf("\n\n------------------------------------------欢迎使用列车票务系统------------------------------------------\n\n");
			printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n", "1、订票服务", "2、输入订单号查询订单", "3、输入手机号查询订单", "4、退票", "5、退出系统");
			printf("------------------------------------------\n\n");
			while (True)
			{
				printf("\t请输入要操作的功能（数字1-5）：");
				scanf("%c", &command);
				getchar();
				if (command >= 49 && command <= 53)
				{
					switch (command)
					{
					case 49: {DP_CheckTrain(); break; }
					case 50: {DP_CheckOrder(); break; }
					case 51: {DP_CheckPhoneOrder(); break; }
					case 52: {DP_WithdrawOrder(); break; }
					case 53: {DP_ExitSys(); break; }
					}
					break;
				}
				else printf("\t请输入正确操作数\n");
			}
		}
	}
}