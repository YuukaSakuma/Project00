//==============================================================
//
//�|���S������[polygon.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"polygon.h"
#include"manager.h"
#include"texture.h"
#include"wall.h"

//�}�N����`
#define WIDTH (2000.0f * 2.0f) //����
#define HEIGHT (2000.0f * 2.0f) //����
#define VERTICL (0.0f)	//�c��
//vertical

//==============================================================
//�R���X�g���N�^
//==============================================================
CWall::CWall()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CWall::CWall(TYPE type,D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	////�I�u�W�F�N�g2D�ʒu�̐ݒ�
	//CObject3D::SetPosition(pos);

	////�G�l�~�[�ʒu�̐ݒ�
	//CEnemy::SetPosition(pos);

	//��ނ̐ݒ�
	SetType(type);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CWall::~CWall()
{

}

//==============================================================
//�G�̂̐�������
//==============================================================
CWall *CWall::Create(TYPE type, D3DXVECTOR3 pos)
{
	CWall *pPolygon = NULL;

	if (pPolygon == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPolygon = new CWall(type,pos);

		//����������
		pPolygon->Init();
	}

	return pPolygon;
}

//==============================================================
//�G�̏���������
//==============================================================
HRESULT CWall::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\wall00.jpg");

	//�I�u�W�F�N�g2D�̏���������
	CObject3D::Init(); 

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	//��ނ̐ݒ�
	CObject::SetType(TYPE_NONE);

	SetPosition(m_pos);


	//�T�C�Y�ݒ�
	SetSize(WIDTH, HEIGHT, VERTICL);
	

	return S_OK;
}

//==============================================================
//�G�̏I������
//==============================================================
void CWall::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject3D::Uninit();
}

//==============================================================
//�G�̍X�V����
//==============================================================
void CWall::Update(void)
{

}

//==============================================================
//�G�̕`�揈��
//==============================================================
void CWall::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject3D::Draw();
}