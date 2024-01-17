//==============================================================
//
//カメラ処理[camera.cpp]
//Author:佐久間優香
//
//==============================================================
#include "camera.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"playermodel.h"
#include"game.h"

//マクロ定義
#define LENGTH	(2500.0f)			//長さ
#define POSVX	(0.0f)				//視点X
#define POSVY	(0.0f)				//視点Y
#define POSVZ	(0.0f)			//視点Z
#define POSRX	(0.0f)			//注視点X
#define POSRY	(0.0f)			//注視点X
#define POSRZ	(0.0f)				//注視点X
#define VECUX	(0.0f)				//上方向ベクトルX
#define VECUY	(1.0f)				//上方向ベクトルY
#define VECUZ	(0.0f)				//上方向ベクトルZ
#define ROTX	(0.0f)				//向きX
#define ROTY	(1.0f)				//向きY
#define ROTZ	(0.0f)				//向きZ
#define MOVE	(1.0f)				//移動量
#define MOVE1	(0.05f)				//移動量
#define CURVE	(0.0f)				//角度
#define CURVE1	(1.0f)				//角度
#define CURVE2	(0.25f)				//角度
#define CURVE3	(0.5f)				//角度
#define CURVE4	(0.75f)				//角度

//==============================================================
//コンストラクタ
//==============================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================
//コンストラクタ
//==============================================================
CCamera::~CCamera()
{

}

