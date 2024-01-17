//==============================================================
//
//背景ヘッダー[bg.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _BG_H_						//このマクロが定義されていなかったら
#define _BG_H_						//2重インクルード防止のマクロを定義する

#include "object2D.h"

//==============================================================
//背景クラス
//==============================================================
class CBg : public CObject2D
{
public:
	CBg();		//コンストラクタ
	~CBg();		//デストラクタ

	static CBg *Create(void);		//背景の生成

	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得

private:
	static CObject2D *m_apObject2D;				//オブジェクト2Dのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;		//共有テクスチャ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;							//位置
	float m_fTexV;								//テクスチャ座標の開始位置(V値)
	float m_fTexU;								//テクスチャ座標の開始位置(U値)
	float m_fmoveV;								//テクスチャ座標の移動量V
	float m_fmoveU;								//テクスチャ座標の移動量V
	int m_nldxTexture;							//テクスチャ番号
};			
#endif // !_BG_H_
