//==============================================================
//
//オブジェクト3Dヘッダー[object3D.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _OBJECT3D_H_							//このマクロ定義がされていなかったら
#define _OBJECT3D_H_							//2重インクルード防止のマクロを定義する

#include "object.h"

//==============================================================
//オブジェクト3Dクラス
//==============================================================
class CObject3D : public CObject
{
public:
	CObject3D ();		//コンストラクタ
	~CObject3D ();		//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	static CObject3D *Create(void);			//生成処理

	void BindTexture(int pTexture) { m_nldxTexture = pTexture; }	//テクスチャ番号の取得

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置の取得

	void SetSize(float width, float heiget,float vertical);	//サイズの設定

	float GetHeight(D3DXVECTOR3 VecPos);		//サイズの設定

private:
	//グローバル変数宣言
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャ(3枚分)へのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_rot;								//向き

	int m_nldxTexture;		//テクスチャ番号
};
#endif