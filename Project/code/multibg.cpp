//==============================================================
//
//多重背景処理[multibg.cpp]
//Author:佐久間優香
//
//==============================================================
#include"multibg.h"
#include"manager.h"
#include"object2D.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CMultiBg::m_pTexture[TYPE_BG_MAX] = {};				//テクスチャへのポインタ

//テクスチャファイル名
const char *CMultiBg::apTexture[] =
{
	"data\\TEXTURE\\bg100.png",	//背景1
	"data\\TEXTURE\\bg101.png",	//背景2
	"data\\TEXTURE\\bg102.png",	//背景3
};

//==============================================================
//多重背景のコンストラクタ
//==============================================================
CMultiBg::CMultiBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntTex = 0; nCntTex < TYPE_BG_MAX; nCntTex++)
	{
		m_apObject2D[nCntTex] = NULL;
		m_fTexV[nCntTex] = 0.0f;
		m_fTexU[nCntTex] = 0.0f;
		m_fmoveV[nCntTex] = 0.0f;
		m_fmoveU[nCntTex] = 0.0f;
	}
}

//==============================================================
//多重背景のデストラクタ
//==============================================================
CMultiBg::~CMultiBg()
{

}

//==============================================================
//多重背景の生成処理
//==============================================================
CMultiBg *CMultiBg::Create(void)
{
	CMultiBg *pMultiBg = NULL;

	if (pMultiBg == NULL)
	{
		//オブジェクト2Dの生成
		pMultiBg = new CMultiBg;

		//初期化処理
		pMultiBg->Init();
	}

	return pMultiBg;
}

//==============================================================
//多重背景の初期化処理
//==============================================================
HRESULT CMultiBg::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	for (int nCntTex = 0; nCntTex < TYPE_BG_MAX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] == NULL)
		{
			m_apObject2D[nCntTex] = CObject2D::Create();

			if (m_apObject2D[nCntTex] != NULL)
			{
				m_aldxTexture[nCntTex] = pTexture->Regist(apTexture[nCntTex]);
				//初期化処理
				m_apObject2D[nCntTex]->Init();

				//テクスチャの割り当て
				m_apObject2D[nCntTex]->BindTexture(m_aldxTexture[nCntTex]);

				//種類設定
				SetType(TYPE_NONE);
			}
		}
	}

	m_fmoveV[0] = 0.001f;
	m_fmoveV[1] = 0.005f;
	m_fmoveV[2] = 0.01f;

	return S_OK;
}

//==============================================================
//多重背景の終了処理
//==============================================================
void CMultiBg::Uninit(void)
{
	//オブジェクトの終了処理
	CObject::Release();
}
//==============================================================
//多重背景の更新処理
//==============================================================
void CMultiBg::Update(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_BG_MAX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] != NULL)
		{
			//移動量
			m_fTexV[nCntTex] += m_fmoveV[nCntTex];
			m_fTexU[nCntTex] += m_fmoveU[nCntTex];

			//元の位置の戻す
			if (m_fTexV[nCntTex] < 0.0f)
			{
				m_fTexV[nCntTex] = 1.0f;
			}
			else if (m_fTexV[nCntTex] > 1.0f)
			{
				m_fTexV[nCntTex] = 0.0f;
			}

			if (m_fTexU[nCntTex] < 0.0f)
			{
				m_fTexU[nCntTex] = 1.0f;
			}
			else if (m_fTexU[nCntTex] > 1.0f)
			{
				m_fTexU[nCntTex] = 0.0f;
			}

			//テクスチャ座標
			m_apObject2D[nCntTex]->SetVtx(m_fTexV[nCntTex], m_fTexU[nCntTex]);
		}
	}
}

//==============================================================
//多重背景の描画処理
//==============================================================
void CMultiBg::Draw(void)
{
	//なし
}