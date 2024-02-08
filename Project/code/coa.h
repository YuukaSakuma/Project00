//==============================================================
//
//弾ヘッダー[bullet.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _COA_H_						//このマクロが定義されていなかったら
#define _COA_H_						//2重インクルード防止のマクロを定義する

#include "object.h"

//前方宣言
class CModel;
class CModelHier;
class CMotion;

//==============================================================
//コアクラス
//==============================================================
class CCOa
{
public:

	CCOa();													//コンストラクタ
	~CCOa();													//デストラクタ

	static CCOa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//弾の生成

	virtual HRESULT Init(void);						//初期化処理
	virtual void Uninit(void);						//終了処理
	virtual void Update(void);						//更新処理
	virtual void Draw(void);						//描画処理

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }			//最小サイズの取得
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }			//最大サイズの取得

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	void SetState(void);

private:
#define NUM_MODEL_BIRD1		(8)			//敵1のモデル数

	int m_nLife;			//寿命
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き	
	//TYPE m_type;			//種類
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//位置(前回)
	D3DXVECTOR3 m_max;		//最大値
	D3DXVECTOR3 m_min;		//最小値
	int m_nldxTexture;		//テクスチャ番号
	int m_nCntAttack;		//アタックカウンター
	int m_nCntDamage;		//ダメージカウンター

	//STATE m_state;			//種類

	int m_nIdxTexture;			//テクスチャの番号
	static int m_nNumAll;		//敵の総数
	int m_nID;					//敵の番号

	CModel* m_pModel;
};
#endif // !_BULLET_H_
