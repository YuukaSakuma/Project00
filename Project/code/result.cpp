//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "objectX.h"
#include "fade.h"
#include "score.h"
#include "ranking.h"

//�ÓI�����o�ϐ�
CScore *CResult::m_pScore = NULL;
int CResult::m_nScore = 0;

//==============================================================
//�R���X�g���N�^
//==============================================================
CResult::CResult()
{

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CResult::~CResult()
{

}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CResult::Init(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	// ���S�̐���
	CObject2D *p = CObject2D::Create();
	p->BindTexture(CManager::Get()->GetTexturet()->Regist("data\\TEXTURE\\result.png"));
	p->SetPosition(D3DXVECTOR3(600.0f, SCREEN_HEIGHT * 0.15f, 0.0f));
	p->SetSize(400, 150);

	m_pScore = CScore::Create(D3DXVECTOR3(400.0f, 500.0f, 0.0f));
	m_pScore->Set(m_nScore);

	pSound->Play(pSound->SOUND_LABEL_RESULT);

	return S_OK;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CResult::Uninit(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Stop();

	m_nScore = 0;

	// �X�R�A
	if (m_pScore != NULL)
	{
		CRanking::SetScore(m_pScore->Get());
		m_pScore->Uninit();
		delete m_pScore;	// �������̊J��
		m_pScore = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void CResult::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//�L�[�{�[�h�̏��擾

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//ENTER�L�[��������

	 //�`���[�g���A�����
		CManager::Get()->GetFade()->Set(MODE_RANKING);
	}
	
	//CScene::Update();

	pDebugProc->Print("\n���U���g\n");
}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void CResult::Draw(void)
{

}