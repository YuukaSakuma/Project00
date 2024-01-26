//==============================================================
//
//爆発処理[explosion.cpp]
//Author:佐久間優香
//
//==============================================================
#include"renderer.h"
#include"tutorial.h"
#include"input.h"
#include"player.h"
#include"manager.h"
#include"object2D.h"
#include"fade.h"


//静的メンバ変数
CPlayer *CTutorial::m_pPlayerModel = NULL;	//プレイヤーの情報
bool CTutorial::m_bReset = true;					//リセットしたかどうか

//==============================================================
//コンストラクタ
//==============================================================
CTutorial::CTutorial()
{

}

//==============================================================
//デストラクタ
//==============================================================
CTutorial::~CTutorial()
{

}

//==============================================================
//タイトル画面の初期化処理
//==============================================================
HRESULT CTutorial::Init(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	//オブジェクト2Dの生成
	CObject2D *pObject2D = CObject2D::Create();

	pObject2D->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\tutrial000.png"));
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pObject2D->SetVtx(0.0f, 0.0f);

	return S_OK;
}

//==============================================================
//タイトル画面の終了処理
//==============================================================
void CTutorial::Uninit(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Stop();
	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//タイトル画面の更新処理
//==============================================================
void CTutorial::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//キーボードの情報取得

	CSound *pSound = CManager::Get()->GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true )
	{//ENTERキー押したら

		pSound->Play(pSound->SOUND_LABEL_SE_PICK);

	 //チュートリアル画面
		CManager::Get()->GetFade()->Set(CScene::MODE_GAME);
		
		
	}

	CScene::Update();

	pDebugProc->Print("\nチュートリアル\n");
}

//==============================================================
//タイトル画面の描画処理
//==============================================================
void CTutorial::Draw(void)
{

}