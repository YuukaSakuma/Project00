//==============================================================
//
//�I�u�W�F�N�g2D����[object2D.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"object2D.h"
#include"manager.h"
#include"bg.h"

#define WIDTH (50.0f) //����
#define HEIGHT (80.0f) //�c��

//==============================================================
//�I�u�W�F�N�g2D�̃R���X�g���N�^
//==============================================================
CObject2D::CObject2D()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================
//�I�u�W�F�N�g2D�̃f�X�g���N�^
//==============================================================
CObject2D::~CObject2D()
{

}

//==============================================================
//�I�u�W�F�N�g2D�̐�������
//==============================================================
CObject2D *CObject2D::Create()
{
	CObject2D *pObject2D = NULL;	//�I�u�W�F�N�g2D�̃|�C���^

	if (pObject2D == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D;

		//����������
		pObject2D->Init();
	}
	return pObject2D;
}

//==============================================================
//�I�u�W�F�N�g2D�̏���������
//==============================================================
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	VERTEX_2D *pVtx;									//���_���ւ̃|�C���^

	CTexture * pTexture = CManager::Get()->GetTexturet();

	BindTexture(m_nldx);

	//��ނ̐ݒ�
	SetType(m_type);

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{//���s�����ꍇ
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.75f) * WIDTH;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.75f) * HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.75f) * WIDTH;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.75f) * HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.25f) * WIDTH;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.25f) * HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.25f) * WIDTH;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.25f) * HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	switch (m_type)
	{
	case TYPE_NONE:

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		break;

	case TYPE_PLAYER:
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

		break;

	case TYPE_EXPLOSION:

		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		break;

	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//SetVtx(0.0f, 0.0f);

	return S_OK;
}

//==============================================================
//�I�u�W�F�N�g2D�̏I������
//==============================================================
void CObject2D::Uninit(void)
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
//�I�u�W�F�N�g2D�̍X�V����
//==============================================================
void CObject2D::Update(void)
{
	//SetVtx(0.0f, 0.0f);
}

//==============================================================
//�I�u�W�F�N�g2D�̕`�揈��
//==============================================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	CTexture * pTexture = CManager::Get()->GetTexturet();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nldx));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==============================================================
//�I�u�W�F�N�g2D�̈ʒu�ݒ菈��
//==============================================================
void CObject2D::SetVtx(int nPattern, TYPE type)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (type)
	{
	case TYPE_NONE:
		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		break;

	case TYPE_PLAYER:
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((nPattern % 5) * 0.2f, (nPattern / 5) * 0.5f);
		pVtx[1].tex = D3DXVECTOR2((nPattern % 5) * 0.2f + 0.2f, (nPattern / 5) * 0.5f);
		pVtx[2].tex = D3DXVECTOR2((nPattern % 5) * 0.2f, (nPattern / 5) * 0.5f + 0.5f);
		pVtx[3].tex = D3DXVECTOR2((nPattern % 5) * 0.2f + 0.2f, (nPattern / 5) * 0.5f + 0.5f);

		break;

	case TYPE_EXPLOSION:
		//�e�N�X�`���̍��W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nPattern * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nPattern * 0.125f + 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nPattern * 0.125f + 0.125f, 1.0f);

		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�e�N�X�`�����W�̐ݒ菈��
//==============================================================
void CObject2D::SetVtx(int nPatternAnim, float nDigitX)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * nDigitX, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * nDigitX + nDigitX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * nDigitX, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * nDigitX + nDigitX, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�I�u�W�F�N�g2D�̈ʒu�ݒ菈��
//==============================================================
void CObject2D::SetVtx(float fTexV, float fTexU)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	//�e�N�X�`���̍��W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fTexU, fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV);
	pVtx[2].tex = D3DXVECTOR2(fTexU, fTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�u���b�N�̒��_���W
//==============================================================
void CObject2D::SetVtxBlock(float width, float heiget)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	SetPosition(m_pos);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + heiget, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y + heiget, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�v���C���[�̒��_���W
//==============================================================
void CObject2D::SetVtxPlayer(float width, float heiget)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	SetPosition(m_pos);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y - heiget, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y - heiget, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�A�C�e���̒��_���W
//==============================================================
void CObject2D::SetVtxItem(float width, float heiget)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	SetPosition(m_pos);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y - width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + heiget, m_pos.y - width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y + heiget, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + heiget, m_pos.y + heiget, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================
//�I�u�W�F�N�g2D�̈ʒu�ݒ菈��
//==============================================================
void CObject2D::SetSize(float width, float heiget)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//SetPosition(m_pos);

	m_fWidth = width;
	m_fHeight = heiget;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.75f) * width;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.75f) * heiget;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.75f) * width;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.75f) * heiget;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI* 0.25f) * width;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI* 0.25f) * heiget;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI* 0.25f) * width;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI* 0.25f) * heiget;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================
//���a�̍X�V
//================================================================
void CObject2D::SetRadius(float m_fRadius)
{
	VERTEX_2D * pVtx;     //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);   

	 //���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fRadius, m_pos.y - m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fRadius, m_pos.y - m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fRadius, m_pos.y + m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fRadius, m_pos.y + m_fRadius, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================
//�F�̐ݒ�
//================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;     //���_���ւ̃|�C���^

						  //���_�o�b�t�@�����b�N���A���_���փ|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}