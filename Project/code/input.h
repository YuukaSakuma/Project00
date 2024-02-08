//==============================================================
//
//入力処理[input.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#define NUM_KEY_MAX	(256)	//キーの最大数

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

#endif