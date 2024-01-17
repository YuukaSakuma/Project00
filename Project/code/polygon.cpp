//==============================================================
//
//ポリゴン処理[polygon.cpp]
//Author:佐久間優香
//
//==============================================================
#include"polygon.h"
#include"manager.h"
#include"texture.h"

#define WIDTH (100.0f) //横幅
#define HEIGHT (0.0f) //高さ
#define VERTICL (100.0f)	//縦幅
//vertical

LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = NULL;				//テクスチャへのポインタ

//==============================================================
//コンストラクタ
//==============================================================
CPolygon::CPolygon()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CPolygon::CPolygon(TYPE type,D3DXVECTOR3 pos)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//オブジェクト2D位置の設定
	CObject3D::SetPosition(pos);

	////エネミー位置の設定
	//CEnemy::SetPosition(pos);

	//種類の設定
	SetType(type);
}

//==============================================================
//デストラクタ
//==============================================================
CPolygon::~CPolygon()
{

}

//==============================================================
//敵のの生成処理
//==============================================================
CPolygon *CPolygon::Create(TYPE type, D3DXVECTOR3 pos)
{
	CPolygon *pPolygon = NULL;

	if (pPolygon == NULL)
	{
		//オブジェクト2Dの生成
		pPolygon = new CPolygon(type,pos);

		//初期化処理
		pPolygon->Init();
	}

	return pPolygon;
}

//==============================================================
//敵の初期化処理
//==============================================================
HRESULT CPolygon::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	//オブジェクト2Dの初期化処理
	CObject3D::Init(); 

	//テクスチャの割り当て
	BindTexture(m_nldxTexture);

	//種類の設定
	CObject::SetType(TYPE_NONE);

	//サイズ設定
	SetSize(WIDTH, HEIGHT, VERTICL);

	return S_OK;
}

//==============================================================
//敵の終了処理
//==============================================================
void CPolygon::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject3D::Uninit();
}

//==============================================================
//敵の更新処理
//==============================================================
void CPolygon::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//位置の設定
	SetPosition(pos);

	//サイズ設定
	SetSize(WIDTH, HEIGHT, VERTICL);

	//オブジェクト2Dの更新処理 
	CObject3D::Update();
}

//==============================================================
//敵の描画処理
//==============================================================
void CPolygon::Draw(void)
{
	//オブジェクト2Dの描画処理
	CObject3D::Draw();
}