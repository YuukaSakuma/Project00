//==============================================================
//
//テクスチャ処理[texture.cpp]
//Author:佐久間優香
//
//==============================================================
#include "Xfile.h"
#include "manager.h"
#include "renderer.h"

//静的メンバ変数宣言
int CXFile::m_nNumAll = -1;
const char *CXFile::m_apFilename[MAX_TEX] = {};
CXFile::Material CXFile::m_Material[MAX_TEX] = {};			//マテリアルの情報

//==============================================================
//コンストラクタ
//==============================================================
CXFile::CXFile()
{
	//マテリアル初期化
	for (int nCntModel = 0; nCntModel < MAX_TEX; nCntModel++)
	{
		m_Material[nCntModel].pBuffMat = NULL;		//マテリアルへのポインタ
		m_Material[nCntModel].pMesh = NULL;			//メッシュへのポインタ
		m_Material[nCntModel].dwNumMat = NULL;		//マテリアルの数
		m_Material[nCntModel].pTexture = NULL;		//テクスチャ
	}
}

//==============================================================
//デストラクタ
//==============================================================
CXFile::~CXFile()
{

}

//==============================================================
//マテリアル読み込み処理
//==============================================================
HRESULT CXFile::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//デバイスの取得

	for (int nCntModel = 0; nCntModel < TEX_MAX; nCntModel++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFilename[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Material[nCntModel].pBuffMat,
			NULL,
			&m_Material[nCntModel].dwNumMat,
			&m_Material[nCntModel].pMesh);

		D3DXMATERIAL *pMat;		//マテリアルへのポインタ

		m_Material[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[m_Material[nCntModel].dwNumMat];

		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)m_Material[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_Material[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャが存在する
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_Material[nCntModel].pTexture[nCntMat]);
			}
			else
			{//テクスチャが存在しない
				m_Material[nCntModel].pTexture[nCntMat] = NULL;
			}
		}

		m_nNumAll++;		//モデルの数加算
	}

	return S_OK;
}

//==============================================================
//マテリアル破棄処理
//==============================================================
void CXFile::Unload(void)
{
	for (int nCntModel = 0; nCntModel < MAX_TEX; nCntModel++)
	{
		//テクスチャの破棄
		for (int nCntMat = 0; nCntMat < (int)m_Material[nCntModel].dwNumMat; nCntMat++)
		{
			if (m_Material[nCntModel].pTexture[nCntMat] != NULL)
			{
				m_Material[nCntModel].pTexture[nCntMat]->Release();
				m_Material[nCntModel].pTexture[nCntMat] = NULL;
			}
		}

		//マテリアルの破棄
		if (m_Material[nCntModel].pBuffMat != NULL)
		{
			m_Material[nCntModel].pBuffMat->Release();
			m_Material[nCntModel].pBuffMat = NULL;
		}

		//メッシュの破棄
		if (m_Material[nCntModel].pMesh != NULL)
		{
			m_Material[nCntModel].pMesh->Release();
			m_Material[nCntModel].pMesh = NULL;
		}
	}
}

//==============================================================
//モデル番号指定処理
//==============================================================
int CXFile::Regit(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//デバイスの取得

	for (int nCntModel = 0; nCntModel < MAX_TEX; nCntModel++)
	{
		if (m_apFilename[nCntModel] == pFilename)
		{//ファイル名が同じとき

			return nCntModel;		//番号
		}
		else if (m_apFilename[nCntModel] != pFilename && nCntModel > m_nNumAll)
		{//ファイル名が違う

			m_apFilename[nCntModel] = pFilename;

			//Xファイルの読み込み
			D3DXLoadMeshFromX(m_apFilename[nCntModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_Material[nCntModel].pBuffMat,
				NULL,
				&m_Material[nCntModel].dwNumMat,
				&m_Material[nCntModel].pMesh);

			D3DXMATERIAL *pMat;		//マテリアルへのポインタ

			m_Material[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[m_Material[nCntModel].dwNumMat];

			//マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)m_Material[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_Material[nCntModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャが存在する
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&m_Material[nCntModel].pTexture[nCntMat]);
				}
				else
				{//テクスチャが存在しない
					m_Material[nCntModel].pTexture[nCntMat] = NULL;
				}
			}

			m_nNumAll++;

			return m_nNumAll;		//マテリアルの番号を返す
		}
	}

	return m_nNumAll;		//マテリアルの番号を返す
}

//==============================================================
//テクスチャの情報取得
//==============================================================
LPDIRECT3DTEXTURE9 CXFile::GetTexAddress(int nIdx, int nMat)
{
	return m_Material[nIdx].pTexture[nMat];		//指定のテクスチャを返す
}

//==============================================================
//マテリアルの情報取得
//==============================================================
LPD3DXBUFFER CXFile::GetMatAddress(int nIdx)
{
	return m_Material[nIdx].pBuffMat;
}

//==============================================================
//マテリアルの数の情報取得
//==============================================================
DWORD CXFile::GetNumMatAddress(int nIdx)
{
	return m_Material[nIdx].dwNumMat;
}

//==============================================================
//メッシュ情報取得
//==============================================================
LPD3DXMESH CXFile::GetMeshAddress(int nIdx)
{
	return m_Material[nIdx].pMesh;
}