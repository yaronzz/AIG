#include "math.h"

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

/// <summary>
/// 功能	 :	开根号
/// 参数	 :	dValue		[in] 值
/// 返回值:  
/// </summary>
double math_Sqrt(double dValue)
{
	if (dValue <= 0)
		return 0;

	double dMin		= 0;
	double dMax		= dValue;
	double dMiddle	= dMax / 2;
	double dTeamp	= dMiddle * dMiddle;

	while (!AIG_MATH_FLOAT_EQUAL(dTeamp, dValue))
	{
		if (dTeamp < dValue)
			dMin = dMiddle;
		else
			dMax = dMiddle;

		dMiddle = (dMin + (dMax - dMin) / 2);
		dTeamp  = dMiddle * dMiddle;
	}

	return dMiddle;
}




/// <summary>
/// 功能	 :	十六进制转十进制
/// 参数	 :	pChar		[in] 值
/// 返回值:  
/// </summary>
int math_HexToDec(char pChar)
{
	if ('0' <= pChar && pChar <= '9')
		return pChar - '0';
	else if ('a' <= pChar && pChar <= 'f')
		return pChar - 'a' + 10;
	else if ('A' <= pChar && pChar <= 'F')
		return pChar - 'A' + 10;
	else
		return -1;
}

/// <summary>
/// 功能	 :	十进制转十六进制
/// 参数	 :	pInt		[in] 值
/// 返回值:  
/// </summary>
char math_DecToHex(short int pInt)
{
	if (0 <= pInt && pInt <= 9)
		return pInt + '0';
	else if (10 <= pInt && pInt <= 15)
		return pInt + 'A' - 10;
	else
		return -1;
}



/// <summary>
/// 功能	 :	获取直线的一般方程
/// 参数	 :	point0		[in] 第一个点的坐标
///			point1		[in] 第二个点的坐标
///			pEquation	[out]直线方程
/// 返回值:  
/// </summary>
int math_GetLinearEquation(AigCoords point0, AigCoords point1, AigEquation* pEquation)
{
	if (pEquation == NULL)
		return eAEC_Input;

	//斜率 k = (y1 - y0)/(x1 - x0)
	//方程 y - y0 = k(x - x0)
	//	  --> y - kx = y0 - kx0
	//	  --> y - x(y1 - y0)/(x1 - x0) = y0 - x0(y1 - y0)/(x1 - x0)
	//	  --> (y0 - y1)x + (x1 - x0)y  = (x1 - x0)y0 - x0(y1 - y0)
	//	  --> A = y0 - y1    B = x1 - x0      C = x0(y1 - y0) - (x1 - x0)y0
	double A = point0.y - point1.y;
	double B = point1.x - point0.x;
	double C = point0.x*(point1.y - point0.y) - point0.y*(point1.x - point0.x);

	pEquation->A = A;
	pEquation->B = B;
	pEquation->C = C;
	return eAEC_Success;
}







/// <summary>
/// 功能	 :	获取两点之间的距离
/// 参数	 :	point0		[in] 第一个点的坐标
///			point1		[in] 第二个点的坐标
/// 返回值:  
/// </summary>
double math_GetTwoPointsDistance(AigCoords point0, AigCoords point1)
{
	if (AIG_MATH_POINT_EQUAL(point0.x, point0.y, point1.x, point1.y))
		return 0;

	return sqrt(pow(point1.x - point0.x, 2) + pow(point1.y - point0.y, 2));
}

/// <summary>
/// 功能	 :	获取点到线的距离
/// 参数	 :	point			[in] 点的坐标
///			line_point0		[in] 第一个线的坐标
///			line_point1		[in] 第二个线的坐标
/// 返回值:  
/// </summary>
double math_GetPointToLineDistance(AigCoords point, AigCoords line_point0, AigCoords line_point1)
{
	if (AIG_MATH_POINT_EQUAL(line_point0.x, line_point0.y, line_point1.x, line_point1.y))
		return math_GetTwoPointsDistance(point, line_point0);

	//Ax+By+C=0
	double A = line_point1.y - line_point0.y;
	double B = line_point0.x - line_point1.x;
	double C = line_point0.y*(line_point1.x - line_point0.x) - line_point0.x*(line_point1.y - line_point0.y);
	//d=|Ax0+By0+C|/√(A²+B²)
	double d = fabs(A*point.x + B*point.y + C) / sqrt(A*A + B*B);

	return d;
}




/// <summary>
/// 功能	 :	获取线与X轴的角度
/// 参数	 :	start_point		[in] 第一个线的坐标
///			end_point		[in] 第二个线的坐标
/// 返回值:  
/// </summary>
double math_GetLineToXAxisAngle(AigCoords start_point, AigCoords end_point)
{
	//360度角 = 2PI弧度  则1弧度 = 180/PI度 
	AigCoords off;
	off.x = end_point.x - start_point.x;
	off.y = end_point.y - start_point.y;

	//atan2取值范围为[-PI,PI],即-180到180
	double dAngle = atan2(off.y, off.x) * 180 / PI;

	//将[-PI,0)的数转为360制
	if (dAngle < 1e-6)
		dAngle += 360;

	return dAngle;
}

