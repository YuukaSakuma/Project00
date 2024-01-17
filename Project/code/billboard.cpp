//==============================================================
//
//�r���{�[�h����[billboard.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "main.h"
#include "billboard.h"
#include"manager.h"
#include"texture.h"
#include"renderer.h"

//�}�N����`
#define WIDTH_BILL		(10.0f)		//����
#define HEIGHT_BILL		(10.0f)		//����
#define VERTICL_BILL	(0.0f)		//�c��
#define SIZE			(10.0f)		//�T�C�Y
#define SIZE_EXPLOSION	(0.125f)	//�����̃T�C�Y


//==============================================================
//�R���X�g���N�^
//==============================================================
CBillboard::CBillboard()
{
	m_pVtxBuff = NULL;
	//m_mtxWorld = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBillboard::~CBillboard()
{

}

//==============================================================
//�r���{�[�h�̐�������
//==============================================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard = NULL;

	if (pBillboard == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBillboard = new CBillboard;

		//����������
		pBillboard->Init();	
	}

	return pBillboard;
}

//==============================================================
//�r���{�[�h�̏���������
//==============================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx;

	CTexture * pTexture = CManager::Get()->GetTexturet();
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SIZE, SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SIZE, SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SIZE, 0.0f, 0.0f);

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
//�r���{�[�h�̏I������
//==============================================================
void CBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}

//==============================================================
//�r���{�[�h�̍X�V����
//==============================================================
void CBillboard::Update(void)
{

}

//==============================================================
//�r���{�[�h�̕`�揈��
//==============================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	CTexture *pTexture = CManager::Get()->GetTexturet();		//�e�N�X�`���̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X�擾�p

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	//�r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,												//�v���~�e�B�u�i�r���{�[�h�̐��j
		2);												//�`�悷��v���~�e�B�u��
}

//==============================================================
//�r���{�[�h�̃T�C�Y�̐ݒ�
//==============================================================
void CBillboard::SetSize(float width, float heiget, float vertical)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//SetPosition(m_pos);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-width, heiget, vertical);
	pVtx[1].pos = D3DXVECTOR3(width, heiget, vertical);
	pVtx[2].pos = D3DXVECTOR3(-width, -heiget, -vertical);
	pVtx[3].pos = D3DXVECTOR3(width, -heiget, -vertical);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================
//���a�̍X�V
//================================================================
void CBillboard::SetRadius(float fRadius)
{
	VERTEX_3D * pVtx;     //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�I�u�W�F�N�g2D�̈ʒu�ݒ菈��
//==============================================================
void CBillboard::SetVtx(int nPattern, TYPE type)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (type)
	{
	case TYPE_EXPLOSION:
		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION + SIZE_EXPLOSION, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nPattern * SIZE_EXPLOSION + SIZE_EXPLOSION, 1.0f);

		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}