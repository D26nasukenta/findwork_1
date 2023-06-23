#include "main.h"
#include "manager.h"
#include "input.h"

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "FootBall Athlete";

float WindowRatio;							//�V�X�e���̃A�C�R���̊g�嗦
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Forward declare message handler from imgui_impl_win32.cpp//main��220�s��
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

HWND g_Window;



HWND GetWindow()
{
	return g_Window;
}

//�G���g���[�|�C���g(��������n�܂�)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	//HWND		hWnd;


	RegisterClassEx(&wcex);
	
	RECT rc = { 0, 0, SCREEN_WIDTH,SCREEN_HEIGHT};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//window�̘g�����
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		hInstance,
		NULL);



	Manager::Init();

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, g_Window, TRUE)))
	{
		return -1;
	}

	//window�̕\��
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);



	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	//�Q�[�����[�v(����)
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				Manager::Update();
				Update();
				Manager::Draw();
				Draw();
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();
	Uninit();

	return (int)msg.wParam;
}



//�v���V�[�W��(�v���C���[�̓����ɂ��ă{�^����)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{


	//���͂̏I������
	UninitInput();

}
//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();


}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{

}
