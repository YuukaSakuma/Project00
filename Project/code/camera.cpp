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
#include"player.h"
#include"game.h"

//マクロ定義
#define LENGTH	(800.0f)			//長さ
#define POSVX	(0.0f)				//視点X
#define POSVY	(100.0f)				//視点Y
#define POSVZ	(-100.0f)			//視点Z
#define POSRX	(0.0f)			//注視点X
#define POSRY	(100.0f)			//注視点X
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
	/*m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/
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
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 2200.0f);		//視点の初期化
	m_posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		//注視点の初期化
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向ベクトルの初期化
	m_rot = D3DXVECTOR3(0.0f, atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z), 1.56f);			//向きの初期化

	SetV();

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
	CPlayer *pPlayer = CGame::GetPlayerModel();			//プレイヤーの情報取得


	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//追従
		Move();	
	}

	//全視点の移動
	//MoveA();

	//視点の移動
	MoveV();

	//注視点の移動
	MoveR();

	pDebugProc->Print("カメラの視点位置 : [%f %f %f] \n", m_posR.x, m_posR.y, m_posR.z);

	pDebugProc->Print("カメラの注視点位置 : [%f %f %f] \n", m_posV.x, m_posV.y, m_posV.z);
}

//==============================================================
//カメラの全移動
//==============================================================
void CCamera::MoveA(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//キーボードの取得

																			//キーが押されたとき
	if (pInputKeyboard->GetPress(DIK_J) == true)
	{//Aキーが押された
		if (pInputKeyboard->GetPress(DIK_I) == true)
		{//左上移動
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.75f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.75f)) * MOVE;
		}
		else if (pInputKeyboard->GetPress(DIK_K) == true)
		{//左下移動
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.25f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.25f)) * MOVE;		
		}
		else
		{//左移動	
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.5f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * MOVE;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_L) == true)
	{//Dキーが押された

		if (pInputKeyboard->GetPress(DIK_I) == true)
		{//右上移動
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.75f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.75f)) * MOVE;	
		}
		else if (pInputKeyboard->GetPress(DIK_K) == true)
		{//右下移動
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.25f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.25f)) * MOVE;
		}
		else
		{//右移動
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.5f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.5f)) * MOVE;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_I) == true)
	{//Wキーが押された
		m_posV.x += -cosf(m_rot.y) * MOVE;
		m_posV.z += -sinf(m_rot.y) * MOVE;
	}
	else if (pInputKeyboard->GetPress(DIK_K) == true)
	{//Sキーが押された
		m_posV.x += cosf(m_rot.y) * MOVE;
		m_posV.z += sinf(m_rot.y) * MOVE;
	}

	SetR();
}

//==============================================================
//カメラの注視点移動
//==============================================================
void CCamera::MoveV(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//キーボードの取得

	if (pInputKeyboard->GetPress(DIK_Z) == true && pInputKeyboard->GetPress(DIK_C) != true)
	{//Zキー入力
		m_rot.y += -D3DX_PI * 0.0154f;
		if (m_rot.y < -D3DX_PI)
		{//角度がΠを超えた場合
			m_rot.y += D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_C) == true && pInputKeyboard->GetPress(DIK_Z) != true)
	{//Cキー入力
		m_rot.y += D3DX_PI * 0.0154f;
	}

	if (pInputKeyboard->GetPress(DIK_Y) == true && pInputKeyboard->GetPress(DIK_N) != true)
	{//Yキー入力
	 //角度の変更
		m_rot.z += -D3DX_PI * 0.0154f;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//角度が限界を超えた場合
			m_rot.z = MIN_CAMERA_ROTZ;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_N) == true && pInputKeyboard->GetPress(DIK_Y) != true)
	{//Nキー入力
	 //角度の変更
		m_rot.z += D3DX_PI * 0.0154f;

		if (m_rot.z > MAX_CAMERA_ROTZ)
		{//角度が限界を超えた場合
			m_rot.z = MAX_CAMERA_ROTZ;
		}
	}

	SetV();
}

//==============================================================
//カメラの視点移動
//==============================================================
void CCamera::MoveR(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//キーボードの取得

	if (pInputKeyboard->GetPress(DIK_Q) == true && pInputKeyboard->GetPress(DIK_E) != true)
	{//Qキー入力
	 //角度の変更
		m_rot.y += D3DX_PI * 0.0154f;
		if (m_rot.y > D3DX_PI)
		{//角度がΠを超えた場合
			m_rot.y += -D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_E) == true && pInputKeyboard->GetPress(DIK_Q) != true)
	{//Eキー入力
	 //角度の変更
		m_rot.y += -D3DX_PI * 0.0154f;

		if (m_rot.y < -D3DX_PI)
		{//角度がΠを超えた場合
			m_rot.y += D3DX_PI * 2;
		}
	}

	if (pInputKeyboard->GetPress(DIK_T) == true && pInputKeyboard->GetPress(DIK_B) != true)
	{//Tキー入力
	 //角度の変更
		m_rot.z += D3DX_PI * 0.0154f;

		if (m_rot.z > MAX_CAMERA_ROTZ)
		{//角度が限界を超えた場合
			m_rot.z = MAX_CAMERA_ROTZ;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_B) == true && pInputKeyboard->GetPress(DIK_T) != true)
	{//Bキー入力
	 //角度の変更
		m_rot.z += -D3DX_PI * 0.0154f;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//角度が限界を超えた場合
			m_rot.z = MIN_CAMERA_ROTZ;
		}
	}

	SetR();
}

//==============================================================
//カメラの設定処理
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
		10.0f,
		40000.0f);

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
//カメラの追従
//==============================================================
void CCamera::Move(void)
{

	CPlayer *pPlayer = CGame::GetPlayerModel();			//プレイヤーの情報取得

	D3DXVECTOR3 posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目標の注視点
	D3DXVECTOR3 posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目標の視点
	D3DXVECTOR3 RDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 注視点の差分
	D3DXVECTOR3 VDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 視点の差分

	//目的の注視点を設定
	//posRDest = D3DXVECTOR3(pos.x - sinf(rot.y) * 30.0f, pos.y + 50.0f + 40.0f , pos.z - cosf(rot.y) * 30.0f);

	m_posRDest.x = pPlayer->GetPosition().x  - sinf(pPlayer->GetRotation().y) * 30.0f;
	m_posRDest.y = pPlayer->GetPosition().y + 200.0f;
	m_posRDest.z = pPlayer->GetPosition().z + cosf(pPlayer->GetRotation().y) * 30.0f;

	//目的の視点を設定
	//posVDest = D3DXVECTOR3(
	//	m_posRDest.x + (sinf(m_rot.z) * cosf(m_rot.y)) * LENGTH,
	//	m_posRDest.y + cosf(m_rot.z) * LENGTH,
	//	m_posRDest.z + (sinf(m_rot.z) * sinf(m_rot.y)) * LENGTH);

	m_posVDest.x = m_posRDest.x + (sinf(GetRotation().z) * cosf(GetRotation().y)) * LENGTH;
	m_posVDest.y = m_posRDest.y + cosf(GetRotation().z)* LENGTH;
	m_posVDest.z = m_posRDest.z + (sinf(GetRotation().z) * sinf(GetRotation().y)) * LENGTH;


	RDiff = D3DXVECTOR3(m_posRDest.x - m_posR.x, m_posRDest.y - m_posR.y, m_posRDest.z - m_posR.z);
	m_posR.x += RDiff.x * 0.2f;
	m_posR.y += RDiff.y * 0.1f;
	m_posR.z += RDiff.z * 0.2f;

	VDiff = D3DXVECTOR3(m_posVDest.x - m_posV.x, m_posVDest.y - m_posV.y, m_posVDest.z - m_posV.z);
	m_posV.x += VDiff.x * 0.2f;
	m_posV.y += VDiff.y * 0.1f;
	m_posV.z += VDiff.z * 0.2f;



	//RDiff = D3DXVECTOR3(posRDest.x - m_posR.x, posRDest.y - m_posR.y, posRDest.z - m_posR.z);
	//m_posR.x += RDiff.x * 0.2f;
	//m_posR.y += RDiff.y * 0.1f;
	//m_posR.z += RDiff.z * 0.2f;

	//VDiff = D3DXVECTOR3(posVDest.x - m_posV.x, posVDest.y - m_posV.y, posVDest.z - m_posV.z);
	//m_posV.x += VDiff.x * 0.2f;
	//m_posV.y += VDiff.y * 0.1f;
	//m_posV.z += VDiff.z * 0.2f;

	//RDiff = m_posRDest - m_posR;
	//VDiff = m_posVDest - m_posV;

	//m_posR += RDiff * 0.4f;
	//m_posV += RDiff * 0.4f;
	 
}

//==============================================================
//投影場所設定
//==============================================================
void CCamera::Setting(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_rot.y = -rot.y + (D3DX_PI * 0.5f);

	//目的の注視点の座標を取得
	m_posR = D3DXVECTOR3(pos.x - sinf(rot.y) * 30.0f, pos.y + 50.0f, pos.z - cosf(rot.y) * 30.0f);

	//目的の視点の座標を獲得
	m_posV = D3DXVECTOR3(
		m_posR.x + (sinf(m_rot.z) * cosf(m_rot.y)) * m_fLength,
		m_posR.y + cosf(m_rot.z) * m_fLength,
		m_posR.z + (sinf(m_rot.z) * sinf(m_rot.y)) * m_fLength);
}

//==============================================================
//カメラの視点設定処理
//==============================================================
void CCamera::SetV(void)
{
	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.y))* LENGTH;
	m_posV.y = m_posR.y + cosf(m_rot.z) * LENGTH;
	m_posV.z = m_posR.z + (sinf(m_rot.z) * sinf(m_rot.y))* LENGTH;
}

//==============================================================
//カメラの注視点設定処理
//==============================================================
void CCamera::SetR(void)
{
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.y))* LENGTH;
	m_posR.y = m_posV.y - cosf(m_rot.z) * LENGTH;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.y))* LENGTH;
}

//==========================================================
// R座標設定
//==========================================================
void CCamera::SetPositionV(D3DXVECTOR3 pos)
{
	m_posV = pos;
	SetV();
}

//==========================================================
// R座標設定
//==========================================================
void CCamera::SetPositionR(D3DXVECTOR3 pos)
{
	m_posR = pos;
	SetR();
}