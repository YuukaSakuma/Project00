//==============================================================
//
//弾処理[player.cpp]
//Author:佐久間優香
//
//==============================================================
#include"enemy.h"
#include"manager.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"score.h"
#include"billboard.h"
#include"texture.h"
#include"object.h"
#include"objectX.h"

//マクロ定義
#define WIDTH				(10.0f)			//横幅
#define HEIGHT				(10.0f)			//縦幅
#define VERTICL_BILL		(0.0f)			//縦幅
#define LIFE				(50)			//寿命
#define EFFECT_LIFE			(15)			//エフェクトの寿命
#define PARTICLE_LIFE		(50)			//パーティクルの寿命
#define EFFECT_RADIUS		(20.0f)			//エフェクトの半径
#define PARTICLE_RADIUS		(50.0f)			//パーティクルの半径
#define ADD_SCORE			(1111)			//スコア

//==============================================================
//コンストラクタ
//==============================================================
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nLife = LIFE;								//寿命
	//m_BType = TYPE_A;
}

//==============================================================
//デストラクタ
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//弾の生成処理
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CEnemy;

		//初期化処理
		pBullet->Init();

		pBullet->SetPosition(pos);

		pBullet->SetRotation(rot);
	}

	return pBullet;
}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CEnemy::Init(void)
{
	//オブジェクト2Dの初期化処理
	CObjectX::Init();

	////種類の設定
	//CObject::SetType(CObject::TYPE_BULLET);

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CEnemy::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObjectX::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CEnemy::Update(void)
{
	//前回の位置を代入
	m_posOld = m_pos;

	//位置を更新
	m_pos += m_move;


	//オブジェクト2Dの更新処理
	CObjectX::Update();
}

//==============================================================
//弾の描画処理
//==============================================================
void CEnemy::Draw(void)
{
	//オブジェクト2Dの描画処理
	CObjectX::Draw();
}