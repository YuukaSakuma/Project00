//==============================================================
//
//オブジェクトX処理[objectX.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include "objectX.h"
#include"input.h"
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include<string.h>
#include"object.h"
#include"material.h"
#include"game.h"
#include"player.h"

//==============================================================
//コンストラクタ
//==============================================================
CObjectX::CObjectX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_type = CObject::TYPE_NONE;		//種類
	m_nIdxModel = -1;

	m_pMesh = NULL;				//メッシュ（頂点情報）へのポインタ
	m_pBuffMat = NULL;			//マテリアルへのポインタ
	m_dwNumMat = 0;					//マテリアルの数

	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);	//頂点数の最小値
	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);	//頂点数の最大値

	m_matColor.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//マテリアルデータへのポインタ
	m_matColor.MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//マテリアルデータへのポインタ
	m_matColor.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//マテリアルデータへのポインタ
	m_matColor.MatD3D.Power = 5.0f;
	m_matColor.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

}

//==============================================================
//デストラクタ
//==============================================================
CObjectX::~CObjectX()
{

}

//==============================================================
//オブジェクトXのの生成処理
//==============================================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pObjectX = NULL;

	if (pObjectX == NULL)
	{
		//オブジェクト2Dの生成
		pObjectX = new CObjectX;

		//初期化処理
		pObjectX->Init();
	}

	return pObjectX;
}

//==============================================================
//オブジェクトXの初期化処理
//==============================================================
HRESULT CObjectX::Init(void)
{
	m_pos = GetPosition();


	//モデルのサイズ設定
	CObjectX::SetObject();

	return S_OK;
}

//==============================================================
//オブジェクトXの終了処理
//==============================================================
void CObjectX::Uninit(void)
{
	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//オブジェクトXの更新処理
//==============================================================
void CObjectX::Update(void)
{
	
	
}

//==============================================================
//オブジェクトXの描画処理
//==============================================================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//デバイスの取得
	CMaterial *pMaterial = CManager::Get()->GetMaterial();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pMaterial->GetMatAddress(m_nIdxModel)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pMaterial->GetNumMatAddress(m_nIdxModel); nCntMat++)
	{
		switch (m_state)
		{
		case STATE_DAMAGE:		//ダメージ状態

								//マテリアルの設定
			pDevice->SetMaterial(&m_matColor.MatD3D);

			break;

		default:

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			break;
		}

		//テクスチャの設定
		pDevice->SetTexture(0, pMaterial->GetTexAddress(m_nIdxModel, nCntMat));

		//モデル（パーツ）の描画
		pMaterial->GetMeshAddress(m_nIdxModel)->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//==============================================================
//マテリアル情報割り当て処理
//==============================================================
void CObjectX::BindMaterial(int nIdx)
{
	m_nIdxModel = nIdx;
}

//==============================================================
//オブジェクトXの/テクスチャの割り当て
//==============================================================
void CObjectX::BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat)
{
	//m_pMesh = pMesh;			//メッシュ
	//m_pBuffMat = pBuffMat;		//マテリアル
	//m_dwNumMat = dwNumMat;

	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	//D3DXMATERIAL *pMat;									//マテリアルデータへのポインタ

	//if (m_apTexture == NULL)
	//{
	//	m_apTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	//}

	////マテリアル情報に対するポインタを取得
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	//{
	//	m_apTexture[nCntMat] = NULL;

	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		//テクスチャの読み込み
	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_apTexture[nCntMat]);
	//	}
	//}

	////モデルの設定処理
	//CObjectX::SetObject();
}

//==============================================================
//モデルとの当たり判定
//==============================================================
void CObjectX::SetObject(void)
{
	CMaterial *pMaterial = CManager::Get()->GetMaterial();

	int nNumVtx;					//頂点数
	DWORD dwSizeFVF;				//頂点フォーマットのサイズ
	BYTE *pVtxBuff;					//頂点バッファへのポインタ

									//頂点数を取得
	nNumVtx = pMaterial->GetMeshAddress(m_nIdxModel)->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(pMaterial->GetMeshAddress(m_nIdxModel)->GetFVF());

	//頂点バッファをロック
	pMaterial->GetMeshAddress(m_nIdxModel)->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//頂点座標の代入

		//全ての頂点を比較してモデルの最大値を抜き出す
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		else if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		else if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}

		//全ての頂点を比較してモデルの最小値を抜き出す
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		else if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		else if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;								//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	pMaterial->GetMeshAddress(m_nIdxModel)->UnlockVertexBuffer();
}

//==============================================================
//モデルとの当たり判定
//==============================================================
bool CObjectX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max)
{

	CPlayer *pPlayer = CGame::GetPlayerModel();			//プレイヤーの情報取得
	bool bLand = false;

	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		//オブジェクトを取得
		CObject *pObj = GetObject(nCntModel);

		if (pObj != NULL)
		{//メモリが使用されているとき

		 //種類を取得
			CObject::TYPE type = pObj->GetType();

			if (type == pObj->TYPE_MODEL || type == TYPE_ITEM)
			{//種類がモデルの場合

			 //モデルの位置取得
				D3DXVECTOR3 posModel = pObj->GetPosition();
				D3DXVECTOR3 minModel = pObj->GetSizeMin();
				D3DXVECTOR3 maxModel = pObj->GetSizeMax();

				if (pPos->y + Max.y > posModel.y + minModel.y
					&& pPos->y < posModel.y + maxModel.y)
				{
					if (pPosOld->x - Min.z <= posModel.x + minModel.x
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//左にめり込んだ場合
						if (type == pObj->TYPE_MODEL)
						{
							pPos->x = posModel.x + minModel.x + Min.z;		//ブロックの左に立たせる
							pMove->x = 0.0f;
						}
						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->x + Min.z >= posModel.x + maxModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//右にめり込んだ場合
						if (type == pObj->TYPE_MODEL)
						{
							pPos->x = posModel.x + maxModel.x - Min.z;		//ブロックの右に立たせる
							pMove->x = 0.0f;

						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->z - Min.z <= posModel.z + minModel.z
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x)
					{//手前にめり込んだ場合
						if (type == pObj->TYPE_MODEL)
						{
							pPos->z = posModel.z + minModel.z + Min.z;		//ブロックの手前に立たせる
							pMove->z = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->z + Min.z >= posModel.z + maxModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x)
					{//奥にめり込んだ場合
						if (type == pObj->TYPE_MODEL)
						{
							pPos->z = posModel.z + maxModel.z - Min.z;		//ブロックの奥に立たせる
							pMove->z = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->y + Max.y <= posModel.y + minModel.y
						&& pPos->y + Max.y > posModel.y + minModel.y
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//底にめり込んだ場合
						if (type == pObj->TYPE_MODEL)
						{
							pPos->y = posModel.y + minModel.y - Max.y;		//ブロックの底下に立たせる
							pMove->y = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->y >= posModel.y + maxModel.y
						&& pPos->y < posModel.y + maxModel.y
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//上にめり込んだ場合
						if (type == pObj->TYPE_MODEL)
						{
							pPos->y = posModel.y + maxModel.y;		//ブロックの上に立たせる
							pMove->y = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}

						bLand = true;
					}
				}
			}
		}
	}

	return bLand;
}