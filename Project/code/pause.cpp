//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//�ÓI�����o�ϐ�
CObject2D *CPause::m_apObject2D[PAUSE_MAX] = {};
LPDIRECT3DTEXTURE9 CPause::m_pTexture[PAUSE_MAX] = {};		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CPause::CPause()
{
	//�ϐ�������
	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		m_nIdxTexture[nCntPause] = -1;		//�e�N�X�`���̔ԍ�
	}

	//m_pause = PAUSE_CONTINUE;		//�|�[�Y���j���[
	m_nSelect = PAUSE_CONTINUE;		//���Ԗڂ�
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CPause::~CPause()
{

}

//==============================================================
//��������
//==============================================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;

	if (pPause == NULL)
	{//���������g�p����ĂȂ�������

	 //�|�[�Y�̐���
		pPause = new CPause;

		//����������
		pPause->Init();

		////��ސݒ�
		//pPause->SetType(TYPE_PAUSE);
	}

	return pPause;
}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CPause::Init(void)
{
	CTexture *pTexture = CManager::Get()->GetTexturet();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regist("data\\TEXTURE\\pause00.png");
	m_nIdxTexture[1] = pTexture->Regist("data\\TEXTURE\\pause01.png");
	m_nIdxTexture[2] = pTexture->Regist("data\\TEXTURE\\pause02.png");

	//���������u
	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		if (m_apObject2D[nCntPause] == NULL)
		{//�g�p����ĂȂ��Ƃ�

		 //2D�I�u�W�F�N�g����
			m_apObject2D[nCntPause] = CObject2D::Create();

			if (m_apObject2D[nCntPause] != NULL)
			{//�����o������

			 //�傫���ݒ�
				//m_apObject2D[nCntPause]->SetSize(WIDTH_MULTI, HEIGHT_MULTI);

				//�e�N�X�`�����蓖��
				m_apObject2D[nCntPause]->BindTexture(m_nIdxTexture[nCntPause]);

				////�ʒu�ݒ�
				//m_apObject2D[nCntPause]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(pos.x, pos.y + (nCntPause * HEIGHT_MULTI * 2.0f), pos.z), WIDTH_MULTI, HEIGHT_MULTI);

				////��ސݒ�
				//m_apObject2D[nCntPause]->SetType(CObject::TYPE_PAUSE);
			}
		}
	}

	////��ސݒ�
	//CObject::SetType(CObject::TYPE_PAUSE);

	return S_OK;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CPause::Uninit(void)
{
	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		if (m_apObject2D[nCntPause] != NULL)
		{//�g�p����Ă�Ƃ�

		 //�I������
			m_apObject2D[nCntPause]->Uninit();
			m_apObject2D[nCntPause] = NULL;
		}
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void CPause::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//�L�[�{�[�h�̏��擾
	//CGame *pGame = CGame::GetMode();		//�Q�[���̏��擾
	CFade *pFade = CManager::Get()->GetFade();		//�t�F�[�h�̏��擾
	//CSound *pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{//P�L�[�������ꂽ

		m_nSelect = PAUSE_CONTINUE;		//�|�[�Y���j���[�̏�����
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{//W�L�[�������ꂽ

	 ////BGM�Đ�
		//pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);

		if (m_nSelect >= PAUSE_RETRY)
		{//��֐i��

			m_nSelect--;
		}
		else if (m_nSelect == PAUSE_CONTINUE)
		{//QUIT�ɖ߂�

			m_nSelect = PAUSE_QUIT;
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{//S�L�[�������ꂽ

	 ////BGM�Đ�
		//pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);

		if (m_nSelect == PAUSE_QUIT)
		{//CONTINUE�ɖ߂�

			m_nSelect = PAUSE_CONTINUE;
		}
		else if (m_nSelect >= PAUSE_CONTINUE)
		{//���֐i��

			m_nSelect++;
		}
	}

	for (int nCntPause = 0; nCntPause < PAUSE_MAX; nCntPause++)
	{
		if (m_apObject2D[nCntPause] != NULL)
		{
			//�F�ݒ�
			if (m_nSelect == nCntPause)
			{//�I�������摜��������

				//m_apObject2D[m_nSelect]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			}
			else if (m_nSelect != nCntPause)
			{//�I�����ĂȂ��摜��������

				//m_apObject2D[nCntPause]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

			}
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//����L�[�iENTER�L�[�j�������ꂽ

	 ////BGM�Đ�
		//pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

		switch (m_nSelect)
		{
		case PAUSE_CONTINUE:		//�R���e�B�j���[

									//�Q�[���ĊJ
			//pGame->SetEnablePauseMenu(false);
			break;

		case PAUSE_RETRY:			//���g���C

									//�|�[�Y����
			//pGame->SetEnablePauseMenu(false);

			//���[�h�ݒ�(�Q�[����ʂ̍ŏ��Ɉڍs)
			CManager::Get()->GetFade()->Set(CScene::MODE_GAME);			//�t�F�[�h�A�E�g
			break;

		case PAUSE_QUIT:			//�^�C�g��

									//�|�[�Y����
			//pGame->SetEnablePauseMenu(false);

			//���[�h�ݒ�(�^�C�g����ʂɈڍs)
			//CManager::GetMode() == CScene::MODE_GAME
			CManager::Get()->GetFade()->Set(CScene::MODE_TITLE);
			//pGame->SetMode(CScene::MODE_TITLE);				//�t�F�[�h�A�E�g
			break;
		}
	}
	//pDebugProc->Print("\n�^�C�g��\n");

}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void CPause::Draw(void)
{

}