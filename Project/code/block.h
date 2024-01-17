//==============================================================
//
//ブロックヘッダー[block.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _BLOCK_H_						//このマクロが定義されていなかったら
#define _BLOCK_H_						//2重インクルード防止のマクロを定義する

#include"object2D.h"

//==============================================================
//ブロッククラス
//==============================================================
class CBlock : public CObject2D
{
public:

	CBlock();									//コンストラクタ
	CBlock(TYPE type, D3DXVECTOR3 pos);			//コンストラクタ(オーバーロード)
	~CBlock();									//デストラクタ

	static CBlock *Create(TYPE type, D3DXVECTOR3 pos);	//弾の生成

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);		//敵との当たり判定

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャ

	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_rot;						//向き	

	static float m_fWidth;					//横幅
	static float m_fHeight;					//縦幅

	int m_nldxTexture;						//テクスチャ番号

};
#endif // !_BLOCK_H_
