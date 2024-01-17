//==============================================================
//
//テクスチャ処理[texture.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "main.h"
#include"object.h"

//マクロ定義
#define MAX_TEX	(256)	//テクスチャの最大数

//==============================================================
//テクスチャクラス
//==============================================================
class CMaterial
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


	CMaterial();		//コンストラクタ
	~CMaterial();	//デストラクタ

	HRESULT Load(void);		//テクスチャ読み込み処理
	void Unload(void);		//テクスチャ破棄処理

	int Regit(const char *pFilename);				//テクスチャの番号指定
	LPDIRECT3DTEXTURE9 GetTexAddress(int nIdx, int nMat);		//テクスチャの情報取得
	LPD3DXBUFFER GetMatAddress(int nIdx);		//マテリアルの情報取得
	DWORD GetNumMatAddress(int nIdx);			//マテリアルの数の情報取得
	LPD3DXMESH GetMeshAddress(int nIdx);		//メッシュの情報取得

private:
	static int m_nNumAll;		//テクスチャの数
	static const char *m_apFilename[MAX_TEX];		//モデルのテキストファイル名
	static Material m_Material[MAX_TEX];			//マテリアルの情報
};
#endif