//==============================================================
//
//マネージャ処理[manager.cpp]
//Author:佐久間優香
//
//==============================================================
#include"manager.h"
#include "object2D.h"
#include"bg.h"
#include"multibg.h"
#include"score.h"
#include"block.h"
#include"object3D.h"
#include"polygon.h"
#include"billboard.h"
#include"objectX.h"
#include"texture.h"
#include"renderer.h"
#include"input.h"
#include"light.h"
#include"sound.h"
#include"camera.h"
#include"blockX.h"
#include"player.h"
#include"field.h"
#include"model.h"
#include"title.h"
#include"tutorial.h"
#include"game.h"
#include"result.h"
#include"ranking.h"
#include"fade.h"
#include"Xfile.h"

//静的メンバ変数

CScene *CManager::m_pScene = NULL;
CFade *CManager::m_pFade = NULL;

//CTitle *CScene::m_pTitle = NULL;
//CTutorial *CScene::m_pTutorial = NULL;
//CGame *CScene::m_pGame = NULL;
//CResult *CScene::m_pResult = NULL;
//CRanking *CScene::m_pRanking = NULL;
CManager *CManager::m_pManager = NULL;


//==============================================================
//コンストラクタ
//==============================================================
CScene::CScene()
{
	m_mode = MODE_TITLE;
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CScene::CScene(MODE mode)
{
	m_mode = mode;
}

//==============================================================
//デストラクタ
//==============================================================
CScene::~CScene()
{

}

//==============================================================
// シーンの生成
//==============================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	if (pScene == NULL)
	{
		switch (mode)
		{
		case MODE_TITLE:			//タイトル画面
			pScene = new CTitle;
			break;

		case MODE_TUTORIAL:			//チュートリアル画面
			pScene = new CTutorial;
			break;

		case MODE_GAME:				//ゲーム画面
			pScene = new CGame;
			break;

		case MODE_RESULT:			//リザルト画面
			pScene = new CResult;
			break;

		case MODE_RANKING:			//ランキング画面
			pScene = new CRanking;
			break;
		}
	}

	if (pScene != NULL)
	{// メモリの確保が出来ていたら

	 // モードの設定
		pScene->m_mode = mode;

		// 初期化処理
		pScene->Init();
	}

	return pScene;
}

//==============================================================
// シーンの初期化処理
//==============================================================
HRESULT CScene::Init(void)
{
	
	return S_OK;
}

//==============================================================
// シーンの終了処理
//==============================================================
void CScene::Uninit(void)
{
	
}

//==============================================================
// シーンの更新処理
//==============================================================
void CScene::Update(void)
{
	

}

//==============================================================
// シーンの描画処理
//==============================================================
void CScene::Draw(void)
{

}

//==============================================================
//コンストラクタ
//==============================================================
CManager::CManager()
{
	m_pCamera = NULL;
	m_pDebugProc = NULL;
	m_pFade = NULL;
	m_pInputKeyboard = NULL;
	m_pLight = NULL;
	m_pMaterial = NULL;
	m_pPlayerModel = NULL;
	m_pRenderer = NULL;
	m_pScene = NULL;
	m_pSound = NULL;
	m_pTexture = NULL;
}

//==============================================================
//デストラクタ
//==============================================================
CManager::~CManager()
{ 

}

