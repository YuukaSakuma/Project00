//==============================================================
//
//�X�R�A����[score.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "time.h"
#include "manager.h"
#include "number.h"
#include"object.h"

//==============================================================
//�X�R�A�̃R���X�g���N�^
//==============================================================
CTime::CTime()
{
	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		m_apNumber[nCntNum] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_fAnimTime = 0.0f;
	m_nldxTexture = -1;
} 

//==============================================================
//�X�R�A�̃f�X�g���N�^
//==============================================================
CTime::~CTime()
{

}

//==============================================================
//�X�R�A�̐�������
//==============================================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		//�X�R�A�̐����̐���
		pTime = new CTime;

		if (pTime != NULL)
		{
			//�l��������
			pTime->m_pos = pos;
			
			//����������
			pTime->Init();
		}
	}
	return pTime;
}

//==============================================================
//�X�R�A�̏���������
//==============================================================
HRESULT CTime::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\number.png");

	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		CNumber *pNum = m_apNumber[nCntNum];

		if (m_apNumber[nCntNum] == NULL)
		{
			D3DXVECTOR3 pos = m_pos;
			pos.x += nCntNum * 50.0f;	// ���ړ�

			//�����̐���
			m_apNumber[nCntNum] = CNumber::Create(pos, 50.0f, 70.0f );

			if (m_apNumber[nCntNum] != NULL)
			{
				//�e�N�X�`���̊��蓖��
				m_apNumber[nCntNum]->GetObject2D()->BindTexture(m_nldxTexture);
			}
		}
	}
	return S_OK;
}

//==============================================================
//�X�R�A�̏I������
//==============================================================
void CTime::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCntNum]->Uninit();

			delete m_apNumber[nCntNum];

			m_apNumber[nCntNum] = NULL;
		}
	}
}

//==============================================================
//�X�R�A�̍X�V����
//==============================================================
void CTime::Update(void)
{
	m_fAnimTime++;

	if (m_fAnimTime >= 60)
	{// 60�t���[��������
		m_fAnimTime = 0;	// �J�E���^�[���Z�b�g
		Add(-1);
	}
}

//==============================================================
//�X�R�A�̕`�揈��
//==============================================================
void CTime::Draw(void)
{

}

//==============================================================
//�X�R�A�̐ݒ菈��
//==============================================================
void CTime::Set(int nNum)
{
	//�l����
	m_nNum = nNum;
	m_nSetNum = nNum;

	//���������߂�
	SetValue();
}

//==============================================================
//�X�R�A�̉��Z����
//==============================================================
void CTime::Add(int nValue)
{
	//�l��ǉ�
	m_nNum += nValue;

	//���������߂�
	SetValue();
}

//==============================================================
//���̒l�����߂鏈��
//==============================================================
void CTime::SetValue(void)
{
	int aTexU[NUM_TEX] = {};		//�i�[�p

	if (m_nNum < 0)
	{//0�ȉ��̂Ƃ�
		m_nNum = 0;
	}
	else if (m_nNum >= 60 * 100)
	{
		m_nNum = 60 * 100 - 1;
	}

	//�^�C����z��Ɋi�[
	aTexU[0] = m_nNum / 60 / 10;
	aTexU[1] = m_nNum / 60 - aTexU[0] * 10;
	aTexU[2] = m_nNum % 60 / 10;
	aTexU[3] = m_nNum % 60 - aTexU[2] * 10;

	for (int nCntNum = 0; nCntNum < NUM_TEX; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{// �g�p����Ă���ꍇ
		
			//������ݒ肷��
			m_apNumber[nCntNum]->SetNumber(aTexU[nCntNum]);
		}
	}
}