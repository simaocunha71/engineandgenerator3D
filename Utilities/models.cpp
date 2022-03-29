#include "points.cpp" 
#include "point.cpp"
#include "transformation.cpp"

class model {
public:
	vector<float> ps;
	vector<unsigned int> idxs;
	GLuint indices, vertices;
	unsigned int indexCount;
	transformation tr;

	model(transformation tr){
		this->idxs;
		this->indexCount = 0;
		this->indices = 0;
		this->vertices = 0;
		this->tr = tr;
	}

	model() {
		this->idxs;
		this->indexCount = 0;
		this->indices = 0;
		this->vertices = 0;
		this->tr = transformation();
	}

	void add_point(point p) {
		ps.push_back(p.getX());
		ps.push_back(p.getY());
		ps.push_back(p.getZ());
	}

	void add_index(int idx) {
		this->idxs.push_back(idx);
		this->indexCount += 1;
	}

	void prepare_data() {
		//criar o VBO
		glGenBuffers(1, &(this->vertices));
		// copiar o vector para a memória gráfica
		glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
		glBufferData(
			GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
			sizeof(float) * this->ps.size(), // tamanho do vector em bytes
			this->ps.data(), // os dados do array associado ao vector
			GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)
		//criar o VBO de indices
		glGenBuffers(1, &(this->indices));
		// copiar o vector dos indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(unsigned int) * this->idxs.size(),
			this->idxs.data(),
			GL_STATIC_DRAW);
	}

	void render() {
		glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indices);
		glDrawElements(GL_TRIANGLES,
			this->indexCount, // número de índices a desenhar
			GL_UNSIGNED_INT, // tipo de dados dos índices
			NULL);// parâmetro não utilizado 
	}
};

class models {
public:
	vector<model> list_model;
	transformation tr;

	models() {
		this->list_model;
		this->tr = transformation();
	}
	models(transformation tr ) {
		this->list_model;
		this->tr = tr;
	}

	void add_model(model m) {
		this->list_model.push_back(m);
	}

	void prepare_data() {

		for (vector<model>::iterator it = this->list_model.begin(); it != this->list_model.end(); ++it) {
			it->prepare_data();
		}
	}

	void render() {
		tr.transform();
		for (vector<model>::iterator it = this->list_model.begin(); it != this->list_model.end(); ++it) {
			it->render();
		}
		tr.destransform();
	}
};