//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "titleTex.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

#define APPEAR_CNT		(60)			//�_�ŃJ�E���g
#define APPEAR_CNT_MIN	(2)				//�_�ŃJ�E���g(Enter�������Ƃ�)

//�ÓI�����o�ϐ�
CObject2D *CTitleTex::m_apObject2D[NUM_TITLE_TEX] = {};

//==============================================================
//�R���X�g���N�^
//==============================================================
CTitleTex::CTitleTex()
{
	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���̔ԍ�
	}

	m_nCntAppear = APPEAR_CNT;			//�_�ŃJ�E���^�[
	m_state = STATE_NONE;
	m_bAppear = true;
	m_fAlpha = 1.0f;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CTitleTex::~CTitleTex()
{

}

//==============================================================
//��������
//==============================================================
CTitleTex *CTitleTex::Create(void)
{
	CTitleTex *pTitleTex = NULL;

	if (pTitleTex == NULL)
	{//���������g�p����ĂȂ�������

	 //�^�C�g���e�N�X�`���̐���
		pTitleTex = new CTitleTex;

		//����������
		pTitleTex->Init();

		//��ސݒ�
		pTitleTex->SetType(TYPE_NONE);
	}

	return pTitleTex;
}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CTitleTex::Init(void)
{
	CTexture *pTexture = CManager::Get()->GetTexturet();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regist("data\\TEXTURE\\title_logo00.png");
	m_nIdxTexture[1] = pTexture->Regist("data\\TEXTURE\\pressenter.png");

	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		//���������u
		if (m_apObject2D[nCntTex] == NULL)
		{//�g�p����ĂȂ��Ƃ�

		 //2D�I�u�W�F�N�g����
			m_apObject2D[nCntTex] = CObject2D::Create();

			if (m_apObject2D[nCntTex] != NULL)
			{//�����o������

			 //�傫���ݒ�
				m_apObject2D[nCntTex]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

				//�e�N�X�`�����蓖��
				m_apObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);

				//�ʒu�ݒ�
				if (nCntTex == 0)
				{
					m_apObject2D[nCntTex]->SetPosition( D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f));

					m_apObject2D[nCntTex]->SetSize(400.0f, 200.0f);

				}
				else if (nCntTex == 1)
				{
					m_apObject2D[nCntTex]->SetPosition( D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f));
					m_apObject2D[nCntTex]->SetSize(300.0f, 150.0f);
				}
			}
		}
	}

	//��ސݒ�
	CObject::SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CTitleTex::Uninit(void)
{

	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] != NULL)
		{//�g�p����Ă�Ƃ�

		 //�I������
			m_apObject2D[nCntTex]->Uninit();
			m_apObject2D[nCntTex] = NULL;
		}
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void CTitleTex::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//�L�[�{�[�h�̏��擾
	CFade *pFade = CManager::Get()->GetFade();		//�t�F�[�h�̏��擾

	switch (m_state)
	{
	case STATE_NONE:		//�ʏ���

		if ((m_nCntAppear % APPEAR_CNT) == 0)
		{//��莞�Ԃ�������

			m_bAppear = m_bAppear ? false : true;

		}

		if (m_bAppear == true)
		{
			m_fAlpha += 1.0f / APPEAR_CNT;
			m_apObject2D[0]->SetPosition(D3DXVECTOR3(m_apObject2D[0]->GetPosition().x, m_apObject2D[0]->GetPosition().y + 0.1f, m_apObject2D[0]->GetPosition().z));
			m_apObject2D[0]->SetSize(400.0f, 200.0f);
		}
		else if (m_bAppear == false)
		{
			m_fAlpha -= 1.0f / APPEAR_CNT;
			m_apObject2D[0]->SetPosition(D3DXVECTOR3(m_apObject2D[0]->GetPosition().x, m_apObject2D[0]->GetPosition().y - 0.1f, m_apObject2D[0]->GetPosition().z));
			m_apObject2D[0]->SetSize(400.0f, 200.0f);
		}

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{//Enter�L�[����������

			//CSound *pSound = CManager::GetSound();

			//SE�Đ�
			//pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);

			m_state = STATE_APPEAR;
			m_nCntAppear = 0;		//�_�ŃJ�E���^�[
		}

		break;

	case STATE_APPEAR:

		if ((m_nCntAppear % APPEAR_CNT_MIN) == 0)
		{//��莞�Ԃ�������

			m_bAppear = m_bAppear ? false : true;
		}

		if (m_nCntAppear >= 60)
		{//��莞�Ԃ�������

			pFade->Set(CScene::MODE_TUTORIAL);
		}

		break;
	}

	//�_�ł�����
	if (m_bAppear == true && m_state == STATE_APPEAR)
	{
		m_apObject2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
	else if (m_bAppear == false && m_state == STATE_APPEAR)
	{
		m_apObject2D[1]->SetCol( D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	}
	else
	{
		m_apObject2D[1]->SetCol( D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

	}

	m_nCntAppear++;

}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void CTitleTex::Draw(void)
{

}