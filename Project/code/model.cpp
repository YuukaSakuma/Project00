//==============================================================
//
//オブジェクトX処理[objectX.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include "objectX.h"
#include"input.h"
#include"camera.h"
#include"manager.h"
#include"model.h"
#include"renderer.h"
#include<string.h>
#include"Xfile.h"

LPD3DXMESH CModel::m_pMesh = NULL;						//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CModel::m_pBuffMat = NULL;					//マテリアルへのポインタ
DWORD CModel::m_dwNumMat = NULL;
const char *CModel::m_pFilename = NULL;					//ファイルの名前

//==============================================================
//コンストラクタ
//==============================================================
CModel::CModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CModel::CModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き
	m_type = TYPE_MODEL;
	m_nLife = 1;
	CModel::Load(pFilename);
}

//==============================================================
//デストラクタ
//==============================================================
CModel::~CModel()
{

}

//==============================================================
//Xファイルの読み込み
//==============================================================
HRESULT CModel::Load(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//デバイスの取得

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	return S_OK;
}


//==============================================================
//モデルの生成処理
//==============================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *pFilename)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{//メモリが使用されてなかったら

	 //モデルの生成
		pModel = new CModel(pos, rot, pFilename);
	}

	//ファイル名代入
	m_pFilename = pFilename;

	////Xファイルの情報割り当て
	//pModel->BindXFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	//初期化処理
	pModel->Init();

	return pModel;
}

//==============================================================
//マテリアル・メッシュの破棄
//==============================================================
void CModel::Unload(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//==============================================================
//モデルの初期化処理
//==============================================================
HRESULT CModel::Init(void)
{
	CXFile *pMaterial = CManager::Get()->GetModelFile();

	//モデルの読み込み
	m_nIdxModel = pMaterial->Regist(m_pFilename);

	//マテリアルの割り当て
	CObjectX::BindMaterial(m_nIdxModel);

	SetPosition(m_pos);

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(m_type);


	return S_OK;
}

//==============================================================
//モデルの終了処理
//==============================================================
void CModel::Uninit(void)
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();
}

//==============================================================
//モデルの更新処理
//==============================================================
void CModel::Update(void)
{
	//オブジェクトXの更新処理
	CObjectX::Update();
}

//==============================================================
//モデルの描画処理
//==============================================================
void CModel::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}