//==============================================================
//
//オブジェクト2Dヘッダー[object2D.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _OBJECT2D_H_						//このマクロが定義されていなかったら
#define _OBJECT2D_H_						//2重インクルード防止のマクロを定義する

#include "main.h"
#include "object.h"

//==============================================================
//オブジェクト2Dクラス
//==============================================================
class CObject2D : public CObject
{
public:

	CObject2D();		//コンストラクタ
	~CObject2D();		//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	static CObject2D *Create(void);		//生成処理

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得

	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//移動量設定
	D3DXVECTOR3 GetMove(void) { return m_move; }		//移動量取得


	void SetVtx(int nPattern, TYPE type);				//
	void SetVtx(float fTexV,float fTexU);				//
	void SetVtx(int nPatternAnim, float nDigitX);		//アニメーションの設定
	void SetRadius(float m_fRadius);					//半径の設定
	void SetSize(float width, float heiget);			//サイズの設定
	void SetVtxBlock(float width, float heiget);		//ブロックの設定
	void SetVtxPlayer(float width, float heiget);		//プレイヤーの設定
	void SetVtxItem(float width, float heiget);			//アイテムの設定

	void SetCol(D3DXCOLOR col);

	void BindTexture(int nldx) {m_nldx = nldx; }		//テクスチャ番号の設定

	//void SetType(TYPE type);
	//int GetType(void);
	
private:

	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_move;							//位置
	TYPE m_type;								//種類
	float m_fWidth;								//横幅
	float m_fHeight;							//縦幅

	int m_nldx;				//テクスチャ番号
};
#endif // !_MAIN_H_


