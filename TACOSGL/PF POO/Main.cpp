#include<Windows.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include "resources.h"

#define Timer1 100
#define FPS 30

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);

HDC hContextoVentana;
Scene *scene;
bool renderiza = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); // Size in bytes of the structure.
	wc.style = CS_HREDRAW | CS_VREDRAW; // 16-bit integer that encodes the style of the window class.
	wc.lpfnWndProc = WindowProc;// Windows Procedure
	wc.hInstance = hInstance;// Identifies the window instance to which this class belongs.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);// Class course identifier. It must be a handler of an icon type resource. If Null, the application will display an icon when the user minimizes the application window.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // Brush identifier for the class.
	wc.lpszClassName = "ProjectRPG"; // Specifies the name of the window class.
	RegisterClassEx(&wc);// Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx functions
	RECT wr = { 0, 0, 1080, 720 }; // Size Windows Default 1080 x 720
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);// Calculate the necessary size of the window rectangle.

	// The previously defined window is created.
	hwndVentana = CreateWindowEx(NULL, // extended window style
		"ProjectRPG",// Specifies the name of the window class.
		"TACOS C++ OpenGL",// Specifies the name of the window class.
		WS_OVERLAPPEDWINDOW,// Window style
		100,// horizontal window position
		100,// Vertical window position
		wr.right - wr.left,// window width
		wr.bottom - wr.top,// window height
		NULL,// parent window handler
		NULL,// menu handle or child window identifier
		hInstance,// application instance handler
		NULL);// pointer to window creation data

	ShowWindow(hwndVentana, nCmdShow);// Show windows created
	
	glewInit();//Init glew

	// Scene instance
	scene = new Scene(hwndVentana);

	// Create a timer with the specified time-out value
	SetTimer(hwndVentana,// Window handler that will receive timer messages
		Timer1,// timer identifier
		FPS,// timeout value
		NULL);// direction of timer procedure

	MSG msg = { 0 };
	
	while (TRUE)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			if (renderiza)
			{
				scene->render(hContextoVentana,hwndVentana);
				renderiza = false;
			}
		}
	}

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;

	switch (message)
	{
	case WM_CREATE:
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		break;
	case WM_KEYDOWN:
		scene->setKeysPressWnd(wParam);
		break;
	case WM_TIMER:
		renderiza = true;
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // structure size
		1, // version number
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // supports window, opengl and will handle double buffering
		PFD_TYPE_RGBA, // 32 bit rgba format
		32, // color size in 32 bits
		0, 0, 0, 0, 0, 0, // color bits (not used)
		0, // no buffer for alpha
		0, // ignore the shift bit
		0, //no accumulation buffer
		0, 0, 0, 0, // no accumulation bits
		16, // float size for z buffer
		0, // no stencil buffers
		0, // no auxiliary buffers
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reserved
		0, 0, 0 //ignored layer masks
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}
