//==============================================================
//
//ライト処理[item.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include "light.h"
#include"renderer.h"
#include"manager.h"

//==============================================================
//コンストラクタ
//==============================================================
CLight::CLight()
{

}
//==============================================================
//コンストラクタ
//==============================================================
CLight::~CLight()
{

}

//==============================================================
//ライトの初期化処理
//==============================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;									//設定用方向ベクトル

	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//デバイスの取得
	pDevice = pRenderer->GetDevice();
	
	for (int nCntLight = 0; nCntLight < 3;nCntLight++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		if (nCntLight == 0)
		{
			//ライトの拡散光を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.8f);	
		}
		else if (nCntLight == 1)
		{
			//ライトの拡散光を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, -0.8f, -1.0f);	
		}
		else if (nCntLight == 2)
		{
			//ライトの拡散光を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);	
		}

		D3DXVec3Normalize(&vecDir, &vecDir);				//ベクトルを正規化する
		
		m_light[nCntLight].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
	
		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//==============================================================
//ライトの終了処理
//==============================================================
void CLight::Uninit(void)
{

}

//==============================================================
//ライトの更新処理
//==============================================================
void CLight::Update(void)
{

}