//==============================================================
//カメラの初期化処理
//==============================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(POSVX, POSVY, POSVZ);		//視点の初期化
	m_posR = D3DXVECTOR3(POSRX, POSRY, POSRZ);		//注視点の初期化
	m_vecU = D3DXVECTOR3(VECUX, VECUY, VECUZ);		//上方向ベクトルの初期化
	m_rot = D3DXVECTOR3(1.5f, D3DX_PI * -0.5f, atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z));			//向きの初期化

	m_posV.x = m_posR.x + (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
	m_posV.y = m_posR.y + cosf(m_rot.x) * LENGTH;
	m_posV.z = m_posR.z + (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;

	m_posR.x = m_posV.x - (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
	m_posR.y = m_posV.y - cosf(m_rot.x) * LENGTH;
	m_posR.z = m_posV.z - (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;

	return S_OK;

}

//==============================================================
//カメラの終了処理
//==============================================================
void CCamera::Uninit(void)
{
	
}

//==============================================================
//カメラの更新処理
//==============================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//キーボードの取得
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();			//プレイヤーの情報取得


	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (pPlayer->GetPosition().x <= 69000.0f)
		{
			//追従
			Move();
		}
		/*else if (pPlayer->GetPosition().x > 70000.0f)
		{
			m_posV.y = pPlayer->GetPosition().y + 200.0f + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
			m_posV.x = 70000.0f + sinf(pPlayer->GetRotation().y + D3DX_PI);

			m_posR.y = pPlayer->GetPosition().y + 200.0f + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
			m_posR.x = 70000.0f + sinf(pPlayer->GetRotation().y + D3DX_PI);
		}*/

		
	}

	////キーが押されたとき
	//if (pInputKeyboard->GetPress(DIK_J) == true)
	//{//Aキーが押された
	//	if (pInputKeyboard->GetPress(DIK_I) == true)
	//	{//左上移動
	//		m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (pInputKeyboard->GetPress(DIK_K) == true)
	//	{//左下移動
	//		m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//左移動			
	//		m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//	}
	//}
	//else if (pInputKeyboard->GetPress(DIK_L) == true)
	//{//Dキーが押された

	//	if (pInputKeyboard->GetPress(DIK_I) == true)
	//	{//右上移動
	//		m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//		m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//		m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//		m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (pInputKeyboard->GetPress(DIK_K) == true)
	//	{//右下移動
	//		m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//		m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//		m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//		m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//右移動
	//		m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//		m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//		m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//		m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//	}
	//}
	//else if (pInputKeyboard->GetPress(DIK_I) == true)
	//{//Wキーが押された
	//	m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;

	//}
	//else if (pInputKeyboard->GetPress(DIK_K) == true)
	//{//Sキーが押された
	//	m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//	m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//	m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//	m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//}

	////視点
	//if (pInputKeyboard->GetPress(DIK_Z) == true)
	//{//Zキーが押された
	//	m_rot.y += MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_C) == true)
	//{//Cキーが押された
	//	m_rot.y -= MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_Y) == true)
	//{//Yキーが押された
	//	m_rot.x -= MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_N) == true)
	//{//Nキーが押された
	//	m_rot.x += MOVE1;
	//}

	////注視点
	//if (pInputKeyboard->GetPress(DIK_Q) == true)
	//{//Qキーが押された
	//	m_rot.y += MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_E) == true)
	//{//Eキーが押された
	//	m_rot.y -= MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_T) == true)
	//{//Tキーが押された
	//	m_rot.x += MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_B) == true)
	//{//Bキーが押された
	//	m_rot.x -= MOVE1;
	//}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;

	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//カメラの上下回転の上限
	if (m_rot.x > D3DX_PI * 0.95f)
	{//上
		m_rot.x = D3DX_PI * 0.95f;
	}
	else if (m_rot.x < D3DX_PI * 0.05f)
	{//下
		m_rot.x = D3DX_PI * 0.05f;
	}

	//視点
	if (pInputKeyboard->GetPress(DIK_Z) == true
		|| pInputKeyboard->GetPress(DIK_C) == true
		|| pInputKeyboard->GetPress(DIK_Y) == true
		|| pInputKeyboard->GetPress(DIK_N) == true)
	{
		m_posV.x = m_posR.x + (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
		m_posV.y = m_posR.y + cosf(m_rot.x) * LENGTH;
		m_posV.z = m_posR.z + (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;
	}

	//注視点
	if (pInputKeyboard->GetPress(DIK_Q) == true
		|| pInputKeyboard->GetPress(DIK_E) == true
		|| pInputKeyboard->GetPress(DIK_T) == true
		|| pInputKeyboard->GetPress(DIK_B) == true)
	{
		m_posR.x = m_posV.x - (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
		m_posR.y = m_posV.y - cosf(m_rot.x) * LENGTH;
		m_posR.z = m_posV.z - (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;
	}

	pDebugProc->Print("カメラの視点位置 : [%f %f %f] \n", m_posR.x, m_posR.y, m_posR.z);

	pDebugProc->Print("カメラの注視点位置 : [%f %f %f] \n", m_posV.x, m_posV.y, m_posV.z);
}

//==============================================================
//カメラの描画処理
//==============================================================
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		500.0f,
		10000.0f);

	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//	SCREEN_WIDTH ,
	//	SCREEN_HEIGHT,
	//	100.0f,
	//	10000.0f);

	//プロジェクトマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//==============================================================
//カメラの描画処理
//==============================================================
void CCamera::Move(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();			//プレイヤーの情報取得

	D3DXVECTOR3 VDiff;
	D3DXVECTOR3 RDiff;
	//目的の注視点を設定

	m_posRDest.x = (pPlayer->GetPosition().x + 1000.0f) + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
	m_posRDest.y = (pPlayer->GetPosition().y + 200.0f) + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
	m_posRDest.z = pPlayer->GetPosition().z + cosf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;

	//目的の視点を設定
	m_posVDest.x = pPlayer->GetPosition().x + sinf(GetRotation().y + D3DX_PI) * LENGTH;
	m_posVDest.y = pPlayer->GetPosition().y + sinf(GetRotation().y + D3DX_PI) * LENGTH;
	m_posVDest.z = pPlayer->GetPosition().z + cosf(GetRotation().y + D3DX_PI) * LENGTH;

	RDiff = m_posRDest - m_posR;
	VDiff = m_posVDest - m_posV;

	m_posR += RDiff * 0.4f;
	m_posV += RDiff * 0.4f;
	 
}