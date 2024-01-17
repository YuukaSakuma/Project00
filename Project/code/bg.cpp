//==============================================================
//
//�w�i����[bg.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"bg.h"
#include"renderer.h"
#include"manager.h"

//�}�N����`
#define MMOVE_V		(0.001f)		//�w�i�̈ړ���

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBg::m_pTexture = NULL;			//�e�N�X�`���ւ̃|�C���^
CObject2D * CBg::m_apObject2D = NULL;				//�I�u�W�F�N�g2D�ւ̃|�C���^			

//==============================================================
//�w�i�̃R���X�g���N�^
//==============================================================
CBg::CBg()
{
	m_pVtxBuff = NULL;							//���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_fTexV = 0.0f;								//�e�N�X�`�����W�̊J�n�ʒu(V�l)
	m_fTexU = 0.0f;								//�e�N�X�`�����W�̊J�n�ʒu(U�l)
	m_fmoveV = 0.0f;							//�e�N�X�`�����W�̈ړ���V
	m_fmoveU = 0.0f;							//�e�N�X�`�����W�̈ړ���V
	m_nldxTexture = 0;							//�e�N�X�`���ԍ�
}

//==============================================================
//�w�i�̃f�X�g���N�^
//==============================================================
CBg::~CBg()
{

}

//==============================================================
//�w�i�̐�������
//==============================================================
CBg *CBg::Create(void)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		//�w�i�̐���
		pBg = new CBg;

		//����������
		pBg->Init();	
	}
	return pBg;
}

//==============================================================
//�w�i�̏���������
//==============================================================
HRESULT CBg::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\bg100.png");

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	//�ݒ菈��
	SetVtx(m_fTexV, m_fTexU);

	////�e�N�X�`���̊��蓖��
	//BindTexture(m_nldxTexture);

	//�ړ��ʂ̐ݒ�
	m_fTexV = 0.0f;
	m_fTexU = 0.0f;
	m_fmoveV = MMOVE_V;
	m_fmoveU = 0.0f;

	return S_OK;
}

//==============================================================
//�w�i�̏I������
//==============================================================
void CBg::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�w�i�̍X�V����
//==============================================================
void CBg::Update(void)
{
	CObject2D::Update();
	SetVtx(m_fTexV, m_fTexU);

	//�l��������
	m_fTexV += m_fmoveV;
	m_fTexU += m_fmoveU;

	//���̈ʒu�̖߂�
	if (m_fTexV < 0.0f )
	{
		m_fTexV = 1.0f;
	}
	else if (m_fTexV > 1.0f)
	{
		m_fTexV = 0.0f;
	}

	if (m_fTexU < 0.0f)
	{
		m_fTexU = 1.0f;
	}
	else if (m_fTexU > 1.0f)
	{
		m_fTexU = 0.0f;
	}
}

//==============================================================
//�w�i�̕`�揈��
//==============================================================
void CBg::Draw(void)
{
	CTexture *pTexture = NULL;

	LPDIRECT3DDEVICE9 pDevice = NULL;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nldxTexture));
}