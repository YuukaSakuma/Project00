//==============================================================
//
//リザルトヘッダー[result.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _RANKING_H_						//このマクロが定義されていなかったら
#define _RANKING_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"

#define NUM_RANK	(5)		// ランキングの順位数

//前方宣言
class CScore;

//==============================================================
//リザルトクラス
//==============================================================
class CRanking : public CScene
{
public:

	CRanking();								//コンストラクタ
	~CRanking();								//デストラクタ

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

	static void SetScore(int nValue) { m_nScore = nValue; }

private:
	// メンバ関数
	void Save(int *pScore);
	void Load(int *pScore);
	void Sort(int *pScore);
	void RankIn(int *pScore, int nResult);

	// メンバ変数
	static CScore *m_apScore[NUM_RANK];	// スコアのポインタ(順位分)
	static int m_nScore;	// 今回のスコア
	int m_nTimer;			// 自動遷移タイマー
	int m_nRank;

};
#endif // !_PLAYER_H_

