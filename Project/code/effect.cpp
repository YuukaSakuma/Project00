//==============================================================
//
//エフェクト処理[effect.cpp]
//Author:佐久間優香
//
//==============================================================
#include"manager.h"
#include"effect.h"
#include"texture.h"
#include"renderer.h"

//==============================================================
//コンストラクタ
//==============================================================
CEffect::CEffect()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);		//色
	m_nLife = 0;								//寿命
	m_fRadius = 0.0f;							//半径
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CEffect::CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	m_move = move;			//移動量
	m_col = col;			//色
	m_nLife = nLife;		//寿命
	m_fRadius = fRadius;	//半径

	//位置の設定
	SetPosition(pos);
}

//==============================================================
//デストラクタ
//==============================================================
CEffect::~CEffect()
{

}

//==============================================================
//エフェクトの生成処理
//==============================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	CEffect *pEffect = NULL;

	if (pEffect == NULL)
	{
		//オブジェクト2Dの生成
		pEffect = new CEffect(pos, move, col, fRadius, nLife);

		//初期化処理
		pEffect->Init();
	}

	return pEffect;
}

//==============================================================
//エフェクトの初期化処理
//==============================================================
HRESULT CEffect::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	//オブジェクト2Dの初期化処理
	CBillboard::Init();

	CObject::SetType(TYPE_EFFECT);

	//半径の設定
	//SetRadius(m_fRadius);

	SetSize(m_fRadius, m_fRadius, 0.0f);

	return S_OK;
}

//==============================================================
//エフェクトの終了処理
//==============================================================
void CEffect::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CBillboard::Uninit();
}

//==============================================================
//エフェクトの更新処理
//==============================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//寿命の減算
	m_nLife--;

	//位置を加算
	pos += m_move;
		
	//半径の設定
	//SetRadius(m_fRadius);

	SetSize(m_fRadius, m_fRadius, 0.0f);

	//半径の減算
	m_fRadius -= 1.0f;

	if (m_nLife <= 0)
	{//寿命が無くなったら
		Uninit();
	}
	else
	{
		//位置の設定
		SetPosition(pos);
	}

	//オブジェクト2Dの更新処理d
	CBillboard::Update();
}

//==============================================================
//エフェクトの描画処理
//==============================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//ライティングをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストを無効化する
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//オブジェクト2Dの描画処理
	CBillboard::Draw();

	//Zテストを有効にする 
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//ライティングをオンにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
