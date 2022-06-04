#include "point.cpp"
#include <map>
#include <iostream>
#include <vector>
using namespace std;

class points {
private:
	map<size_t, point> map_points;
	vector<size_t> hash_indices;
public:
	points() {}

	void add_point(point p) {
		size_t code = p.get_hash_code();
		map_points.insert(make_pair(code, p));
		hash_indices.push_back(code);
	}

	point get_point(size_t i) {
		return map_points.at(i);
	}

	map<size_t, point> get_points() {
		return map_points;
	}

	void write_to_file(FILE* file) {
		map<size_t, int> indices;
		int i = 0;
		for (auto& x : this->map_points)
		{
			fprintf(file, "%f %f %f %f %f %f %f %f\n", x.second.getX(), x.second.getY(), x.second.getZ(),x.second.getNX(), x.second.getNY(), x.second.getNZ(), x.second.getTX(), x.second.getTY());
			indices.insert(make_pair(x.second.get_hash_code(), i));
			i++;
		}

		for (size_t i : hash_indices) {
			int ind = indices.at(i);
			fprintf(file, "i%d\n", ind);
		}
		indices.clear();
	}
};