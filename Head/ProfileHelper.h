#if !defined __AIG_PROFILE_H__
#define __AIG_PROFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "StringHelper.h"
#include "PathHelper.h"
#include "FileHelper.h"

/// <summary>
/// ����	 :	��ȡ�����ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pDefault			Ĭ��ֵ
///			pReturnString		����ַ���
///			iReturnStringLen	����ַ�������
///			pProfilePath		�ļ�·��
/// ����ֵ: 
/// </summary>
int   profile_GetString(char* pGroup, char* pKey, char* pDefault, char* pValue, int iValueLen, char* pProfilePath);
int   profile_GetInt(char* pGroup, char* pKey, int pDefault, char* pProfilePath);
float profile_GetFloat(char* pGroup, char* pKey, float pDefault, char* pProfilePath);

/// <summary>
/// ����	 :	���������ļ��е�ֵ
/// ����	 :	pGroup				����
///			pKey				�ؼ�����
///			pValue				ֵ
///			pProfilePath		�ļ�·��
/// ����ֵ: 
/// </summary>
int profile_SetString(char* pGroup, char* pKey, char* pValue, char* pProfilePath);
int profile_SetInt(char* pGroup, char* pKey, int iValue, char* pProfilePath);
int profile_Setfloat(char* pGroup, char* pKey, float fValue, char* pProfilePath);

#ifdef __cplusplus
}
#endif

#endif  //__AIG_PROFILE_H__