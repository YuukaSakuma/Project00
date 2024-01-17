//==============================================================
//
//���͏���[input.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)						//�L�[�̍ő吔

//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==============================================================
//���͏����̃R���X�g���N�^
//==============================================================
CInput::CInput()
{

}

//==============================================================
//���͏����̃f�X�g���N�^
//==============================================================
CInput::~CInput()
{

}

//==============================================================
//���͏����̏���������
//==============================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}


	return S_OK;

}

//==============================================================
//���͏����̏I������
//==============================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//Direct�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//==============================================================
//���͏����̃R���X�g���N�^
//==============================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//==============================================================
//���͏����̃f�X�g���N�^
//==============================================================
CInputKeyboard::~CInputKeyboard()
{

}

//==============================================================
//�L�[�{�[�h�̏���������
//==============================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
		m_pDevice->Acquire();
		return S_OK;
	}

	return S_OK;
}

//==============================================================
//�L�[�{�[�h�̏I������
//==============================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//==============================================================
//�L�[�{�[�h�̍X�V����
//==============================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//�L�[�{�[�h�̃g���K�[���̕ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//==============================================================
//�L�[�{�[�h�̃v���X���̊l��
//==============================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//==============================================================
//�L�[�{�[�h�̃g���K�[���̊l��
//==============================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}