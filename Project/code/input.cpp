//==============================================================
//
//入力処理[input.cpp]
//Author:佐久間優香
//
//==============================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)						//キーの最大数

//静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==============================================================
//入力処理のコンストラクタ
//==============================================================
CInput::CInput()
{

}

//==============================================================
//入力処理のデストラクタ
//==============================================================
CInput::~CInput()
{

}

//==============================================================
//入力処理の初期化処理
//==============================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}


	return S_OK;

}

//==============================================================
//入力処理の終了処理
//==============================================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//Directオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//==============================================================
//入力処理のコンストラクタ
//==============================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//==============================================================
//入力処理のデストラクタ
//==============================================================
CInputKeyboard::~CInputKeyboard()
{

}

//==============================================================
//キーボードの初期化処理
//==============================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		//キーボードへのアクセス権を獲得
		m_pDevice->Acquire();
		return S_OK;
	}

	return S_OK;
}

//==============================================================
//キーボードの終了処理
//==============================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//==============================================================
//キーボードの更新処理
//==============================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//キーボードのトリガー情報の保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();		//キーボードへのアクセス権を獲得
	}
}

//==============================================================
//キーボードのプレス情報の獲得
//==============================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//==============================================================
//キーボードのトリガー情報の獲得
//==============================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}