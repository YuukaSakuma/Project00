//==============================================================
//
//スコア処理[score.cpp]
//Author:佐久間優香
//
//==============================================================
#include "score.h"
#include "manager.h"
#include "number.h"
#include"object.h"

//マクロ定義　

//静的メンバ変数
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;		//テクスチャ
CNumber *CScore::m_apNumber[NUM_SCORE] = {};
int CScore::m_nNumber = 0;			//スコアの値

//==============================================================
//スコアのコンストラクタ
//==============================================================
CScore::CScore()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_nNumber = 0;								//スコアの値

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore] = 0;
	}
} 

//==============================================================
//スコアのデストラクタ
//==============================================================
CScore::~CScore()
{

}

//==============================================================
//スコアの生成処理
//==============================================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		//スコアの生成の生成
		pScore = new CScore;

		if (pScore != NULL)
		{
			//値を代入する
			pScore->m_pos = pos;
			
			//初期化処理
			pScore->Init();
		}
	}
	return pScore;
}

//==============================================================
//スコアの初期化処理
//==============================================================
HRESULT CScore::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\number.png");

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] == NULL)
		{
			D3DXVECTOR3 pos = m_pos;

			//横にずらす
			pos.x += nCntScore * 60;

			//数字の生成
			m_apNumber[nCntScore] = CNumber::Create(pos, 50.0f, 70.0f );

			if (m_apNumber[nCntScore] != NULL)
			{
				//テクスチャの割り当て
				m_apNumber[nCntScore]->GetObject2D()->BindTexture(m_nldxTexture);

				////種類の設定
				//SetType(TYPE_SCORE);
			}
		}
	}

	//スコアの設定
	CScore::Set(m_nNumber);

	return S_OK;
}

//==============================================================
//スコアの終了処理
//==============================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] != NULL)
		{
			if (m_apNumber[nCntScore] != NULL)
			{// 使用していない場合
				m_apNumber[nCntScore]->Uninit();

				delete m_apNumber[nCntScore];

				m_apNumber[nCntScore] = NULL;
			}
		}
	}
}
//==============================================================
//スコアの更新処理
//==============================================================
void CScore::Update(void)
{

}

//==============================================================
//スコアの描画処理
//==============================================================
void CScore::Draw(void)
{

}

//==============================================================
//スコアの設定処理
//==============================================================
void CScore::Set(int nNum)
{
	//値を代入
	m_nNumber = nNum;

	//桁数を求める
	SetValue();
}

//==============================================================
//スコアの加算処理
//==============================================================
void CScore::Add(int nValue)
{
	//値を追加
	m_nNumber += nValue;

	//桁数を求める
	SetValue();
}

//==============================================================
//スコアの桁の値を求める処理
//==============================================================
void CScore::SetValue(void)
{
	if (m_nNumber < 0)
	{//0以下のとき
		m_nNumber = 0;
	}

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//桁の値を求める
		int nNum = m_nNumber % (int)pow(10, (NUM_SCORE - nCntScore)) / (int)pow(10, (NUM_SCORE - nCntScore) - 1);

		if (m_apNumber[nCntScore] != NULL)
		{// 使用されている場合
		
			//数字を設定する
			m_apNumber[nCntScore]->SetNumber(nNum);
		}
	}
}

//===============================================
// 色設定
//===============================================
void CScore::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用していない場合
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}