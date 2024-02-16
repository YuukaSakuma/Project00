//==============================================================
//
//コアヘッダー[coa.h]
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
		TYPE_COA_0 = 0,		//赤
		TYPE_COA_1,			//青
		TYPE_COA_MAX,
	}COA;

	CCOa();			//コンストラクタ
	~CCOa();		//デストラクタ

	HRESULT Init(void);						
	void Uninit(void);						
	void Update(void);						
	void Draw(void);						

	static CCOa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, COA type);

	//取得
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	COA GetCoaType(void) { return m_CoaType; }

	//設定
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
	//STATE m_state;		//種類
	COA m_CoaType;			//コアの種類
};
#endif // !_BULLET_H_
