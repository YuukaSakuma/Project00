//==============================================================
//
//爆発処理[explosion.cpp]
//Author:佐久間優香
//
//==============================================================
#include"renderer.h"
#include"edit.h"
#include"input.h"
#include"manager.h"
#include"objectX.h"
#include"model.h"
#include"blockX.h"

#define MODEL (1)

//オブジェクトファイル名
const char *c_Obj[MODEL] =
{
	"data\\MODEL\\block.x"
};

//静的メンバ変数宣言
CModel *CEdit::m_apObjectX[NUM_MODEL] = {};

//==============================================================
//コンストラクタ
//==============================================================
CEdit::CEdit()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = 0;
	m_nTypeIdx = 0;
	m_bUse = false;
}

//==============================================================
//デストラクタ
//==============================================================
CEdit::~CEdit()
{

}

//==============================================================
//生成処理
//==============================================================
CEdit *CEdit::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEdit *pEdit = NULL;

	if (pEdit == NULL)
	{//メモリが使用されてなかったら

	 //モーションの生成
		pEdit = new CEdit;
	}

	if (pEdit != NULL)
	{//メモリが使用されてなかったら

	 //モーションの生成
		pEdit->Init();
	}

	return pEdit;
}

//==============================================================
//エディットの初期化処理
//==============================================================
HRESULT CEdit::Init(void)
{
	
	return S_OK;
}

//==============================================================
//エディットの終了処理
//==============================================================
void CEdit::Uninit(void)
{
	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//エディットの更新処理
//==============================================================
void CEdit::Update(void)
{
	////キーボード情報の取得
	//CInputKeyboard *pInputKey = CManager::GetInputKeybard();
	//CDebugProc *pDebug = CManager::GetDebugProc();

	//if (pInputKey->GetTrigger(DIK_F3))
	//{
	//	m_bUse = m_bUse ? false : true;			//使用するかの有無

	//	if (m_bUse == true)
	//	{
	//		//オブジェクトの初期化
	//		CModel::Init();
	//	}
	//	else
	//	{
	//		CModel::Release();
	//	}

	//	//オブジェクト種類の変更
	//	if (pInputKey->GetTrigger(DIK_1))
	//	{
	//		m_nTypeIdx++;

	//		CModel::Create(m_pos, m_rot, c_Obj[m_nTypeIdx]);

	//		m_nTypeIdx %= MAX_MODEL;			//繰り返し
	//	}

	//	//移動
	//	if (pInputKey->GetPress(DIK_UP))
	//	{
	//		m_pos.z += 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_DOWN))
	//	{
	//		m_pos.z -= 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_LEFT))
	//	{
	//		m_pos.x -= 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_RIGHT))
	//	{
	//		m_pos.x += 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_LSHIFT))
	//	{
	//		m_pos.y += 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_LCONTROL))
	//	{
	//		m_pos.y -= 1.0f;
	//	}

	//	//位置の更新
	//	SetPosition(m_pos);

	//	//オブジェクトの設置
	//	if (pInputKey->GetTrigger(DIK_RETURN))
	//	{
	//		//生成
	//		m_apObjectX[m_nIdx] = CModel::Create(m_pos, m_rot, c_Obj[m_nTypeIdx]);

	//		m_nIdx++;
	//	}

	//	//ファイル書き込み(セーブ)
	//	if (pInputKey->GetTrigger(DIK_0))
	//	{
	//		SaveFile();
	//	}
	//}
}

//==============================================================
//エディットの描画処理
//==============================================================
void CEdit::Draw(void)
{
	////オブジェクトの描画
	//CModel::Draw();
}

//==============================================================
//Xファイルの読み込み
//==============================================================
HRESULT CEdit::LoadFile(void)
{
	char aString[128] = {};		//文字列のゴミ箱
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE *pFile = NULL;			//ファイルポインタを宣言

								//ファイルを開く
	pFile = fopen("data\\TXT\\map.txt", "r");

	if (pFile != NULL)
	{
		while (strcmp("END_SCRIPT", &aString[0]) != 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp("OBJECTSET", &aString[0]) == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp("TYPE", &aString[0]) == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &nType);			//位置Ｘ
					}
					if (strcmp("POS", &aString[0]) == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%f", &pos.x);			//位置Ｘ
						fscanf(pFile, "%f", &pos.y);			//位置Ｙ
						fscanf(pFile, "%f", &pos.z);			//位置Ｚ
					}
					if (strcmp("ROT", &aString[0]) == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%f", &rot.x);			//位置Ｘ
						fscanf(pFile, "%f", &rot.y);			//位置Ｙ
						fscanf(pFile, "%f", &rot.z);			//位置Ｚ

						break;
					}
				}
			}
			else if (strcmp("END_OBJECTSET", &aString[0]) == 0)
			{
				CModel::Create(pos,rot, c_Obj[nType]);
			}
		}
	}

	return S_OK;
}

//==============================================================
//ファイル書き出し
//==============================================================
void CEdit::SaveFile(void)
{
	FILE *pFile = NULL;

	pFile = fopen("data\\TXT\\map.txt", "w");

	if (pFile != NULL)
	{
		//ヘッダーコメント
		fprintf(pFile, "#=====================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# マップ配置情報  [map.txt]\n");
		fprintf(pFile, "# Auther : 佐久間優香\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#=====================================================================\n");

		//モデル配置情報
		fprintf(pFile, "#---------------------------------------------------------------------\n");
		fprintf(pFile, "# モデル配置情報\n");
		fprintf(pFile, "#---------------------------------------------------------------------\n");

		fprintf(pFile, "\n");

		fprintf(pFile, "SCREPT					#消さない\n");

		for (int nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
		{
			CObject *pObj = CObject::GetObjectA(nCntModel);

			if (pObj != NULL && pObj->GetType() == TYPE_MODEL)
			{
				D3DXVECTOR3 pos = pObj->GetPosition();
				D3DXVECTOR3 rot = pObj->GetRotation();

				fprintf(pFile, "MODELSET\n");
				fprintf(pFile, "	SET_TYPE = %d\n",m_nTypeIdx);
				fprintf(pFile, "	POS = %.1f %.1f %.1f\n",pos.x, pos.y, pos.z);
				fprintf(pFile, "	ROT = %.1f %.1f %.1f\n",rot.x, rot.y, rot.z);
				fprintf(pFile, "END_MODELSET\n");

				fprintf(pFile, "\n");
			}
		}

		fprintf(pFile, "END_SCREPT					#消さない\n");

		fclose(pFile);
	}
}