// 本文件用于比较、提取字符等基础函数
// 本文件的函数名以'BF_'开头
//
// Test Status: Undo
// Code Status: Working
//
// 函数与功能对应：
// 
// 提取车次中的数字
// int BF_Get_Train_Number(chat* TrainNum)
// 返回值：对应的数字, -1（传入空值）
//
//

// 提取车次中的数字
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

	while (j <= i) // 将编号中的的数字转换为整数
	{
		sum = sum * 10 + *(TrainNum + j);
		j++;
	} // while (j <= i)

	return sum;
}


