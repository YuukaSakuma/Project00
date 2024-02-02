//==============================================================
//
//�e����[player.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"bullet.h"
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
CBullet::CBullet()
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
CBullet::~CBullet()
{

}

//==============================================================
//�e�̐�������
//==============================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,BulletType btype,TYPE type)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		switch (btype)
		{
		case CBullet::TYPE_A:

			pBullet = new CBulletA;

			break;

		case CBullet::TYPE_B:

			pBullet = new CBulletB;

			break;

		case CBullet::TYPE_C:

			pBullet = new CBulletC;

			break;
		
		}

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
HRESULT CBullet::Init(void)
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
void CBullet::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CBullet::Update(void)
{
	//�O��̈ʒu����
	m_posOld = m_pos;

	//�ʒu���X�V
	m_pos += m_move;

	//�G�Ƃ̓����蔻��
	if (CBullet::CollisionModel(&m_pos, &m_posOld) == true)
	{//�G�Ɠ���������

		//�����̐���
		CExplosion::Create(m_pos, CObject::TYPE_EXPLOSION);

		//�r���{�[�h�̏I������
		CBullet::Uninit();

		return;
	}

	//���������Z
	m_nLife--;

	if (m_nLife <= 0)
	{//�����������Ȃ�����
	 //�����̐���
		CExplosion::Create(m_pos, CObject::TYPE_EXPLOSION);

		//�I������
		Uninit();
		return;
	}

	CBillboard::SetPosition(m_pos);

	//�I�u�W�F�N�g2D�̍X�V����
	CBillboard::Update();
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CBullet::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CBillboard::Draw();
}

//==============================================================
//�e�̓����蔻��(2D)
//==============================================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject *pObj;

		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCntObj);

		if (pObj != NULL)
		{
			CObject::TYPE type;

			//��ނ��擾
			type = pObj->GetType();

			if (type == pObj->TYPE_ENEMY)
			{//��ނ��G�̏ꍇ
				if (pos.x >= pObj->GetPosition().x - 50.0f
					&& pos.x <= pObj->GetPosition().x + 50.0f
					&& pos.y >= pObj->GetPosition().y - 50.0f
					&& pos.y <= pObj->GetPosition().y + 50.0f)
				{
					//�����̐���
					//CExplosion::Create(pos, TYPE_EXPLOSION);

					//�p�[�e�B�N���̐���
					CParticle::Create(pos, D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f), type, PARTICLE_RADIUS, PARTICLE_LIFE);

					//�X�R�A�̉��Z
					CScore::Add(ADD_SCORE);

					//�I�u�W�F�N�g�̔j��
					pObj->Uninit();

					return TRUE;
				}
			}
			else if (type == pObj->TYPE_BLOCK)
			{//��ނ��u���b�N�̂Ƃ�

			 //�G�̈ʒu�擾
				D3DXVECTOR3 posBlock = pObj->GetPosition();

				//�u���b�N�̓����蔻��(����)
				if (CBullet::ColisionLeft(pos, posBlock) == true)
				{//�������Ă���

				 //�����̐���
				 CExplosion::Create(pos, CObject::TYPE_EXPLOSION);

					return true;
				}
			}
		}
	}
	return FALSE;
}

//==============================================================
//�����蔻�� ����
//==============================================================
bool CBullet::ColisionLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x + WIDTH >= posBlock.x 
		&& pos.x - WIDTH <= posBlock.x + 50.0f 
		&& pos.y >= posBlock.y 
		&& pos.y - HEIGHT <= posBlock.y + 50.0f)
	{//����������

		return true;
	}

	return false;
}

//==============================================================
//�����蔻��(�^��)
//==============================================================
bool CBullet::ColisionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x >= posBlock.x - 50.0f 
		&& pos.x <= posBlock.x + 50.0f 
		&& pos.y >= posBlock.y - 50.0f 
		&& pos.y <= posBlock.y + 50.0f)
	{//����������

		return true;
	}

	return false;
}

