//==============================================================
//
//オブジェクト3D処理[object3D.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include "object3D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//==============================================================
//コンストラクタ
//==============================================================
CObject3D::CObject3D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	//m_mtxWorld = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nldxTexture = -1;
}

//==============================================================
//コンストラクタ
//==============================================================
CObject3D::~CObject3D()
{

}

//==============================================================
//オブジェクト2Dの生成処理
//==============================================================
CObject3D *CObject3D::Create()
{
	CObject3D *pObject3D = NULL;	//オブジェクト2Dのポインタ

	if (pObject3D == NULL)
	{
		//オブジェクト2Dの生成
		pObject3D = new CObject3D;

		//初期化処理
		pObject3D->Init();
	}
	return pObject3D;
}

//==============================================================
//ポリゴンの初期化処理
//==============================================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	BindTexture(m_nldxTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================
//ポリゴンの終了処理
//==============================================================
void CObject3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//==============================================================
//ポリゴンの更新処理
//==============================================================
void CObject3D::Update(void)
{
	
}

//==============================================================
//ポリゴンの描画処理
//==============================================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	CTexture * pTexture = CManager::Get()->GetTexturet();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;						//計算用マトリックス

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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nldxTexture));
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==============================================================
//オブジェクト3Dのサイズの設定
//==============================================================
void CObject3D::SetSize(float width, float heiget, float vertical)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//SetPosition(m_pos);

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-width, heiget, vertical);
	pVtx[1].pos = D3DXVECTOR3(width, heiget, vertical);
	pVtx[2].pos = D3DXVECTOR3(-width, 0.0f, -vertical);
	pVtx[3].pos = D3DXVECTOR3(width, 0.0f, -vertical);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//高さの取得
//==============================================================
float CObject3D::GetHeight(D3DXVECTOR3 VecPos)
{
	D3DXVECTOR3 vec1, vec2, nor;
	float fHeight;

	//2つのベクトルから法線を求める
	D3DXVec3Cross(&nor, &vec1, &vec2);

	//法線を正規化する
	D3DXVec3Normalize(&nor, &nor);


	if (nor.y != 0.0f)
	{
		fHeight = 0;
	}

	return fHeight;
}