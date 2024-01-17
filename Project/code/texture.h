//==============================================================
//
//テクスチャ処理[texture.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"
#include"object.h"

//マクロ定義
#define MAX_TEXTURE	(256)	//テクスチャの最大数

//==============================================================
//テクスチャクラス
//==============================================================
class CTexture
{
public:

	//種類
	typedef enum
	{
		TYPE_TEX_NONE = 0,
		TYPE_TEX_EXPLOSION,		//爆発
		TYPE_TEX_EFFECT,		//エフェクト
		TYPE_TEX_SCORE,			//スコア
		TYPE_TEX_BLOCK,			//ブロック
		TYPE_TEX_BG_0,			//背景0
		TYPE_TEX_BG_1,			//背景1
		TYPE_TEX_BG_2,			//背景2
		TYPE_TEX_FIELD,			//フィールド
		TYPE_TEX_WALL,			//壁
		TYPE_TEX_TITLELOGO,		//タイトルロゴ
		TYPE_TEX_PRESS,			//押せ
		TYPE_TEX_TITLEBG,		//タイトル背景
		TYPE_TEX_RANK,			//順位
		TYPE_TEX_TUTORIAL,		//チュートリアル
		TYPE_TEX_RANKINGLOGO,	//ランキングロゴ
		TYPE_TEX_RESULT,		//リザルト

		TYPE_TEX_MAX
	}TYPE_TEX;

	CTexture();					//コンストラクタ
	~CTexture();				//デストラクタ

	 HRESULT Load(void);		//全てのテクスチャ読み込み
	 void Unload(void);			//全てのテクスチャ破棄

	 int Regist(const char *pFilename);			//指定テクスチャの読み込み
	 LPDIRECT3DTEXTURE9 GetAddress(int nldx);	//テクスチャ番号の取得

private:
	static const char *apTexture[TYPE_TEX_MAX];				//ファイル名

	char m_aFileName[MAX_TEXTURE][256];

	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];
	static int m_nNumAll;
};
#endif