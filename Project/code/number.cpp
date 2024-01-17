//==============================================================
//
//�}���`�w�i����[multibg.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "number.h"
#include "manager.h"
#include"object2D.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
//==============================================================
//�}���`�e�N�X�`���̃R���X�g���N�^
//==============================================================
CNumber::CNumber()
{
	m_aObject2D = NULL;

	m_nNumber = 0;
}

//==============================================================
//�}���`�e�N�X�`���̃f�X�g���N�^
//==============================================================
CNumber::~CNumber()
{

}

//==============================================================
//�}���`�e�N�X�`���̐�������
//==============================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{//���������g�p����ĂȂ�������

		//�����̐���
		pNumber = new CNumber;

		//����������
		pNumber->Init(pos, fWidth, fHeight);
	}
	return pNumber;
}

//==============================================================
//�����̏���������
//==============================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\number.png");

	if (m_aObject2D == NULL)
	{// �g�p����Ă��Ȃ��ꍇ

		//�I�u�W�F�N�g2D�̐���
		m_aObject2D = CObject2D::Create();

		if (m_aObject2D != NULL)
		{// �g�p����Ă���ꍇ

			// ����������
			m_aObject2D->Init();

			//�e�N�X�`���ԍ��̐ݒ�
			m_aObject2D->BindTexture(m_nldxTexture);

			// �e�N�X�`���ݒ�
			SetNumber(m_nNumber);

			//�ʒu�̐ݒ�
			m_aObject2D->SetPosition(pos);

			//�T�C�Y�̐ݒ�
			m_aObject2D->SetSize(fWidth, fHeight);
		}
	}

	return S_OK;
}

//==============================================================
//�����̏I������
//==============================================================
void CNumber::Uninit(void)
{
	// �I������
	m_aObject2D->Uninit();
}
//==============================================================
//�����̍X�V����
//==============================================================
void CNumber::Update(void)
{
	// �X�V����
	m_aObject2D->Update();
}

//==============================================================
//�����̕`�揈��
//==============================================================
void CNumber::Draw(void)
{
	// �`�揈��
	m_aObject2D->Draw();	
}

//==============================================================
//�����̎擾
//==============================================================
CObject2D * CNumber::GetObject2D(void)
{
	return m_aObject2D;
}

//==============================================================
//�����̐ݒ菈��
//==============================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;	// �l��ݒ�

	if (m_nNumber > 10)
	{// �l�����E�𒴂����ꍇ
		m_nNumber = 9;
	}
	else if (m_nNumber < 0)
	{// �l���Œ�l�𒴂����ꍇ
		m_nNumber = 0;
	}

	if (m_aObject2D != NULL)
	{// �g�p����Ă���ꍇ

	 // ���_���̐ݒ�
		m_aObject2D->SetVtx(m_nNumber, 0.1f);
	}
}