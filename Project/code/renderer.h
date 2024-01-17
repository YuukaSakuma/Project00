//==============================================================
//
//レンダラーヘッダー[renderer.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _RENDERER_H_						//このマクロが定義されていなかったら
#define _RENDERER_H_						//2重インクルード防止のマクロを定義する

#include "main.h"

//前方宣言
class CDebugProc;

//==============================================================
//レンダラークラス
//==============================================================
class CRenderer
{
public:
	CRenderer();			//コンストラクタ
	~CRenderer();			//デストラクタ

	HRESULT Init( HWND hWnd, BOOL bWindow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	LPDIRECT3DDEVICE9 GetDevice(void);		//デバイスの取得
	
private:

	LPDIRECT3D9 m_pD3D;										//Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;							//Direc3Dデバイスへのポインタ
};
#endif // !_MAIN_H_
