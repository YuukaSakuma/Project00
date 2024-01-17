//==============================================================
//
//スコア処理[score.cpp]
//Author:佐久間優香
//
//==============================================================
#include "time.h"
#include "manager.h"
#include "number.h"
#include"object.h"

//==============================================================
//スコアのコンストラクタ
//==============================================================
CTime::CTime()
{
	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		m_apNumber[nCntNum] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_fAnimTime = 0.0f;
	m_nldxTexture = -1;
} 

//==============================================================
//スコアのデストラクタ
//==============================================================
CTime::~CTime()
{

}

//==============================================================
//スコアの生成処理
//==============================================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		//スコアの生成の生成
		pTime = new CTime;

		if (pTime != NULL)
		{
			//値を代入する
			pTime->m_pos = pos;
			
			//初期化処理
			pTime->Init();
		}
	}
	return pTime;
}

//==============================================================
//スコアの初期化処理
//==============================================================
HRESULT CTime::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\number.png");

	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		CNumber *pNum = m_apNumber[nCntNum];

		if (m_apNumber[nCntNum] == NULL)
		{
			D3DXVECTOR3 pos = m_pos;
			pos.x += nCntNum * 50.0f;	// 横移動

			//数字の生成
			m_apNumber[nCntNum] = CNumber::Create(pos, 50.0f, 70.0f );

			if (m_apNumber[nCntNum] != NULL)
			{
				//テクスチャの割り当て
				m_apNumber[nCntNum]->GetObject2D()->BindTexture(m_nldxTexture);
			}
		}
	}
	return S_OK;
}

//==============================================================
//スコアの終了処理
//==============================================================
void CTime::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{// 使用していない場合
			m_apNumber[nCntNum]->Uninit();

			delete m_apNumber[nCntNum];

			m_apNumber[nCntNum] = NULL;
		}
	}
}

//==============================================================
//スコアの更新処理
//==============================================================
void CTime::Update(void)
{
	m_fAnimTime++;

	if (m_fAnimTime >= 60)
	{// 60フレーム立った
		m_fAnimTime = 0;	// カウンターリセット
		Add(-1);
	}
}

//==============================================================
//スコアの描画処理
//==============================================================
void CTime::Draw(void)
{

}

//==============================================================
//スコアの設定処理
//==============================================================
void CTime::Set(int nNum)
{
	//値を代入
	m_nNum = nNum;
	m_nSetNum = nNum;

	//桁数を求める
	SetValue();
}

//==============================================================
//スコアの加算処理
//==============================================================
void CTime::Add(int nValue)
{
	//値を追加
	m_nNum += nValue;

	//桁数を求める
	SetValue();
}

//==============================================================
//桁の値を求める処理
//==============================================================
void CTime::SetValue(void)
{
	int aTexU[NUM_TEX] = {};		//格納用

	if (m_nNum < 0)
	{//0以下のとき
		m_nNum = 0;
	}
	else if (m_nNum >= 60 * 100)
	{
		m_nNum = 60 * 100 - 1;
	}

	//タイムを配列に格納
	aTexU[0] = m_nNum / 60 / 10;
	aTexU[1] = m_nNum / 60 - aTexU[0] * 10;
	aTexU[2] = m_nNum % 60 / 10;
	aTexU[3] = m_nNum % 60 - aTexU[2] * 10;

	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{// 使用されている場合
		
			//数字を設定する
			m_apNumber[nCntNum]->SetNumber(aTexU[nCntNum]);
		}
	}
}