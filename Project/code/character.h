//==============================================================
//
//プレイヤーヘッダー[player.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _CHARACTER_H_						//このマクロが定義されていなかったら
#define _CHARACTER_H_						//2重インクルード防止のマクロを定義する

#include "object.h"

//==============================================================
//プレイヤークラス
//==============================================================
class CCharacter 
{
public:

	CCharacter();								//コンストラクタ
	~CCharacter();								//デストラクタ

	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//プレイヤーの生成

	HRESULT Init(void);						//プレイヤーの初期化処理
	void Uninit(void);						//プレイヤーの終了処理
	void Update(void);						//プレイヤーの更新処理
	void Draw(void);						//プレイヤーの描画処理

private:


};
#endif // !_PLAYER_H_
