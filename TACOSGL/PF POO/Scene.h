#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include <stdlib.h>
#include "Camera.h"
#include "Level_01.h"

class Scene
{
public:
	Level_01* _level_01;
	SoundSystemLevels* _soundSystemLevels;
	Camera* camera;

	Scene(HWND hWnd)
	{
		camera = new Camera();
		_level_01 = new Level_01(hWnd);
	}

	~Scene() {
		delete _soundSystemLevels;
	}

	void setKeysPressWnd(int key) {
		_level_01->actionsKeys(key);
	}

	void render(HDC hDC, HWND hWnd)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();
		
		GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);

		camera->cameraUpdate();
		_level_01->render(hDC, hWnd);

		// Don't touch
		SwapBuffers(hDC);
	}

};
#endif
