//==============================================================
//
//数字ヘッダー[number.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _NUMBER_H_						//このマクロが定義されていなかったら
#define _NUMBER_H_						//2重インクルード防止のマクロを定義する

#include"object.h"

#include "object2D.h"

//==============================================================
//数字のクラス
//==============================================================
class CNumber
{
public:
	CNumber();			//コンストラクタ
	~CNumber();			//デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);			//初期化処理
	virtual void Uninit(void);													//終了処理
	virtual void Update(void);													//更新処理
	virtual void Draw(void);													//描画処理

	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		//数字の生成
	static HRESULT Load(void);													//テクスチャの読み込み
	static void Unload(void);													//テクスチャの破棄

	void SetNumber(int nNumber);			//数字の設定
	CObject2D * GetObject2D(void);			//オブジェト2Dの取得
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャ
	CObject2D *m_aObject2D;					//オブジェクト2Dのポインタ
	int m_nNumber;							//数字の値
	int m_nldxTexture;						//テクスチャ番号

};			

#endif // !_MULTIBG_H_
