//==============================================================
//
//爆発処理[explosion.cpp]
//Author:佐久間優香
//
//==============================================================
#include "titleTex.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

#define APPEAR_CNT		(60)			//点滅カウント
#define APPEAR_CNT_MIN	(2)				//点滅カウント(Enter押したとき)

//静的メンバ変数
CObject2D *CTitleTex::m_apObject2D[NUM_TITLE_TEX] = {};

//==============================================================
//コンストラクタ
//==============================================================
CTitleTex::CTitleTex()
{
	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//テクスチャの番号
	}

	m_nCntAppear = APPEAR_CNT;			//点滅カウンター
	m_state = STATE_NONE;
	m_bAppear = true;
	m_fAlpha = 1.0f;
}

//==============================================================
//デストラクタ
//==============================================================
CTitleTex::~CTitleTex()
{

}

//==============================================================
//生成処理
//==============================================================
CTitleTex *CTitleTex::Create(void)
{
	CTitleTex *pTitleTex = NULL;

	if (pTitleTex == NULL)
	{//メモリが使用されてなかったら

	 //タイトルテクスチャの生成
		pTitleTex = new CTitleTex;

		//初期化処理
		pTitleTex->Init();

		//種類設定
		pTitleTex->SetType(TYPE_NONE);
	}

	return pTitleTex;
}

//==============================================================
//タイトル画面の初期化処理
//==============================================================
HRESULT CTitleTex::Init(void)
{
	CTexture *pTexture = CManager::Get()->GetTexturet();

	//テクスチャの読み込み
	m_nIdxTexture[0] = pTexture->Regist("data\\TEXTURE\\title_logo00.png");
	m_nIdxTexture[1] = pTexture->Regist("data\\TEXTURE\\pressenter.png");

	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		//初期化処置
		if (m_apObject2D[nCntTex] == NULL)
		{//使用されてないとき

		 //2Dオブジェクト生成
			m_apObject2D[nCntTex] = CObject2D::Create();

			if (m_apObject2D[nCntTex] != NULL)
			{//生成出来たら

			 //大きさ設定
				m_apObject2D[nCntTex]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

				//テクスチャ割り当て
				m_apObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);

				//位置設定
				if (nCntTex == 0)
				{
					m_apObject2D[nCntTex]->SetPosition( D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f));

					m_apObject2D[nCntTex]->SetSize(400.0f, 200.0f);

				}
				else if (nCntTex == 1)
				{
					m_apObject2D[nCntTex]->SetPosition( D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f));
					m_apObject2D[nCntTex]->SetSize(300.0f, 150.0f);
				}
			}
		}
	}

	//種類設定
	CObject::SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==============================================================
//タイトル画面の終了処理
//==============================================================
void CTitleTex::Uninit(void)
{

	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] != NULL)
		{//使用されてるとき

		 //終了処理
			m_apObject2D[nCntTex]->Uninit();
			m_apObject2D[nCntTex] = NULL;
		}
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//タイトル画面の更新処理
//==============================================================
void CTitleTex::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//キーボードの情報取得
	CFade *pFade = CManager::Get()->GetFade();		//フェードの情報取得

	switch (m_state)
	{
	case STATE_NONE:		//通常状態

		if ((m_nCntAppear % APPEAR_CNT) == 0)
		{//一定時間たったら

			m_bAppear = m_bAppear ? false : true;

		}

		if (m_bAppear == true)
		{
			m_fAlpha += 1.0f / APPEAR_CNT;
			m_apObject2D[0]->SetPosition(D3DXVECTOR3(m_apObject2D[0]->GetPosition().x, m_apObject2D[0]->GetPosition().y + 0.1f, m_apObject2D[0]->GetPosition().z));
			m_apObject2D[0]->SetSize(400.0f, 200.0f);
		}
		else if (m_bAppear == false)
		{
			m_fAlpha -= 1.0f / APPEAR_CNT;
			m_apObject2D[0]->SetPosition(D3DXVECTOR3(m_apObject2D[0]->GetPosition().x, m_apObject2D[0]->GetPosition().y - 0.1f, m_apObject2D[0]->GetPosition().z));
			m_apObject2D[0]->SetSize(400.0f, 200.0f);
		}

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{//Enterキーを押したら

			//CSound *pSound = CManager::GetSound();

			//SE再生
			//pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);

			m_state = STATE_APPEAR;
			m_nCntAppear = 0;		//点滅カウンター
		}

		break;

	case STATE_APPEAR:

		if ((m_nCntAppear % APPEAR_CNT_MIN) == 0)
		{//一定時間たったら

			m_bAppear = m_bAppear ? false : true;
		}

		if (m_nCntAppear >= 60)
		{//一定時間たったら

			pFade->Set(CScene::MODE_TUTORIAL);
		}

		break;
	}

	//点滅させる
	if (m_bAppear == true && m_state == STATE_APPEAR)
	{
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
	else if (m_bAppear == false && m_state == STATE_APPEAR)
	{
		m_apObject2D[1]->SetCol( D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	}
	else
	{
		m_apObject2D[1]->SetCol( D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

	}

	m_nCntAppear++;

}

//==============================================================
//タイトル画面の描画処理
//==============================================================
void CTitleTex::Draw(void)
{

}