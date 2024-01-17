//==============================================================
//
//フェード処理[fade.cpp]
//Author:佐久間優香
//
//==============================================================
#include"fade.h"

//静的メンバ変数

//==============================================================
//コンストラクタ
//==============================================================
CFade::CFade()
{
	m_state = STATE_NONE;
	m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//==============================================================
//デストラクタ
//==============================================================
CFade::~CFade()
{


}

//==============================================================
//生成処理
//==============================================================
CFade *CFade::Create(CScene::MODE modeNext)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;

		if (pFade != NULL)
		{
			pFade->Init(modeNext);
			pFade->SetState(STATE_IN);
		}
	}

	return pFade;
}

//==============================================================
//初期化処理
//==============================================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	CObject2D::Init();

	//サイズ設定
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetVtx(0.0f, 0.0f);

	Set(modeNext);

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//==============================================================
//更新処理
//==============================================================
void CFade::Update(void)
{
	if (m_state != STATE_NONE)
	{//何もしていない状態以外のとき

		if (m_state == STATE_IN)
		{//フェードイン状態

			m_Col.a -= 0.02f;

			if (m_Col.a <= 0.0f)
			{//完全に透明になったら

				m_Col.a = 0.0f;
				m_state = STATE_NONE;
			}
		}
		else if (m_state == STATE_OUT)
		{//フェードアウト状態

			m_Col.a += 0.02f;

			if (m_Col.a >= 1.0f)
			{//完全に不透明になったら

				m_Col.a = 1.0f;

				//モードの設定
				CManager::SetMode(m_modeNext);
				return;
			}
		}
	}

	SetCol(m_Col);
}

//==============================================================
//描画処理
//==============================================================
void CFade::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//==============================================================
//次の画面設定
//==============================================================
void CFade::Set(CScene::MODE modeNext)
{
	if (m_state != STATE_OUT)
	{
		m_state = STATE_OUT;
		m_modeNext = modeNext;
		m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//==============================================================
//状態設定
//==============================================================
void CFade::SetState(STATE state)
{
	if (m_state == state)
	{
		return;
	}

	m_state = state;

	switch (m_state)
	{
	case STATE_NONE:

		m_Col.a = 0.0f;
		
		break;

	case STATE_IN:

		m_Col.a = 1.0f;

		break;

	case STATE_OUT:

		m_Col.a = 0.0f;

		break;
	default:
		break;
	}

	SetCol(m_Col);
}