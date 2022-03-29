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
};