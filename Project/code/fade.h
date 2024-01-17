//==============================================================
//
//フェードヘッダー[fade.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _FADE_H_						//このマクロが定義されていなかったら
#define _FADE_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"
#include"object2D.h"
#include"main.h"

//前方宣言

//==============================================================
//リザルトクラス
//==============================================================
class CFade : public CObject2D
{
public:

	typedef enum
	{
		STATE_NONE = 0,		//何もしていない状態
		STATE_IN,			//フェードイン状態
		STATE_OUT,			//フェードアウト状態
		STATE_MAX
	}STATE;

	CFade();								//コンストラクタ
	~CFade();								//デストラクタ

	HRESULT Init(CScene::MODE modeNext);

	//HRESULT Init(void);					//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void Set(CScene::MODE modeNext);
	void SetState(STATE state);
	STATE GetFadeState(void) { return m_state; }

	static CFade *Create(CScene::MODE modeNext);

private:

	STATE m_state;				//状態
	CScene::MODE m_modeNext;	//次の画面
	D3DXCOLOR m_Col;			//フェードの色

};
#endif // !_PLAYER_H_

