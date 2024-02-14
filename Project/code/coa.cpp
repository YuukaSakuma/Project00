//==============================================================
//
//�e����[player.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"coa.h"
#include"manager.h"
#include"explosion.h"
#include"model.h"
#include"particle.h"
#include"Xfile.h"

//�}�N����`
#define LIFE				(50)			//����
//==============================================================
//�R���X�g���N�^
//==============================================================
CCOa::CCOa()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_type = CObject::TYPE_COA;
	m_nLife = LIFE;								//����
	m_nldxTexture = -1;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CCOa::~CCOa()
{

}

//==============================================================
//�e�̐�������
//==============================================================
CCOa *CCOa::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, COA type)
{
	CCOa *pCoa = nullptr;

	if (pCoa == nullptr)
	{
		pCoa = new CCOa;

		pCoa->SetPosition(pos);

		//pCoa->SetRotation(rot);

		pCoa->SetCoaType(type);

		//����������
		pCoa->Init();
	}

	return pCoa;
}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CCOa::Init(void)
{
	CXFile *pXFile = CManager::Get()->GetModelFile();

	switch (m_CoaType)
	{
	case TYPE_COA_0:
		m_nldxTexture = pXFile->Regist("data\\MODEL\\coa0.x");

		break;

	case TYPE_COA_1:
		m_nldxTexture = pXFile->Regist("data\\MODEL\\coa1.x");
		break;
	}
	CObjectX::BindMaterial(m_nldxTexture);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	CObjectX::SetPosition(m_pos);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_COA);

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CCOa::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CCOa::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	SetState();

	pDebugProc->Print("�R�A�̗̑� : [%d] \n", m_nLife);

	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CCOa::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}

//==============================================================
//��Ԑݒ�
//==============================================================
void CCOa::SetState(void)
{

}

//==============================================================
//�v���C���[���f���̃q�b�g����
//==============================================================
void CCOa::Hit(void)
{
	m_nLife--;

	if (m_nLife > 0)
	{

		//m_nCntDamage = 5;
	}
	else if (m_nLife <= 0)
	{
		//�p�[�e�B�N������
		CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), CObject::TYPE_COA, 30, 40);

		////�I������
		Uninit();
	}
}