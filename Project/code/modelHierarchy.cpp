//==============================================================
//
//�K�w�\������[objectX.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "modelHierarchy.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "objectX.h"
#include "material.h"

//�}�N����`
#define NUM_MODEL			(2)			//���f���̎��
#define POS					(10.0f)		//pos�����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l
#define MODEL_LEN			(3.0f)		//����
#define CURVE_RL			(0.5f)		//���E�̊p�x
#define CURVE_UP			(0.0f)		//��̊p�x
#define CURVE_DOWN			(1.0f)		//���̊p�x

//==============================================================
//�R���X�g���N�^
//==============================================================
CModelHier::CModelHier()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_posDefault = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����ʒu
	m_rotDefault = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��������
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_pParent = NULL;		//�e���f���ւ̃|�C���^
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pMesh = NULL;

	m_state = CObjectX::STATE_NONE;		//�ʏ���
	m_matColor.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Power = 5.0f;
	m_matColor.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	m_nIdxModel = -1;

}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CModelHier::CModelHier(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_posDefault = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����ʒu
	m_rotDefault = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��������
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_pParent = NULL;	//�e���f���ւ̃|�C���^
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pMesh = NULL;

	m_state = CObjectX::STATE_NONE;		//�ʏ���
	m_matColor.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Power = 5.0f;
	m_matColor.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	m_nIdxModel = -1;

	m_bDisp = true;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CModelHier::~CModelHier()
{

}

//==============================================================
//X�t�@�C���̓ǂݍ���
//==============================================================
HRESULT CModelHier::Load(char *pFileName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

																			//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFileName,
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
CModelHier *CModelHier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName)
{
	CModelHier *pModelHier = NULL;

	if (pModelHier == NULL)
	{//���������g�p����ĂȂ�������

	 //���f���̐���
		pModelHier = new CModelHier(pos, rot);
	}

	//����������
	pModelHier->Init(pos, rot, pFileName);

	return pModelHier;
}


//==============================================================
//���f���̏���������
//==============================================================
HRESULT CModelHier::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName)
{
	CMaterial *pMaterial = CManager::Get()->GetMaterial();

	//���f���̓ǂݍ���
	m_nIdxModel = pMaterial->Regit(pFileName);

	//�ʒu�̐ݒ�
	m_pos = pos;

	//�����̐ݒ�
	m_rot = rot;

	//���f���̐ݒ菈��
	CModelHier::SetObject();

	return S_OK;
}



//==============================================================
//���f���̏I������
//==============================================================
void CModelHier::Uninit(void)
{
	////�e�N�X�`���̔j��
	//if (m_pTexture != NULL)
	//{
	//	delete[] m_pTexture;
	//	m_pTexture = NULL;
	//}
}


//==============================================================
//���f���̍X�V����
//==============================================================
void CModelHier::Update(void)
{
	
}

//==============================================================
//���f���̕`�揈��
//==============================================================
void CModelHier::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	CMaterial *pMaterial = CManager::Get()->GetMaterial();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	D3DXMATRIX mtxParent;		//�e���f���̃}�g���b�N�X

	if (m_pParent != NULL)
	{//�e�����݂���

	 //�e���f���̃}�g���b�N�X���擾����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e�����݂��Ȃ�

	 //���݁i�ŐV�j�̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);

	}

	//�e�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMaterial->GetMatAddress(m_nIdxModel)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pMaterial->GetNumMatAddress(m_nIdxModel); nCntMat++)
	{
		switch (m_state)
		{
		case CObjectX::STATE_DAMAGE:		//�_���[�W���

											//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&m_matColor.MatD3D);

			break;

		case CObjectX::STATE_APPEAR:		//�_�ŏ��

			if (m_bDisp == false)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&m_matColor.MatD3D);
			}
			else
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			}

			break;

		default:

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			break;
		}

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pMaterial->GetTexAddress(m_nIdxModel, nCntMat));

		//���f���i�p�[�c�j�̕`��
		pMaterial->GetMeshAddress(m_nIdxModel)->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//==============================================================
//���f���̐ݒ菈��
//==============================================================
void CModelHier::SetObject(void)
{
	CMaterial *pMaterial = CManager::Get()->GetMaterial();

	int nNumVtx;					//���_��
	DWORD dwSizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^

									//���_�����擾
	nNumVtx = pMaterial->GetMeshAddress(m_nIdxModel)->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(pMaterial->GetMeshAddress(m_nIdxModel)->GetFVF());

	//���_�o�b�t�@�����b�N
	pMaterial->GetMeshAddress(m_nIdxModel)->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��

															//�S�Ă̒��_���r���ă��f���̍ő�l�𔲂��o��
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		else if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		else if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}

		//�S�Ă̒��_���r���ă��f���̍ŏ��l�𔲂��o��
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		else if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		else if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;								//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	pMaterial->GetMeshAddress(m_nIdxModel)->UnlockVertexBuffer();
}



