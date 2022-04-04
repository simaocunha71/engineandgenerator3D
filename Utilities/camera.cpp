#include <stdio.h>
class camera {
public:
	float px, py, pz, lx, ly, lz, ux, uy, uz, fov, near, far;
	camera() {
		this->px = 5.0f;
		this->py = 5.0f;
		this->pz = 5.0f;
		this->lx = 0.0f;
		this->ly = 0.0f;
		this->lz = 0.0f;
		this->ux = 0.0f;
		this->uy = 1.0f;
		this->uz = 0.0f;
		this->fov = 45.0f;
		this->near = 0.0f;
		this->far = 100.0f;
	}

	void print_camera() {
		printf("CAMERA:");
		printf("Position: %f %f %f\n",this->px,this->py,this->pz);
		printf("LookAt: %f %f %f\n", this->lx, this->ly, this->lz);
		printf("Up: %f %f %f\n", this->ux, this->uy, this->uz);
		printf("Projection: %f %f %f\n", this->fov, this->near, this->far);
	}
};