#include "../Utilities/points.cpp" 
#include "../Utilities/point.cpp"

#define INIT_BUFFER_MODELS 10

class model {
private:
	string filename;
	points ps;
public:
	model() {
		this->filename = "";
		this->ps = points();
	}
	void add_point(point p) {
		ps.add_point(p);
	}

	void add_triangle_index(string t) {
		ps.add_triangle_index(t);
	}

	void set_filename(string filename) {
		this->filename = filename;
	}
	string get_filename() {
		return this->filename;
	}
	point get_point(int i) {
		return this->ps.get_point(i);
	}

	void draw() {
		ps.draw_triangles();
	}
};

class models {
private:
	model* list_model;
	int nmodels;
	size_t buffer;
public:
	models() {
		this->buffer = INIT_BUFFER_MODELS;
		this->list_model = new model[this->buffer];
		this->nmodels = 0;
	}
	void add_model(model m) {
		this->list_model[nmodels] = m;
		this->nmodels += 1;
		if (nmodels >= this->buffer) { //se exceder o buffer atual -> 
			size_t new_buffer = this->buffer * 2; // duplica-o -> 
			model* new_models = new model[new_buffer]; // cria um novo "array" com o tamanho novo -> 
			memcpy(new_models, list_model, this->buffer * sizeof(model)); // copia as cenas do antigo para o novo -> 
			this->buffer = new_buffer;
			delete[] this->list_model; // deita fora o "array".
			this->list_model = new_models;
		}
	}

	void draw() {
		for (int i = 0; i < this->nmodels; i++) {
			this->list_model[i].draw();
		}
	}
};