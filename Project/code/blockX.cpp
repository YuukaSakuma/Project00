//==============================================================
//
//�u���b�N���f������[blockX.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "main.h"
#include"blockX.h"
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include<string.h>
#include"model.h"
#include"modelHierarchy.h"

//==============================================================
//�R���X�g���N�^
//==============================================================
CBlockX::CBlockX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ŏ��l
	m_pMesh = NULL;						
	m_pBuffMat= NULL;				
	m_dwNumMat = NULL;		
	m_mtxWorld = {};
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CBlockX::CBlockX(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu�̐ݒ�
	m_rot = rot;		//����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ŏ��l
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_mtxWorld = {};
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBlockX::~CBlockX()
{

}

//==============================================================
//�u���b�N���f���̂̐�������
//==============================================================
CBlockX *CBlockX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlockX *pBlockX = NULL;

	if (pBlockX == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlockX = new CBlockX(pos,rot);

		//����������
		pBlockX->Init();

		pBlockX->SetPosition(pos);

		pBlockX->SetType(TYPE_MODEL);
	}

	return pBlockX;
}

//==============================================================
//�u���b�N���f���̏���������
//==============================================================
HRESULT CBlockX::Init(void)
{
	m_apModel[0] = m_apModel[0]->Create(m_pos, m_rot, "data\\MODEL\\block.x");

	//�ő�l�E�ŏ��l���
	for (int nCntPlayer = 0; nCntPlayer < 1; nCntPlayer++)
	{
		//�ő�lY
		if (nCntPlayer <= 0 )
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//�ő�l���Z
		}

	//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//�ŏ��lZ

		}
		 
		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//�ŏ��lZ

		}
	}

	return S_OK;
}

//==============================================================
//�u���b�N���f���̏I������
//==============================================================
void CBlockX::Uninit(void)
{
	CObject::Release();
}

//==============================================================
//�u���b�N���f���̍X�V����
//==============================================================
void CBlockX::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	m_pos = m_apModel[0]->GetPosition();

	m_posOld = m_pos;

	//m_move.x += -10.0f;

	m_pos.x += m_move.x;

	//pDebugProc->Print("\n�u���b�N�̈ʒu (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);

	for (int nCntMat = 0; nCntMat < 1; nCntMat++)
	{
		m_apModel[nCntMat]->SetPosition(m_pos);
		//m_apModel[nCntMat]->SetRotation(m_rot);
	}
}

//==============================================================
//�u���b�N���f���̕`�揈��
//==============================================================
void CBlockX::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < 1; nCntMat++)
	{
		m_apModel[nCntMat]->Draw();
	}
}