//==============================================================
//
//�X�R�A����[score.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "score.h"
#include "manager.h"
#include "number.h"
#include"object.h"

//�}�N����`�@

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;		//�e�N�X�`��
CNumber *CScore::m_apNumber[NUM_SCORE] = {};
int CScore::m_nNumber = 0;			//�X�R�A�̒l

//==============================================================
//�X�R�A�̃R���X�g���N�^
//==============================================================
CScore::CScore()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_nNumber = 0;								//�X�R�A�̒l

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore] = 0;
	}
} 

//==============================================================
//�X�R�A�̃f�X�g���N�^
//==============================================================
CScore::~CScore()
{

}

//==============================================================
//�X�R�A�̐�������
//==============================================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{
		//�X�R�A�̐����̐���
		pScore = new CScore;

		if (pScore != NULL)
		{
			//�l��������
			pScore->m_pos = pos;
			
			//����������
			pScore->Init();
		}
	}
	return pScore;
}

//==============================================================
//�X�R�A�̏���������
//==============================================================
HRESULT CScore::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\number.png");

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] == NULL)
		{
			D3DXVECTOR3 pos = m_pos;

			//���ɂ��炷
			pos.x += nCntScore * 60;

			//�����̐���
			m_apNumber[nCntScore] = CNumber::Create(pos, 50.0f, 70.0f );

			if (m_apNumber[nCntScore] != NULL)
			{
				//�e�N�X�`���̊��蓖��
				m_apNumber[nCntScore]->GetObject2D()->BindTexture(m_nldxTexture);

				////��ނ̐ݒ�
				//SetType(TYPE_SCORE);
			}
		}
	}

	//�X�R�A�̐ݒ�
	CScore::Set(m_nNumber);

	return S_OK;
}

//==============================================================
//�X�R�A�̏I������
//==============================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] != NULL)
		{
			if (m_apNumber[nCntScore] != NULL)
			{// �g�p���Ă��Ȃ��ꍇ
				m_apNumber[nCntScore]->Uninit();

				delete m_apNumber[nCntScore];

				m_apNumber[nCntScore] = NULL;
			}
		}
	}
}
//==============================================================
//�X�R�A�̍X�V����
//==============================================================
void CScore::Update(void)
{

}

//==============================================================
//�X�R�A�̕`�揈��
//==============================================================
void CScore::Draw(void)
{

}

//==============================================================
//�X�R�A�̐ݒ菈��
//==============================================================
void CScore::Set(int nNum)
{
	//�l����
	m_nNumber = nNum;

	//���������߂�
	SetValue();
}

//==============================================================
//�X�R�A�̉��Z����
//==============================================================
void CScore::Add(int nValue)
{
	//�l��ǉ�
	m_nNumber += nValue;

	//���������߂�
	SetValue();
}

//==============================================================
//�X�R�A�̌��̒l�����߂鏈��
//==============================================================
void CScore::SetValue(void)
{
	if (m_nNumber < 0)
	{//0�ȉ��̂Ƃ�
		m_nNumber = 0;
	}

	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//���̒l�����߂�
		int nNum = m_nNumber % (int)pow(10, (NUM_SCORE - nCntScore)) / (int)pow(10, (NUM_SCORE - nCntScore) - 1);

		if (m_apNumber[nCntScore] != NULL)
		{// �g�p����Ă���ꍇ
		
			//������ݒ肷��
			m_apNumber[nCntScore]->SetNumber(nNum);
		}
	}
}

//===============================================
// �F�ݒ�
//===============================================
void CScore::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}