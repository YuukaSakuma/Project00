//==============================================================
//
//タイトルヘッダー[title.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _PAUSE_H_						//このマクロが定義されていなかったら
#define _PAUSE_H_						//2重インクルード防止のマクロを定義する

#include "object.h"

//前方宣言
class CObject2D;	

//==============================================================
//タイトルクラス
//==============================================================
class CPause : public CObject
{
public:

	//ポーズメニュー
	typedef enum
	{
		PAUSE_CONTINUE = 0,		//ゲームに戻る
		PAUSE_RETRY,			//ゲームをやり直す
		PAUSE_QUIT,				//タイトル画面に戻る
		PAUSE_MAX
	} PAUSE;

	CPause();								//コンストラクタ
	~CPause();								//デストラクタ

	static CPause *Create(void);			//プレイヤーの生成

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

private:

	static CObject2D *m_apObject2D[PAUSE_MAX];		//オブジェクト2Dのポインタ

	static LPDIRECT3DTEXTURE9 m_pTexture[PAUSE_MAX];	//テクスチャへのポインタ
	int m_nIdxTexture[PAUSE_MAX];		//テクスチャの番号
	PAUSE m_pause;						//ポーズメニュー
	int m_nSelect;						//選択肢

};
#endif // !_PLAYER_H_

