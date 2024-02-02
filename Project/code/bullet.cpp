//==============================================================
//
//弾処理[player.cpp]
//Author:佐久間優香
//
//==============================================================
#include"bullet.h"
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
CBullet::CBullet()
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
CBullet::~CBullet()
{

}

//==============================================================
//弾の生成処理
//==============================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,BulletType btype,TYPE type)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		switch (btype)
		{
		case CBullet::TYPE_A:

			pBullet = new CBulletA;

			break;

		case CBullet::TYPE_B:

			pBullet = new CBulletB;

			break;

		case CBullet::TYPE_C:

			pBullet = new CBulletC;

			break;
		
		}

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
HRESULT CBullet::Init(void)
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
void CBullet::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CBullet::Update(void)
{
	//前回の位置を代入
	m_posOld = m_pos;

	//位置を更新
	m_pos += m_move;

	//敵との当たり判定
	if (CBullet::CollisionModel(&m_pos, &m_posOld) == true)
	{//敵と当たったら

		//爆発の生成
		CExplosion::Create(m_pos, CObject::TYPE_EXPLOSION);

		//ビルボードの終了処理
		CBullet::Uninit();

		return;
	}

	//寿命を減算
	m_nLife--;

	if (m_nLife <= 0)
	{//寿命が無くなったら
	 //爆発の生成
		CExplosion::Create(m_pos, CObject::TYPE_EXPLOSION);

		//終了処理
		Uninit();
		return;
	}

	CBillboard::SetPosition(m_pos);

	//オブジェクト2Dの更新処理
	CBillboard::Update();
}

//==============================================================
//弾の描画処理
//==============================================================
void CBullet::Draw(void)
{
	//オブジェクト2Dの描画処理
	CBillboard::Draw();
}

//==============================================================
//弾の当たり判定(2D)
//==============================================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject *pObj;

		//オブジェクトを取得
		pObj = CObject::GetObject(nCntObj);

		if (pObj != NULL)
		{
			CObject::TYPE type;

			//種類を取得
			type = pObj->GetType();

			if (type == pObj->TYPE_ENEMY)
			{//種類が敵の場合
				if (pos.x >= pObj->GetPosition().x - 50.0f
					&& pos.x <= pObj->GetPosition().x + 50.0f
					&& pos.y >= pObj->GetPosition().y - 50.0f
					&& pos.y <= pObj->GetPosition().y + 50.0f)
				{
					//爆発の生成
					//CExplosion::Create(pos, TYPE_EXPLOSION);

					//パーティクルの生成
					CParticle::Create(pos, D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f), type, PARTICLE_RADIUS, PARTICLE_LIFE);

					//スコアの加算
					CScore::Add(ADD_SCORE);

					//オブジェクトの破棄
					pObj->Uninit();

					return TRUE;
				}
			}
			else if (type == pObj->TYPE_BLOCK)
			{//種類がブロックのとき

			 //敵の位置取得
				D3DXVECTOR3 posBlock = pObj->GetPosition();

				//ブロックの当たり判定(左上)
				if (CBullet::ColisionLeft(pos, posBlock) == true)
				{//当たってたら

				 //爆発の生成
				 CExplosion::Create(pos, CObject::TYPE_EXPLOSION);

					return true;
				}
			}
		}
	}
	return FALSE;
}

//==============================================================
//当たり判定 左上
//==============================================================
bool CBullet::ColisionLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x + WIDTH >= posBlock.x 
		&& pos.x - WIDTH <= posBlock.x + 50.0f 
		&& pos.y >= posBlock.y 
		&& pos.y - HEIGHT <= posBlock.y + 50.0f)
	{//当たったら

		return true;
	}

	return false;
}

//==============================================================
//当たり判定(真ん中)
//==============================================================
bool CBullet::ColisionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x >= posBlock.x - 50.0f 
		&& pos.x <= posBlock.x + 50.0f 
		&& pos.y >= posBlock.y - 50.0f 
		&& pos.y <= posBlock.y + 50.0f)
	{//当たったら

		return true;
	}

	return false;
}

