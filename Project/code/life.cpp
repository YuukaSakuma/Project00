//==============================================================
//
//弾処理[player.cpp]
//Author:佐久間優香
//
//==============================================================
#include"life.h"
#include"manager.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"texture.h"

//マクロ定義
#define WIDTH				(10.0f)			//横幅
#define HEIGHT				(10.0f)			//縦幅
#define VERTICL_BILL		(0.0f)			//縦幅
#define LIFE				(50)			//寿命
#define EFFECT_LIFE			(15)			//エフェクトの寿命
#define PARTICLE_LIFE		(50)			//パーティクルの寿命
#define EFFECT_RADIUS		(20.0f)			//エフェクトの半径
#define PARTICLE_RADIUS		(50.0f)			//パーティクルの半径

//==============================================================
//コンストラクタ
//==============================================================
CLife::CLife()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nLife = LIFE;								//寿命
}

//==============================================================
//デストラクタ
//==============================================================
CLife::~CLife()
{

}

//==============================================================
//弾の生成処理
//==============================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,TYPE type)
{
	CLife *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CLife;

		//初期化処理
		pBullet->Init();

		pBullet->SetPosition(pos);

		pBullet->SetRotation(rot);

		pBullet->SetMove(move);

		pBullet->SetType(type);
	}

	return pBullet;
}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CLife::Init(void)
{
	//オブジェクト2Dの初期化処理
	CBillboard::Init();

	//種類の設定
	CObject::SetType(CObject::TYPE_BULLET);

	//サイズの設定
	SetSize(WIDTH, HEIGHT, VERTICL_BILL);

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CLife::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CLife::Update(void)
{
	CBillboard::SetPosition(m_pos);

	//オブジェクト2Dの更新処理
	CBillboard::Update();
}

//==============================================================
//弾の描画処理
//==============================================================
void CLife::Draw(void)
{
	//オブジェクト2Dの描画処理
	CBillboard::Draw();
}