/// <summary>
/// 功能	 :	判断点在线的哪一侧
/// 参数	 :	point			[in] 点的坐标
///			start_point		[in] 第一个线的坐标
///			end_point		[in] 第二个线的坐标
/// 返回值:  0显示 1左侧 2右侧 -1错误
/// </summary> 
int math_GetPointSideToLine(AigCoords point, AigCoords start_point, AigCoords end_point)
{
	//	定义：平面上的三点P1(x1, y1), P2(x2, y2), P3(x3, y3)的面积量：
	//	                | x1  x2  x3 |
	//	S(P1, P2, P3) = | y1  y2  y3 | = (x1 - x3)*(y2 - y3) - (y1 - y3)(x2 - x3)
	//	                | 1   1   1 |
	//	当P1P2P3逆时针时S为正的，当P1P2P3顺时针时S为负的。

	//	令矢量的起点为A，终点为B，判断的点为C，
	//	如果S（A，B，C）为正数，则C在矢量AB的左侧；
	//	如果S（A，B，C）为负数，则C在矢量AB的右侧；
	//	如果S（A，B，C）为0，则C在直线AB上。
	if (AIG_MATH_POINT_EQUAL(start_point.x, start_point.y, end_point.x, end_point.y))
		return -1;

	double dArea = (start_point.x - point.x)*(end_point.y - point.y) - (end_point.x - point.x)*(start_point.y - point.y);
	if (dArea > FLOAT_EQUAL_LIMIT)
		return 2;
	else if (dArea < FLOAT_EQUAL_LIMIT)
		return 1;

	return 0;
}

/// <summary>
/// 功能	 :	求点到直线的垂足点
/// 参数	 :	point			[in] 点的坐标
///			start_point		[in] 第一个线的坐标
///			end_point		[in] 第二个线的坐标
///			out_point		[out]垂足
/// 返回值:  
/// </summary> 
int math_GetVerticalPoint(AigCoords point, AigCoords start_point, AigCoords end_point, AigCoords* out_point)
{
	//  点A(x,y),线Ax+By+C =0
	//  垂足点为B(x1,y1)  x1=(B²x - ABy - AC)/(A²+B²)
	//				     y1=(A²y - ABx - BC)/(A²+B²)
	if (out_point == NULL)
		return -1;
	//构不成直线
	if (AIG_MATH_POINT_EQUAL(start_point.x, start_point.y, end_point.x, end_point.y))
		return -1;

	//求直线的二元一次方程 Ax+By+C=0
	AigEquation aLineEquation;
	int Check = math_GetLinearEquation(start_point, end_point, &aLineEquation);

	double x = point.x;
	double y = point.y;
	double A = aLineEquation.A;
	double B = aLineEquation.B;
	double C = aLineEquation.C;
	double dTmp = A*A + B*B;

	out_point->x = (B*B*x - A*B*y - A*C) / (A*A + B*B);
	out_point->y = (A*A*y - A*B*x - B*C) / (A*A + B*B);

	return eAEC_Success;
}





/// <summary>
/// 功能	 :	判断点是否在矩形框内
/// 参数	 :	point			[in] 点的坐标
///			rect			[in] 矩形框
///			isIncBoundary	[in] 是否包括边界(1是-点落在框边界也算在其内,0否)
/// 返回值:  
/// </summary> 
int math_PointInRect(AigCoords point, AigRect rect, int isIncBoundary)
{
	if (isIncBoundary)
	{
		if (point.x >= rect.left && point.x <= rect.right
			&& point.y >= rect.bottom && point.y <= rect.top)
			return 1;
	}
	else
	{
		if (point.x > rect.left && point.x < rect.right
			&& point.y > rect.bottom && point.y < rect.top)
			return 1;
	}
	return 0;

}

/// <summary>
/// 功能	 :	判断矩形框是否相交(包含的情况也当作相交)
/// 参数	 :	rect0			[in] 矩形框
///			rect1			[in] 矩形框
/// 返回值:  
/// </summary> 
int math_IsRectIntersect(AigRect* in_Rect0, AigRect* in_Rect1)
{
	//	矩形框取坐标点，左上角和右下角 A1/2(Left,Top)、B1/2(Right,Bottom)
	//  1、首先求出A1与A2点在X方向较大值与Y方向较大值的交点，记为M点.
	//  2、求出B1与B2在X方向较小值与Y方向较小值的交点，记为N点.
	//  3、如果M点的X坐标和Y坐标值均比N点相应的X坐标和Y坐标值小，亦即M和N可以分别构成一个矩形的左上角点和右上角点，则两矩形相交；其余情况则不相交。
	AigCoords pointM, pointN;
	if (in_Rect0 == NULL || in_Rect1 == NULL)
		return -1;

	pointM.x = in_Rect0->left	> in_Rect1->left	? in_Rect0->left	: in_Rect1->left;
	pointM.y = in_Rect0->top	> in_Rect1->top		? in_Rect0->top		: in_Rect1->top;
	pointN.x = in_Rect0->right	< in_Rect1->right	? in_Rect0->right	: in_Rect1->right;
	pointN.y = in_Rect0->bottom < in_Rect1->bottom	? in_Rect0->bottom	: in_Rect1->bottom;

	if (pointM.x < pointN.x && pointM.y < pointN.y)
		return 1;
	return 0;
}