//==============================================================
//当たり判定
//==============================================================
bool CBullet::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		//オブジェクトを取得
		CObject *pObj = GetObject(nCntModel);

		if (pObj != NULL)
		{//メモリが使用されているとき

		 //種類を取得
			CObject::TYPE type = pObj->GetType();

			if (m_type == TYPE_PLAYER)
			{
				if (type == pObj->TYPE_MODEL || type == TYPE_ENEMY)
				{//種類がモデルの場合

				 //モデルの位置取得
					D3DXVECTOR3 posModel = pObj->GetPosition();
					//D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->y + HEIGHT > posModel.y
						&& pPos->y < posModel.y + maxModel.y)
					{
						if (pPosOld->x <= posModel.x + minModel.x
							&& pPos->x > posModel.x + minModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//左にめり込んだ場合

							if (type == TYPE_ENEMY)
							{//敵の場合
							 //敵のヒット処理
								pObj->Hit();
							}
							return true;

						}

						if (pPosOld->x >= posModel.x + maxModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//右にめり込んだ場合

							if (type == TYPE_ENEMY)
							{//敵の場合
							 //敵のヒット処理
								pObj->Hit();
							 
							}

							return true;
						}

						if (pPosOld->z <= posModel.z + minModel.z
							&& pPos->z > posModel.z + minModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//手前にめり込んだ場合

							if (type == TYPE_ENEMY)
							{//敵の場合

							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->z >= posModel.z + maxModel.z
							&& pPos->z < posModel.z + maxModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//奥にめり込んだ場合

							if (type == TYPE_ENEMY)
							{//敵の場合
							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y <= posModel.y + minModel.y
							&& pPos->y > posModel.y + minModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//底にめり込んだ場合

							if (type == TYPE_ENEMY)
							{//敵の場合

							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y >= posModel.y + maxModel.y
							&& pPos->y < posModel.y + maxModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//上にめり込んだ場合

							if (type == TYPE_ENEMY)
							{//敵の場合

							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}
					}
				}
			}
			else if (m_type == TYPE_ENEMY)
			{
				if (type == pObj->TYPE_MODEL || type == TYPE_PLAYER)
				{//種類がモデルの場合

				 //モデルの位置取得
					D3DXVECTOR3 posModel = pObj->GetPosition();
					//D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->y + HEIGHT > posModel.y
						&& pPos->y < posModel.y + maxModel.y)
					{
						if (pPosOld->x <= posModel.x + minModel.x
							&& pPos->x > posModel.x + minModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//左にめり込んだ場合

							if (type == TYPE_PLAYER)
							{//敵の場合
							 //敵のヒット処理
								pObj->Hit();
							}
							return true;

						}

						if (pPosOld->x >= posModel.x + maxModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//右にめり込んだ場合


							if (type == TYPE_PLAYER)
							{//敵の場合
							 //敵のヒット処理
								pObj->Hit();

							}

							return true;
						}

						if (pPosOld->z <= posModel.z + minModel.z
							&& pPos->z > posModel.z + minModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//手前にめり込んだ場合

							if (type == TYPE_PLAYER)
							{//敵の場合

							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->z >= posModel.z + maxModel.z
							&& pPos->z < posModel.z + maxModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//奥にめり込んだ場合

							if (type == TYPE_PLAYER)
							{//敵の場合
							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y <= posModel.y + minModel.y
							&& pPos->y > posModel.y + minModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//底にめり込んだ場合

							if (type == TYPE_PLAYER)
							{//敵の場合

							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y >= posModel.y + maxModel.y
							&& pPos->y < posModel.y + maxModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//上にめり込んだ場合

							if (type == TYPE_PLAYER)
							{//敵の場合

							 //敵のヒット処理
								pObj->Hit();
							}

							return true;
						}
					}
				}
			}
		}
	}
	return false;
}


bool CBullet::CollisionData(D3DXVECTOR3 pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		//オブジェクトの取得
		CObject *pObj = GetObject(nCntObject);

		if (pObj != NULL)
		{
			//種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_ENEMY || type == TYPE_MODEL)
			{//種類が敵の場合

				D3DXVECTOR3 posEne = pObj->GetPosition();

				//当たり判定
				if (pos.x >= posEne.x - 30.0f  && pos.x <= posEne.x + 30.0f
					&&	pos.z >= posEne.z - 30.0f && pos.z <= posEne.z + 30.0f)
				{
					//爆発の生成
					CExplosion::Create(pos, TYPE_EXPLOSION);

					//pObj->Uninit();			//オブジェクトの削除
					//Release();			//自分自身(弾)の破棄

					return TRUE;
				}
			}
		}
	}


	return false;
}

//==============================================================
//コンストラクタ
//==============================================================
CBulletA::CBulletA()
{
	
}

//==============================================================
//デストラクタ
//==============================================================
CBulletA::~CBulletA()
{

}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CBulletA::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexture();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\ball000.png");

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	CBullet::Init();

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CBulletA::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CBulletA::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = GetPosition();

	//エフェクトの生成
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), EFFECT_RADIUS, EFFECT_LIFE);
}

//==============================================================
//弾の描画処理
//==============================================================
void CBulletA::Draw(void)
{
	//オブジェクト2Dの描画処理
	CBullet::Draw();
}

//==============================================================
//コンストラクタ
//==============================================================
CBulletB::CBulletB()
{

}

//==============================================================
//デストラクタ
//==============================================================
CBulletB::~CBulletB()
{

}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CBulletB::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexture();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\bullet000.png");

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	CBullet::Init();

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CBulletB::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CBulletB::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = GetPosition();

	//エフェクトの生成
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), EFFECT_RADIUS, EFFECT_LIFE);
}

//==============================================================
//弾の描画処理
//==============================================================
void CBulletB::Draw(void)
{
	//オブジェクト2Dの描画処理
	CBullet::Draw();
}

//==============================================================
//コンストラクタ
//==============================================================
CBulletC::CBulletC()
{

}

//==============================================================
//デストラクタ
//==============================================================
CBulletC::~CBulletC()
{

}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CBulletC::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexture();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\ball000.png");

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	CBullet::Init();

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CBulletC::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CBulletC::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = GetPosition();

	//エフェクトの生成
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECT_RADIUS, EFFECT_LIFE);
}

//==============================================================
//弾の描画処理
//==============================================================
void CBulletC::Draw(void)
{
	//オブジェクト2Dの描画処理
	CBullet::Draw();
}