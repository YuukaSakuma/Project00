//==============================================================
//
//ビルボード処理[billboard.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include "billboard.h"
#include"manager.h"
#include"texture.h"
#include"renderer.h"

//マクロ定義
#define WIDTH_BILL		(10.0f)		//横幅
#define HEIGHT_BILL		(10.0f)		//高さ
#define VERTICL_BILL	(0.0f)		//縦幅
#define SIZE			(10.0f)		//サイズ
#define SIZE_EXPLOSION	(0.125f)	//爆発のサイズ


//==============================================================
//コンストラクタ
//==============================================================
CBillboard::CBillboard()
{
	m_pVtxBuff = NULL;
	//m_mtxWorld = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================
//デストラクタ
//==============================================================
CBillboard::~CBillboard()
{

}

//==============================================================
//ビルボードの生成処理
//==============================================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard = NULL;

	if (pBillboard == NULL)
	{
		//オブジェクト2Dの生成
		pBillboard = new CBillboard;

		//初期化処理
		pBillboard->Init();	
	}

	return pBillboard;
}

//==============================================================
//ビルボードの初期化処理
//==============================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx;

	CTexture * pTexture = CManager::Get()->GetTexturet();
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SIZE, SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SIZE, SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SIZE, 0.0f, 0.0f);

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
//ビルボードの終了処理
//==============================================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}

//==============================================================
//ビルボードの更新処理
//==============================================================
void CBillboard::Update(void)
{

}

//==============================================================
//ビルボードの描画処理
//==============================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//デバイスの取得
	CTexture *pTexture = CManager::Get()->GetTexturet();		//テクスチャの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;				//ビューマトリックス取得用

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	//ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,												//プリミティブ（ビルボードの数）
		2);												//描画するプリミティブ数
}

//==============================================================
//ビルボードのサイズの設定
//==============================================================
void CBillboard::SetSize(float width, float heiget, float vertical)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//SetPosition(m_pos);

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-width, heiget, vertical);
	pVtx[1].pos = D3DXVECTOR3(width, heiget, vertical);
	pVtx[2].pos = D3DXVECTOR3(-width, -heiget, -vertical);
	pVtx[3].pos = D3DXVECTOR3(width, -heiget, -vertical);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//半径の更新
//================================================================
void CBillboard::SetRadius(float fRadius)
{
	VERTEX_3D * pVtx;     //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//オブジェクト2Dの位置設定処理
//==============================================================
void CBillboard::SetVtx(int nPattern, TYPE type)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (type)
	{
	case TYPE_EXPLOSION:
		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION + SIZE_EXPLOSION, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION + SIZE_EXPLOSION, 1.0f);

		break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}