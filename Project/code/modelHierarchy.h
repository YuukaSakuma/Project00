//==============================================================
//
//階層構造処理[modelHierarchy.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _MODELHIERARCHY_H_		//このマクロ定義がされていなかったら
#define _MODELHIERARCHY_H_		//2重インクルード防止のマクロを定義する

#include "objectX.h"

//==============================================================
//モデルの階層構造クラスの定義
//==============================================================
class CModelHier
{
public:
	CModelHier();										//コンストラクタ
	CModelHier(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//コンストラクタ(オーバーロード)
	~CModelHier();										//デストラクタ

	HRESULT Load(char *pFileName);		//テクスチャの読み込み
	static CModelHier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName);	//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理
	void SetObject(void);		//モデルの設定処理						

	void SetParent(CModelHier *pModelHier) { m_pParent = pModelHier; }		//親モデルの設定
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }						//ワールドマトリックス取得
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }						//位置設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }							//位置取得
	void SetDefaultPosition(D3DXVECTOR3 pos) { m_posDefault = pos; }		//初期位置設定
	D3DXVECTOR3 GetDefaultPosition(void) { return m_posDefault; }			//初期位置取得
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }						//向き設定
	D3DXVECTOR3 GetRotation(void) { return m_rot; }							//向き取得
	void SetDefaultRotation(D3DXVECTOR3 rot) { m_rotDefault = rot; }		//初期向き設定
	D3DXVECTOR3 GetDefaultRotation(void) { return m_rotDefault; }			//初期向き取得
	void SetDisp(void) { m_bDisp = m_bDisp ? false : true; }				//表示設定

	D3DXVECTOR3 GetSizeMax(void) { return m_vtxMax; }			//モデルの最大の大きさ
	D3DXVECTOR3 GetSizeMin(void) { return m_vtxMin; }			//モデルの最小の大きさ
	void SetState(CObjectX::STATE state) { m_state = state; }	//敵の状態設定
	CObjectX::STATE GetState(void) { return m_state; }			//敵の状態取得

private:

	LPD3DXMESH m_pMesh;					//メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	DWORD m_dwNumMat;					//マテリアルの数

	D3DXVECTOR3 m_vtxMin;				//モデルの最小値
	D3DXVECTOR3 m_vtxMax;				//モデルの最大値

	int m_nIdxModel;		//モデルの番号

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//向き
	D3DXVECTOR3 m_posDefault;		//初期位置
	D3DXVECTOR3 m_rotDefault;		//初期向き
	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス

	CObjectX::STATE m_state;		//状態
	D3DXMATERIAL m_matColor;		//マテリアルデータへのポインタ

	CModelHier *m_pParent;			//親モデルへのポインタ

	bool m_bDisp;
};

#endif