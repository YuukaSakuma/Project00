//==============================================================
//
//�e�N�X�`������[texture.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"texture.h"
#include"manager.h"
#include<string.h>

//�ÓI�����o�ϐ�
int CTexture::m_nNumAll = 0;

//�e�N�X�`���t�@�C����
const char *CTexture::apTexture[TYPE_TEX_MAX] =
{
	"data\\TEXTURE\\download.png",			//�Ȃ�(�����Ȃ�)
	"data\\TEXTURE\\explosion000.png",		//����
	"data\\TEXTURE\\effect000.jpg",			//�G�t�F�N�g
	"data\\TEXTURE\\number.png",			//����
	"data\\TEXTURE\\block000.png",			//�u���b�N
	"data\\TEXTURE\\bg100.png",				//�w�i0
	"data\\TEXTURE\\bg101.png",				//�w�i1
	"data\\TEXTURE\\bg102.png",				//�w�i2
	"data\\TEXTURE\\meadow.jpg",			//�t�B�[���h
	"data\\TEXTURE\\wall00.jpg",
	"data\\TEXTURE\\title_logo00.png",
	"data\\TEXTURE\\pressenter.png",
	"data\\TEXTURE\\bg.jpg",
	"data\\TEXTURE\\rank.png",
	"data\\TEXTURE\\tutrial000.png",
	"data\\TEXTURE\\ranking.png",
	"data\\TEXTURE\\result.png",
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
		memset(&m_aFileName[nCnt][0], '\0', sizeof(m_aFileName[nCnt]));
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CTexture::~CTexture()
{
	 
}
//==============================================================
//�S�Ẵe�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CTexture::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < TYPE_TEX_MAX; nCntTex++)
	{
		//�e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			apTexture[nCntTex],
			&m_apTexture[nCntTex])))
		{//���s�����ꍇ
			return E_FAIL;
		}
		m_nNumAll++;
		strcpy(m_aFileName[nCntTex], apTexture[nCntTex]);
	}
	return S_OK;
}

//==============================================================
//�S�Ẵe�N�X�`���̔j��
//==============================================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_TEX_MAX; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==============================================================
//�w��e�N�X�`���̓ǂݍ���
//==============================================================
int CTexture::Regist(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	int nNumOld = m_nNumAll;

	CTexture * pTexture = CManager::Get()->GetTexturet();

	for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	{
		if (strcmp(pFilename, &m_aFileName[nCntTex][0]) == 0)
		{
			return nCntTex;
		}
	}
	if (m_nNumAll < MAX_TEXTURE)
	{
		//�e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			pFilename,
			&m_apTexture[m_nNumAll])))
		{//���s�����ꍇ
			return E_FAIL;
		}

		strcpy(m_aFileName[m_nNumAll], apTexture[m_nNumAll]);

		m_nNumAll++;

		return nNumOld;
	}
	
	return NULL;
}

//==============================================================
//�e�N�X�`���̔ԍ��̎擾
//==============================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nldx)
{
	return m_apTexture[nldx];
}