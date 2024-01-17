//==============================================================
//
//���d�w�i����[multibg.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"multibg.h"
#include"manager.h"
#include"object2D.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CMultiBg::m_pTexture[TYPE_BG_MAX] = {};				//�e�N�X�`���ւ̃|�C���^

//�e�N�X�`���t�@�C����
const char *CMultiBg::apTexture[] =
{
	"data\\TEXTURE\\bg100.png",	//�w�i1
	"data\\TEXTURE\\bg101.png",	//�w�i2
	"data\\TEXTURE\\bg102.png",	//�w�i3
};

//==============================================================
//���d�w�i�̃R���X�g���N�^
//==============================================================
CMultiBg::CMultiBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntTex = 0; nCntTex < TYPE_BG_MAX; nCntTex++)
	{
		m_apObject2D[nCntTex] = NULL;
		m_fTexV[nCntTex] = 0.0f;
		m_fTexU[nCntTex] = 0.0f;
		m_fmoveV[nCntTex] = 0.0f;
		m_fmoveU[nCntTex] = 0.0f;
	}
}

//==============================================================
//���d�w�i�̃f�X�g���N�^
//==============================================================
CMultiBg::~CMultiBg()
{

}

//==============================================================
//���d�w�i�̐�������
//==============================================================
CMultiBg *CMultiBg::Create(void)
{
	CMultiBg *pMultiBg = NULL;

	if (pMultiBg == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pMultiBg = new CMultiBg;

		//����������
		pMultiBg->Init();
	}

	return pMultiBg;
}

//==============================================================
//���d�w�i�̏���������
//==============================================================
HRESULT CMultiBg::Init(void)
{
	CTexture * pTexture = CManager::Get()->GetTexturet();

	for (int nCntTex = 0; nCntTex < TYPE_BG_MAX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] == NULL)
		{
			m_apObject2D[nCntTex] = CObject2D::Create();

			if (m_apObject2D[nCntTex] != NULL)
			{
				m_aldxTexture[nCntTex] = pTexture->Regist(apTexture[nCntTex]);
				//����������
				m_apObject2D[nCntTex]->Init();

				//�e�N�X�`���̊��蓖��
				m_apObject2D[nCntTex]->BindTexture(m_aldxTexture[nCntTex]);

				//��ސݒ�
				SetType(TYPE_NONE);
			}
		}
	}

	m_fmoveV[0] = 0.001f;
	m_fmoveV[1] = 0.005f;
	m_fmoveV[2] = 0.01f;

	return S_OK;
}

//==============================================================
//���d�w�i�̏I������
//==============================================================
void CMultiBg::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	CObject::Release();
}
//==============================================================
//���d�w�i�̍X�V����
//==============================================================
void CMultiBg::Update(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_BG_MAX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] != NULL)
		{
			//�ړ���
			m_fTexV[nCntTex] += m_fmoveV[nCntTex];
			m_fTexU[nCntTex] += m_fmoveU[nCntTex];

			//���̈ʒu�̖߂�
			if (m_fTexV[nCntTex] < 0.0f)
			{
				m_fTexV[nCntTex] = 1.0f;
			}
			else if (m_fTexV[nCntTex] > 1.0f)
			{
				m_fTexV[nCntTex] = 0.0f;
			}

			if (m_fTexU[nCntTex] < 0.0f)
			{
				m_fTexU[nCntTex] = 1.0f;
			}
			else if (m_fTexU[nCntTex] > 1.0f)
			{
				m_fTexU[nCntTex] = 0.0f;
			}

			//�e�N�X�`�����W
			m_apObject2D[nCntTex]->SetVtx(m_fTexV[nCntTex], m_fTexU[nCntTex]);
		}
	}
}

//==============================================================
//���d�w�i�̕`�揈��
//==============================================================
void CMultiBg::Draw(void)
{
	//�Ȃ�
}