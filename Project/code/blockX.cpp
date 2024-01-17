//==============================================================
//
//ブロックモデル処理[blockX.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include"blockX.h"
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include<string.h>
#include"model.h"
#include"modelHierarchy.h"

//==============================================================
//コンストラクタ
//==============================================================
CBlockX::CBlockX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最小値
	m_pMesh = NULL;						
	m_pBuffMat= NULL;				
	m_dwNumMat = NULL;		
	m_mtxWorld = {};
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CBlockX::CBlockX(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置の設定
	m_rot = rot;		//向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//敵の最小値
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_mtxWorld = {};
}

//==============================================================
//デストラクタ
//==============================================================
CBlockX::~CBlockX()
{

}

//==============================================================
//ブロックモデルのの生成処理
//==============================================================
CBlockX *CBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlockX *pBlockX = NULL;

	if (pBlockX == NULL)
	{
		//オブジェクト2Dの生成
		pBlockX = new CBlockX(pos,rot);

		//初期化処理
		pBlockX->Init();

		pBlockX->SetPosition(pos);

		pBlockX->SetType(TYPE_MODEL);
	}

	return pBlockX;
}

//==============================================================
//ブロックモデルの初期化処理
//==============================================================
HRESULT CBlockX::Init(void)
{
	m_apModel[0] = m_apModel[0]->Create(m_pos, m_rot, "data\\MODEL\\block.x");

	//最大値・最小値代入
	for (int nCntPlayer = 0; nCntPlayer < 1; nCntPlayer++)
	{
		//最大値Y
		if (nCntPlayer <= 0 )
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//最大値加算
		}

	//最大値入れ替え
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//最小値Z

		}
		 
		//最小値入れ替え
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//最小値Z

		}
	}

	return S_OK;
}

//==============================================================
//ブロックモデルの終了処理
//==============================================================
void CBlockX::Uninit(void)
{
	CObject::Release();
}

//==============================================================
//ブロックモデルの更新処理
//==============================================================
void CBlockX::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	m_pos = m_apModel[0]->GetPosition();

	m_posOld = m_pos;

	//m_move.x += -10.0f;

	m_pos.x += m_move.x;

	//pDebugProc->Print("\nブロックの位置 (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);

	for (int nCntMat = 0; nCntMat < 1; nCntMat++)
	{
		m_apModel[nCntMat]->SetPosition(m_pos);
		//m_apModel[nCntMat]->SetRotation(m_rot);
	}
}

//==============================================================
//ブロックモデルの描画処理
//==============================================================
void CBlockX::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス

	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < 1; nCntMat++)
	{
		m_apModel[nCntMat]->Draw();
	}
}