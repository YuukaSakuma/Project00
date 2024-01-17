//==============================================================
//
//�p�[�e�B�N������[particle.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"manager.h"
#include"effect.h"
#include"particle.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^

//==============================================================
//�R���X�g���N�^
//==============================================================
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fRadius = 0.0f;
	m_nType = TYPE_NONE;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CParticle::~CParticle()
{

}

//==============================================================
//�p�[�e�B�N���̐�������
//==============================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col,TYPE type, float fRadius, int nLife)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pParticle = new CParticle;

		//����������
		pParticle->Init();

		//�p�[�e�B�N���̐ݒ�
		pParticle->Set(pos, col, type, fRadius, nLife);
	}

	return pParticle;
}

//==============================================================
//�p�[�e�B�N���̏���������
//==============================================================
HRESULT CParticle::Init(void)
{
	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_PARTICLE);

	//���a�̐ݒ�
	//SetRadius(m_fRadius);

	return S_OK;
}

//==============================================================
//�p�[�e�B�N���̏I������
//==============================================================
void CParticle::Uninit(void)
{

}

//==============================================================
//�p�[�e�B�N���̍X�V����
//==============================================================
void CParticle::Update(void)
{

}

//==============================================================
//�p�[�e�B�N���̕`�揈��
//==============================================================
void CParticle::Draw(void)
{

}

//==============================================================
//�p�[�e�B�N���̐ݒ菈��
//==============================================================
void CParticle::Set(D3DXVECTOR3 pos, D3DXCOLOR col, CObject::TYPE type, float fRadius, int nLife)
{
	m_nType = type;

	//�p�[�e�B�N���̐���
	for (int nCntAppear = 0; nCntAppear < 30; nCntAppear++)
	{
		if (m_nType == TYPE_ENEMY)
		{
			//�ʒu�̐ݒ�
			m_pos = pos;

			//�p�x�����߂�
			m_fAngle = (float)(rand() % 629 - 314) / 1.0f;

			//�ړ��ʂ����߂�
			m_fMove = (float)(rand() % 50) / 10.0f + 1.0f;

			//�ړ��ʂ̐ݒ�
			m_move.x = sinf(m_fAngle) * m_fMove;
			m_move.y = cosf(m_fAngle) * m_fMove;
			//m_move.z = cosf(m_fAngle) * m_fMove;

			//�F�̐ݒ�
			m_col = col;

			//���a�̐ݒ�
			m_fRadius = fRadius;

			//�����̐ݒ�
			m_nLife = nLife;

			m_nType = type;
		}
		//�G�t�F�N�g�̐���
		CEffect::Create(m_pos,m_move,m_col,m_fRadius,m_nLife);
	}
}