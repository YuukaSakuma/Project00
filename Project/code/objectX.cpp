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
#include"renderer.h"
#include<string.h>
#include"object.h"
#include"material.h"
#include"game.h"
#include"player.h"

//==============================================================
//�R���X�g���N�^
//==============================================================
CObjectX::CObjectX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_type = CObject::TYPE_NONE;		//���
	m_nIdxModel = -1;

	m_pMesh = NULL;				//���b�V���i���_���j�ւ̃|�C���^
	m_pBuffMat = NULL;			//�}�e���A���ւ̃|�C���^
	m_dwNumMat = 0;					//�}�e���A���̐�

	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);	//���_���̍ŏ��l
	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);	//���_���̍ő�l

	m_matColor.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�}�e���A���f�[�^�ւ̃|�C���^
	m_matColor.MatD3D.Power = 5.0f;
	m_matColor.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CObjectX::~CObjectX()
{

}

//==============================================================
//�I�u�W�F�N�gX�̂̐�������
//==============================================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pObjectX = NULL;

	if (pObjectX == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pObjectX = new CObjectX;

		//����������
		pObjectX->Init();
	}

	return pObjectX;
}

//==============================================================
//�I�u�W�F�N�gX�̏���������
//==============================================================
HRESULT CObjectX::Init(void)
{
	m_pos = GetPosition();


	//���f���̃T�C�Y�ݒ�
	CObjectX::SetObject();

	return S_OK;
}

//==============================================================
//�I�u�W�F�N�gX�̏I������
//==============================================================
void CObjectX::Uninit(void)
{
	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�I�u�W�F�N�gX�̍X�V����
//==============================================================
void CObjectX::Update(void)
{
	
	
}

//==============================================================
//�I�u�W�F�N�gX�̕`�揈��
//==============================================================
void CObjectX::Draw(void)
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

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMaterial->GetMatAddress(m_nIdxModel)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pMaterial->GetNumMatAddress(m_nIdxModel); nCntMat++)
	{
		switch (m_state)
		{
		case STATE_DAMAGE:		//�_���[�W���

								//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&m_matColor.MatD3D);

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
//�}�e���A����񊄂蓖�ď���
//==============================================================
void CObjectX::BindMaterial(int nIdx)
{
	m_nIdxModel = nIdx;
}

//==============================================================
//�I�u�W�F�N�gX��/�e�N�X�`���̊��蓖��
//==============================================================
void CObjectX::BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat)
{
	//m_pMesh = pMesh;			//���b�V��
	//m_pBuffMat = pBuffMat;		//�}�e���A��
	//m_dwNumMat = dwNumMat;

	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//D3DXMATERIAL *pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

	//if (m_apTexture == NULL)
	//{
	//	m_apTexture = new LPDIRECT3DTEXTURE9[(int)m_dwNumMat];
	//}

	////�}�e���A�����ɑ΂���|�C���^���擾
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	//{
	//	m_apTexture[nCntMat] = NULL;

	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		//�e�N�X�`���̓ǂݍ���
	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_apTexture[nCntMat]);
	//	}
	//}

	////���f���̐ݒ菈��
	//CObjectX::SetObject();
}

//==============================================================
//���f���Ƃ̓����蔻��
//==============================================================
void CObjectX::SetObject(void)
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

//==============================================================
//���f���Ƃ̓����蔻��
//==============================================================
bool CObjectX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max)
{

	CPlayer *pPlayer = CGame::GetPlayerModel();			//�v���C���[�̏��擾
	bool bLand = false;

	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = GetObject(nCntModel);

		if (pObj != NULL)
		{//���������g�p����Ă���Ƃ�

		 //��ނ��擾
			CObject::TYPE type = pObj->GetType();

			if (type == pObj->TYPE_MODEL || type == TYPE_ITEM)
			{//��ނ����f���̏ꍇ

			 //���f���̈ʒu�擾
				D3DXVECTOR3 posModel = pObj->GetPosition();
				D3DXVECTOR3 minModel = pObj->GetSizeMin();
				D3DXVECTOR3 maxModel = pObj->GetSizeMax();

				if (pPos->y + Max.y > posModel.y + minModel.y
					&& pPos->y < posModel.y + maxModel.y)
				{
					if (pPosOld->x - Min.z <= posModel.x + minModel.x
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//���ɂ߂荞�񂾏ꍇ
						if (type == pObj->TYPE_MODEL)
						{
							pPos->x = posModel.x + minModel.x + Min.z;		//�u���b�N�̍��ɗ�������
							pMove->x = 0.0f;
						}
						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->x + Min.z >= posModel.x + maxModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//�E�ɂ߂荞�񂾏ꍇ
						if (type == pObj->TYPE_MODEL)
						{
							pPos->x = posModel.x + maxModel.x - Min.z;		//�u���b�N�̉E�ɗ�������
							pMove->x = 0.0f;

						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->z - Min.z <= posModel.z + minModel.z
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x)
					{//��O�ɂ߂荞�񂾏ꍇ
						if (type == pObj->TYPE_MODEL)
						{
							pPos->z = posModel.z + minModel.z + Min.z;		//�u���b�N�̎�O�ɗ�������
							pMove->z = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->z + Min.z >= posModel.z + maxModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x)
					{//���ɂ߂荞�񂾏ꍇ
						if (type == pObj->TYPE_MODEL)
						{
							pPos->z = posModel.z + maxModel.z - Min.z;		//�u���b�N�̉��ɗ�������
							pMove->z = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->y + Max.y <= posModel.y + minModel.y
						&& pPos->y + Max.y > posModel.y + minModel.y
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//��ɂ߂荞�񂾏ꍇ
						if (type == pObj->TYPE_MODEL)
						{
							pPos->y = posModel.y + minModel.y - Max.y;		//�u���b�N�̒ꉺ�ɗ�������
							pMove->y = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}
					}

					if (pPosOld->y >= posModel.y + maxModel.y
						&& pPos->y < posModel.y + maxModel.y
						&& pPos->x - Min.z > posModel.x + minModel.x
						&& pPos->x + Min.z < posModel.x + maxModel.x
						&& pPos->z - Min.z > posModel.z + minModel.z
						&& pPos->z + Min.z < posModel.z + maxModel.z)
					{//��ɂ߂荞�񂾏ꍇ
						if (type == pObj->TYPE_MODEL)
						{
							pPos->y = posModel.y + maxModel.y;		//�u���b�N�̏�ɗ�������
							pMove->y = 0.0f;
						}

						if (type == pObj->TYPE_ITEM)
						{
							pObj->Hit();
						}

						bLand = true;
					}
				}
			}
		}
	}

	return bLand;
}