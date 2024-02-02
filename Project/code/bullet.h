//==============================================================
//
//弾ヘッダー[bullet.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _BULLET_H_						//このマクロが定義されていなかったら
#define _BULLET_H_						//2重インクルード防止のマクロを定義する

#include"object2D.h"
#include"billboard.h"

//==============================================================
//弾クラス
//==============================================================
class CBullet : public CBillboard
{
public:

	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_C,
		TYPE_MAX
	}BulletType;

	CBullet();													//コンストラクタ
	~CBullet();													//デストラクタ

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,BulletType btype, TYPE type);	//弾の生成

	virtual HRESULT Init(void);						//初期化処理
	virtual void Uninit(void);						//終了処理
	virtual void Update(void);						//更新処理
	virtual void Draw(void);						//描画処理

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }

	TYPE GetType(void) { return m_type; }

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetType(TYPE type) {m_type = type;}

	bool Collision(D3DXVECTOR3 pos);								//敵との当たり判定
	bool ColisionLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);		//ブロックの当たり判定(中心：[左上])
	bool ColisionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);		//ブロックの当たり判定(中心：[中央])
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);	//モデルとの当たり判定
	bool CollisionData(D3DXVECTOR3 pos);							//モデルとの当たり判定

private:

	int m_nLife;			//寿命
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き	
	TYPE m_type;			//種類
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//位置(前回)

	BulletType m_BType;		//弾の種類
};

class CBulletA :public CBullet
{
public:

	CBulletA();													//コンストラクタ
	~CBulletA();													//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

private:

	int m_nldxTexture;		//テクスチャ番号

};

class CBulletB :public CBullet
{
public:

	CBulletB();													//コンストラクタ
	~CBulletB();													//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

private:

	int m_nldxTexture;		//テクスチャ番号

};

class CBulletC :public CBullet
{
public:

	CBulletC();													//コンストラクタ
	~CBulletC();													//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

private:

	int m_nldxTexture;		//テクスチャ番号

};
#endif // !_BULLET_H_
