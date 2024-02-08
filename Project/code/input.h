//==============================================================
//
//���͏���[input.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔

//==============================================================
//���̓N���X
//==============================================================
class CInput
{
public:
	CInput();					//�R���X�g���N�^
	virtual ~CInput();			//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	virtual void Uninit(void);									//�I������
	virtual void Update(void) = 0;								//�X�V����

protected:
	static LPDIRECTINPUT8 m_pInput;			//�C���v�b�g�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;			//�f�o�C�X�̃|�C���^
};

//==============================================================
//�L�[�{�[�h�N���X
//==============================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();		//�R���X�g���N�^
	~CInputKeyboard();		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����

	bool GetPress(int nKey);			//�v���X�̎擾
	bool GetTrigger(int nKey);			//�g���K�[�̎擾
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];
	int m_aRepeatCnt[NUM_KEY_MAX];	// ���s�[�g�^�C�}�[
};

#endif