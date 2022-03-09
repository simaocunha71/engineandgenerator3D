#include "point.cpp"
#include <map>
#include <list>

using namespace std;

class points {
private:
	map<size_t, point> map_points;
	list<size_t> indexs;
public:
	points() {
		this->map_points;
		this->indexs;
	}
	void add_point_sort(point p) {
		add_point(p);
		add_index(p.get_hash_code());
	}

	void add_point(point p) {
		map_points.insert(make_pair(p.get_hash_code(), p));
	}

	void add_index(size_t i) {
		indexs.push_back(i);
	}

	point get_point(size_t i) {
		return map_points.at(i);
	}

	point get_next_point() {
		size_t i = indexs.front();
		indexs.pop_front();
		return get_point(i);
	}
};