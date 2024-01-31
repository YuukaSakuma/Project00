//==============================================================
//
//モデル処理[model.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _MODEL_H_							//このマクロ定義がされていなかったら
#define _MODEL_H_							//2重インクルード防止のマクロを定義するv

#include"objectX.h"

//==============================================================
//モデルクラス
//==============================================================
class CModel:public CObjectX
{
public:

	CModel();																//コンストラクタ
	CModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);		//コンストラクタ(オーバーロード)
	~CModel();																//デストラクタ

	static HRESULT Load(const char *pFilename);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);		//生成処理

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

private:

	static LPD3DXMESH m_pMesh;			//メッシュ（頂点情報）へのポインタ
	static LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	static DWORD m_dwNumMat;			//マテリアルの数

	static const char *m_pFilename;					//ファイルの名前

	int m_nIdxModel;		//モデルの番号

	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//移動量

	//int nldxShadow;
};

////==============================================================
////モデルクラス
////==============================================================
//class CModel :public CObject
//{
//public:
//
//	CModel();	// コンストラクタ
//	~CModel();	// デストラクタ
//
//
//	HRESULT Init(void);
//	HRESULT Init(const char *pFileName);
//	void Uninit(void);
//	void Update(void);
//	void Draw(void);
//	static CModel *Create(const char *pFileName);
//	void SetParent(D3DXMATRIX *pMtx);
//	void SetCharaParent(D3DXMATRIX *pMtx) { m_pCharacterMtx = pMtx; }
//	void BindModelFile(int nIdx);
//	void SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot);
//
//	D3DXVECTOR3 GetPosition(void) { return m_pos; }
//	D3DXVECTOR3 GetRotation(void) { return m_rot; }
//	D3DXVECTOR3 GetCurrentPosition(void) { return m_CurPos; }
//	D3DXVECTOR3 GetCurrentRotation(void) { return m_CurRot; }
//	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
//	D3DXMATRIX *GetMtxParent(void) { return m_pParentMtx; }
//	int GetId(void) { return m_nIdxModel; }
//
//	void SetPosition(const D3DXVECTOR3 pos);
//	void SetRotation(const D3DXVECTOR3 rot);
//	void SetCurrentPosition(const D3DXVECTOR3 pos);
//	void SetCurrentRotation(const D3DXVECTOR3 rot);
//	void SetDraw(bool bDraw = true) { m_bDraw = bDraw; }
//	void SetShadow(bool bShadow = false) { m_bShadow = bShadow; }
//	void SetMaterial(const D3DMATERIAL9& Material) { m_ChangeMat = Material; }
//	void ChangeCol(bool bValue = false) { m_bChangeCol = bValue; }
//
//private:
//
//			// メンバ変数
//	int m_nIdxModel;		// モデル番号
//	bool m_bChangeCol;	// 色変更をするかどうか
//	bool m_bDraw;
//	D3DMATERIAL9 m_ChangeMat;
//	D3DXVECTOR3 m_pos;		// 位置
//	D3DXVECTOR3 m_rot;		// 向き
//	D3DXVECTOR3 m_CurPos;		// 現在の位置
//	D3DXVECTOR3 m_CurRot;		// 現在の向き
//	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
//	D3DXMATRIX *m_pParentMtx;	// 親のワールドマトリックス
//	D3DXMATRIX *m_pCharacterMtx;	// まとめている親のマトリックス
//	bool m_bShadow;		// 影も描画するか否か
//};
#endif