//==============================================================
//
//弾処理[player.cpp]
//Author:佐久間優香
//
//==============================================================
#include"coa.h"
#include"manager.h"
#include"explosion.h"
#include"model.h"
#include"particle.h"
#include"Xfile.h"

//マクロ定義
#define LIFE				(50)			//寿命
//==============================================================
//コンストラクタ
//==============================================================
CCOa::CCOa()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_type = CObject::TYPE_COA;
	m_nLife = LIFE;								//寿命
	m_nldxTexture = -1;
}

//==============================================================
//デストラクタ
//==============================================================
CCOa::~CCOa()
{

}

//==============================================================
//弾の生成処理
//==============================================================
CCOa *CCOa::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, COA type)
{
	CCOa *pCoa = nullptr;

	if (pCoa == nullptr)
	{
		pCoa = new CCOa;

		pCoa->SetPosition(pos);

		//pCoa->SetRotation(rot);

		pCoa->SetCoaType(type);

		//初期化処理
		pCoa->Init();
	}

	return pCoa;
}

//==============================================================
//弾の初期化処理
//==============================================================
HRESULT CCOa::Init(void)
{
	CXFile *pXFile = CManager::Get()->GetModelFile();

	switch (m_CoaType)
	{
	case TYPE_COA_0:
		m_nldxTexture = pXFile->Regist("data\\MODEL\\coa0.x");

		break;

	case TYPE_COA_1:
		m_nldxTexture = pXFile->Regist("data\\MODEL\\coa1.x");
		break;
	}
	CObjectX::BindMaterial(m_nldxTexture);

	//オブジェクトXの初期化処理
	CObjectX::Init();

	CObjectX::SetPosition(m_pos);

	//種類の設定
	CObject::SetType(CObject::TYPE_COA);

	return S_OK;
}

//==============================================================
//弾の終了処理
//==============================================================
void CCOa::Uninit(void)
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();
}

//==============================================================
//弾の更新処理
//==============================================================
void CCOa::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	SetState();

	pDebugProc->Print("コアの体力 : [%d] \n", m_nLife);

	//オブジェクトXの更新処理
	CObjectX::Update();
}

//==============================================================
//弾の描画処理
//==============================================================
void CCOa::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}

//==============================================================
//状態設定
//==============================================================
void CCOa::SetState(void)
{

}

//==============================================================
//プレイヤーモデルのヒット処理
//==============================================================
void CCOa::Hit(void)
{
	m_nLife--;

	if (m_nLife > 0)
	{

		//m_nCntDamage = 5;
	}
	else if (m_nLife <= 0)
	{
		//パーティクル生成
		CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), CObject::TYPE_COA, 30, 40);

		////終了処理
		Uninit();
	}
}