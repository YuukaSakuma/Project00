//==============================================================
//
//メイン処理[main.cpp]
//Author:佐久間優香
//
//==============================================================
#include "main.h"
#include "manager.h"

//マクロ定義
#define CLASS_NAME				"WindowClass"					//ウインドウクラスの名前
#define WINDOW_NAME				"FreeRun"				//ウインドウの名前(キャプションに表示)
#define ID_BUTTON_FINISH		(101)							//終了ボタンのID
#define ID_TIMER				(131)							//タイマーのID
#define TIMER_INTERVAL			(1000/60)						//タイマーの発生間隔(ミリ秒)

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//グローバル変数
int g_nCountFPS = 0;	//FPSカウンター

//==============================================================
//メイン関数
//==============================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wcex
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,									//ウインドウのスタイル
		WindowProc,									//ウインドウのプロシージャ
		0,											//0にする(通常は使用しない)
		0,											//0にする(通常は使用しない)
		hInstance,									//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),				//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),					//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),					//クライアント領域の背景色
		NULL,										//メニューバー
		CLASS_NAME,									//ウインドクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),				//ファイルのアイコン
	};

	HWND hWnd;			//ウインドウハンドル(識別子)
	MSG msg;			//メッセージを格納する変数
	DWORD dwCurrentTime;											//現在時刻
	DWORD dwExecLastTime;											//最後に処理した時刻
	DWORD dwFrameCount;												//フレームカウント
	DWORD dwFPSLastTime;											//最後にを計測した時刻

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };		//画面サイズの構造体

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_EX_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,				//拡張ウインドウスタイル
		CLASS_NAME,							//ウインドウクラスの名前
		WINDOW_NAME,						//ウインドウの名前
		WS_OVERLAPPEDWINDOW,				//ウインドウのスタイル
		CW_USEDEFAULT,						//ウインドウの左上X座標
		CW_USEDEFAULT,						//ウインドウの左上Y座標
		(rect.right - rect.left),			//ウインドウの幅
		(rect.bottom - rect.top),			//ウインドウの高さ
		NULL,								//親ウインドウのハンドル
		NULL,								//メニューハンドルまたは子ウインドウID
		hInstance,							//インスタンスハンドル
		NULL);								//ウインドウ作成データ

	CManager::Get();

	if (CManager::Get() != NULL)
	{
		//レンダラーの初期化処理
		if (FAILED(CManager::Get()->Init(hInstance, hWnd, TRUE)))
		{//初期化処理が失敗した場合

			return -1;
		}
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;												//初期化
	dwExecLastTime = timeGetTime();									//現在時刻を取得(保存)

																	// ランダムの種を再生成
	srand((unsigned)time(0));

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);					//ウインドウの表示状態を設定
	UpdateWindow(hWnd);							//クライアント領域を更新
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);			//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);			//ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();	//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			 //FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	//FPSを測定した時刻を保存
				dwFrameCount = 0;	//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;	//処理開始の時刻[現在時刻]を保存

				if (CManager::Get() != NULL)
				{// 生成できた場合

				 // 更新処理
					CManager::Get()->Update();

					// 描画処理
					CManager::Get()->Draw();
				}

				dwFrameCount++;	//フレームカウントを加算
			}

		}
	}

	CManager::Get()->Release();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;

}

//==============================================================
//ウインドウプロシージャ
//==============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;		//返り値を格納
	
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:		//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//[ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{

				//ウインドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}
		
		break;

	case WM_COMMAND:		//コマンド発行のメッセージ
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{
			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{

				//ウインドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:

		nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウインドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		//0を返さないと終了してしまう
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//既定の処理を返す
}

//================================================
//FPSの取得
//================================================
int GetFPS(void)
{
	return g_nCountFPS;
}