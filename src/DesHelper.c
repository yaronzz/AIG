#include "DesHelper.h"

typedef unsigned char UINT1;

static	void DesGetSubKey(UINT1 subkey[16][48], const UINT1 Key[8]);
static	void DesPC1_func(UINT1 output[56], UINT1 input[64]);
static	void DesPC2_func(UINT1 output[48], UINT1 input[56]);
static	void DesIP1_func(UINT1 output[64], UINT1 input[64]);
static	void DesIP2_func(UINT1 output[64], UINT1 input[64]);
static	void DesE_func(UINT1 output[48], UINT1 input[32]);
static	void DesP_func(UINT1 output[32], UINT1 input[32]);
static	void DesS_func(UINT1 output[32], const UINT1 input[48]);
static	void DesByteToBit(UINT1 *output, const UINT1 *input, int bits);
static	void DesBitToByte(UINT1 *output, const UINT1 *input, int bits);
static	void DesLeftshift(UINT1 *output, UINT1 *input, int len, int loop);
static	void DesF_func(UINT1 output[32], UINT1 R0[32], const UINT1 K[48]);
static	void DesXor(UINT1 *InA, const UINT1 *InB, int len);

//iv--初始向量,CBC模式用到,一般模式iv为0
static	void DesEnc(UINT1 output[8], UINT1 input[8], UINT1 subkey[16][48], UINT1 iv[64]);
static	void DesDec(UINT1 output[8], UINT1 input[8], UINT1 subkey[16][48], UINT1 iv[64]);

const UINT1 AIG_DES_STRING[32] = {
	0x78, 0x12, 0x4B, 0xCE, 0x49, 0xaf, 0x4B, 0x2C,
	0x0C, 0x14, 0x2D, 0xAE, 0xC8, 0x11, 0xC8, 0x2C,
	0x04, 0x00, 0xDB, 0x8F, 0x1F, 0x34, 0x72, 0x6C,
	0xCE, 0x36, 0x6F, 0x97, 0x0F, 0x45, 0xBE, 0xB5
};


