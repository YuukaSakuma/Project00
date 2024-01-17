//==============================================================
//
//タイトルヘッダー[title.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _TUTORIAL_H_						//このマクロが定義されていなかったら
#define _TUTORIAL_H_						//2重インクルード防止のマクロを定義する

#include"manager.h"

//前方宣言
class CScore;			//スコアの情報
class CPlayerModel;		//プレイヤーの情報
class CEnemyModel;		//敵の情報
class CModel;			//モデルの情報
class CField;			//床の情報

//==============================================================
//タイトルクラス
//==============================================================
class CTutorial : public CScene
{
public:
	CTutorial();								//コンストラクタ
	~CTutorial();								//デストラクタ

	HRESULT Init(void);						//タイトルの初期化処理
	void Uninit(void);						//タイトルの終了処理
	void Update(void);						//タイトルの更新処理
	void Draw(void);						//タイトルの描画処理

private:

	static CScore *m_pScore;
	static CPlayerModel *m_pPlayerModel;
	static CEnemyModel *m_pEnemyModel;
	static CModel *m_pModel;
	static CField *m_pField;

	static bool m_bReset;

};
#endif // !_PLAYER_H_


