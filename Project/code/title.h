//==============================================================
//
//タイトルヘッダー[title.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _TITLE_H_						//このマクロが定義されていなかったら
#define _TITLE_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"

//前方宣言
class CModel;
class CField;

//==============================================================
//タイトルクラス
//==============================================================
class CTitle : public CScene
{
public:
	CTitle();								//コンストラクタ
	~CTitle();								//デストラクタ

	//static CTitle *Create(void);			//プレイヤーの生成

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

private:

	static CModel *m_pModel;
	static CField *m_pField;

	static bool m_bReset;

	int m_nTimer;	// 自動遷移タイマー

};
#endif // !_PLAYER_H_

