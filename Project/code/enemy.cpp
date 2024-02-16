//==============================================================
//
//敵処理[enemy.cpp]
//Author:佐久間優香
//
//==============================================================
#include "enemy.h"
#include "manager.h"
#include "explosion.h"
#include "billboard.h"
#include "texture.h"
#include "object.h"
#include "modelHierarchy.h"
#include "model.h"
#include "motion.h"
#include "player.h"
#include "game.h"
#include "bullet.h"

//マクロ定義
#define LIFE				(50)			//寿命

//静的メンバ変数
LPD3DXMESH CEnemy::m_pMesh = NULL;						//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;				//マテリアルへのポインタ
DWORD CEnemy::m_dwNumMat = NULL;
int CEnemy::m_nNumAll = 0;			//敵の総数

//敵のモデル
char *CEnemy::m_apFileName[ENEMY_MODEL] =
{
	"data\\MODEL\\enemy\\00_waist.x",
	"data\\MODEL\\enemy\\01_body.x",
	"data\\MODEL\\enemy\\02_head.x",
	"data\\MODEL\\enemy\\03_arm_L.x",
	"data\\MODEL\\enemy\\04_arm_R.x",
	"data\\MODEL\\enemy\\05_foot_L.x",
	"data\\MODEL\\enemy\\06_foot_R.x",
	"data\\MODEL\\enemy\\stick.x",
};

//==============================================================
//コンストラクタ
//==============================================================
CEnemy::CEnemy()
{
	for (int nCntPlayer = 0; nCntPlayer < ENEMY_MODEL; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = nullptr;		//敵(パーツ)へのポインタ
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nLife = LIFE;								//寿命
}

//==============================================================
//デストラクタ
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//生成処理
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		//初期化処理
		pEnemy->Init();

		pEnemy->SetPosition(pos);

		pEnemy->SetRotation(rot);
	}

	return pEnemy;
}

//==============================================================
//初期化処理
//==============================================================
HRESULT CEnemy::Init(void)
{
	//敵の生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < ENEMY_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//モデルのファイル読み込み
	SetModel("data\\TXT\\enemy01.txt");

	m_pMotion = NULL;

	if (m_pMotion == NULL)
	{
		m_pMotion = m_pMotion->Create();

		if (m_pMotion != NULL)
		{
			//モーションの初期化・生成
			m_pMotion->SetModel(&m_apModel[0], 7);
			m_pMotion->Init("data\\TXT\\enemy01.txt", ENEMY_MODEL);
		}
	}

	//最大値・最小値代入
	for (int nCntPlayer = 0; nCntPlayer < ENEMY_MODEL; nCntPlayer++)
	{
		if ((nCntPlayer <= 0 && nCntPlayer <= 2) ||
			(nCntPlayer <= 5 && nCntPlayer <= 6))
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//最大値加算
		}
																//最大値入れ替え
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//最小値Z

		}
	}

	////オブジェクト2Dの初期化処理
	//CObject::Init();

	//種類の設定
	CObject::SetType(CObject::TYPE_ENEMY);

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CEnemy::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_MODEL; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//使用されてるとき

		 //終了処理
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//使用されてるとき

	 //モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CEnemy::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();
	CPlayer *pPlyer = CGame::GetPlayerModel();

		//モーションの更新処理
		m_pMotion->Update();
	
		m_posOld = m_pos;

		m_pos += (pPlyer->GetPosition() - m_pos) * 0.005f;

		//回転量増加(仮)
		//m_rot.y += 0.01f;
	
		SetState();

		pDebugProc->Print("敵の体力 : [%d] \n", m_nLife);
}

//==============================================================
//描画処理
//==============================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < ENEMY_MODEL; nCntMat++)
	{
		m_apModel[nCntMat]->Draw();
	}
}

//==============================================================
//状態設定
//==============================================================
void CEnemy::SetState(void)
{
	CPlayer *pPlayerModel = CGame::GetPlayerModel();

	float fAngle = 0.0f;
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_state)
	{
	case STATE_NONE:

		if (m_nCntAttack >= 50)
		{
			m_state = STATE_ATTACK;
			m_nCntAttack = 0;
		}
		else
		{
			m_nCntAttack++;
		}

		break;

	case STATE_ATTACK:

		//プレイヤーの座標に向けて弾を
		rot = D3DXVECTOR3(pPlayerModel->GetPosition().x - m_pos.x, pPlayerModel->GetPosition().y - m_pos.y, pPlayerModel->GetPosition().z - m_pos.z);

		move = D3DXVECTOR3(-sinf(m_rot.y) * 10.0f, 0.0f, -cosf(m_rot.y) * 10.0f);

		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f * 0.5f, m_pos.z),m_rot, move,CBullet::TYPE_C ,TYPE_ENEMY);
		
		m_state = STATE_NONE;

		break;

	case STATE_DAMAGE:

		m_nCntDamage--;

		if (m_nCntDamage <= 0)
		{
			m_state = STATE_NONE;

			//状態設定
			for (int nCntEnemy = 0; nCntEnemy < ENEMY_MODEL; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//通常状態にする
			}
		}
		break;
	}
}

//==============================================================
//ヒット処理
//==============================================================
void CEnemy::Hit(void)
{
	m_nLife--;

	if (m_nLife > 0)
	{
		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < ENEMY_MODEL; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//ダメージ状態にする
		}

		m_nCntDamage = 5;
	}
	else if (m_nLife <= 0)
	{
		//パーティクル生成
		//CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), TYPE_PLAYER, 30, 40);

		//終了処理
		Uninit();

	}
}

//=============================================================
//モデルの読み込み
//=============================================================
void CEnemy::SetModel(const char * c_FileName)
{
	FILE *pFile;				//ファイルポインタ
	char aString[126];		//文字読み込み
	int nIndex = 0, nParent = 0;	//パーツNo.,親番号
	D3DXVECTOR3 pos, rot;

	//ファイル開く
	pFile = fopen(c_FileName, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]するまでの間

			fscanf(pFile, "%s", &aString[0]);		//文字読み込み
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]が来たら

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]がくるまでの間

				fscanf(pFile, "%s", &aString[0]);		//文字読み込み

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]が来たら

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]がくるまでの間

						fscanf(pFile, "%s", &aString[0]);		//文字読み込み

						if (strcmp(&aString[0], "INDEX") == 0)
						{//パーツNo.

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nIndex);			//パーツNo.読み込み

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//親情報

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nParent);			//親番号読み込み

							if (nParent == -1)
							{//親がいなかったら

								m_apModel[nIndex]->SetParent(NULL);		//NULLを入れる
							}
							else
							{//親がいたら

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//親番号入れる
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//位置情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &pos.x);		//位置読み込み
							fscanf(pFile, "%f", &pos.y);		//位置読み込み
							fscanf(pFile, "%f", &pos.z);		//位置読み込み

							m_apModel[nIndex]->SetPosition(pos);		//位置設定
							m_apModel[nIndex]->SetDefaultPosition(pos);	//初期位置設定

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//向き情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &rot.x);		//向き読み込み
							fscanf(pFile, "%f", &rot.y);		//向き読み込み
							fscanf(pFile, "%f", &rot.z);		//向き読み込み

							m_apModel[nIndex]->SetRotation(rot);		//向き設定
							m_apModel[nIndex]->SetDefaultRotation(rot);	//初期向き設定
						}
					}
				}
			}
		}

		//ファイル閉じる
		fclose(pFile);
	}
}