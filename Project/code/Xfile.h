//==============================================================
//
//テクスチャ処理[texture.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _XFILE_H_
#define _XFILE_H_

#include "main.h"

//マクロ定義
#define MAX_TEX	(256)	//テクスチャの最大数

//==============================================================
//テクスチャクラス
//==============================================================
class CXFile
{
public:

	//テクスチャの種類
	typedef enum
	{
		TEX_MAX = 0

	} TEX;

	//モデルの構造体の定義
	typedef struct
	{
		LPD3DXMESH pMesh;					//メッシュ（頂点情報）へのポインタ
		LPD3DXBUFFER pBuffMat;				//マテリアルへのポインタ
		DWORD dwNumMat;						//マテリアルの数
		LPDIRECT3DTEXTURE9 *pTexture;
	} Material;

	CXFile();		//コンストラクタ
	~CXFile();	//デストラクタ

	HRESULT Load(void);		//テクスチャ読み込み処理
	void Unload(void);		//テクスチャ破棄処理

	int Regist(const char *pFilename);				//テクスチャの番号指定
	LPDIRECT3DTEXTURE9 GetTexAddress(int nIdx, int nMat);		//テクスチャの情報取得
	LPD3DXBUFFER GetMatAddress(int nIdx);		//マテリアルの情報取得
	DWORD GetNumMatAddress(int nIdx);			//マテリアルの数の情報取得
	LPD3DXMESH GetMeshAddress(int nIdx);		//メッシュの情報取得

private:

	static int m_nNumAll;		//テクスチャの数
	static const char *m_apFilename[MAX_TEX];		//モデルのテキストファイル名
	static Material m_Material[MAX_TEX];			//マテリアルの情報
};

////==============================================================
////テクスチャクラス
////==============================================================
//class CXFile
//{
//
//private:
//	const static int MAX_FILE = 256;
//	const static int MAX_NAME = 256;
//
//public:
//
//	//Xファイル情報
//	struct FileData
//	{
//		LPD3DXMESH pMesh;					//メッシュ（頂点情報）へのポインタ
//		LPD3DXBUFFER pBuffMat;				//マテリアルへのポインタ
//		int *pIdexTexture;					//テクスチャ番号
//		DWORD dwNumMat;						//マテリアルの数
//		D3DXVECTOR3 vtxMin;					//最小
//		D3DXVECTOR3 vtxMax;					//最大
//		LPDIRECT3DTEXTURE9 *pTexture;
//	};
//
//private:
//	// ファイル読み込み情報
//	struct FileInfo
//	{
//		char aFileName[MAX_NAME];	// ファイル名
//		FileData filedata;			// ファイル情報
//	};
//
//public:
//
//	CXFile();		//コンストラクタ
//	~CXFile();	//デストラクタ
//
//	// メンバ関数
//	int Regist(const char *pFileName);
//	void Unload(void);
//	void SetSizeVtxMax(int nIdx, D3DXVECTOR3 vtxMax) { m_apModelFileData[nIdx]->filedata.vtxMax = vtxMax; }
//	void SetSizeVtxMin(int nIdx, D3DXVECTOR3 vtxMin) { m_apModelFileData[nIdx]->filedata.vtxMin = vtxMin; }
//
//	// メンバ関数(取得)
//	FileData *SetAddress(int nIdx);
//	static int GetNumAll(void) { return m_nNumAll; }
//	D3DXVECTOR3 GetMax(int nIdx) { return m_apModelFileData[nIdx]->filedata.vtxMax; }
//	D3DXVECTOR3 GetMin(int nIdx) { return m_apModelFileData[nIdx]->filedata.vtxMin; }
//	char *GetFileName(int nIdx) { return &m_apModelFileData[nIdx]->aFileName[0]; }
//
//private:
//
//	HRESULT FileLoad(int nIdx);
//
//	FileInfo *m_apModelFileData[MAX_FILE];	// モデルのファイル情報のポインタ
//	static int m_nNumAll;	// 読み込み総数
//};
#endif