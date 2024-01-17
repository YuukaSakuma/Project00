//==============================================================
//
//ポリゴンヘッダー[polygon.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _POLYGON_H_						//このマクロが定義されていなかったら
#define _POLYGON_H_						//2重インクルード防止のマクロを定義する

#include "object3D.h"

//==============================================================
//ポリゴンクラス
//==============================================================
class CPolygon : public CObject3D
{
public:

	CPolygon();									//コンストラクタ
	CPolygon(TYPE type,D3DXVECTOR3 pos);		//コンストラクタ(オーバーロード)
	~CPolygon();								//デストラクタ

	static CPolygon *Create(TYPE type, D3DXVECTOR3 pos);			//エネミーの生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	//void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	//D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置の取得

private:

	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_rot;						//向き
	D3DXVECTOR3 m_pos;						//位置

	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャ

	int m_nldxTexture;
};
#endif // !_ENEMY_H_
