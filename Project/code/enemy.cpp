//==============================================================
//
//�e����[player.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"enemy.h"
#include"manager.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"score.h"
#include"billboard.h"
#include"texture.h"
#include"object.h"
#include"objectX.h"

//�}�N����`
#define WIDTH				(10.0f)			//����
#define HEIGHT				(10.0f)			//�c��
#define VERTICL_BILL		(0.0f)			//�c��
#define LIFE				(50)			//����
#define EFFECT_LIFE			(15)			//�G�t�F�N�g�̎���
#define PARTICLE_LIFE		(50)			//�p�[�e�B�N���̎���
#define EFFECT_RADIUS		(20.0f)			//�G�t�F�N�g�̔��a
#define PARTICLE_RADIUS		(50.0f)			//�p�[�e�B�N���̔��a
#define ADD_SCORE			(1111)			//�X�R�A

//==============================================================
//�R���X�g���N�^
//==============================================================
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nLife = LIFE;								//����
	//m_BType = TYPE_A;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//�e�̐�������
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CEnemy;

		//����������
		pBullet->Init();

		pBullet->SetPosition(pos);

		pBullet->SetRotation(rot);
	}

	return pBullet;
}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CEnemy::Init(void)
{
	//�I�u�W�F�N�g2D�̏���������
	CObjectX::Init();

	////��ނ̐ݒ�
	//CObject::SetType(CObject::TYPE_BULLET);

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CEnemy::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObjectX::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CEnemy::Update(void)
{
	//�O��̈ʒu����
	m_posOld = m_pos;

	//�ʒu���X�V
	m_pos += m_move;


	//�I�u�W�F�N�g2D�̍X�V����
	CObjectX::Update();
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CEnemy::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObjectX::Draw();
}