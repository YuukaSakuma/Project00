//==============================================================
//
//スコアヘッダー[score.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _SCORE_H_						//このマクロが定義されていなかったら
#define _SCORE_H_						//2重インクルード防止のマクロを定義する

#include "main.h"
#include"object.h"
#include"number.h"

//前方宣言
class CNumber;

#define NUM_SCORE	(8)	// スコアの桁数

//==============================================================
//スコアのクラス
//==============================================================
class CScore /*:CObject*/
{
public:
	CScore();		//コンストラクタ
	~CScore();		//デストラクタ

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	static CScore *Create(D3DXVECTOR3 pos);		//生成処理

	//void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置の設定
	//D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置の取得

	static void Set(int nNum);					//スコア設定
	static void Add(int nValue);				//スコア足して設定
	int Get(void) { return m_nNumber; }			//スコア取得
	static void SetValue(void);
	void SetColor(D3DXCOLOR col);
private:

	static LPDIRECT3DTEXTURE9 m_pTexture;		//共有テクスチャ
	static int m_nNumber;
	static CNumber *m_apNumber[NUM_SCORE];				//オブジェクト2Dのテクスチャ
	D3DXVECTOR3 m_pos;							//位置
	int m_nldxTexture;
};			
#endif // !_MULTIBG_H_
