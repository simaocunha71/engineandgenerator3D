#include "points.cpp" 
#include "transformation.cpp"
#include <IL/il.h>

class rgb {
public:
	//maybe tem de ser floats
	int r;
	int g;
	int b;
	rgb() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	rgb(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	float* toFloatArr() {
		float rgb[4] = { r / 255.0,g / 255.0,b / 255.0,1};
		return rgb;
	}
};

class color {
public:
	rgb diffuse;
	rgb ambient;
	rgb specular;
	rgb emissive;
	int shininess; //maybe tem de ser float

	color(){
		this->diffuse = rgb(200,200,200);
		this->ambient = rgb(50,50,50);
		this->specular = rgb();
		this->emissive = rgb();
		this->shininess = 0;
	}
	void add_diffuse(int r, int g, int b) {
		this->diffuse = rgb(r, g, b);
	}

	float* get_diffuse() {
		return this->diffuse.toFloatArr();
	}

	void add_ambient(int r, int g, int b) {
		this->ambient = rgb(r, g, b);
	}

	float* get_ambient() {
		return this->ambient.toFloatArr();
	}

	void add_specular(int r, int g, int b) {
		this->specular = rgb(r, g, b);
	}

	float* get_specular() {
		return this->specular.toFloatArr();
	}

	void add_emissive(int r, int g, int b) {
		this->emissive = rgb(r, g, b);
	}

	float* get_emissive() {
		return this->emissive.toFloatArr();
	}

	void add_shininess(int shininess) {
		this->shininess = shininess;
	}
};

class model {
public:
	vector<float> ps; //pontos do modelo
	vector<float> ns; //pontos das normais
	vector<float> ts; //pontos de textura
	vector<unsigned int> idxs;
	GLuint indices, vertices, normals, textures, textureID;
	unsigned int indexCount;
	color c;
	bool hastx;
	char* texturename;
	char* name;

	model() {
		this->idxs;
		this->indexCount = 0;
		this->indices = 0;
		this->vertices = 0;
		this->normals = 0;
		this->textures = 0;
		this->texturename = "";
		this->c = color();
		this->name = "";
		this->hastx = false;
	}

	void add_color(color c) {
		this->c = c;
	}

	void add_name(const char * name) {
		this->name = strdup(name);
	}

	void add_point(point p) {
		ps.push_back(p.getX());
		ps.push_back(p.getY());
		ps.push_back(p.getZ());
		ns.push_back(p.getNX());
		ns.push_back(p.getNY());
		ns.push_back(p.getNZ());
		ts.push_back(p.getTX());
		ts.push_back(p.getTY());
	}

	void add_index(int idx) {
		this->idxs.push_back(idx);
		this->indexCount += 1;
	}

	void add_texture(const char* texture) {
		this->texturename = strdup(texture);
		this->hastx = true;
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

		//criar o VBO de normais
		glGenBuffers(1, &(this->normals));
		// copiar o vector das normais
		glBindBuffer(GL_ARRAY_BUFFER, this->normals);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(float) * this->ns.size(),
			this->ns.data(),
			GL_STATIC_DRAW);

		//criar o VBO das texturas
		if (this->hastx) {
			glGenBuffers(1, &(this->textures));
			// copiar o vector das normais
			glBindBuffer(GL_ARRAY_BUFFER, this->textures);
			glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * this->ts.size(),
				this->ts.data(),
				GL_STATIC_DRAW);
		}
		load_texture();
	}

	void render() {
		if (!this->hastx) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, c.get_ambient());
			glMaterialfv(GL_FRONT, GL_DIFFUSE, c.get_diffuse());
			glMaterialfv(GL_FRONT, GL_SPECULAR, c.get_specular());
			glMaterialf(GL_FRONT, GL_SHININESS, (GLfloat)c.shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, c.get_emissive());
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, this->normals);
		glNormalPointer(GL_FLOAT, 0, 0);

		if (this->hastx) {
			glBindBuffer(GL_ARRAY_BUFFER, this->textures);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
			glBindTexture(GL_TEXTURE_2D, this->textureID);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indices);
		glDrawElements(GL_TRIANGLES,
			this->indexCount, // número de índices a desenhar
			GL_UNSIGNED_INT, // tipo de dados dos índices
			NULL);// parâmetro não utilizado 

		if (this->hastx)
			glBindTexture(GL_TEXTURE_2D, 0);
	}

	void load_texture() {
		if (this->hastx) {
			unsigned int t, tw, th;
			unsigned char* texData;
			ilInit();
			ilEnable(IL_ORIGIN_SET);
			ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
			ilGenImages(1, &t);
			ilBindImage(t);
			ilLoadImage((ILstring)this->texturename);
			cout << "name>> " << this->texturename << "\n";
			tw = ilGetInteger(IL_IMAGE_WIDTH);
			th = ilGetInteger(IL_IMAGE_HEIGHT);
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
			texData = ilGetData();

			glGenTextures(1, &this->textureID);

			glBindTexture(GL_TEXTURE_2D, this->textureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
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