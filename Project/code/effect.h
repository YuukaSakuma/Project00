//==============================================================
//
//エフェクトヘッダー[effect.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _EFFECT_H_						//このマクロが定義されていなかったら
#define _EFFECT_H_						//2重インクルード防止のマクロを定義する

#include"billboard.h"

//==============================================================
//エフェクトクラス
//==============================================================
class CEffect : public CBillboard
{
public:

	CEffect();																					//コンストラクタ
	CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);		//コンストラクタ(オーバーロード)
	~CEffect();																					//デストラクタ

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);			//エフェクトの生成

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

private:

	D3DXVECTOR3 m_move;		//移動量
	D3DXCOLOR m_col;		//色
	float m_fRadius;		//半径(大きさ)
	int m_nLife;			//寿命(表示時間)
	int m_nldxTexture;		//テクスチャ番号
};
#endif // !_EFFECT_H_
