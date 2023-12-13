// 本文件为主函数，用于调用各模块并实现与用户的交互
//
// Test Status: Undo
// Code Status: Undo


#include "V_Lib.h"
#include "F_Lib.h"

void WAIT_main()
{
	while (True)
	{
		// 操作面板行分隔
		printf("%s\n","-------------------------------------------------------------------------------------------------------------------");
		printf("------------------------------------------欢迎使用列车票务系统------------------------------------------\n\n");
		printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n", "1、订票服务", "2、输入订单号查询订单", "3、输入手机号查询订单", "4、退票", "5、退出系统");
		printf("------------------------------------------\n\n");
		
		char command;
		while (True)
		{
			printf("请输入要操作的功能（数字1-5）：");
			scanf("%c", &command);
			getchar();
			if (command >= 49 && command <= 53)
			{
				switch (command)
				{
				case 49: {CheckTrain(); break; }
				case 50: {CheckOrder(); break; }
				case 51: {ChechPhoneOrder(); break; }
				case 52: {WithdrawOrder(); break; }
				case 53: {ExitSys(); break; }
				}
			}
			else printf("请输入正确操作数\n");
		}
	}
}