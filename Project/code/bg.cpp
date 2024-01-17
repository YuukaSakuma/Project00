//==============================================================
//
//背景処理[bg.cpp]
//Author:佐久間優香
//
//==============================================================
#include"bg.h"
#include"renderer.h"
#include"manager.h"

//マクロ定義
#define MMOVE_V		(0.001f)		//背景の移動量

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBg::m_pTexture = NULL;			//テクスチャへのポインタ
CObject2D * CBg::m_apObject2D = NULL;				//オブジェクト2Dへのポインタ			

//==============================================================
//背景のコンストラクタ
//==============================================================
CBg::CBg()
{
	m_pVtxBuff = NULL;							//頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_fTexV = 0.0f;								//テクスチャ座標の開始位置(V値)
	m_fTexU = 0.0f;								//テクスチャ座標の開始位置(U値)
	m_fmoveV = 0.0f;							//テクスチャ座標の移動量V
	m_fmoveU = 0.0f;							//テクスチャ座標の移動量V
	m_nldxTexture = 0;							//テクスチャ番号
}

//==============================================================
//背景のデストラクタ
//==============================================================
CBg::~CBg()
{

}

//==============================================================
//背景の生成処理
//==============================================================
CBg *CBg::Create(void)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		//背景の生成
		pBg = new CBg;

		//初期化処理
		pBg->Init();	
	}
	return pBg;
}

//==============================================================
//背景の初期化処理
//==============================================================
HRESULT CBg::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\bg100.png");

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	//設定処理
	SetVtx(m_fTexV, m_fTexU);

	////テクスチャの割り当て
	//BindTexture(m_nldxTexture);

	//移動量の設定
	m_fTexV = 0.0f;
	m_fTexU = 0.0f;
	m_fmoveV = MMOVE_V;
	m_fmoveU = 0.0f;

	return S_OK;
}

//==============================================================
//背景の終了処理
//==============================================================
void CBg::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//==============================================================
//背景の更新処理
//==============================================================
void CBg::Update(void)
{
	CObject2D::Update();
	SetVtx(m_fTexV, m_fTexU);

	//値を代入する
	m_fTexV += m_fmoveV;
	m_fTexU += m_fmoveU;

	//元の位置の戻す
	if (m_fTexV < 0.0f )
	{
		m_fTexV = 1.0f;
	}
	else if (m_fTexV > 1.0f)
	{
		m_fTexV = 0.0f;
	}

	if (m_fTexU < 0.0f)
	{
		m_fTexU = 1.0f;
	}
	else if (m_fTexU > 1.0f)
	{
		m_fTexU = 0.0f;
	}
}

//==============================================================
//背景の描画処理
//==============================================================
void CBg::Draw(void)
{
	CTexture *pTexture = NULL;

	LPDIRECT3DDEVICE9 pDevice = NULL;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//オブジェクト2Dの描画処理
	CObject2D::Draw();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nldxTexture));
}