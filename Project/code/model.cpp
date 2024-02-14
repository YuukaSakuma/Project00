//==============================================================
//
//�I�u�W�F�N�gX����[objectX.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "main.h"
#include "objectX.h"
#include"input.h"
#include"camera.h"
#include"manager.h"
#include"model.h"
#include"renderer.h"
#include<string.h>
#include"Xfile.h"

LPD3DXMESH CModel::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CModel::m_pBuffMat = NULL;					//�}�e���A���ւ̃|�C���^
DWORD CModel::m_dwNumMat = NULL;
const char *CModel::m_pFilename = NULL;					//�t�@�C���̖��O

//==============================================================
//�R���X�g���N�^
//==============================================================
CModel::CModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CModel::CModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_type = TYPE_MODEL;
	m_nLife = 1;
	CModel::Load(pFilename);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CModel::~CModel()
{

}

//==============================================================
//X�t�@�C���̓ǂݍ���
//==============================================================
HRESULT CModel::Load(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	return S_OK;
}


//==============================================================
//���f���̐�������
//==============================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *pFilename)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{//���������g�p����ĂȂ�������

	 //���f���̐���
		pModel = new CModel(pos, rot, pFilename);
	}

	//�t�@�C�������
	m_pFilename = pFilename;

	////X�t�@�C���̏�񊄂蓖��
	//pModel->BindXFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	//����������
	pModel->Init();

	return pModel;
}

//==============================================================
//�}�e���A���E���b�V���̔j��
//==============================================================
void CModel::Unload(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//==============================================================
//���f���̏���������
//==============================================================
HRESULT CModel::Init(void)
{
	CXFile *pMaterial = CManager::Get()->GetModelFile();

	//���f���̓ǂݍ���
	m_nIdxModel = pMaterial->Regist(m_pFilename);

	//�}�e���A���̊��蓖��
	CObjectX::BindMaterial(m_nIdxModel);

	SetPosition(m_pos);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(m_type);


	return S_OK;
}

//==============================================================
//���f���̏I������
//==============================================================
void CModel::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//���f���̍X�V����
//==============================================================
void CModel::Update(void)
{
	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//���f���̕`�揈��
//==============================================================
void CModel::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}