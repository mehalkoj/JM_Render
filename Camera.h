#pragma once
#include <SDL3/SDL.h>
#include "JM_Math.h"

class Camera {

};


	Vec3 cameraPos = Vec3(0.0, 0.0, 3.0);
	Vec3 cameraFront = Vec3(0.0, 0.0, -1.0);
	Vec3 cameraUp = Vec3(0.0, 1.0, 0.0);


	Vec3 up = Vec3(0.0, 1.0, 0.0);
	//Vec3 cameraRight = up.cross(cameraDirection).normalized();
	
	//Vec3 cameraUp = cameraDirection.cross(cameraRight);

	Mat4 view;



	void camera() {
		view = view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

