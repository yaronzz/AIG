#if !defined __AIG_DES_H__
#define __AIG_DES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DefHelper.h"
	int	des_BlockDecrypt(unsigned char*output, unsigned char *input, int datalen);
	int	des_BlockEncrypt(unsigned char*output, unsigned char*input, int datalen);



#ifdef __cplusplus
}
#endif

#endif  //__AIG_DES_H__
