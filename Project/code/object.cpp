//==============================================================
//
//オブジェクト処理[object.cpp]
//Author:佐久間優香
//
//==============================================================
#include"object.h"
#include"renderer.h"
#include"manager.h"

//静的メンバ変数
CObject * CObject::m_apObject[MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//==============================================================
//コンストラクタ
//==============================================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		//自分自身を代入
			m_nID = nCntObject;					//自分自身のIDを保存
			m_nNumAll++;						//総数をカウントアップ
			break;
		}
	} 
}

//==============================================================
//コンストラクタ
//==============================================================
CObject::CObject(TYPE type)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		//自分自身を代入
			m_nID = nCntObject;					//自分自身のIDを保存
			m_type = type;
			m_nNumAll++;						//総数をカウントアップ
			break;
		}
	}
}

//==============================================================
//デストラクタ
//==============================================================
CObject::~CObject()
{
	
}

//==============================================================
//全てのオブジェクトの破棄
//==============================================================
void CObject::ReleseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//終了処理
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//==============================================================
//全てのオブジェクトの更新
//==============================================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//更新処理
			m_apObject[nCntObject]->Update();
		}
	}
}

//==============================================================
//全てのオブジェクトの描画
//==============================================================
void CObject::DrawAll(void)
{
	//カメラの取得
	CCamera *pCamera = CManager::Get()->GetCamera();

	//カメラの設定
	pCamera->Set();

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//描画処理
			m_apObject[nCntObject]->Draw();
		}
	}	
}

//==============================================================
//オブジェクトの破棄
//==============================================================
void CObject::Release(void)
{
	int nData = m_nID;

	if (m_apObject[nData] != NULL)
	{//使用していたら

		delete m_apObject[nData];
		m_apObject[nData] = NULL;

		m_nNumAll--;
	}
}

//==============================================================
//マップのリセット
//==============================================================
void CObject::ResetMapAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			if (m_apObject[nCntObject]->m_type != TYPE_PLAYER &&
				m_apObject[nCntObject]->m_type != TYPE_NONE)
			{
				//終了処理
				m_apObject[nCntObject]->Uninit();
			}
		}
	}
}