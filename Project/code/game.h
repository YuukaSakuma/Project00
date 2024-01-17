//==============================================================
//
//ゲームヘッダー[game.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _GAME_H_						//このマクロが定義されていなかったら
#define _GAME_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"

//前方宣言
class CScore;			//スコアの情報
class CModel;			//モデルの情報
class CField;			//床の情報
class CScore;
class CTime;
class CEdit;
class CEnemyBoss;
class CMap;
class CGame;

//==============================================================
//プレイヤークラス
//==============================================================
class CGame : public CScene
{
public:

	CGame();								//コンストラクタ
	~CGame();								//デストラクタ

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static CPlayerModel *GetPlayerModel(void) { return m_pPlayerModel; }				//プレイヤーの情報
	static CScore *GetScore(void) { return m_pScore; }
	CTime *GetTime(void) { return m_pTime; }
	//static CLife *GetLife(void) { return m_pLife; }

private:

	static CScore *m_pScore;		//スコアの情報
	static CPlayerModel *m_pPlayerModel;	//プレイヤーの情報
	static CModel *m_pModel;		//モデルの情報
	static CField *m_pField;		//床の情報
	static CTime *m_pTime;
	static CEdit *m_pEdit;
	static CMap *m_pMap;
	//static CLife *m_pLife;

	int nData;

	static bool m_bReset;				//リセットしたか
};
#endif // !_PLAYER_H_

