//==============================================================
//
//ブロックX処理[blockX.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _ITEMX_H_							//このマクロ定義がされていなかったら
#define _ITEMX_H_							//2重インクルード防止のマクロを定義するv

#include"objectX.h"

//==============================================================
//ブロックXクラス
//==============================================================
class CItemX : public CObjectX
{
public:

	CItemX();										//コンストラクタ
	CItemX(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//コンストラクタ(オーバーロード)
	~CItemX();										//デストラクタ

	static CItemX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//ブロックXの生成

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void Hit(void);


	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得

private:

	static int m_nNumAll;			//モデルの種類

	static LPD3DXMESH m_pMesh;			//メッシュ（頂点情報）へのポインタ
	static LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	static DWORD m_dwNumMat;			//マテリアルの数

	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	int m_nMaxModel;			//モデルの設置数
	int m_nIdx;					//モデルの番号

	int m_type;			//アイテムの種類
};
#endif