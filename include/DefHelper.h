#if !defined __AIG_DEF_H__
#define __AIG_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define AIG_DEBUG
#define AIG_NORELEASE				//��ʾ����ûʵ��
#define AIG_TRUE			1		//��ȷ
#define AIG_FALSE			0		//����
#define AIG_MAXLEN_FILEPATH	1024	//Ŀ¼������󳤶�
#define AIG_MAXLEN_FILENAME 256		//�ļ�������󳤶�

#define AIG_FUNC_MALLOC com_malloc		//�����ڴ�
#define AIG_FUNC_FREE	com_free		//�ͷ��ڴ�
typedef int(*pfn_AIG_CMP_CALLBACK)(void* in_pKeyA, void* in_pKeyB, int in_KeyLen);		//�ؼ��ֱȽϻص�������0���,>0 A>B,<0 A<B��


//������
typedef enum _AIG_ERRORCODE
{
	eAEC_Err				= -1,
	eAEC_Success			= 0,
	eAEC_Malloc				= 1,	//�����ڴ�ռ�ʧ��
	eAEC_Input				= 2,	//�����������
	eAEC_Open				= 3,	//���ļ�ʧ��
	eAEC_Mkdir				= 4,	//�½��ļ���ʧ��
	eAEC_Creat				= 5,	//�½��ļ�ʧ��
	eAEC_NoFile				= 6,	//�ļ�������
	eAEC_NoDir				= 7,	//Ŀ¼������
	eAEC_PathOver			= 8,	//·���������
	eAEC_IndexOver			= 9,	//�±����
	eAEC_End				= 10,	//����

	eAEC_ParaNumOver		= 20,	//����������������
	eAEC_BufferOver			= 21,	//�ռ����
	eAEC_HandleNoLoad		= 22,	//���δװ�ع�����
	eAEC_OptErr				= 23,	//Opt��ʽ����
	eAEC_PwdLenOver	        = 24,   //���볤�ȳ���������
	eAEC_PwdErr             = 25,   //�������
	eAEC_InvalidTime		= 26,	//��Ч��ʱ��
	eAEC_AlreadyExist		= 27,	//�Ѿ�����
	eAEC_TimeOut			= 28,	//��ʱ

	eAEC_InitErr			= 30,	//��ʼ��ʧ��
	eAEC_CoverAddr			= 31,	//��ַת��
	eAEC_BindErr			= 32,	//��
	eAEC_ListenErr			= 33,	//����
}AIG_ERRORCODE;


#ifdef __cplusplus
}
#endif

#endif  //__AIG_DEF_H__