//==============================================================
//マネージャの初期化処理
//==============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL hWindow)
{
	CNumber * pNum = NULL;

	m_pRenderer = NULL;
	m_pCamera = NULL;
	m_pDebugProc = NULL;
	m_pFade = NULL;
	m_pInputKeyboard = NULL;
	m_pLight = NULL;
	m_pMaterial = NULL;
	m_pPlayerModel = NULL;
	
	m_pScene = NULL;
	m_pSound = NULL;
	m_pTexture = NULL;

	//レンダラーの生成・初期化処理
	if (m_pRenderer == NULL)
	{//使用していないとき	
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{//使用しているとき
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//デバッグ表示の生成
	if (m_pDebugProc == NULL)
	{//メモリが使用されてないとき

		m_pDebugProc = new CDebugProc;
	}

	if (m_pDebugProc != NULL)
	{//メモリが確保されたとき

	 //デバッグ表示の初期化処理
		m_pDebugProc->Init();
	}

	//キーボードの生成・初期化処理
	if (m_pInputKeyboard == NULL)
	{//使用していないとき
		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{//使用しているとき 
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//サウンドの生成・初期化処理
	if (m_pSound == NULL)
	{//使用していないとき
		m_pSound = new CSound;
	}

	if (m_pSound != NULL)
	{//使用しているとき
		if (FAILED(m_pSound->Init(hWnd)))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//サウンドの生成・初期化処理
	if (m_pCamera == NULL)
	{//使用していないとき
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//使用しているとき
		if (FAILED(m_pCamera->Init()))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//サウンドの生成・初期化処理
	if (m_pLight == NULL)
	{//使用していないとき
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//使用しているとき
		if (FAILED(m_pLight->Init()))
		{//初期化処理が失敗した場合
			return -1;
		}
	}

	//サウンドの生成・初期化処理
	if (m_pTexture == NULL)
	{//使用していないとき
		m_pTexture = new CTexture;
	}
	m_pTexture->Load();

	//マテリアルの生成
	if (m_pMaterial == NULL)
	{
		m_pMaterial = new CXFile;
	}

	if (m_pMaterial != NULL)
	{//メモリ確保できてたら

	 //マテリアルの読み込み
		if (FAILED(m_pMaterial->Load()))
		{//読み込みが失敗した場合

			return E_FAIL;
		}
	}

	//モード設定
	SetMode(CScene::MODE_TITLE);

	////サウンドの再生
	//CSound::Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==============================================================
//マネージャの終了処理
//==============================================================
void CManager::Uninit(void)
{
	//全てのテクスチャの破棄
	if (m_pMaterial != NULL)
	{
		//テクスチャの終了処理
		m_pMaterial->Unload();

		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	//全てのテクスチャの破棄
	if (m_pTexture != NULL)
	{
		//テクスチャの終了処理
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}

	//全ての生成
	CObject::ReleseAll();

	////サウンドの停止
	//CSound::Stop();

	//カメラの終了処理
	if (m_pCamera != NULL)
	{//使用していたら	
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//カメラの終了処理
	if (m_pLight != NULL)
	{//使用していたら	
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//サウンドの終了処理
	if (m_pSound != NULL)
	{//使用していたら	
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//デバッグ表示の破棄
	if (m_pDebugProc != NULL)
	{
		//デバッグ表示の終了処理
		m_pDebugProc->Uninit();

		//メモリ開放
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//レンダラーの終了処理
	if (m_pRenderer != NULL)
	{//使用していたら	
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//キーボードの終了処理
	if (m_pRenderer != NULL)
	{//使用していたら
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
}

//==============================================================
//マネージャの更新処理
//==============================================================
void CManager::Update(void)
{
	//キーボードの更新処理
	m_pInputKeyboard->Update();
	m_pCamera->Update();

	//デバッグ表示の更新処理
	m_pDebugProc->Update();

	m_pLight->Update();

	//マップの再生成
	CManager::ResetMap();

	//レンダラーの更新処理
	m_pRenderer->Update();
}

//==============================================================
//マネージャの描画処理
//==============================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}

//==============================================================
// モードの設定
//==============================================================
void CManager::SetMode(CScene::MODE mode)
{
	Get()->m_pSound->Stop();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		//delete m_pScene;
		m_pScene = NULL;
	}

	//すべて破棄する
	CObject::ReleseAll();

	m_pFade = NULL;

	//サウンドの生成・初期化処理
	if (Get()->m_pTexture == NULL)
	{//使用していないとき
		Get()->m_pTexture = new CTexture;

		if (Get()->m_pTexture != NULL)
		{
			Get()->m_pTexture->Load();
		}
	}

	// 新しいモードの生成
	m_pScene = CScene::Create(mode);
	m_pScene->SetMode(mode);


	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(mode);
	}

	// フェードの生成
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(mode);
	}
}

//==============================================================
// モードの取得
//==============================================================
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}

//==============================================================
//生成処理
//==============================================================
void CManager::CreateAll(void)
{
	////スコアの生成
	//CScore::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));
}

//==============================================================
//リセット
//==============================================================
void CManager::ResetMap(void)
{
	////リセット
	//if (m_pInputKeyboard->GetPress(DIK_F2) == true)
	//{//F2を押したとき

	//	//マップのオブジェクトのリセット
	//	CObject::ResetMapAll();

	//	//オブジェクトの生成
	//	CManager::CreateAll();
	//}
}

//==============================================================
//レンダラーのデバイスの取得
//==============================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//==============================================================
//キーボードのデバイスの取得
//==============================================================
CInputKeyboard *CManager::GetInputKeybard(void)
{
	return m_pInputKeyboard;
}

//==============================================================
//プレイヤーのデバイスの取得
//==============================================================
CPlayer *CManager::GetPlayerModel(void)
{
	return m_pPlayerModel;
}

//==============================================================
//カメラの取得
//==============================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//==============================================================
//テクスチャの取得
//==============================================================
CTexture * CManager::GetTexturet(void)
{
	return m_pTexture;
}

//===================================================
// デバッグ表示の取得
//===================================================
CDebugProc *CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//===================================================
// デバッグ表示の取得
//===================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//===================================================
// デバッグ表示の取得
//===================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//===================================================
// デバッグ表示の取得
//===================================================
CManager *CManager::Get(void)
{
	if (m_pManager == NULL)
	{
		return m_pManager = new CManager;
	}
	else
	{
		return m_pManager;
	}

}

//===================================================
// デバッグ表示の取得
//===================================================
HRESULT CManager::Release(void)
{
	if (m_pManager != NULL)
	{//使用していたら

	 //レンダラーの終了処理
		m_pManager->Uninit();

		delete m_pManager;
		m_pManager = NULL;
	}

	return S_OK;

}