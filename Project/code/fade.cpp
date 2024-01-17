//==============================================================
//
//�t�F�[�h����[fade.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"fade.h"

//�ÓI�����o�ϐ�

//==============================================================
//�R���X�g���N�^
//==============================================================
CFade::CFade()
{
	m_state = STATE_NONE;
	m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CFade::~CFade()
{


}

//==============================================================
//��������
//==============================================================
CFade *CFade::Create(CScene::MODE modeNext)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;

		if (pFade != NULL)
		{
			pFade->Init(modeNext);
			pFade->SetState(STATE_IN);
		}
	}

	return pFade;
}

//==============================================================
//����������
//==============================================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	CObject2D::Init();

	//�T�C�Y�ݒ�
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetVtx(0.0f, 0.0f);

	Set(modeNext);

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//==============================================================
//�X�V����
//==============================================================
void CFade::Update(void)
{
	if (m_state != STATE_NONE)
	{//�������Ă��Ȃ���ԈȊO�̂Ƃ�

		if (m_state == STATE_IN)
		{//�t�F�[�h�C�����

			m_Col.a -= 0.02f;

			if (m_Col.a <= 0.0f)
			{//���S�ɓ����ɂȂ�����

				m_Col.a = 0.0f;
				m_state = STATE_NONE;
			}
		}
		else if (m_state == STATE_OUT)
		{//�t�F�[�h�A�E�g���

			m_Col.a += 0.02f;

			if (m_Col.a >= 1.0f)
			{//���S�ɕs�����ɂȂ�����

				m_Col.a = 1.0f;

				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
				return;
			}
		}
	}

	SetCol(m_Col);
}

//==============================================================
//�`�揈��
//==============================================================
void CFade::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//==============================================================
//���̉�ʐݒ�
//==============================================================
void CFade::Set(CScene::MODE modeNext)
{
	if (m_state != STATE_OUT)
	{
		m_state = STATE_OUT;
		m_modeNext = modeNext;
		m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//==============================================================
//��Ԑݒ�
//==============================================================
void CFade::SetState(STATE state)
{
	if (m_state == state)
	{
		return;
	}

	m_state = state;

	switch (m_state)
	{
	case STATE_NONE:

		m_Col.a = 0.0f;
		
		break;

	case STATE_IN:

		m_Col.a = 1.0f;

		break;

	case STATE_OUT:

		m_Col.a = 0.0f;

		break;
	default:
		break;
	}

	SetCol(m_Col);
}