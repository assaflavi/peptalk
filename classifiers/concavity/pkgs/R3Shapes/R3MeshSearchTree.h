// Include file for mesh search tree class



// Node declaration

class R3MeshSearchTreeFace;
class R3MeshSearchTreeNode;



// Class declaration

class R3MeshSearchTree {
public:
  // Constructor/destructors
  R3MeshSearchTree(R3Mesh *mesh);
  ~R3MeshSearchTree(void);

  // Property functions
  const R3Box& BBox(void) const;

  // Insert/delete functions
  void InsertFace(R3MeshFace *face);
  void Empty(void);

  // Find mesh feature closest to a query point
  void FindClosest(const R3Point& query, R3MeshIntersection& closest,
    RNScalar min_distance = 0, RNScalar max_distance = RN_INFINITY,
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *) = NULL, 
    void *compatible_data = NULL);

  // Find mesh feature closest to a query point and normal
  void FindClosest(const R3Point& query, const R3Vector& normal, R3MeshIntersection& closest,
    RNScalar min_distance = 0, RNScalar max_distance = RN_INFINITY, 
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *) = NULL, 
    void *compatible_data = NULL);

  // Find all mesh features with distance from a query point
  void FindAll(const R3Point& query, RNArray<R3MeshIntersection *>& hits,
    RNScalar min_distance = 0, RNScalar max_distance = RN_INFINITY,
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *) = NULL, 
    void *compatible_data = NULL);

  // Find all mesh features with distance from a query point and normal
  void FindAll(const R3Point& query, const R3Vector& normal, RNArray<R3MeshIntersection *>& hits,
    RNScalar min_distance = 0, RNScalar max_distance = RN_INFINITY, 
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *) = NULL, 
    void *compatible_data = NULL);

  // Visualization/debugging functions
  int NNodes(void) const;
  void Outline(void) const;
  void Print(void) const;

public:
  // Internal manipulations functions
  void Empty(R3MeshSearchTreeNode *node);

  // Internal insert functions
  void InsertFace(R3MeshSearchTreeFace *face, R3MeshSearchTreeNode *node, const R3Box& node_box, int depth);

  // Internal closest point search functions
  void FindClosest(const R3Point& query, const R3Vector& normal, R3MeshIntersection& closest, 
    RNScalar min_distance_squared, RNScalar& max_distance_squared, 
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *), void *compatible_data,
    R3MeshSearchTreeNode *node, const R3Box& node_box) const;
  void FindClosest(const R3Point& query, const R3Vector& normal, R3MeshIntersection& closest, 
    RNScalar min_distance_squared, RNScalar& max_distance_squared, 
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *), void *compatible_data,
    R3MeshFace *face) const;

  // Internal all point search functions
  void FindAll(const R3Point& query, const R3Vector& normal, RNArray<R3MeshIntersection *>& hits,
    RNScalar min_distance_squared, RNScalar max_distance_squared, 
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *), void *compatible_data,
    R3MeshSearchTreeNode *node, const R3Box& node_box) const;
  void FindAll(const R3Point& query, const R3Vector& normal, RNArray<R3MeshIntersection *>& hits,
    RNScalar min_distance_squared, RNScalar max_distance_squared, 
    int (*IsCompatible)(const R3Point&, const R3Vector&, R3Mesh *, R3MeshFace *, void *), void *compatible_data,
    R3MeshFace *face) const;

  // Internal visualization and debugging functions
  void Outline(R3MeshSearchTreeNode *node, const R3Box& node_box) const;
  int Print(R3MeshSearchTreeNode *node, int depth) const;

  // Internal utility functions
  RNScalar DistanceSquared(const R3Point& query, const R3Box& box, RNScalar max_distance_squared) const;
  RNScalar DistanceSquared(const R3Point& query, const R3Point& point) const;

public:
  // Internal data
  R3Mesh *mesh;
  R3MeshSearchTreeNode *root;
  int nnodes;
  RNMark mark;
};



