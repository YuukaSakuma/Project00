//==============================================================
//
//���C�g����[item.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "main.h"
#include "light.h"
#include"renderer.h"
#include"manager.h"

//==============================================================
//�R���X�g���N�^
//==============================================================
CLight::CLight()
{

}
//==============================================================
//�R���X�g���N�^
//==============================================================
CLight::~CLight()
{

}

//==============================================================
//���C�g�̏���������
//==============================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;									//�ݒ�p�����x�N�g��

	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();
	
	for (int nCntLight = 0; nCntLight < 3;nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		if (nCntLight == 0)
		{
			//���C�g�̊g�U����ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.8f);	
		}
		else if (nCntLight == 1)
		{
			//���C�g�̊g�U����ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, -1.0f);	
		}
		else if (nCntLight == 2)
		{
			//���C�g�̊g�U����ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);	
		}

		D3DXVec3Normalize(&vecDir, &vecDir);				//�x�N�g���𐳋K������
		
		m_light[nCntLight].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
	
		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//==============================================================
//���C�g�̏I������
//==============================================================
void CLight::Uninit(void)
{

}

//==============================================================
//���C�g�̍X�V����
//==============================================================
void CLight::Update(void)
{

}

