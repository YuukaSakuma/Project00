//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"renderer.h"
#include"manager.h"
#include"explosion.h"

//�}�N����`
#define LIFE (100)			//����
#define SIZE (10.0f)		//�T�C�Y

//==============================================================
//�R���X�g���N�^
//==============================================================
CExplosion::CExplosion()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nLife = LIFE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CExplosion::CExplosion(D3DXVECTOR3 pos,TYPE type)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nLife = LIFE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//�ʒu�̐ݒ�
	SetPosition(pos);

	//��ނ̎擾
	SetType(type);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CExplosion::~CExplosion()
{

}

//==============================================================
//�G�t�F�N�g�̐�������
//==============================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, TYPE type)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		//�����̐���
		pExplosion = new CExplosion(pos,type);

		//����������
		pExplosion->Init();
	}
	return pExplosion;
}

//==============================================================
//�����̏���������
//==============================================================
HRESULT CExplosion::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\explosion000.png");

	//�I�u�W�F�N�g2D�̏���������
	CBillboard::Init();

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	SetSize(SIZE, SIZE, 0.0f);
	SetVtx(m_nPatternAnim, TYPE_EXPLOSION);

	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//==============================================================
//�����̏I������
//==============================================================
void CExplosion::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�����̍X�V����
//==============================================================
void CExplosion::Update(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	m_nCounterAnim++;							//�J�E���^�[�����Z

	if ((m_nCounterAnim % 8) == 0)
	{
		m_nCounterAnim = 0;
		m_nPatternAnim++;	//�p�^�[��No.���X�V

		//�ʒu�̐ݒ�
		SetPosition(pos);
		SetSize(SIZE, SIZE, 0.0f);
		SetVtx(m_nPatternAnim, TYPE_EXPLOSION);
	}
	else if (m_nPatternAnim >= 8)
	{//���p�^�[�����𒴂���
		Uninit();
	}

	//�I�u�W�F�N�g2D�̍X�V����
	CBillboard::Update();
}

//==============================================================
//�����̕`�揈��
//==============================================================
void CExplosion::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CBillboard::Draw();
}