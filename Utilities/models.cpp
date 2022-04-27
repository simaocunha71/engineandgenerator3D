#include "points.cpp" 
#include "transformation.cpp"

class model {
public:
	vector<float> ps;
	vector<unsigned int> idxs;
	GLuint indices, vertices;
	unsigned int indexCount;

	model() {
		this->idxs;
		this->indexCount = 0;
		this->indices = 0;
		this->vertices = 0;
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
	vector<model> mds;

	models() {
		this->mds;
	}

	void add_model(model m) {
		this->mds.push_back(m);
	}


	void prepare_data() {
		for (vector<model>::iterator it = this->mds.begin(); it != this->mds.end(); ++it) {
			it->prepare_data();
		}
	}

	void render() {
		for (vector<model>::iterator it = this->mds.begin(); it != this->mds.end(); ++it) {
			it->render();
		}
	}
};

class transformations {
public:
	vector<transformation*> trs;

	transformations() {}

	void add_transformation(transformation* tr) {
		this->trs.push_back(tr);
	}

	void transform() {
		glPushMatrix();
		for (vector<transformation*>::iterator it = this->trs.begin(); it != this->trs.end(); ++it) {
			(*it)->transform();
		}
	}

	void destransform() {
		glPopMatrix();
	}

};


class group {
public:
	vector<group> gs;
	models ms;
	transformations trs;

	group(){
		this->ms = models();
	}

	void add_group(group g) {
		gs.push_back(g);
	}

	void add_models(models ms) {
		this->ms = ms;
	}

	void add_transformations(transformations trs) {
		this->trs = trs;
	}

	void prepare_data() {
		for (vector<group>::iterator it = this->gs.begin(); it != this->gs.end(); ++it) {
			it->prepare_data();
		}
		ms.prepare_data();
	}

	void render() {
		trs.transform();
		for (vector<group>::iterator it2 = this->gs.begin(); it2 != this->gs.end(); ++it2) {
			it2->render();
		}
		ms.render();
		trs.destransform();
	}
};