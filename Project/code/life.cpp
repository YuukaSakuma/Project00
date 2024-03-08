//==============================================================
//
//�e����[player.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"life.h"
#include"manager.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"texture.h"

//�}�N����`
#define WIDTH				(10.0f)			//����
#define HEIGHT				(10.0f)			//�c��
#define VERTICL_BILL		(0.0f)			//�c��
#define LIFE				(50)			//����
#define EFFECT_LIFE			(15)			//�G�t�F�N�g�̎���
#define PARTICLE_LIFE		(50)			//�p�[�e�B�N���̎���
#define EFFECT_RADIUS		(20.0f)			//�G�t�F�N�g�̔��a
#define PARTICLE_RADIUS		(50.0f)			//�p�[�e�B�N���̔��a

//==============================================================
//�R���X�g���N�^
//==============================================================
CLife::CLife()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nLife = LIFE;								//����
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CLife::~CLife()
{

}

//==============================================================
//�e�̐�������
//==============================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,TYPE type)
{
	CLife *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CLife;

		//����������
		pBullet->Init();

		pBullet->SetPosition(pos);

		pBullet->SetRotation(rot);

		pBullet->SetMove(move);

		pBullet->SetType(type);
	}

	return pBullet;
}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CLife::Init(void)
{
	//�I�u�W�F�N�g2D�̏���������
	CBillboard::Init();

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_BULLET);

	//�T�C�Y�̐ݒ�
	SetSize(WIDTH, HEIGHT, VERTICL_BILL);

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CLife::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CLife::Update(void)
{
	CBillboard::SetPosition(m_pos);

	//�I�u�W�F�N�g2D�̍X�V����
	CBillboard::Update();
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CLife::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CBillboard::Draw();
}