#include "MathHelper.h"

/// <summary>
/// 功能	 :	查看是否为大端模式
/// 返回值: 
/// </summary>
int math_IsBigEndian()
{
	//	大端BigEndian：   认为第一个字节是最高位字节（按照从低地址到高地址的顺序存放数据的高位字节到低位字节）
	//	小端LittleEndian：它认为第一个字节是最低位字节（按照从低地址到高地址的顺序存放数据的低位字节到高位字节）
	//  x86 系列CPU 都是littleEndian 的字节序，PowerPC 通常是BigEndian，还有的CPU 能通过跳线来设置CPU 工作于Little endian 还是Big endian 模式。
	//  判断方法：设置一个int型为1，取第一个字节，如果是1则为小端
	unsigned int iNum = 0xff;
	unsigned char* pTmp = (unsigned char*)&iNum;
	if (*pTmp == 0xff)
		return AIG_FALSE;

	return AIG_TRUE;
}

/// <summary>
/// 功能	 :	获取四字节对齐的长度
/// 参数	 :	iSize			[in] 原始长度
/// 返回值: 
/// </summary>
int math_Get4ByteAlignSize(int iSize)
{
	//	四字节对齐的必要条件是：		1、只能补齐不能减少，比如未对齐之前的长度为1，对齐后只能是4而不是0
	//							2、判断字节对齐的条件是对4求余，如果为0就是对齐
	//	((in_Size + 3) >> 2) << 2 ：加三之后，保证只能被补齐而不会减少。右移除于4，余数后面的都没了；再左移乘于4，则对齐
	return iSize < 0 ? 0 : ((iSize + 3) >> 2) << 2;  //或者(in_Size + 3 & ~3)
}

/// <summary>
/// 功能	 :	将1米转换为其他单位
/// 参数	 :	eUnit		[in] 单位
/// 返回值: 
/// </summary>
double math_MetersToUnits(enumAigLenghtUnit eUnit)
{
	switch (eUnit)
	{
	case eALUnit_km:		//千米
		return 0.001;
	case eALUnit_m:			//米
		return 1;
	case eALUnit_dm:		//分米
		return 10;
	case eALUnit_cm:		//厘米
		return 100;
	case eALUnit_mm:		//毫米
		return 1000;
	case eALUnit_um:		//微米
		return 1000 * 1000;
	case eALUnit_nm:		//纳米
		return 1000 * 1000 * 1000;

	case eALUnit_mi:		//英里
		return 0.0006214;
	case eALUnit_ft:		//英尺
		return 3.2808399;
	case eALUnit_in:		//英寸
		return 39.3700787;

	case eALUnit_nmi:		//海里
		return 0.00054;
	case eALUnit_yd:		//码
		return 1.0936133;

	case eALUnit_L:			//里
		return 0.002;
	case eALUnit_Z:			//丈
		return 0.3;
	case eALUnit_CHI:		//尺
		return 3;
	case eALUnit_CUN:		//寸
		return 30;
	case eALUnit_FEN:		//分
		return 300;
	case eALUnit_LI:		//厘
		return 3000;
	case eALUnit_HAO:		//毫
		return 30000;
	}
	return 0;
}