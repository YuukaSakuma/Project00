//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"renderer.h"
#include"tutorial.h"
#include"input.h"
#include"player.h"
#include"manager.h"
#include"object2D.h"
#include"fade.h"


//�ÓI�����o�ϐ�
CPlayer *CTutorial::m_pPlayerModel = NULL;	//�v���C���[�̏��
bool CTutorial::m_bReset = true;					//���Z�b�g�������ǂ���

//==============================================================
//�R���X�g���N�^
//==============================================================
CTutorial::CTutorial()
{

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CTutorial::~CTutorial()
{

}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CTutorial::Init(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	//�I�u�W�F�N�g2D�̐���
	CObject2D *pObject2D = CObject2D::Create();

	pObject2D->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\tutrial000.png"));
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pObject2D->SetVtx(0.0f, 0.0f);

	return S_OK;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CTutorial::Uninit(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Stop();
	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void CTutorial::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//�L�[�{�[�h�̏��擾

	CSound *pSound = CManager::Get()->GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true )
	{//ENTER�L�[��������

		pSound->Play(pSound->SOUND_LABEL_SE_PICK);

	 //�`���[�g���A�����
		CManager::Get()->GetFade()->Set(CScene::MODE_GAME);
		
		
	}

	CScene::Update();

	pDebugProc->Print("\n�`���[�g���A��\n");
}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void CTutorial::Draw(void)
{

}