//==============================================================
//
//リザルトヘッダー[result.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _RESULT_H_						//このマクロが定義されていなかったら
#define _RESULT_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"

//前方宣言
class CScore;

//==============================================================
//リザルトクラス
//==============================================================
class CResult : public CScene
{
public:

	CResult();								//コンストラクタ
	~CResult();								//デストラクタ

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

	static CScore *GetScore() { return m_pScore; }
	static void SetScore(int nValue) { m_nScore = nValue; }

private:

	static CScore *m_pScore;
	static int m_nScore;
};
#endif // !_PLAYER_H_


