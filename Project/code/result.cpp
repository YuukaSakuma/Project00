//==============================================================
//
//爆発処理[explosion.cpp]
//Author:佐久間優香
//
//==============================================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "objectX.h"
#include "fade.h"
#include "score.h"
#include "ranking.h"

//静的メンバ変数
CScore *CResult::m_pScore = NULL;
int CResult::m_nScore = 0;

//==============================================================
//コンストラクタ
//==============================================================
CResult::CResult()
{

}

//==============================================================
//デストラクタ
//==============================================================
CResult::~CResult()
{

}

//==============================================================
//タイトル画面の初期化処理
//==============================================================
HRESULT CResult::Init(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	// ロゴの生成
	CObject2D *p = CObject2D::Create();
	p->BindTexture(CManager::Get()->GetTexturet()->Regist("data\\TEXTURE\\result.png"));
	p->SetPosition(D3DXVECTOR3(600.0f, SCREEN_HEIGHT * 0.15f, 0.0f));
	p->SetSize(400, 150);

	m_pScore = CScore::Create(D3DXVECTOR3(400.0f, 500.0f, 0.0f));
	m_pScore->Set(m_nScore);

	pSound->Play(pSound->SOUND_LABEL_RESULT);

	return S_OK;
}

//==============================================================
//タイトル画面の終了処理
//==============================================================
void CResult::Uninit(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Stop();

	m_nScore = 0;

	// スコア
	if (m_pScore != NULL)
	{
		CRanking::SetScore(m_pScore->Get());
		m_pScore->Uninit();
		delete m_pScore;	// メモリの開放
		m_pScore = NULL;	// 使用していない状態にする
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//タイトル画面の更新処理
//==============================================================
void CResult::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//キーボードの情報取得

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//ENTERキー押したら

	 //チュートリアル画面
		CManager::Get()->GetFade()->Set(MODE_RANKING);
	}
	
	//CScene::Update();

	pDebugProc->Print("\nリザルト\n");
}

//==============================================================
//タイトル画面の描画処理
//==============================================================
void CResult::Draw(void)
{

}