//==============================================================
//
//弾ヘッダー[bullet.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _COA_H_						//このマクロが定義されていなかったら
#define _COA_H_						//2重インクルード防止のマクロを定義する

#include "objectX.h"

//前方宣言
class CModel;

//==============================================================
//コアクラス
//==============================================================
class CCOa : CObjectX
{
public:

	typedef enum
	{
		TYPE_COA_0 = 0,
		TYPE_COA_1,
		TYPE_COA_MAX,
	}COA;

	CCOa();													//コンストラクタ
	~CCOa();													//デストラクタ

	static CCOa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, COA type);	//弾の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCoaType(COA type) { m_CoaType = type; }

	void SetState(void);
	void Hit(void);

private:

	int m_nLife;			//寿命
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き	
	TYPE m_type;			//種類
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//位置(前回)
	int m_nldxTexture;		//テクスチャ番号
	int m_nCntAttack;		//アタックカウンター
	int m_nCntDamage;		//ダメージカウンター

	//STATE m_state;			//種類
	static int m_nNumAll;		//敵の総数
	int m_nID;					//敵の番号
	COA m_CoaType;

};
#endif // !_BULLET_H_
