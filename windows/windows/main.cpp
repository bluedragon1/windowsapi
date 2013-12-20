#include <windows.h>
#include <iostream>
#define BUTTON_ID1 1
#define BUTTON_ID2 2
#define EDIT_ID 3

int a;

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	static HWND edit;
	PAINTSTRUCT ps;
	LPSTR strText,szStr1=TEXT("カウントダウンの秒数（1～10秒の間）を指定してください。");
	int i;
	HDC hdc;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 30, 10, szStr1, strlen(szStr1));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_CREATE:
		edit = CreateWindow(
			TEXT("EDIT") , TEXT("5") , 
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT ,
			220 , 40 , 50 , 25 , hwnd , (HMENU)EDIT_ID ,
			((LPCREATESTRUCT)(lp))->hInstance , NULL
		);


		CreateWindow(
			TEXT("BUTTON") , TEXT("OK") ,
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
			80 , 70 , 150 , 30 ,
			hwnd , (HMENU)BUTTON_ID1 , ((LPCREATESTRUCT)(lp))->hInstance , NULL);

		CreateWindow(
			TEXT("BUTTON") , TEXT("cancel") ,
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
			250 , 70 , 150 , 30 ,
			hwnd , (HMENU)BUTTON_ID2 , ((LPCREATESTRUCT)(lp))->hInstance , NULL);
		case WM_COMMAND:
			switch(LOWORD(wp)) {
				case BUTTON_ID1:
					//コンボボックスの情報からint型を返す
					strText = (LPSTR)malloc(GetWindowTextLength(hwnd) + 4);
					GetWindowTextA(edit , strText , GetWindowTextLength(hwnd) + 4);
					i=atoi(strText);
					if(i<1||i>10){
						MessageBox(hwnd , "値が指定範囲外です。" , TEXT("error") , MB_OK);
					}else{
						a=i;
						DestroyWindow(hwnd);
						PostQuitMessage(0);
					}
					free(strText);
					break;
				case BUTTON_ID2:
					//値を変化せずに終了(ok)
					DestroyWindow(hwnd);
					PostQuitMessage(0);
					break;
			}
			return 0;
		return 0;		
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow ) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("STATIC");
	a=5;
	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
			TEXT("STATIC") , TEXT("countdown設定") ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			500 , 150 ,
			NULL , NULL , hInstance , NULL
	);

	if (hwnd == NULL) return -1;

	while(GetMessage(&msg , NULL , 0 , 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	std::cout<<a<<std::endl;
	return msg.wParam;
}