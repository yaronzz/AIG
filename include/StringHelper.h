#if !defined __AIG_STRING_H__
#define __AIG_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"

#define AIG_STRING_EMPTY "\t \n"	//�մ���ʶ TAB\�ո�\����


/// <summary>
/// ����	 :	ȥ���ַ�������ߵ��ַ�
/// ����	 :	in_out_pStr		�ַ������������
///			remove_Chr		��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_LeftTrim(char* in_out_pStr, char* remove_Chr);

/// <summary>
/// ����	 :	ȥ���ַ������ұߵ��ַ�
/// ����	 :	in_out_pStr		�ַ������������
///			remove_Chr		��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_RightTrim(char* in_out_pStr, char* remove_Chr);

/// <summary>
/// ����	 :	ȥ���ַ��������ұߵ��ַ�
/// ����	 :	in_out_pStr		�ַ������������
///			remove_Chr		��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_Trim(char* in_out_pStr, char* remove_Chr);




/// <summary>
/// ����	 :	�����ַ������ַ�������
/// ����	 :	in_pStr			�ַ���
///			in_Chr			��Ӧ�ַ�
/// ����ֵ:
/// </summary>
int string_CountChr(char* in_pStr, char in_Chr);

/// <summary>
/// ����	 :	�����ַ������Ӵ�������
/// ����	 :	in_pStr			�ַ���
///			in_Src			��Ӧ�Ӵ�
/// ����ֵ:
/// </summary>
int string_CountStr(char* in_pStr, char* in_Src);




/// <summary>
/// ����	 :	�����ַ����е�һ��ƥ���ַ����±�
/// ����	 :	in_pStr			�ַ���
///			in_Chr			��Ӧ�ַ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_FindChr(char* in_pStr, char in_Chr);

/// <summary>
/// ����	 :	�����ַ����е�һ��ƥ���Ӵ����±�
/// ����	 :	in_pStr			�ַ���
///			in_Src			��Ӧ�Ӵ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_FindStr(char* in_pStr, char* in_Src);

/// <summary>
/// ����	 :	�����ַ����д�iFromIndex��ʼ��ƥ���Ӵ����±�
/// ����	 :	in_pStr			�ַ���
///			iFromIndex		��ʼ�±�
///			in_Src			��Ӧ�Ӵ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_FindStrFrom(char* in_pStr, int iFromIndex, char* in_Src);




/// <summary>
/// ����	 :	�ַ����ַ��滻
/// ����	 :	in_pStr			�ַ���
///			in_Src			Դ
///			in_Desc			�滻���ַ�
/// ����ֵ:  
/// </summary>
int string_ReplaceChr(char *in_out_pStr, char in_Src, char in_Desc);

/// <summary>
/// ����	 :	�ַ����Ӵ��滻
/// ����	 :	in_pStr			�ַ���
///			in_Src			Դ
///			in_Desc			�滻���ַ�
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_ReplaceStr(char *in_pStr, char* in_Src, char* in_Desc, char* out_pResult, int in_ResultLen);




/// <summary>
/// ����	 :	�Ƴ��Ӵ�
/// ����	 :	in_out_pStr		�ַ���
///			in_Src			�Ӵ�
/// ����ֵ:  >= 0 ����
/// </summary>
int string_Remove(char *in_out_pStr, char* in_Src);

/// <summary>
/// ����	 :	�����ַ���
/// ����	 :	in_pStr			�ַ���
///			in_iIndex		�����±�
///			in_Src			�����Ӵ�
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_Insert(char* in_pStr, int in_iIndex, char* in_Src, char* out_pResult, int in_ResultLen);

/// <summary>
/// ����	 :	�ַ������
/// ����	 :	in_out_pResult	����ַ���
/// ����ֵ: 
/// </summary>
int string_Strcat(char* in_out_pResult, ...);

/// <summary>
/// ����	 :	�ߵ��ַ���˳��
/// ����	 :	in_out_pResult	����ַ���
/// ����ֵ: 
/// </summary>
int string_MakeReverse(char* in_out_pStr);

/// <summary>
/// ����	 :	��ȡ�ַ���
/// ����	 :	in_pStr			�ַ���
///			in_iIndex		��ʼ�±�
///			in_Length		����
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_Substring(char* in_pStr, int in_iIndex, int in_Length, char* out_pResult, int in_ResultLen);

/// <summary>
/// ����	 :	��ȡ�^�g�ȵ��ַ���
/// ����	 :	in_pStr			�ַ���
///			in_cStartChr	�_ʼ�ַ�
///			in_cEndChr		�Y���ַ�
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_SubstringByInterval(char* in_pStr, char in_cStartChr, char in_cEndChr, char* out_pResult, int in_ResultLen);

