//==============================================================
//
//爆発処理[explosion.cpp]
//Author:佐久間優香
//
//==============================================================
#include"renderer.h"
#include"manager.h"
#include"explosion.h"

//マクロ定義
#define LIFE (100)			//寿命
#define SIZE (10.0f)		//サイズ

//==============================================================
//コンストラクタ
//==============================================================
CExplosion::CExplosion()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nLife = LIFE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CExplosion::CExplosion(D3DXVECTOR3 pos,TYPE type)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nLife = LIFE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//位置の設定
	SetPosition(pos);

	//種類の取得
	SetType(type);
}

//==============================================================
//デストラクタ
//==============================================================
CExplosion::~CExplosion()
{

}

//==============================================================
//エフェクトの生成処理
//==============================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, TYPE type)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		//爆発の生成
		pExplosion = new CExplosion(pos,type);

		//初期化処理
		pExplosion->Init();
	}
	return pExplosion;
}

//==============================================================
//爆発の初期化処理
//==============================================================
HRESULT CExplosion::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\explosion000.png");

	//オブジェクト2Dの初期化処理
	CBillboard::Init();

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	SetSize(SIZE, SIZE, 0.0f);
	SetVtx(m_nPatternAnim, TYPE_EXPLOSION);

	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//==============================================================
//爆発の終了処理
//==============================================================
void CExplosion::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//爆発の更新処理
//==============================================================
void CExplosion::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPosition();

	m_nCounterAnim++;							//カウンターを加算

	if ((m_nCounterAnim % 8) == 0)
	{
		m_nCounterAnim = 0;
		m_nPatternAnim++;	//パターンNo.を更新

		//位置の設定
		SetPosition(pos);
		SetSize(SIZE, SIZE, 0.0f);
		SetVtx(m_nPatternAnim, TYPE_EXPLOSION);
	}
	else if (m_nPatternAnim >= 8)
	{//総パターン数を超えた
		Uninit();
	}

	//オブジェクト2Dの更新処理
	CBillboard::Update();
}

//==============================================================
//爆発の描画処理
//==============================================================
void CExplosion::Draw(void)
{
	//オブジェクト2Dの描画処理
	CBillboard::Draw();
}