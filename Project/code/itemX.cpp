//==============================================================
//
//ブロックモデル処理[blockX.cpp]
//Author:佐久間優香
//
//==============================================================
#include"itemX.h"
#include"game.h"
#include "model.h"
#include "playerModel.h"
#include "material.h"
#include "sound.h"
#include "score.h"

//静的メンバ変数宣言
LPD3DXMESH CItemX::m_pMesh = NULL;						//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CItemX::m_pBuffMat = NULL;					//マテリアルへのポインタ
DWORD CItemX::m_dwNumMat = NULL;

//==============================================================
//コンストラクタ
//==============================================================
CItemX::CItemX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nIdx = -1;				//モデルの番号
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CItemX::CItemX(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き
	m_nIdx = -1;				//モデルの番号
}

//==============================================================
//デストラクタ
//==============================================================
CItemX::~CItemX()
{

}

//==============================================================
//ブロックモデルのの生成処理
//==============================================================
CItemX *CItemX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CItemX *pItemX = NULL;

	if (pItemX == NULL)
	{
		//オブジェクト2Dの生成
		pItemX = new CItemX(pos,rot);

		//初期化処理
		pItemX->Init();

		pItemX->SetPosition(pos);

		pItemX->SetType(TYPE_ITEM);
	}

	return pItemX;
}

//==============================================================
//ブロックモデルの初期化処理
//==============================================================
HRESULT CItemX::Init(void)
{
	CMaterial *pMaterial = CManager::Get()->GetMaterial();

	//モデルの読み込み
	m_nIdx = pMaterial->Regit("data\\MODEL\\coin.x");

	//マテリアルの割り当て
	CObjectX::BindMaterial(m_nIdx);

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//ブロックモデルの終了処理
//==============================================================
void CItemX::Uninit(void)
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();
}

//==============================================================
//ブロックモデルの更新処理
//==============================================================
void CItemX::Update(void)
{
	//オブジェクトXの更新処理
	CObjectX::Update();
}

//==============================================================
//ブロックモデルの描画処理
//==============================================================
void CItemX::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}

//==============================================================
//アイテムのヒット処理
//==============================================================
void CItemX::Hit(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();
	CScore *pScore = CGame::GetScore();
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Play(pSound->SOUND_LABEL_SE_COIN);

	//スコア加算
	pScore->Add(700);

	//終了処理
	CItemX::Uninit();
}