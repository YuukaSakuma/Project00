//==============================================================
//
//オブジェクト2D処理[object2D.cpp]
//Author:佐久間優香
//
//==============================================================
#include"object2D.h"
#include"manager.h"
#include"bg.h"

#define WIDTH (50.0f) //横幅
#define HEIGHT (80.0f) //縦幅

//==============================================================
//オブジェクト2Dのコンストラクタ
//==============================================================
CObject2D::CObject2D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================
//オブジェクト2Dのデストラクタ
//==============================================================
CObject2D::~CObject2D()
{

}

//==============================================================
//オブジェクト2Dの生成処理
//==============================================================
CObject2D *CObject2D::Create()
{
	CObject2D *pObject2D = NULL;	//オブジェクト2Dのポインタ

	if (pObject2D == NULL)
	{
		//オブジェクト2Dの生成
		pObject2D = new CObject2D;

		//初期化処理
		pObject2D->Init();
	}
	return pObject2D;
}

//==============================================================
//オブジェクト2Dの初期化処理
//==============================================================
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	VERTEX_2D *pVtx;									//頂点情報へのポインタ

	CTexture * pTexture = CManager::Get()->GetTexturet();

	BindTexture(m_nldx);

	//種類の設定
	SetType(m_type);

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{//失敗した場合
		return E_FAIL;
	}

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.75f) * WIDTH;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.75f) * HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.75f) * WIDTH;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.75f) * HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.25f) * WIDTH;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.25f) * HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.25f) * WIDTH;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.25f) * HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	switch (m_type)
	{
	case TYPE_NONE:

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		break;

	case TYPE_PLAYER:
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

		break;

	case TYPE_EXPLOSION:

		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		break;

	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//SetVtx(0.0f, 0.0f);

	return S_OK;
}

//==============================================================
//オブジェクト2Dの終了処理
//==============================================================
void CObject2D::Uninit(void)
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
//オブジェクト2Dの更新処理
//==============================================================
void CObject2D::Update(void)
{
	//SetVtx(0.0f, 0.0f);
}

//==============================================================
//オブジェクト2Dの描画処理
//==============================================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	CTexture * pTexture = CManager::Get()->GetTexturet();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nldx));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==============================================================
//オブジェクト2Dの位置設定処理
//==============================================================
void CObject2D::SetVtx(int nPattern, TYPE type)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (type)
	{
	case TYPE_NONE:
		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		break;

	case TYPE_PLAYER:
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((nPattern % 5) * 0.2f, (nPattern / 5) * 0.5f);
		pVtx[1].tex = D3DXVECTOR2((nPattern % 5) * 0.2f + 0.2f, (nPattern / 5) * 0.5f);
		pVtx[2].tex = D3DXVECTOR2((nPattern % 5) * 0.2f, (nPattern / 5) * 0.5f + 0.5f);
		pVtx[3].tex = D3DXVECTOR2((nPattern % 5) * 0.2f + 0.2f, (nPattern / 5) * 0.5f + 0.5f);

		break;

	case TYPE_EXPLOSION:
		//テクスチャの座標の設定
		pVtx[0].tex = D3DXVECTOR2(nPattern * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nPattern * 0.125f + 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nPattern * 0.125f + 0.125f, 1.0f);

		break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//テクスチャ座標の設定処理
//==============================================================
void CObject2D::SetVtx(int nPatternAnim, float nDigitX)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * nDigitX, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * nDigitX + nDigitX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * nDigitX, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * nDigitX + nDigitX, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//オブジェクト2Dの位置設定処理
//==============================================================
void CObject2D::SetVtx(float fTexV, float fTexU)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	//テクスチャの座標の設定
	pVtx[0].tex = D3DXVECTOR2(fTexU, fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV);
	pVtx[2].tex = D3DXVECTOR2(fTexU, fTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV + 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//ブロックの頂点座標
//==============================================================
void CObject2D::SetVtxBlock(float width, float heiget)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	SetPosition(m_pos);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + heiget, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y + heiget, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//プレイヤーの頂点座標
//==============================================================
void CObject2D::SetVtxPlayer(float width, float heiget)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	SetPosition(m_pos);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y - heiget, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y - heiget, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//アイテムの頂点座標
//==============================================================
void CObject2D::SetVtxItem(float width, float heiget)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	SetPosition(m_pos);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y - width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + heiget, m_pos.y - width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y + heiget, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + heiget, m_pos.y + heiget, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================
//オブジェクト2Dの位置設定処理
//==============================================================
void CObject2D::SetSize(float width, float heiget)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//SetPosition(m_pos);

	m_fWidth = width;
	m_fHeight = heiget;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.75f) * width;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.75f) * heiget;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.75f) * width;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.75f) * heiget;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.25f) * width;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.25f) * heiget;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.25f) * width;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.25f) * heiget;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//半径の更新
//================================================================
void CObject2D::SetRadius(float m_fRadius)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);   

	 //頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fRadius, m_pos.y - m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fRadius, m_pos.y - m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fRadius, m_pos.y + m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fRadius, m_pos.y + m_fRadius, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================
//色の設定
//================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;     //頂点情報へのポインタ

						  //頂点バッファをロックし、頂点情報へポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}