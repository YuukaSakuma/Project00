//==============================================================
//
//スコアヘッダー[score.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _TIME_H_						//このマクロが定義されていなかったら
#define _TIME_H_						//2重インクルード防止のマクロを定義する

#include "main.h"

//前方宣言
class CNumber;

//==============================================================
//スコアのクラス
//==============================================================
class CTime /*:CObject*/
{
public:
	CTime();		//コンストラクタ
	~CTime();		//デストラクタ

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	static CTime *Create(D3DXVECTOR3 pos);		//生成処理

	void Set(int nNum);					//スコア設定
	void Add(int nValue);				//スコア足して設定

	int GetNum(void) { return m_nNum; }			//スコア取得
	int GetStartNum(void) { return m_nSetNum; }
	float GetAnim(void) { m_fAnimTime; };

private:

#define NUM_TEX (4)	//テクスチャ数

	void SetValue(void);

	CNumber *m_apNumber[NUM_TEX];			//数字のポインタ
	D3DXVECTOR3 m_pos;				//位置

	int m_nNum;				//現在の値
	int m_nSetNum;			//設定する値
	float m_fAnimTime;		//カウント
	int m_nldxTexture;		//テクスチャ番号

};			
#endif // !_MULTIBG_H_
