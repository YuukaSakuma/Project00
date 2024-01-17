//==============================================================
//
//テクスチャ処理[texture.cpp]
//Author:佐久間優香
//
//==============================================================
#include"texture.h"
#include"manager.h"
#include<string.h>

//静的メンバ変数
int CTexture::m_nNumAll = 0;

//テクスチャファイル名
const char *CTexture::apTexture[TYPE_TEX_MAX] =
{
	"data\\TEXTURE\\download.png",			//なし(消さない)
	"data\\TEXTURE\\explosion000.png",		//爆発
	"data\\TEXTURE\\effect000.jpg",			//エフェクト
	"data\\TEXTURE\\number.png",			//数字
	"data\\TEXTURE\\block000.png",			//ブロック
	"data\\TEXTURE\\bg100.png",				//背景0
	"data\\TEXTURE\\bg101.png",				//背景1
	"data\\TEXTURE\\bg102.png",				//背景2
	"data\\TEXTURE\\meadow.jpg",			//フィールド
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
//コンストラクタ
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
//デストラクタ
//==============================================================
CTexture::~CTexture()
{
	 
}
//==============================================================
//全てのテクスチャの読み込み
//==============================================================
HRESULT CTexture::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < TYPE_TEX_MAX; nCntTex++)
	{
		//テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			apTexture[nCntTex],
			&m_apTexture[nCntTex])))
		{//失敗した場合
			return E_FAIL;
		}
		m_nNumAll++;
		strcpy(m_aFileName[nCntTex], apTexture[nCntTex]);
	}
	return S_OK;
}

//==============================================================
//全てのテクスチャの破棄
//==============================================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_TEX_MAX; nCntTex++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==============================================================
//指定テクスチャの読み込み
//==============================================================
int CTexture::Regist(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
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
		//テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			pFilename,
			&m_apTexture[m_nNumAll])))
		{//失敗した場合
			return E_FAIL;
		}

		strcpy(m_aFileName[m_nNumAll], apTexture[m_nNumAll]);

		m_nNumAll++;

		return nNumOld;
	}
	
	return NULL;
}

//==============================================================
//テクスチャの番号の取得
//==============================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nldx)
{
	return m_apTexture[nldx];
}