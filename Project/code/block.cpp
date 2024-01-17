//==============================================================
//
//ブロック処理[block.cpp]
//Author:佐久間優香
//
//==============================================================
#include"block.h"
#include"manager.h"

//マクロ定義
#define WIDTH				(50.0f)			//横幅
#define HEIGHT				(50.0f)			//縦幅
#define EFFECT_LIFE			(15)			//エフェクトの寿命
#define PARTICLE_LIFE		(50)			//パーティクルの寿命
#define EFFECT_RADIUS		(20.0f)			//エフェクトの半径
#define PARTICLE_RADIUS		(50.0f)			//パーティクルの半径
#define ADD_SCORE			(1111)			//スコア

//静的メンバ変数
LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;				//テクスチャへのポインタ

float CBlock::m_fWidth = 0.0f;
float CBlock::m_fHeight = 0.0f;

//==============================================================
//コンストラクタ
//==============================================================
CBlock::CBlock()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_fWidth = WIDTH;
	m_fHeight = HEIGHT;
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CBlock::CBlock(TYPE type, D3DXVECTOR3 pos)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	m_fWidth = WIDTH;
	m_fHeight = HEIGHT;

	//位置の設定
	CBlock::SetPosition(pos);

	//種類の設定
	SetType(type);
}

//==============================================================
//デストラクタ
//==============================================================
CBlock::~CBlock()
{
	 
}

//==============================================================
//ブロックの生成処理
//==============================================================
CBlock *CBlock::Create(TYPE type, D3DXVECTOR3 pos)
{
	CBlock *pBullet = NULL;

	if (pBullet == NULL)
	{
		//オブジェクト2Dの生成
		pBullet = new CBlock(type,pos);

		//初期化処理
		pBullet->Init();
	}

	return pBullet;
}

//==============================================================
//ブロックの初期化処理
//==============================================================
HRESULT CBlock::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\block000.png");

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	//種類の設定
	SetType(TYPE_BLOCK);

	//サイズの設定
	SetVtxBlock(m_fWidth, m_fHeight);

	m_fWidth = WIDTH;
	m_fHeight = HEIGHT;

	return S_OK;
}

//==============================================================
//ブロックの終了処理
//==============================================================
void CBlock::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//==============================================================
//ブロックの更新処理
//==============================================================
void CBlock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//位置の設定
	SetPosition(pos);

	////オブジェクト2Dの位置設定処理
	//SetSize(50.0f, 50.0f);

	//オブジェクト2Dの更新処理
	CObject2D::Update();
}

//==============================================================
//ブロックの描画処理
//==============================================================
void CBlock::Draw(void)
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//==============================================================
//ブロックの当たり判定
//==============================================================
bool CBlock::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECT; nCntBlock++)
	{
		CObject *pObj;

		//オブジェクトを取得
		pObj = CObject::GetObject(nCntBlock);

		if (pObj != NULL)
		{
			CObject::TYPE type;

			//種類を取得
			type = pObj->GetType();

			if (type == pObj->TYPE_BLOCK)
			{//種類が敵の場合

				D3DXVECTOR3 posBlock = pObj->GetPosition();

				if (pPosOld->y <= posBlock.y 
					&& pPos->y > posBlock.y 
					&& pPos->x + fWidth > posBlock.x 
					&& pPos->x - fWidth < posBlock.x + m_fWidth)
				{//ブロックの上にめり込んだ
					pPos->y = posBlock.y;
					pMove->y = 0.0f;

					//着地した
					return true;
				}

				if (pPosOld->y - fHeight >= posBlock.y + m_fHeight 
					&& pPos->y - fHeight < posBlock.y + m_fHeight 
					&&pPos->x + fWidth > posBlock.x 
					&& pPos->x - fWidth < posBlock.x + m_fWidth)
				{//ブロックの下にめり込んだ
					pPos->y = posBlock.y + m_fHeight + fHeight;
					pMove->y = 0.0f;

					return false;
				}

				if (pPosOld->x + fWidth <= posBlock.x 
					&& pPos->x + fWidth > posBlock.x 
					&& pPos->y > posBlock.y 
					&& pPos->y - fHeight < posBlock.y + m_fHeight)
				{//ブロックの左にめり込んだ
					pPos->x = posBlock.x - fWidth;
					pMove->x = 0.0f;

					return false;
				}

				if (pPosOld->x - fWidth >= posBlock.x + m_fWidth 
					&& pPos->x - fWidth < posBlock.x + m_fWidth 
					&& pPos->y > posBlock.y 
					&& pPos->y - fHeight < posBlock.y + m_fHeight)
				{//ブロックの右にめり込んだ
					pPos->x = posBlock.x + m_fWidth + fWidth;
					pMove->x = 0.0f;
					return false;
				}
			}
		}
	}
	return false;
}