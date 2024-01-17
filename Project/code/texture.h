//==============================================================
//
//�e�N�X�`������[texture.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"
#include"object.h"

//�}�N����`
#define MAX_TEXTURE	(256)	//�e�N�X�`���̍ő吔

//==============================================================
//�e�N�X�`���N���X
//==============================================================
class CTexture
{
public:

	//���
	typedef enum
	{
		TYPE_TEX_NONE = 0,
		TYPE_TEX_EXPLOSION,		//����
		TYPE_TEX_EFFECT,		//�G�t�F�N�g
		TYPE_TEX_SCORE,			//�X�R�A
		TYPE_TEX_BLOCK,			//�u���b�N
		TYPE_TEX_BG_0,			//�w�i0
		TYPE_TEX_BG_1,			//�w�i1
		TYPE_TEX_BG_2,			//�w�i2
		TYPE_TEX_FIELD,			//�t�B�[���h
		TYPE_TEX_WALL,			//��
		TYPE_TEX_TITLELOGO,		//�^�C�g�����S
		TYPE_TEX_PRESS,			//����
		TYPE_TEX_TITLEBG,		//�^�C�g���w�i
		TYPE_TEX_RANK,			//����
		TYPE_TEX_TUTORIAL,		//�`���[�g���A��
		TYPE_TEX_RANKINGLOGO,	//�����L���O���S
		TYPE_TEX_RESULT,		//���U���g

		TYPE_TEX_MAX
	}TYPE_TEX;

	CTexture();					//�R���X�g���N�^
	~CTexture();				//�f�X�g���N�^

	 HRESULT Load(void);		//�S�Ẵe�N�X�`���ǂݍ���
	 void Unload(void);			//�S�Ẵe�N�X�`���j��

	 int Regist(const char *pFilename);			//�w��e�N�X�`���̓ǂݍ���
	 LPDIRECT3DTEXTURE9 GetAddress(int nldx);	//�e�N�X�`���ԍ��̎擾

private:
	static const char *apTexture[TYPE_TEX_MAX];				//�t�@�C����

	char m_aFileName[MAX_TEXTURE][256];

	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];
	static int m_nNumAll;
};
#endif