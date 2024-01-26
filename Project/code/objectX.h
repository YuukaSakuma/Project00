//==============================================================
//
//オブジェクトX処理[objectX.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _OBJECTX_H_							//このマクロ定義がされていなかったら
#define _OBJECTX_H_							//2重インクルード防止のマクロを定義するv

#include "main.h"
#include"object.h"

// マクロ定義
#define NUM_TEXTURE	(64)	// テクスチャ最大数


//==============================================================
//オブジェクトXクラス
//==============================================================
class CObjectX : public CObject
{
public:

	CObjectX();		//コンストラクタ
	~CObjectX();	//デストラクタ

	static CObjectX *Create(void);			//オブジェクトXの生成
	static HRESULT Load(void);				//テクスチャの読み込み
	static void Unload(void);				//テクスチャの破棄


	virtual HRESULT Init(void);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理

	void BindMaterial(int nIdx);		//外部からマテリアル指定
	void BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);		//ファイルの設定

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得

	void SetRotation(TYPE type, D3DXVECTOR3 rot) { m_rot = rot; }			//向き設定
	D3DXVECTOR3 GetRotation(void) { return m_rot; }							//向きの取得

	void SetSize(D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax) { m_vtxMin = vtxMin;  m_vtxMax = vtxMax; }		//モデルの大きさ設定
	D3DXVECTOR3 GetSizeMin(void) { return m_vtxMin; }		//最小の大きさ取得
	D3DXVECTOR3 GetSizeMax(void) { return m_vtxMax; }		//最大の大きさ取得

	void SetState(STATE state) { m_state = state; }		//敵の状態設定
	STATE GetState(void) { return m_state; }			//敵の状態取得

	void SetObject(void);
	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max);
	static bool CollisionHit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max);

private:

	LPD3DXMESH m_pMesh;					//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	DWORD m_dwNumMat;					//マテリアルの数

	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 m_vtxMin;				//最小
	D3DXVECTOR3 m_vtxMax;				//最大

	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//移動量
	D3DXVECTOR3 m_move;					//移動量
	TYPE m_type;						//タイプの設定
	STATE m_state;						//状態

	int m_nIdxParent;				//親モデルのインデックス
	D3DXMATERIAL m_matColor;		//マテリアルデータへのポインタ

	int m_nIdxModel;		//モデルの番号
};

////==============================================================
////オブジェクトXクラス
////==============================================================
//class CObjectX : public CObject
//{
//public:	// 誰でもアクセス可能
//
//	CObjectX(int nPriority = 0);	// コンストラクタ
//	virtual ~CObjectX();	// デストラクタ
//
//							// メンバ関数
//	virtual HRESULT Init(void);
//	virtual void Uninit(void);
//	virtual void Update(void);
//	virtual void Draw(void);
//	void BindFile(int nIdx);
//
//	static CObjectX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, const int nPriority = 4);
//	static bool Collision(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const float fRefMulti = 0.5f);
//	static bool Collision(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMinOld, D3DXVECTOR3 vtxMaxOld);
//	static bool Touch(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
//	static bool CollisionCloss(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3* posCollisioned = nullptr);
//	static void CollisionLand(D3DXVECTOR3 &pos);
//	void SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot);
//
//	// メンバ関数(設定)
//	void SetPosition(const D3DXVECTOR3 pos);
//	void SetRotation(const D3DXVECTOR3 rot);
//	void SetEnableCollision(const bool bEnable) { m_bEnableCollision = bEnable; }
//
//	// メンバ関数(取得)
//	D3DXVECTOR3 GetPosition(void) { return m_pos; }
//	D3DXVECTOR3 GetRotation(void) { return m_rot; }
//	CObject2D *GetObject2D(void) { return NULL; }
//	virtual D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
//	int GetIdx(void) { return m_nIdxModel; }
//	void ListOut(void);
//	int GetModelType(void) { return m_nIdxModel; }
//
//private:	// 自分だけがアクセス可能
//	enum COLLISION_AXIS
//	{
//		TYPE_X = 0,
//		TYPE_Y,
//		TYPE_Z
//	};
//
//	// メンバ関数
//	//D3DMATERIAL9 SetSlowCol(D3DMATERIAL9 *pMat);
//	bool CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, COLLISION_AXIS axis, const float fRefMulti = 0.5f);
//	bool CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMinOld, D3DXVECTOR3 vtxMaxOld, COLLISION_AXIS axis);
//	bool CollisionCheckCloss(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3* posCollisioned = nullptr);
//
//	// メンバ変数c
//	static CObjectX *m_pTop;	// 先頭のオブジェクトへのポインタ
//	static CObjectX *m_pCur;	// 最後尾のオブジェクトへのポインタ
//	CObjectX *m_pPrev;	// 前のオブジェクトへのポインタ
//	CObjectX *m_pNext;	// 次のオブジェクトへのポインタ
//	D3DXVECTOR3 m_pos;	// 位置
//	D3DXVECTOR3 m_rot;	// 向き
//	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
//	int m_nIdxModel;		// モデル番号
//	bool m_bEnableCollision;	//当たり判定の有効・無効
//};
#endif