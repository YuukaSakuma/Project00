//==============================================================
//
//プレイヤーヘッダー[player.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _PLAYERMODEL_H_						//このマクロが定義されていなかったら
#define _PLAYERMODEL_H_						//2重インクルード防止のマクロを定義する

#include "object.h"

//前方宣言
class CModelHier;	//モデルの階層構造
class CMotion;		//モーションの階層構造

//==============================================================
//プレイヤークラス
//==============================================================
class CPlayerModel : public CObject
{
public:

	CPlayerModel();								//コンストラクタ
	CPlayerModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//コンストラクタ
	~CPlayerModel();								//デストラクタ

	static CPlayerModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//プレイヤーの生成

	HRESULT Init(void);						//プレイヤーの初期化処理
	void Uninit(void);						//プレイヤーの終了処理
	void Update(void);						//プレイヤーの更新処理
	void Draw(void);						//プレイヤーの描画処理

	void Control(void);		//入力処理
	void Screen(void);		//画面外判定

	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//向き取得
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }


	void SetModel(const char * c_FileName);			//モデルの設定
	void SetMotion(void);							//モーションの設定
	void Walk(void);								//移動(歩き)
	void RotCorrection(void);						//向きの補正
	void Hit(void);									//ヒット処理
	void SetState(void);
	
	int GetLife(void) { return m_nLife; }
	void SetCounter(int nCounter) { m_nCntScore = nCounter; }

private:

	static char *m_apFileName[15];		//ファイル名

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_posOld;			//前回の位置
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_rot;				//向き
	D3DXVECTOR3 m_max;				//最大値
	D3DXVECTOR3 m_min;				//最小値
	D3DXMATRIX m_mxtWorld;			//ワールドマトリックス

	D3DXVECTOR3 m_Wpos;				//マップ位置

	STATE m_state;					//種類

	int m_nCntDamage;

	CModelHier *m_apModel[15];		//モデル(パーツ)へのポインタ

	int m_nNumModel;		//モデル(パーツ)の総数
	bool m_bJump;			//ジャンプしたかの判定
	bool m_bMove;			//歩いてるかの判定
	bool m_bLand;			//着地したか

	int m_nldxTexture;

	float m_fRotDest;		//目標
	float m_fRotDiff;		//差分
	float m_fRotMove;

	CMotion *m_pMotion;		//モーション情報

	int m_nLife;			//体力

	int m_nCntStart;		//開始までの時間
	int m_nCntScore;		//スコア増加量の変化時間

	bool m_bAutoMove;		//自動移動するか
	bool m_bSecondJump;		//二段ジャンプしているか
	bool m_bHit;			//死んでいるか

};
#endif // !_PLAYER_H_
