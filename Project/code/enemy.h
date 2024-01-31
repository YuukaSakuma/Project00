//==============================================================
//
//弾ヘッダー[bullet.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _BULLET_H_						//このマクロが定義されていなかったら
#define _BULLET_H_						//2重インクルード防止のマクロを定義する

#include "objectX.h"
//==============================================================
//弾クラス
//==============================================================
class CEnemy : public CObjectX
{
public:

	CEnemy();													//コンストラクタ
	~CEnemy();													//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//弾の生成

	virtual HRESULT Init(void);						//初期化処理
	virtual void Uninit(void);						//終了処理
	virtual void Update(void);						//更新処理
	virtual void Draw(void);						//描画処理

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
private:

	int m_nLife;			//寿命
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き	
	TYPE m_type;			//種類
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//位置(前回)
};
#endif // !_BULLET_H_
