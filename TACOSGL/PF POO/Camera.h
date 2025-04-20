#ifndef __Camera
#define __Camera

class Camera
{

public:

	// Position - Orientation - Up
	GLdouble px = 0, py = 2, pz = 4, dx = 0, dy = 2, dz = 3, ux = 0, uy = 1, uz = 0;

	int camind = 0;

	Camera()
	{

	}

	void cameraInitialize()
	{
		px = 0, py = 2, pz = 4, dx = 0, dy = 2, dz = 3;
		ux = 0, uy = 1, uz = 0;
		//gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
		gluLookAt(px, py, pz, dx + px, dy + py, dz + pz, ux, uy, uz);
	}
	//Las coordenadas 'P' son el Eye (position), Coordenadas 'D' (observation)

	void cameraUpdate()
	{
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

};
#endif