//==============================================================
//�����蔻��
//==============================================================
bool CBullet::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = GetObject(nCntModel);

		if (pObj != NULL)
		{//���������g�p����Ă���Ƃ�

		 //��ނ��擾
			CObject::TYPE type = pObj->GetType();

			if (m_type == TYPE_PLAYER)
			{
				if (type == pObj->TYPE_MODEL || type == TYPE_ENEMY)
				{//��ނ����f���̏ꍇ

				 //���f���̈ʒu�擾
					D3DXVECTOR3 posModel = pObj->GetPosition();
					//D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->y + HEIGHT > posModel.y
						&& pPos->y < posModel.y + maxModel.y)
					{
						if (pPosOld->x <= posModel.x + minModel.x
							&& pPos->x > posModel.x + minModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//���ɂ߂荞�񂾏ꍇ

							if (type == TYPE_ENEMY)
							{//�G�̏ꍇ
							 //�G�̃q�b�g����
								pObj->Hit();
							}
							return true;

						}

						if (pPosOld->x >= posModel.x + maxModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//�E�ɂ߂荞�񂾏ꍇ

							if (type == TYPE_ENEMY)
							{//�G�̏ꍇ
							 //�G�̃q�b�g����
								pObj->Hit();
							 
							}

							return true;
						}

						if (pPosOld->z <= posModel.z + minModel.z
							&& pPos->z > posModel.z + minModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//��O�ɂ߂荞�񂾏ꍇ

							if (type == TYPE_ENEMY)
							{//�G�̏ꍇ

							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->z >= posModel.z + maxModel.z
							&& pPos->z < posModel.z + maxModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//���ɂ߂荞�񂾏ꍇ

							if (type == TYPE_ENEMY)
							{//�G�̏ꍇ
							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y <= posModel.y + minModel.y
							&& pPos->y > posModel.y + minModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//��ɂ߂荞�񂾏ꍇ

							if (type == TYPE_ENEMY)
							{//�G�̏ꍇ

							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y >= posModel.y + maxModel.y
							&& pPos->y < posModel.y + maxModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//��ɂ߂荞�񂾏ꍇ

							if (type == TYPE_ENEMY)
							{//�G�̏ꍇ

							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}
					}
				}
			}
			else if (m_type == TYPE_ENEMY)
			{
				if (type == pObj->TYPE_MODEL || type == TYPE_PLAYER)
				{//��ނ����f���̏ꍇ

				 //���f���̈ʒu�擾
					D3DXVECTOR3 posModel = pObj->GetPosition();
					//D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->y + HEIGHT > posModel.y
						&& pPos->y < posModel.y + maxModel.y)
					{
						if (pPosOld->x <= posModel.x + minModel.x
							&& pPos->x > posModel.x + minModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//���ɂ߂荞�񂾏ꍇ

							if (type == TYPE_PLAYER)
							{//�G�̏ꍇ
							 //�G�̃q�b�g����
								pObj->Hit();
							}
							return true;

						}

						if (pPosOld->x >= posModel.x + maxModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//�E�ɂ߂荞�񂾏ꍇ


							if (type == TYPE_PLAYER)
							{//�G�̏ꍇ
							 //�G�̃q�b�g����
								pObj->Hit();

							}

							return true;
						}

						if (pPosOld->z <= posModel.z + minModel.z
							&& pPos->z > posModel.z + minModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//��O�ɂ߂荞�񂾏ꍇ

							if (type == TYPE_PLAYER)
							{//�G�̏ꍇ

							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->z >= posModel.z + maxModel.z
							&& pPos->z < posModel.z + maxModel.z
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x)
						{//���ɂ߂荞�񂾏ꍇ

							if (type == TYPE_PLAYER)
							{//�G�̏ꍇ
							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y <= posModel.y + minModel.y
							&& pPos->y > posModel.y + minModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//��ɂ߂荞�񂾏ꍇ

							if (type == TYPE_PLAYER)
							{//�G�̏ꍇ

							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}

						if (pPosOld->y >= posModel.y + maxModel.y
							&& pPos->y < posModel.y + maxModel.y
							&& pPos->x > posModel.x + minModel.x
							&& pPos->x < posModel.x + maxModel.x
							&& pPos->z > posModel.z + minModel.z
							&& pPos->z < posModel.z + maxModel.z)
						{//��ɂ߂荞�񂾏ꍇ

							if (type == TYPE_PLAYER)
							{//�G�̏ꍇ

							 //�G�̃q�b�g����
								pObj->Hit();
							}

							return true;
						}
					}
				}
			}
		}
	}
	return false;
}


bool CBullet::CollisionData(D3DXVECTOR3 pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		//�I�u�W�F�N�g�̎擾
		CObject *pObj = GetObject(nCntObject);

		if (pObj != NULL)
		{
			//��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_ENEMY || type == TYPE_MODEL)
			{//��ނ��G�̏ꍇ

				D3DXVECTOR3 posEne = pObj->GetPosition();

				//�����蔻��
				if (pos.x >= posEne.x - 30.0f  && pos.x <= posEne.x + 30.0f
					&&	pos.z >= posEne.z - 30.0f && pos.z <= posEne.z + 30.0f)
				{
					//�����̐���
					CExplosion::Create(pos, TYPE_EXPLOSION);

					//pObj->Uninit();			//�I�u�W�F�N�g�̍폜
					//Release();			//�������g(�e)�̔j��

					return TRUE;
				}
			}
		}
	}


	return false;
}

//==============================================================
//�R���X�g���N�^
//==============================================================
CBulletA::CBulletA()
{
	
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBulletA::~CBulletA()
{

}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CBulletA::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexture();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\ball000.png");

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	CBullet::Init();

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CBulletA::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CBulletA::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = GetPosition();

	//�G�t�F�N�g�̐���
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), EFFECT_RADIUS, EFFECT_LIFE);
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CBulletA::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CBullet::Draw();
}

//==============================================================
//�R���X�g���N�^
//==============================================================
CBulletB::CBulletB()
{

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBulletB::~CBulletB()
{

}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CBulletB::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexture();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\bullet000.png");

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	CBullet::Init();

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CBulletB::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CBulletB::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = GetPosition();

	//�G�t�F�N�g�̐���
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), EFFECT_RADIUS, EFFECT_LIFE);
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CBulletB::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CBullet::Draw();
}

//==============================================================
//�R���X�g���N�^
//==============================================================
CBulletC::CBulletC()
{

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBulletC::~CBulletC()
{

}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CBulletC::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexture();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\ball000.png");

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	CBullet::Init();

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CBulletC::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CBulletC::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = GetPosition();

	//�G�t�F�N�g�̐���
	CEffect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECT_RADIUS, EFFECT_LIFE);
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CBulletC::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CBullet::Draw();
}