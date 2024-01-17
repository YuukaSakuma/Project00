//==============================================================
//
//爆発処理[explosion.cpp]
//Author:佐久間優香
//
//==============================================================
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//静的メンバ変数
CObject2D *CPause::m_apObject2D[PAUSE_MAX] = {};
LPDIRECT3DTEXTURE9 CPause::m_pTexture[PAUSE_MAX] = {};		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CPause::CPause()
{
	//変数初期化
	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		m_nIdxTexture[nCntPause] = -1;		//テクスチャの番号
	}

	//m_pause = PAUSE_CONTINUE;		//ポーズメニュー
	m_nSelect = PAUSE_CONTINUE;		//何番目か
}

//==============================================================
//デストラクタ
//==============================================================
CPause::~CPause()
{

}

//==============================================================
//生成処理
//==============================================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;

	if (pPause == NULL)
	{//メモリが使用されてなかったら

	 //ポーズの生成
		pPause = new CPause;

		//初期化処理
		pPause->Init();

		////種類設定
		//pPause->SetType(TYPE_PAUSE);
	}

	return pPause;
}

//==============================================================
//タイトル画面の初期化処理
//==============================================================
HRESULT CPause::Init(void)
{
	CTexture *pTexture = CManager::Get()->GetTexturet();

	//テクスチャの読み込み
	m_nIdxTexture[0] = pTexture->Regist("data\\TEXTURE\\pause00.png");
	m_nIdxTexture[1] = pTexture->Regist("data\\TEXTURE\\pause01.png");
	m_nIdxTexture[2] = pTexture->Regist("data\\TEXTURE\\pause02.png");

	//初期化処置
	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		if (m_apObject2D[nCntPause] == NULL)
		{//使用されてないとき

		 //2Dオブジェクト生成
			m_apObject2D[nCntPause] = CObject2D::Create();

			if (m_apObject2D[nCntPause] != NULL)
			{//生成出来たら

			 //大きさ設定
				//m_apObject2D[nCntPause]->SetSize(WIDTH_MULTI, HEIGHT_MULTI);

				//テクスチャ割り当て
				m_apObject2D[nCntPause]->BindTexture(m_nIdxTexture[nCntPause]);

				////位置設定
				//m_apObject2D[nCntPause]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(pos.x, pos.y + (nCntPause * HEIGHT_MULTI * 2.0f), pos.z), WIDTH_MULTI, HEIGHT_MULTI);

				////種類設定
				//m_apObject2D[nCntPause]->SetType(CObject::TYPE_PAUSE);
			}
		}
	}

	////種類設定
	//CObject::SetType(CObject::TYPE_PAUSE);

	return S_OK;
}

//==============================================================
//タイトル画面の終了処理
//==============================================================
void CPause::Uninit(void)
{
	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		if (m_apObject2D[nCntPause] != NULL)
		{//使用されてるとき

		 //終了処理
			m_apObject2D[nCntPause]->Uninit();
			m_apObject2D[nCntPause] = NULL;
		}
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//タイトル画面の更新処理
//==============================================================
void CPause::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//キーボードの情報取得
	//CGame *pGame = CGame::GetMode();		//ゲームの情報取得
	CFade *pFade = CManager::Get()->GetFade();		//フェードの情報取得
	//CSound *pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{//Pキーが押された

		m_nSelect = PAUSE_CONTINUE;		//ポーズメニューの初期化
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{//Wキーが押された

	 ////BGM再生
		//pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);

		if (m_nSelect >= PAUSE_RETRY)
		{//上へ進む

			m_nSelect--;
		}
		else if (m_nSelect == PAUSE_CONTINUE)
		{//QUITに戻る

			m_nSelect = PAUSE_QUIT;
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{//Sキーが押された

	 ////BGM再生
		//pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);

		if (m_nSelect == PAUSE_QUIT)
		{//CONTINUEに戻る

			m_nSelect = PAUSE_CONTINUE;
		}
		else if (m_nSelect >= PAUSE_CONTINUE)
		{//下へ進む

			m_nSelect++;
		}
	}

	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		if (m_apObject2D[nCntPause] != NULL)
		{
			//色設定
			if (m_nSelect == nCntPause)
			{//選択した画像だったら

				//m_apObject2D[m_nSelect]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			}
			else if (m_nSelect != nCntPause)
			{//選択してない画像だったら

				//m_apObject2D[nCntPause]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

			}
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//決定キー（ENTERキー）が押された

	 ////BGM再生
		//pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

		switch (m_nSelect)
		{
		case PAUSE_CONTINUE:		//コンティニュー

									//ゲーム再開
			//pGame->SetEnablePauseMenu(false);
			break;

		case PAUSE_RETRY:			//リトライ

									//ポーズ解除
			//pGame->SetEnablePauseMenu(false);

			//モード設定(ゲーム画面の最初に移行)
			CManager::Get()->GetFade()->Set(CScene::MODE_GAME);			//フェードアウト
			break;

		case PAUSE_QUIT:			//タイトル

									//ポーズ解除
			//pGame->SetEnablePauseMenu(false);

			//モード設定(タイトル画面に移行)
			//CManager::GetMode() == CScene::MODE_GAME
			CManager::Get()->GetFade()->Set(CScene::MODE_TITLE);
			//pGame->SetMode(CScene::MODE_TITLE);				//フェードアウト
			break;
		}
	}
	//pDebugProc->Print("\nタイトル\n");

}

//==============================================================
//タイトル画面の描画処理
//==============================================================
void CPause::Draw(void)
{

}