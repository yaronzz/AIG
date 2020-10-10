
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#endif

#if defined(__linux) || defined(linux) || defined(__LYNX)
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <time.h>
#include <strings.h>
#include <sys/stat.h>
#endif

#include "BPTreeHelper.h"
//
//typedef struct _BPTNode
//{
//	short   IsLeaf;							//是否为叶子
//	short	KeyNum;							//Key的数量
//	long	Keys[AIG_PTREE_MVALUE - 1];		//Key集合
//	long    Value[AIG_PTREE_MVALUE];		//值
//	struct _BPTNode* Parent;				//父节点
//	struct _BPTNode* Next;					//下一个节点(链表)
//	struct _BPTNode* LeafNext;				//下一个叶子节点
//}BPTNode;
//
//typedef struct __AIG_BPTREE_HANDLE
//{
//	int CurrentCount;						//当前树中Key数量		
//	int SplitNodeKeyNum;					//新分裂的节点Key数量
//
//	KEYPTR** TmpKeys;						//用于分裂时的临时Key集合
//	void** TmpValues;						//用于分裂时的临时值集合
//
//	int KeyLen;								//关键字的长度
//	int MValue;								//M值
//	BPTNode* pRoot;							//根结点
//	BPTNode* pLeafList;						//叶子节点链表
//	BPTNode* pTraverseHandle;				//用于遍历
//	int		 TraverseIndex;					//用于遍历
//
//	pfn_AIG_CMP_CALLBACK2 pCmp_func;		//节点比较回调函数
//	pfn_EARSE_CALLBACK pEarse_func;			//节点的Key和Value内存释放回调函数
//
//} AIG_BPTREE_HANDLE;
