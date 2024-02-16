//==============================================================
//
//入力処理[input.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "Xinput.h"

#pragma comment(lib, "xinput.lib")


//マクロ定義
#define NUM_KEY_MAX	(256)	//キーの最大数
#define NUM_PLAYER (4)		//プレイヤーの人数

//==============================================================
//入力クラス
//==============================================================
class CInput
{
public:
	CInput();					//コンストラクタ
	virtual ~CInput();			//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	virtual void Uninit(void);									//終了処理
	virtual void Update(void) = 0;								//更新処理

protected:
	static LPDIRECTINPUT8 m_pInput;			//インプットのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;			//デバイスのポインタ
};

//==============================================================
//キーボードクラス
//==============================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();		//コンストラクタ
	~CInputKeyboard();		//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理

	bool GetPress(int nKey);			//プレスの取得
	bool GetTrigger(int nKey);			//トリガーの取得
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];				//キーボードのプレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		//キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];
	int m_aRepeatCnt[NUM_KEY_MAX];	// リピートタイマー
};

//==============================================================
//キーボードクラス
//==============================================================
class CInputPad : public CInput
{
public:

	//ボタン配置の列挙
	typedef enum
	{
		BUTTON_UP = 0,			//上ボタン
		BUTTON_DOWN,			//下ボタン
		BUTTON_LEFT,			//左ボタン
		BUTTON_RIGHT,			//右ボタン
		BUTTON_START,			//start
		BUTTON_BACK,			//back
		BUTTON_LEFTSTCPUSH,		//左スティック押し込み
		BUTTON_RIGHTSTCPUSH,	//右スティック押し込み
		BUTTON_LEFTBUTTON,		//LB(L)ボタン
		BUTTON_RIGHTBUTTON,		//RB(R)ボタン
		BUTTON_11,				//Lトリガー
		BUTTON_12,				//Rトリガー
		BUTTON_A,				//Aボタン
		BUTTON_B,				//Bボタン
		BUTTON_X,				//Xボタン
		BUTTON_Y,				//Yボタン
		BUTTON_LEFT_Y,			//左(Y)
		BUTTON_LEFT_X,			//左(X)
		BUTTON_RIGHT_Y,			//右(Y)
		BUTTON_RIGHT_X,			//右(X)
		BUTTON_MAX
	}BUTTON;

	//CInputPad();		//コンストラクタ
	//~CInputPad();		//デストラクタ


};
#endif