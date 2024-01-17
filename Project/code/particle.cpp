//==============================================================
//
//パーティクル処理[particle.cpp]
//Author:佐久間優香
//
//==============================================================
#include"manager.h"
#include"effect.h"
#include"particle.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;				//テクスチャへのポインタ

//==============================================================
//コンストラクタ
//==============================================================
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fRadius = 0.0f;
	m_nType = TYPE_NONE;
}

//==============================================================
//デストラクタ
//==============================================================
CParticle::~CParticle()
{

}

//==============================================================
//パーティクルの生成処理
//==============================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col,TYPE type, float fRadius, int nLife)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{
		//オブジェクト2Dの生成
		pParticle = new CParticle;

		//初期化処理
		pParticle->Init();

		//パーティクルの設定
		pParticle->Set(pos, col, type, fRadius, nLife);
	}

	return pParticle;
}

//==============================================================
//パーティクルの初期化処理
//==============================================================
HRESULT CParticle::Init(void)
{
	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_PARTICLE);

	//半径の設定
	//SetRadius(m_fRadius);

	return S_OK;
}

//==============================================================
//パーティクルの終了処理
//==============================================================
void CParticle::Uninit(void)
{

}

//==============================================================
//パーティクルの更新処理
//==============================================================
void CParticle::Update(void)
{

}

//==============================================================
//パーティクルの描画処理
//==============================================================
void CParticle::Draw(void)
{

}

//==============================================================
//パーティクルの設定処理
//==============================================================
void CParticle::Set(D3DXVECTOR3 pos, D3DXCOLOR col, CObject::TYPE type, float fRadius, int nLife)
{
	m_nType = type;

	//パーティクルの生成
	for (int nCntAppear = 0; nCntAppear < 30; nCntAppear++)
	{
		if (m_nType == TYPE_ENEMY)
		{
			//位置の設定
			m_pos = pos;

			//角度を求める
			m_fAngle = (float)(rand() % 629 - 314) / 1.0f;

			//移動量を求める
			m_fMove = (float)(rand() % 50) / 10.0f + 1.0f;

			//移動量の設定
			m_move.x = sinf(m_fAngle) * m_fMove;
			m_move.y = cosf(m_fAngle) * m_fMove;
			//m_move.z = cosf(m_fAngle) * m_fMove;

			//色の設定
			m_col = col;

			//半径の設定
			m_fRadius = fRadius;

			//寿命の設定
			m_nLife = nLife;

			m_nType = type;
		}
		//エフェクトの生成
		CEffect::Create(m_pos,m_move,m_col,m_fRadius,m_nLife);
	}
}