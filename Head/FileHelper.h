#if !defined __AIG_FILE_H__
#define __AIG_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
#include "StringHelper.h"

typedef enum _enumAigFileRight
{
	eAFileRight_ReadOnly,	//ֻ��
	eAFileRight_Hide, 		//����

}enumAigFileRight;

/// <summary>
/// ���ܣ��ݹ��½�Ŀ¼
/// ����ֵ����0��ʾʧ��
/// </summary>
int file_Mkdirs(char* pPath);

/// <summary>
/// ���ܣ���ȡ�ļ���С
/// ����ֵ��С��0��ʾʧ��
/// </summary>
long file_GetFileLen(char* pPath);

/// <summary>
/// ���ܣ������ļ�����
/// ����ֵ����0��ʾ����
/// </summary>
int file_SetFileAttributes(char *pPath, enumAigFileRight eType);

/// <summary>
/// ���ܣ��ļ��Ƿ����
///	����ֵ��AIG_TRUE-����
/// </summary>
int file_IsFileExist(char* pPath);




//����Ŀ¼
int file_BakDir(char* pSrcPath, char* pDescPath);


/// <summary>
/// ���ܣ���ȡ����·��
/// ������pFilePath:			ԭʼ·��
///	˵��������ֵ��Ҫ�˹��ͷ�
/// </summary>
char* file_GetFullPath(char* pFilePath);


/***************************************************************************************************************************
����·�����ļ�������չ��
***************************************************************************************************************************/
char* file_GetDirectoryName(char* pPath);				//��ȡ�ļ�����Ŀ¼
char* file_GetFileName(char* pPath);					//��ȡ�ļ���
char* file_GetFileNameWithoutExtension(char* pPath);	//��ȡ�ļ���(������չ��)
char* file_GetExtension(char* pPath);					//��ȡ�ļ���չ��
char* file_GetPathRoot(char* pPath);					//��ȡ��Ŀ¼



/***************************************************************************************************************************
���ܣ������ļ�����
�ļ�������ʽ��
            #��ע/����
            ��xxx��
             xxx = yyy
***************************************************************************************************************************/
#define AIG_FILE_PROFILE_LINE_MAXLEN	1024	//�����ļ�������󳤶�
#define AIG_FILE_PROFILE_NOTE_FLAG		"#;��"	//�����ļ���ע���б�־
//��д�����ļ�
//������pHandle	�ļ����
//	   pGroup   С����(������ʾ)
//     pKey     �ؼ���
//	   pValue   �ַ���ֵ
//     fValue   ����ֵ
//     fDefault Ĭ��ֵ(��û���ҵ��ؼ���ʱ��ؼ��ֺ�û��ֵʱ,��Ĭ��ֵ����)
//����ֵ��0��ȷ
int   file_InitProfile(void** pHandle,char* pFileName);														//��ʼ��
int   file_UnintProfile(void** pHandle);																	//���ʼ��

int   file_SaveProfile(void* pHandle);																		//����
int   file_SaveAsProfile(void* pHandle, char* pFileName);													//���Ϊ

int   file_WriteProfileString(void* pHandle, char* pGroup, char* pKey, char* pValue,char* pComment);		//д���ַ���ֵ
int   file_WriteProfileFloat(void* pHandle, char* pGroup, char* pKey, float fValue, char* pComment);		//д�븡����

char* file_ReadProfileString(void* pHandle, char* pGroup, char* pKey);										//��ȡ�ַ���ֵ
float file_ReadProfileFloat(void* pHandle, char* pGroup, char* pKey);										//��ȡ������

int   file_RemoveProfileAllKey(void* pHandle);																//ɾ��ȫ���ؼ���
int   file_RemoveProfileGroup(void* pHandle, char* pGroup);													//ɾ��С��
int   file_RemoveProfileKey(void* pHandle, char* pGroup, char* pKey);										//ɾ��ĳһ���ؼ���

#ifdef __cplusplus
}
#endif

#endif  //__AIG_FILE_H__