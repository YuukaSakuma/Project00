//==============================================================
//
//タイトルヘッダー[title.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _TITLETEX_H_						//このマクロが定義されていなかったら
#define _TITLETEX_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"


#define NUM_TITLE_TEX		(2)		//タイトルのテクスチャの数

//前方宣言
class CModel;
class CField;
class CObject2D;

//==============================================================
//タイトルクラス
//==============================================================
class CTitleTex : public CObject
{
public:
	CTitleTex();								//コンストラクタ
	~CTitleTex();								//デストラクタ

	static CTitleTex *Create(void);			//プレイヤーの生成

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

private:

	static CObject2D *m_apObject2D[NUM_TITLE_TEX];		//オブジェクト2Dのポインタ
	int m_nIdxTexture[NUM_TITLE_TEX];		//テクスチャの番号
	int m_nCntAppear;				//点滅カウンター
	bool m_bAppear;					//点滅の切り替え
	float m_fAlpha;					//アルファ値
	STATE m_state;					//状態
};
#endif // !_PLAYER_H_

