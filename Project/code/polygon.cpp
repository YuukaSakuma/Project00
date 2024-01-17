//==============================================================
//
//�|���S������[polygon.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"polygon.h"
#include"manager.h"
#include"texture.h"

#define WIDTH (100.0f) //����
#define HEIGHT (0.0f) //����
#define VERTICL (100.0f)	//�c��
//vertical

LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^

//==============================================================
//�R���X�g���N�^
//==============================================================
CPolygon::CPolygon()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CPolygon::CPolygon(TYPE type,D3DXVECTOR3 pos)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//�I�u�W�F�N�g2D�ʒu�̐ݒ�
	CObject3D::SetPosition(pos);

	////�G�l�~�[�ʒu�̐ݒ�
	//CEnemy::SetPosition(pos);

	//��ނ̐ݒ�
	SetType(type);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CPolygon::~CPolygon()
{

}

//==============================================================
//�G�̂̐�������
//==============================================================
CPolygon *CPolygon::Create(TYPE type, D3DXVECTOR3 pos)
{
	CPolygon *pPolygon = NULL;

	if (pPolygon == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pPolygon = new CPolygon(type,pos);

		//����������
		pPolygon->Init();
	}

	return pPolygon;
}

//==============================================================
//�G�̏���������
//==============================================================
HRESULT CPolygon::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	//�I�u�W�F�N�g2D�̏���������
	CObject3D::Init(); 

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	//��ނ̐ݒ�
	CObject::SetType(TYPE_NONE);

	//�T�C�Y�ݒ�
	SetSize(WIDTH, HEIGHT, VERTICL);

	return S_OK;
}

//==============================================================
//�G�̏I������
//==============================================================
void CPolygon::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject3D::Uninit();
}

//==============================================================
//�G�̍X�V����
//==============================================================
void CPolygon::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//�ʒu�̐ݒ�
	SetPosition(pos);

	//�T�C�Y�ݒ�
	SetSize(WIDTH, HEIGHT, VERTICL);

	//�I�u�W�F�N�g2D�̍X�V���� 
	CObject3D::Update();
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void CPolygon::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject3D::Draw();
}