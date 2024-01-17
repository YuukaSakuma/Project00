//==============================================================
//
//�G�t�F�N�g����[effect.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"manager.h"
#include"effect.h"
#include"texture.h"
#include"renderer.h"

//==============================================================
//�R���X�g���N�^
//==============================================================
CEffect::CEffect()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);		//�F
	m_nLife = 0;								//����
	m_fRadius = 0.0f;							//���a
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CEffect::CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	m_move = move;			//�ړ���
	m_col = col;			//�F
	m_nLife = nLife;		//����
	m_fRadius = fRadius;	//���a

	//�ʒu�̐ݒ�
	SetPosition(pos);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEffect::~CEffect()
{

}

//==============================================================
//�G�t�F�N�g�̐�������
//==============================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	CEffect *pEffect = NULL;

	if (pEffect == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pEffect = new CEffect(pos, move, col, fRadius, nLife);

		//����������
		pEffect->Init();
	}

	return pEffect;
}

//==============================================================
//�G�t�F�N�g�̏���������
//==============================================================
HRESULT CEffect::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	m_nldxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	//�e�N�X�`���̊��蓖��
	BindTexture(m_nldxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CBillboard::Init();

	CObject::SetType(TYPE_EFFECT);

	//���a�̐ݒ�
	//SetRadius(m_fRadius);

	SetSize(m_fRadius, m_fRadius, 0.0f);

	return S_OK;
}

//==============================================================
//�G�t�F�N�g�̏I������
//==============================================================
void CEffect::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�G�t�F�N�g�̍X�V����
//==============================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//�����̌��Z
	m_nLife--;

	//�ʒu�����Z
	pos += m_move;
		
	//���a�̐ݒ�
	//SetRadius(m_fRadius);

	SetSize(m_fRadius, m_fRadius, 0.0f);

	//���a�̌��Z
	m_fRadius -= 1.0f;

	if (m_nLife <= 0)
	{//�����������Ȃ�����
		Uninit();
	}
	else
	{
		//�ʒu�̐ݒ�
		SetPosition(pos);
	}

	//�I�u�W�F�N�g2D�̍X�V����d
	CBillboard::Update();
}

//==============================================================
//�G�t�F�N�g�̕`�揈��
//==============================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�𖳌�������
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�I�u�W�F�N�g2D�̕`�揈��
	CBillboard::Draw();

	//Z�e�X�g��L���ɂ��� 
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