/// <summary>
/// ����	 :	��ȡ�ַ���߅���ַ���
/// ����	 :	in_pStr			�ַ���
///			in_Chr			���g�ַ�
///			out_pDesc1		����ַ���1
///			in_Desc1Len		����ַ���1����
///			out_pDesc2		����ַ���2
///			in_Desc2Len		����ַ���2����
/// ����ֵ: 
/// </summary>
int string_SubstringByChr(char* in_pStr, char in_Chr, char* out_pDesc1, int in_Desc1Len, char* out_pDesc2, int in_Desc2Len);

/// <summary>
/// ����	 :	��split����,��ȡ�ֶ�����
/// ����	 :	in_pStr			�ַ���
///			in_Chr			�ַ�
/// ����ֵ: 
/// </summary>
int string_GetFieldNum(char* in_pStr, char in_Chr);

/// <summary>
/// ����	 :	��ȡ��N���ֶ�
/// ����	 :	in_pStr			�ַ���
///			in_Chr			�ַ�
///			in_Order		�ֶ����
///			out_pResult		����ַ���
///			in_ResultLen	����ַ�������
/// ����ֵ: 
/// </summary>
int string_GetFieldSting(char* in_pStr, char in_Chr, int in_Order, char* out_pResult, int in_ResultLen);

/// <summary>
/// ����	 :	��ȡ���ּ���
/// ����	 :	in_pStr			�ַ���
///			in_Chr			�ַ�
///			pArray			����
///			lArrayLength	���ϴ�С
/// ����ֵ:  ��������
/// </summary>
int string_GetFieldNumberSting(char* in_pStr, char in_Chr, long* pArray, long lArrayLength);




/// <summary>
/// ����	 :	�ڴ潻��
/// ����	 :	pMemA	 [in-out] ����1
///			pMemB	 [in-out] ����2
///			iSize	 [in]     ����
/// ����ֵ:
/// </summary>
void string_MemorySwap(void* pMemA, void* pMemB, int iSize);

/// <summary>
/// ����	 :	�ڴ�Ƚ�
/// ����	 :	pMemA	 [in] ����1
///			pMemB	 [in] ����2
///			iSize	 [in]     ����
/// ����ֵ:  0-��� 1A�� -1B��
/// </summary>
int string_MemoryCmp(void* pMemA, void* pMemB, int iSize);

/// <summary>
/// ����	 :	�ڴ渴��
/// ����	 :	pDesc	 [out] �������
///			pSrc	 [in]  ��Դ
///			iSize	 [in]  ����
/// ����ֵ:
/// </summary>
void string_MemoryCopy(void* pDesc, void* pSrc, int iSize);

/// <summary>
/// ����	 :	�ڴ滺������
/// ����	 :	pBuffer:				��ʹ�õ��ڴ滺��
///			in_out_BufferLen:		��ʹ�õ��ڴ滺���С
///			iNewLen:				������Ĵ�С
/// ����ֵ:  
/// </summary>
void* string_Malloc(void* pBuffer, int* in_out_BufferLen, int iNewLen);

/// <summary>
/// ����	 :	�ڴ滺����������
/// ����	 :	pBuffer:				��ʹ�õ��ڴ滺��
///			in_out_BufferLen:		��ʹ�õ��ڴ滺���С
///			iNewLen:				������Ĵ�С
/// ����ֵ:  
/// </summary>
void* string_Realloc(void* pBuffer, int* in_out_BufferLen, int iNewLen);

/// <summary>
/// ����	 :	�ڴ滺���ͷ�
/// ����	 :	in_pStr:				��ʹ�õ��ڴ滺��
/// ����ֵ:  
/// </summary>
void string_Free(void** in_pStr);

/// <summary>
/// ����	 :	�ж��ַ����Ƿ�Ϊ�մ�
/// ����	 :	in_pStr:				�ַ���
/// ����ֵ:  
/// </summary>
int string_IsNullOrEmpty(char *in_pStr);

/// <summary>
/// ����	 :	�����ַ�������
/// ����	 :	in_pStr					�ַ���
///			IsUnicode				�Ƿ�Ϊ���ַ�
/// ����ֵ:  
/// </summary>
int string_GetLen(char* in_pStr, int IsUnicode);






typedef enum _enumAigEncodingConvert
{
	eAEConv_AnsiToUnicode,
	eAEConv_UnicodeToAnsi,
}enumAigEncodingConvert;

/// <summary>
/// ����	 :	����ת��
/// ����	 :	pStr				�ַ���
///			pDesc				����ַ���
///			iDescLen			����ַ�������
///			eType				ת������
/// ����ֵ:  
/// </summary>
int string_ConvertEncodingFormat(char* pStr, char* pDesc, int iDescLen, enumAigEncodingConvert eType);



#ifdef __cplusplus
}
#endif

#endif  //__AIG_STRING_H__