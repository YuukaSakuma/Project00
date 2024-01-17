//==============================================================
//
//�|���S������[polygon.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"polygon.h"
#include"manager.h"
#include"texture.h"
#include"field.h"

//�}�N����`
#define WIDTH (500.0f) //����
#define HEIGHT (0.0f) //����
#define VERTICL (500.0f)	//�c��
//vertical

//==============================================================
//�R���X�g���N�^
//==============================================================
CField::CField()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CField::CField(TYPE type,D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//��ނ̐ݒ�
	SetType(type);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CField::~CField()
{

}

//==============================================================
//�G�̂̐�������
//==============================================================
CField *CField::Create(TYPE type, D3DXVECTOR3 pos)
{
	CField *pField = NULL;

	if (pField == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pField = new CField(type,pos);

		//����������
		pField->Init();
	}

	return pField;
}

//==============================================================
//�G�̏���������
//==============================================================
HRESULT CField::Init(void)
{
	CObject3D *p = CObject3D::Create();
	p->BindTexture(CManager::Get()->GetTexturet()->Regist("data\\TEXTURE\\meadow.jpg"));
	p->SetPosition(m_pos);
	p->SetSize(WIDTH, HEIGHT, VERTICL);

	return S_OK;
}

//==============================================================
//�G�̏I������
//==============================================================
void CField::Uninit(void)
{
	////�I�u�W�F�N�g2D�̏I������
	CObject3D::Uninit();
}

//==============================================================
//�G�̍X�V����
//==============================================================
void CField::Update(void)
{
	/*CObject3D::Update();*/
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void CField::Draw(void)
{
	////�I�u�W�F�N�g2D�̕`�揈��
	//CObject3D::Draw();
}