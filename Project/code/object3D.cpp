//==============================================================
//
//�I�u�W�F�N�g3D����[object3D.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "main.h"
#include "object3D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//==============================================================
//�R���X�g���N�^
//==============================================================
CObject3D::CObject3D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	//m_mtxWorld = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nldxTexture = -1;
}

//==============================================================
//�R���X�g���N�^
//==============================================================
CObject3D::~CObject3D()
{

}

//==============================================================
//�I�u�W�F�N�g2D�̐�������
//==============================================================
CObject3D *CObject3D::Create()
{
	CObject3D *pObject3D = NULL;	//�I�u�W�F�N�g2D�̃|�C���^

	if (pObject3D == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject3D = new CObject3D;

		//����������
		pObject3D->Init();
	}
	return pObject3D;
}

//==============================================================
//�|���S���̏���������
//==============================================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	BindTexture(m_nldxTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================
//�|���S���̏I������
//==============================================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//==============================================================
//�|���S���̍X�V����
//==============================================================
void CObject3D::Update(void)
{
	
}

//==============================================================
//�|���S���̕`�揈��
//==============================================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	CTexture * pTexture = CManager::Get()->GetTexturet();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nldxTexture));
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==============================================================
//�I�u�W�F�N�g3D�̃T�C�Y�̐ݒ�
//==============================================================
void CObject3D::SetSize(float width, float heiget, float vertical)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//SetPosition(m_pos);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-width, heiget, vertical);
	pVtx[1].pos = D3DXVECTOR3(width, heiget, vertical);
	pVtx[2].pos = D3DXVECTOR3(-width, 0.0f, -vertical);
	pVtx[3].pos = D3DXVECTOR3(width, 0.0f, -vertical);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�����̎擾
//==============================================================
float CObject3D::GetHeight(D3DXVECTOR3 VecPos)
{
	D3DXVECTOR3 vec1, vec2, nor;
	float fHeight;

	//2�̃x�N�g������@�������߂�
	D3DXVec3Cross(&nor, &vec1, &vec2);

	//�@���𐳋K������
	D3DXVec3Normalize(&nor, &nor);


	if (nor.y != 0.0f)
	{
		fHeight = 0;
	}

	return fHeight;
}