// initial permutation IP
const UINT1 AIG_DES_IP_TABLE[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
// final permutation IP^-1 
const UINT1 AIG_DES_IPR_TABLE[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};
// expansion operation matrix
const UINT1 AIG_DES_E_TABLE[48] = {
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};
// 32-bit permutation function P used on the output of the S-boxes 
const UINT1 AIG_DES_P_TABLE[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};
// permuted choice table (key) 
const UINT1 AIG_DES_PC1_TABLE[56] = {
	57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};
// permuted choice key (table) 
const UINT1 AIG_DES_PC2_TABLE[48] = {
	14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
// number left rotations of pc1 
const UINT1 AIG_DES_LOOP_TABLE[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
// The (in)famous S-boxes 
const UINT1 AIG_DES_S_BOX[8][4][16] = {
	// S1 
	14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
	// S2 
	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
	// S3 
	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
	// S4 
	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
	// S5 
	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
	// S6 
	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
	// S7 
	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
	// S8 
	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

/*密钥正确*/
static	void DesGetSubKey(UINT1 subkey[16][48], const UINT1 key[8])
{
	UINT1 bitkey[64];
	UINT1 pc1key[56];
	UINT1 KC[17][28], KD[17][28], KCD[17][56];
	int i;

	if (subkey == NULL&&key == NULL)
		return;

	DesByteToBit(bitkey, key, 64);
	DesPC1_func(pc1key, bitkey);

	memcpy(KC[0], &pc1key[0], 28);
	memcpy(KD[0], &pc1key[28], 28);

	for (i = 0; i<16; i++)
	{
		DesLeftshift(KC[i + 1], KC[i], 28, AIG_DES_LOOP_TABLE[i]);
		DesLeftshift(KD[i + 1], KD[i], 28, AIG_DES_LOOP_TABLE[i]);

		memcpy(&KCD[i][0], KC[i + 1], 28);
		memcpy(&KCD[i][28], KD[i + 1], 28);

		DesPC2_func(subkey[i], KCD[i]);
	}
}

static	void DesPC1_func(UINT1 output[56], UINT1 input[64])
{
	int i;
	for (i = 0; i<56; i++)
	{
		output[i] = input[AIG_DES_PC1_TABLE[i] - 1];
	}
}

static	void DesPC2_func(UINT1 output[48], UINT1 input[56])
{
	int i;
	for (i = 0; i<48; i++)
	{
		output[i] = input[AIG_DES_PC2_TABLE[i] - 1];
	}
}

static	void DesIP1_func(UINT1 output[64], UINT1 input[64])
{
	int i;
	for (i = 0; i<64; i++)
	{
		output[i] = input[AIG_DES_IP_TABLE[i] - 1];
	}
}

static	void DesIP2_func(UINT1 output[64], UINT1 input[64])
{
	int i;
	for (i = 0; i<64; i++)
	{
		output[i] = input[AIG_DES_IPR_TABLE[i] - 1];
	}
}

static	void DesE_func(UINT1 output[48], UINT1 input[32])
{
	int i;
	for (i = 0; i<48; i++)
	{
		output[i] = input[AIG_DES_E_TABLE[i] - 1];
	}
}

static	void DesP_func(UINT1 output[32], UINT1 input[32])
{
	int i;
	for (i = 0; i<32; i++)
	{
		output[i] = input[AIG_DES_P_TABLE[i] - 1];
	}
}

static	void DesS_func(UINT1 output[32], const UINT1 input[48])
{
	UINT1 i, j, k;
	for (i = 0; i<8; i++, input += 6, output += 4)
	{
		j = (input[0] << 1) + input[5];
		k = (input[1] << 3) + (input[2] << 2) + (input[3] << 1) + input[4];
		DesByteToBit(output, &AIG_DES_S_BOX[i][j][k], 4);
	}
}

static	void DesLeftshift(UINT1 *output, UINT1 *input, int len, int loop)
{
	UINT1 tmp[255];
	memcpy(output, input, len);
	memcpy(tmp, output, loop);
	memcpy(output, output + loop, len - loop);
	memcpy(output + len - loop, tmp, loop);
}

static	void DesF_func(UINT1 output[32], UINT1 R[32], const UINT1 K[48])
{
	UINT1 MR[48];
	UINT1 tmp[32];

	DesE_func(MR, R);
	DesXor(MR, K, 48);
	DesS_func(tmp, MR);
	DesP_func(output, tmp);
}

static	void DesXor(UINT1 *InA, const UINT1 *InB, int len)
{
	int i;
	for (i = 0; i<len; ++i)
	{
		InA[i] ^= InB[i];
	}
}

static	void DesByteToBit(UINT1 *output, const UINT1 *input, int bits)
{
	int i;
	for (i = 0; i<bits; ++i)
	{
		output[i] = (input[i / 8] >> (i & 7)) & 1;//i%8
	}
}

static	void DesBitToByte(UINT1 *output, const UINT1 *input, int bits)
{
	int i;

	memset(output, 0, bits / 8);
	for (i = 0; i<bits; ++i)
	{
		output[i / 8] |= input[i] << (i & 7);
	}
}

static	void DesEnc(UINT1 output[8], UINT1 input[8], UINT1 subkey[16][48], UINT1 iv[64])
{
	UINT1 bitinput[64], bitoutput[64];
	UINT1 achIV[64];
	UINT1 ip_input[64];
	UINT1 L[17][32], R[17][32];
	UINT1 LR[64];

	int i;

	DesByteToBit(bitinput, input, 64);
	if (iv)
	{
		DesByteToBit(achIV, iv, 64);
		DesXor(bitinput, achIV, 64);
	}


	DesIP1_func(ip_input, bitinput);

	memcpy(L[0], &ip_input[0], 32);
	memcpy(R[0], &ip_input[32], 32);

	for (i = 0; i<16; i++)
	{
		UINT1 f_tmp[32];

		memcpy(L[i + 1], R[i], 32);
		DesF_func(f_tmp, R[i], subkey[i]);
		DesXor(f_tmp, L[i], 32);
		memcpy(R[i + 1], f_tmp, 32);
	}


	memcpy(&LR[0], R[16], 32);
	memcpy(&LR[32], L[16], 32);
	DesIP2_func(bitoutput, LR);
	DesBitToByte(output, bitoutput, 64);
}

static	void DesDec(UINT1 output[8], UINT1 input[8], UINT1 subkey[16][48], UINT1 iv[64])
{
	UINT1 bitinput[64], bitoutput[64];
	UINT1 ip_input[64];
	UINT1 L[17][32], R[17][32];
	UINT1 LR[64];
	UINT1 achIV[64];
	int i;

	DesByteToBit(bitinput, input, 64);
	DesIP1_func(ip_input, bitinput);


	memcpy(R[16], &ip_input[0], 32);
	memcpy(L[16], &ip_input[32], 32);

	for (i = 15; i >= 0; i--)
	{
		UINT1 f_tmp[32];

		memcpy(R[i], L[i + 1], 32);
		DesF_func(f_tmp, R[i], subkey[i]);
		DesXor(f_tmp, R[i + 1], 32);
		memcpy(L[i], f_tmp, 32);
	}


	memcpy(&LR[0], L[0], 32);
	memcpy(&LR[32], R[0], 32);
	DesIP2_func(bitoutput, LR);

	if (iv)
	{
		DesByteToBit(achIV, iv, 64);
		DesXor(bitoutput, achIV, 64);
	}

	DesBitToByte(output, bitoutput, 64);
}

static	int InBlockEnc(UINT1 *output, UINT1 *input, int datalen, const UINT1 *key)
{
	UINT1 subkey[16][48];
	int i, j;

	if (!(output && input && key && (datalen = (datalen + 7) & 0xfffffff8)))
	{
		return -1;
	}

	DesGetSubKey(subkey, key);
	for (i = 0, j = datalen >> 3; i<j; i++, output += 8, input += 8)
	{
		DesEnc(output, input, subkey, NULL);
	}

	return 0;
}

static	int InDesBlockDec(UINT1 *output, UINT1 *input, int datalen, const UINT1 *key)
{
	UINT1 subkey[16][48];
	int i, j;

	if (!(output && input && key && (datalen = (datalen + 7) & 0xfffffff8)))
	{
		return -1;
	}

	DesGetSubKey(subkey, key);
	for (i = 0, j = datalen >> 3; i<j; i++, output += 8, input += 8)
	{
		DesDec(output, input, subkey, NULL);
	}

	return 0;
}

/// <summary>
/// 功能：DES解密
/// 注意：解密长度与原始数据长度一致
/// </summary>
int	des_BlockDecrypt(unsigned char*output, unsigned char *input, int datalen)
{
	UINT1 des[8] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		des[i] = AIG_DES_STRING[4 * i + 1];
	}
	return InDesBlockDec(output, input, datalen, des);
}

/// <summary>
/// 功能：DES加密
/// 参数：pOutput		输出的数据
///		 pInput		输入的数据
///		 iDatalen   输入数据的长度
/// 注意：DES加密后的长度以8字节对齐，如果原始数据长度为8的倍数，加密后数据长度不变；否则补齐为8的倍数
/// </summary>
int	des_BlockEncrypt(unsigned char*output, unsigned char*input, int datalen)
{
	
	UINT1 des[8] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		des[i] = AIG_DES_STRING[4 * i + 1];
	}
	return InBlockEnc(output, input, datalen, des);
}