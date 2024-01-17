//==============================================================
//
//ビルボードヘッダー[billboard.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _BILLBOARD_H_							//このマクロ定義がされていなかったら
#define _BILLBOARD_H_							//2重インクルード防止のマクロを定義する

#include"object.h"


//==============================================================
//ビルボードクラス
//==============================================================
class CBillboard : public CObject
{
public:
	CBillboard();								//コンストラクタ
	~CBillboard();								//デストラクタ

	static CBillboard *Create(void);			//ビルボードの生成

	//プロトタイプ宣言
	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	void BindTexture(int pTexture) { m_nldxTexture = pTexture; }		//テクスチャの割り当て
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }					//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }						//位置の取得

	void SetSize(float width, float heiget, float vertical);	//サイズ設定

	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//移動量設定
	D3DXVECTOR3 GetMove(void) { return m_move; }		//移動量取得

	void SetRadius(float fRadius);
	void SetVtx(int nPattern, TYPE type);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_rot;								//向き
	D3DXVECTOR3 m_move;								//移動量

	int m_nldxTexture;								//テクスチャ番号
};
#endif