#include "DBSCAN.hpp"
#include "nanoflann.hpp"
#include "PointCloud.hpp"

#define UNVISITED 0
#define NOISE 1
#define CLUSTERED 2

using namespace std;

class DBSCAN::Impl {

public:

  Impl(const std::vector<Point4>& points, float epsilon, size_t minPts);
  ~Impl() = default;

  std::vector< std::vector<Point4> > cluster();

private:
  
  typedef std::unordered_map<size_t, uint8_t > statusmap_t;

  typedef nanoflann::KDTreeSingleIndexAdaptor<
    nanoflann::L2_Simple_Adaptor<float, PointCloud>,
    PointCloud,
    3
  > my_kd_tree_t;

  const float eps;
  const size_t minPts;

  const PointCloud cloud;

  my_kd_tree_t tree;
  statusmap_t visited;

  void expandCluster(size_t focalPoint,
    std::vector<size_t>& cluster,
    std::vector<size_t>& neighborV,
    std::unordered_set<size_t>& neighborS);

  std::vector<size_t> getNeighbors(size_t point);
};

DBSCAN::Impl::Impl(const vector<Point4>& points, float epsilon, size_t minPts) :
	eps(epsilon), minPts(minPts), cloud(PointCloud{ points }),
	tree(3, cloud, nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
	tree.buildIndex();
}

vector< vector<Point4> > DBSCAN::Impl::cluster() {
	vector< vector<size_t> > clusters;

	for (size_t i = 0; i < cloud.pts.size(); i++) {
		//Holds a reference to the pointStatus in the vector,
		//can directly assign things to this variable and it will work
		uint8_t& status = visited[i];

		if (status != UNVISITED) continue;

		//Detect nearest neighbors based on eps value
		vector<size_t> neighborsV = getNeighbors(i);

		if (neighborsV.size() < minPts) {
			//Density not high enough, this is noise (can change later though)
			status = NOISE;
		}
		else {
			//Its a core point, mark it
			status = CLUSTERED;
			vector<size_t> newCluster;
      unordered_set<size_t> neighborsS(neighborsV.begin(), neighborsV.end());
			expandCluster(i, newCluster, neighborsV, neighborsS);
			clusters.push_back(newCluster);
		}
		i++;
	}
	vector< vector<Point4> > result(clusters.size());
	size_t idx = 0;
	//for (auto cluster = clusters.begin(); cluster != clusters.end(); cluster++) {
	for (vector< vector< size_t> >::iterator cluster = clusters.begin(); cluster != clusters.end(); cluster++)
	{
		//result[idx].reserve(cluster->size());
		result[idx] = vector<Point4>(cluster->size());
		size_t idy = 0;
		//for (auto point = cluster->begin(); point!=cluster->end();point++) {
		for (vector<size_t>::iterator point = cluster->begin(); point != cluster->end(); point++)
		{
			Point4 pt = cloud.pts[*point];
			result[idx][idy] = cloud.pts[*point];
			//result[idx].push_back(cloud.pts[*point]);
			idy++;
		}
		idx++;
	}
	return result;
}

/**
 * IMPORTANT: Mutates the neighbors vector, recommend no using it after this
 */
void DBSCAN::Impl::expandCluster(size_t focalPoint, std::vector<size_t>& cluster,
	std::vector<size_t>& neighborsV, std::unordered_set<size_t>& neighborsS) {
	cluster.push_back(focalPoint);
	//auto it = neighbors.begin();
	size_t i = 0;
	while (i < neighborsV.size()) {
		size_t currentPoint = neighborsV[i];
		//Holds a reference to the pointStatus in the vector,
		//can directly assign things to this variable and it will work
		uint8_t& pointStatus = visited[currentPoint];
		if (pointStatus == UNVISITED) {
			vector<size_t> newNeighbors = getNeighbors(currentPoint);
			if (newNeighbors.size() >= minPts) {
				merge(neighborsV, neighborsS, newNeighbors);
			}
			//Otherwise, dont add the new neighbors
		}

		//These points are visited, but might still be flagged as UNVISITED
		if (pointStatus != CLUSTERED) {
		  pointStatus = CLUSTERED;
			cluster.push_back(currentPoint);
		}

		//increment iterator, use this instead of it++ to be generic
		//advance(it,1);
		i++;
	}

}

vector<size_t> DBSCAN::Impl::getNeighbors(size_t point) {
	//pairs of pointindex, L2_Squared distance
	vector< pair<size_t, float> > pairs;
	const Point4 point4 = cloud.pts[point];
	const float query_pt[3] = { point4.x,point4.y,point4.z }; 
	tree.radiusSearch(query_pt, eps, pairs, nanoflann::SearchParams());
	vector<size_t> neighbors(pairs.size());
	for (auto pair : pairs) {
    const Point4 other = cloud.pts[pair.first];
    float dw = point4.w - other.w;
    if ((pair.second + dw*dw) <= eps) neighbors.push_back(pair.first);
	}
	// cout << neighbors.size() << endl;
	return neighbors;
}

DBSCAN::DBSCAN(const vector<Point4>& points, float epsilon, size_t minPts) :
  impl(new Impl(points, epsilon, minPts)) {}

DBSCAN::~DBSCAN() = default;

std::vector< std::vector<Point4> > DBSCAN::cluster() {
  return impl->cluster();
}