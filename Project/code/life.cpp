//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"renderer.h"
#include"life.h"
#include"input.h"
#include"titleTex.h"
#include"fade.h"
#include"game.h"
#include"playermodel.h"

#define WIDTH_LIFE		(400.0f)		//�̗͕\���̉���
#define HEIGHT_LIFE		(20.0f)			//�̗͕\���̏c��



//�ÓI�����o�ϐ�
CObject2D *CLife::m_apObject2D[NUM_LIFE_FRAME] = {};		//�I�u�W�F�N�g2D�̏��

//==============================================================
//�R���X�g���N�^
//==============================================================
CLife::CLife()
{
	for (int nCntTex = 0; nCntTex < NUM_LIFE_FRAME; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���̔ԍ�
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
												//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���

	m_nNumCon = 0;		//�̗͏��
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CLife::CLife(D3DXVECTOR3 pos)
{
	for (int nCntTex = 0; nCntTex < NUM_LIFE_FRAME; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���̔ԍ�
	}

	m_pos = pos;		//�ʒu

	m_nNumCon = 0;		//�̗͏��
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CLife::~CLife()
{

}

//==============================================================
//�̗͕\���̐�������
//==============================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{//���������g�p����ĂȂ�������

	 //�̗͕\���̐���
		pLife = new CLife(pos);
	}

	if (pLife != NULL)
	{//�������m�ۂł��Ă���

	 //����������
		pLife->Init();
	}

	return pLife;
}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CLife::Init(void)
{
	CTexture *pTexture = CManager::Get()->GetTexturet();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regist("data\\TEXTURE\\life.jpg");
	m_nIdxTexture[1] = pTexture->Regist("data\\TEXTURE\\life01.png");

	//���������u
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		if (m_apObject2D[nCntLife] == NULL)
		{//�g�p����ĂȂ��Ƃ�

		 //2D�I�u�W�F�N�g����
			m_apObject2D[nCntLife] = CObject2D::Create();

			if (m_apObject2D[nCntLife] != NULL)
			{//�����o������

			 //�傫���ݒ�
				m_apObject2D[nCntLife]->SetSize(WIDTH_LIFE, HEIGHT_LIFE);

				//�e�N�X�`�����蓖��
				m_apObject2D[nCntLife]->BindTexture(m_nIdxTexture[nCntLife]);

				//�ʒu�ݒ�
				m_apObject2D[nCntLife]->SetPosition(m_pos);

				m_apObject2D[0]->SetVtxBlock(WIDTH_LIFE - m_nNumCon, HEIGHT_LIFE);
			}
		}
	}

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_BLOCK);

	
	return S_OK;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CLife::Uninit(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		if (m_apObject2D[nCntLife] != NULL)
		{
			m_apObject2D[nCntLife]->Uninit();
			m_apObject2D[nCntLife] = NULL;
		}
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void CLife::Update(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		//�I�u�W�F�N�g2D�̍X�V����
		m_apObject2D[nCntLife]->Update();

		//�ʒu�X�V
		m_apObject2D[0]->SetPosition(m_pos);
		m_apObject2D[0]->SetVtxBlock(float(m_nMaxLife - m_nNumCon), HEIGHT_LIFE);

	}
}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void CLife::Draw(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		//2D�I�u�W�F�N�g�̕`�揈��
		m_apObject2D[nCntLife]->Draw();
	}
}

//==============================================================
//�̗͕\���̐ݒ菈��
//==============================================================
void CLife::SetNum(int nNumBullet)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	if (nNumBullet > 0)
	{//�񕜂̏ꍇ

		if ((m_nMaxLife - m_nNumCon) < m_nMaxLife - nNumBullet)
		{//�񕜗ʂ��̗͂�菭�Ȃ��ꍇ

			m_nNumCon -= nNumBullet;
		}
		else
		{
			m_nNumCon = 0;
		}


	}
	else if ((m_nMaxLife - m_nNumCon) > 0)
	{//�̗͂���������

		m_nNumCon -= nNumBullet;

	}
	else
	{
		//�v���C���[�����S��Ԃɂ���
		//pPlayer->SetState(STATE_DEATH);
	}
}