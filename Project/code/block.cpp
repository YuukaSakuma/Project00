//==============================================================
//
//�u���b�N����[block.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"block.h"
#include"manager.h"

//�}�N����`
#define WIDTH				(50.0f)			//����
#define HEIGHT				(50.0f)			//�c��
#define EFFECT_LIFE			(15)			//�G�t�F�N�g�̎���
#define PARTICLE_LIFE		(50)			//�p�[�e�B�N���̎���
#define EFFECT_RADIUS		(20.0f)			//�G�t�F�N�g�̔��a
#define PARTICLE_RADIUS		(50.0f)			//�p�[�e�B�N���̔��a
#define ADD_SCORE			(1111)			//�X�R�A

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^

float CBlock::m_fWidth = 0.0f;
float CBlock::m_fHeight = 0.0f;

//==============================================================
//�R���X�g���N�^
//==============================================================
CBlock::CBlock()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_fWidth = WIDTH;
	m_fHeight = HEIGHT;
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CBlock::CBlock(TYPE type, D3DXVECTOR3 pos)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	m_fWidth = WIDTH;
	m_fHeight = HEIGHT;

	//�ʒu�̐ݒ�
	CBlock::SetPosition(pos);

	//��ނ̐ݒ�
	SetType(type);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBlock::~CBlock()
{
	 
}

//==============================================================
//�u���b�N�̐�������
//==============================================================
CBlock *CBlock::Create(TYPE type, D3DXVECTOR3 pos)
{
	CBlock *pBullet = NULL;

	if (pBullet == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBullet = new CBlock(type,pos);

		//����������
		pBullet->Init();
	}

	return pBullet;
}

//==============================================================
//�u���b�N�̏���������
//==============================================================
HRESULT CBlock::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\block000.png");

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	//��ނ̐ݒ�
	SetType(TYPE_BLOCK);

	//�T�C�Y�̐ݒ�
	SetVtxBlock(m_fWidth, m_fHeight);

	m_fWidth = WIDTH;
	m_fHeight = HEIGHT;

	return S_OK;
}

//==============================================================
//�u���b�N�̏I������
//==============================================================
void CBlock::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�u���b�N�̍X�V����
//==============================================================
void CBlock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//�ʒu�̐ݒ�
	SetPosition(pos);

	////�I�u�W�F�N�g2D�̈ʒu�ݒ菈��
	//SetSize(50.0f, 50.0f);

	//�I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();
}

//==============================================================
//�u���b�N�̕`�揈��
//==============================================================
void CBlock::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//==============================================================
//�u���b�N�̓����蔻��
//==============================================================
bool CBlock::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECT; nCntBlock++)
	{
		CObject *pObj;

		//�I�u�W�F�N�g���擾
		pObj = CObject::GetObject(nCntBlock);

		if (pObj != NULL)
		{
			CObject::TYPE type;

			//��ނ��擾
			type = pObj->GetType();

			if (type == pObj->TYPE_BLOCK)
			{//��ނ��G�̏ꍇ

				D3DXVECTOR3 posBlock = pObj->GetPosition();

				if (pPosOld->y <= posBlock.y 
					&& pPos->y > posBlock.y 
					&& pPos->x + fWidth > posBlock.x 
					&& pPos->x - fWidth < posBlock.x + m_fWidth)
				{//�u���b�N�̏�ɂ߂荞��
					pPos->y = posBlock.y;
					pMove->y = 0.0f;

					//���n����
					return true;
				}

				if (pPosOld->y - fHeight >= posBlock.y + m_fHeight 
					&& pPos->y - fHeight < posBlock.y + m_fHeight 
					&&pPos->x + fWidth > posBlock.x 
					&& pPos->x - fWidth < posBlock.x + m_fWidth)
				{//�u���b�N�̉��ɂ߂荞��
					pPos->y = posBlock.y + m_fHeight + fHeight;
					pMove->y = 0.0f;

					return false;
				}

				if (pPosOld->x + fWidth <= posBlock.x 
					&& pPos->x + fWidth > posBlock.x 
					&& pPos->y > posBlock.y 
					&& pPos->y - fHeight < posBlock.y + m_fHeight)
				{//�u���b�N�̍��ɂ߂荞��
					pPos->x = posBlock.x - fWidth;
					pMove->x = 0.0f;

					return false;
				}

				if (pPosOld->x - fWidth >= posBlock.x + m_fWidth 
					&& pPos->x - fWidth < posBlock.x + m_fWidth 
					&& pPos->y > posBlock.y 
					&& pPos->y - fHeight < posBlock.y + m_fHeight)
				{//�u���b�N�̉E�ɂ߂荞��
					pPos->x = posBlock.x + m_fWidth + fWidth;
					pMove->x = 0.0f;
					return false;
				}
			}
		}
	}
	return false;
}