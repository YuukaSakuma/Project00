//==============================================================
//
//マルチ背景処理[multibg.cpp]
//Author:佐久間優香
//
//==============================================================
#include "number.h"
#include "manager.h"
#include"object2D.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;				//テクスチャへのポインタ
//==============================================================
//マルチテクスチャのコンストラクタ
//==============================================================
CNumber::CNumber()
{
	m_aObject2D = NULL;

	m_nNumber = 0;
}

//==============================================================
//マルチテクスチャのデストラクタ
//==============================================================
CNumber::~CNumber()
{

}

//==============================================================
//マルチテクスチャの生成処理
//==============================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{//メモリが使用されてなかったら

		//数字の生成
		pNumber = new CNumber;

		//初期化処理
		pNumber->Init(pos, fWidth, fHeight);
	}
	return pNumber;
}

//==============================================================
//数字の初期化処理
//==============================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\number.png");

	if (m_aObject2D == NULL)
	{// 使用されていない場合

		//オブジェクト2Dの生成
		m_aObject2D = CObject2D::Create();

		if (m_aObject2D != NULL)
		{// 使用されている場合

			// 初期化処理
			m_aObject2D->Init();

			//テクスチャ番号の設定
			m_aObject2D->BindTexture(m_nldxTexture);

			// テクスチャ設定
			SetNumber(m_nNumber);

			//位置の設定
			m_aObject2D->SetPosition(pos);

			//サイズの設定
			m_aObject2D->SetSize(fWidth, fHeight);
		}
	}

	return S_OK;
}

//==============================================================
//数字の終了処理
//==============================================================
void CNumber::Uninit(void)
{
	// 終了処理
	m_aObject2D->Uninit();
}
//==============================================================
//数字の更新処理
//==============================================================
void CNumber::Update(void)
{
	// 更新処理
	m_aObject2D->Update();
}

//==============================================================
//数字の描画処理
//==============================================================
void CNumber::Draw(void)
{
	// 描画処理
	m_aObject2D->Draw();	
}

//==============================================================
//数字の取得
//==============================================================
CObject2D * CNumber::GetObject2D(void)
{
	return m_aObject2D;
}

//==============================================================
//数字の設定処理
//==============================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;	// 値を設定

	if (m_nNumber > 10)
	{// 値が限界を超えた場合
		m_nNumber = 9;
	}
	else if (m_nNumber < 0)
	{// 値が最低値を超えた場合
		m_nNumber = 0;
	}

	if (m_aObject2D != NULL)
	{// 使用されている場合

	 // 頂点情報の設定
		m_aObject2D->SetVtx(m_nNumber, 0.1f);
	}
}