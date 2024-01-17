//==============================================================
//
//爆発ヘッダー[explosion.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _EXPLOSION_H_						//このマクロが定義されていなかったら
#define _EXPLOSION_H_						//2重インクルード防止のマクロを定義する

#include "billboard.h"

//==============================================================
//爆発クラス
//==============================================================
class CExplosion : public CBillboard
{
public:

	CExplosion();								//コンストラクタ
	CExplosion(D3DXVECTOR3 pos, TYPE type);		//コンストラクタ(オーバーロード)
	~CExplosion();								//デストラクタ

	static CExplosion *Create(D3DXVECTOR3 pos, TYPE type);			//爆発の生成

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

private:

	int m_nLife;							//寿命
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_rot;						//向き	
	int m_nCounterAnim;						//アニメーションカウンター
	int m_nPatternAnim;						//パターンNo.カウンター
	int m_nldxTexture;						//テクスチャ番号
	
};
#endif // !_EXPLOSION_H_
