//==============================================================
//
//モーションヘッダー[player.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _MOTION_H_						//このマクロが定義されていなかったら
#define _MOTION_H_						//2重インクルード防止のマクロを定義

#include "main.h"

//マクロ定義
#define MAX_PARTS		(15)		//パーツ最大数
#define MAX_KEY			(32)		//キー最大数

//前方宣言
class CModelHier;			//モデルの階層構造

//==============================================================
//モーションクラスの定義
//==============================================================
class CMotion
{
public:

	//モーションの種類
	typedef enum
	{
		MOTION_NEUTRAL = 0,		//待機
		MOTION_WALK,			//歩き
		MOTION_JUMP,			//ジャンプ
		MOTION_LAND,			//着地
		MOTOIN_CLIMB,			//壁登り
		MOTION_CLIMB_NEUTRAL,	//壁登りの待機
		MOTION_MAX

	} MOTION;

	//キーの構造体
	typedef struct
	{
		float fPosX;		//位置X
		float fPosY;		//位置Y
		float fPosZ;		//位置Z
		float fRotX;		//向きX
		float fRotY;		//向きY
		float fRotZ;		//向きZ

	} KEY;

	//キー情報の構造体
	typedef struct
	{
		int nFrame;				//再生フレーム
		KEY aKey[MAX_PARTS];	//各モデルのキー要素
	} KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool bLoop;						//ループするかどうか
		int nNumKey;					//キーの総数
		KEY_INFO aKeInfo[MAX_KEY];		//キー情報

	} INFO;

	CMotion();		//コンストラクタ
	~CMotion();		//デストラクタ

	static CMotion *Create(void);		//生成処理

	void Set(int nType);						//設定処理
	void Init(const char *c_MotionFile, int nNumModel);							//初期化処理
	void Update(void);							//更新処理
	int GetType(void) { return m_nType; }		//種類の取得
	bool IsFinish(void);						//終了
	void SetInfo(INFO info) { m_aInfo[m_nType] = info; }
	void SetModel(CModelHier **ppModel, int nNumModel) { m_ppModel = ppModel; }		//モデルの情報設定

	//void FileLoad(void);
	void FileLoad(const char *c_MotionFile);

private:
	INFO m_aInfo[MOTION_MAX];
	int m_nNumAll;				//総数
	int m_nType;				//モーションの種類
	bool m_bLoop;				//ループするか
	int m_NumKey;				//キー数
	int m_nKey;					//キー
	int m_nCounter;				//モーションカウンター
	bool m_bFinish;				//終了したかどうか

	CModelHier **m_ppModel;		//モデルへのポインタ
	int m_nNumModel;			//モデルの総数
};

#endif
