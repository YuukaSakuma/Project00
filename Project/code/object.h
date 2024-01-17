//==============================================================
//
//オブジェクトヘッダー[object.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _OBJECT_H_						//このマクロが定義されていなかったら
#define _OBJECT_H_						//2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_OBJECT (1024)

//==============================================================
//オブジェクトクラス
//==============================================================
class CObject
{
public:

	//種類
	typedef enum
	{
		TYPE_NONE = 0,	//なし
		TYPE_PLAYER,	//プレイヤー
		TYPE_ENEMY,		//敵
		TYPE_BULLET,	//弾
		TYPE_EXPLOSION,	//爆発
		TYPE_EFFECT,	//エフェクト
		TYPE_PARTICLE,	//パーティクル
		TYPE_SCORE,		//スコア
		TYPE_BLOCK,		//ブロック
		TYPE_ITEM,		//アイテム
		TYPE_MODEL,
		TYPE_MAX
	}TYPE;

	//オブジェクトの状態
	typedef enum
	{
		STATE_NONE = 0,		//通常状態
		STATE_ATTACK,		//攻撃状態
		STATE_DAMAGE,		//ダメージ状態
		STATE_APPEAR,		//復活状態
		STATE_F_JUMP,		//1回目のジャンプ状態
		STATE_S_JUMP,		//2回目のジャンプ状態
		STATE_DEATH,		//死亡状態

	} STATE;

	CObject();				//コンストラクタ
	CObject(TYPE type);		//コンストラクタ(オーバーロード)
	virtual ~CObject();		//デストラクタ

	virtual HRESULT Init(void) = 0;		//初期化処理
	virtual void Uninit(void) = 0;		//終了処理
	virtual void Update(void) = 0;		//更新処理
	virtual void Draw(void) = 0;		//描画処理

	virtual void Hit(void) {};		//ヒット処理

	virtual void SetRotation(D3DXVECTOR3 rot) {};										//位置の設定
	virtual D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//位置の取得

	virtual void SetPosition(D3DXVECTOR3 pos) {};										//位置の設定
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//位置の取得
																						
	virtual D3DXVECTOR3 GetSizeMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//最小サイズの取得
	virtual D3DXVECTOR3 GetSizeMax(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//最大サイズの取得

	static void ReleseAll(void);										//
	static void UpdateAll(void);										//全ての更新
	static void DrawAll(void);											//全ての描画
	static void ResetMapAll(void);										//
	static CObject * GetObject(int nIdx) { return m_apObject[nIdx]; }	//オブジェクト情報の取得

	void SetType(TYPE type) { m_type = type; }	//タイプの設定
	TYPE GetType(void) { return m_type; }		//タイプの取得

	virtual void SetState(STATE state) {}					//オブジェクトの状態設定
	virtual STATE GetState(void) { return STATE_NONE; }		//オブジェクトの状態取得
	
protected:

	void Release(void);

private:
	static CObject * m_apObject[MAX_OBJECT];	//オブジェクトのポインタ
	static int m_nNumAll;						//オブジェクトの総数
	int m_nID;									//自分自身のクラス
	TYPE m_type;								//種類
	STATE m_state;								//オブジェクトの状態

};
#endif // !_MAIN_H_

