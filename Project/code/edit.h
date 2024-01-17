//==============================================================
//
//エディットヘッダー[edit.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _EDIT_H_						//このマクロが定義されていなかったら
#define _EDIT_H_						//2重インクルード防止のマクロを定義する

#include"object.h"
#include"objectX.h"
#include"model.h"

#define NUM_MODEL (256)			//モデル数

//前方宣言
class CField;
class CObjectX;

//==============================================================
//タイトルクラス
//==============================================================
class CEdit : public CModel
{
public:

	//種類
	typedef enum
	{
		TYPE_KISO = 0,
		TYPE_KISO1,
		TYPE_MAX
	} TYPE;

	CEdit();								//コンストラクタ
	~CEdit();								//デストラクタ

	static CEdit *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

	static HRESULT LoadFile(void);
	void SaveFile(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	//取得用
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;
	static CModel *m_apObjectX[NUM_MODEL];
	int m_nTypeIdx;
	int m_nIdx;
	bool m_bUse;
};
#endif // !_PLAYER_H_

