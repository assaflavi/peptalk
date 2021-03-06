// Include file for KDTree class

#ifndef __R3KDTREE__H__
#define __R3KDTREE__H__



// Node declaration

template <class PtrType>
class R3KdtreeNode;



// Class declaration

template <class PtrType>
class R3Kdtree {
public:
  // Constructor/destructors
  R3Kdtree(const R3Box& bbox, int position_offset = 0);
  R3Kdtree(const RNArray<PtrType>& points, int position_offset = 0);
  R3Kdtree(const RNArray<PtrType>& points, R3Point (*position_callback)(PtrType, void *), void *data);
  ~R3Kdtree(void);

  // Property functions
  const R3Box& BBox(void) const;
  int NNodes(void) const;

  // Search for closest to a point
  PtrType FindClosest(PtrType point, RNLength min_distance = 0, RNLength max_distance = RN_INFINITY, RNLength *closest_distance = NULL) const;
  PtrType FindClosest(const R3Point& position, RNLength min_distance = 0, RNLength max_distance = RN_INFINITY, RNLength *closest_distance = NULL) const;

  // Search for all within some distance to a point
  int FindAll(PtrType point, RNLength min_distance, RNLength max_distance, RNArray<PtrType>& points) const;
  int FindAll(const R3Point& position, RNLength min_distance, RNLength max_distance, RNArray<PtrType>& points) const;

public:
  // Internal search functions
  void FindClosest(R3KdtreeNode<PtrType> *node, const R3Box& node_box, const R3Point& position, 
    RNLength min_distance_squared, RNLength max_distance_squared, 
    PtrType& closest_point, RNLength& closest_distance_squared) const;
  void FindAll(R3KdtreeNode<PtrType> *node, const R3Box& node_box, const R3Point& position, 
    RNLength min_distance_squared, RNLength max_distance_squared, RNArray<PtrType>& points) const;

  // Internal manipulation functions
  void InsertPoints(R3KdtreeNode<PtrType> *node, const R3Box& node_box, PtrType *points, int npoints);
  int PartitionPoints(PtrType *points, int npoints, RNDimension dim, int imin, int imax);

  // Internal visualization functions
  void Outline(R3KdtreeNode<PtrType> *node, const R3Box& bbox) const;
  void Outline(void) const;

  // Internal debugging functions
  void PrintDebugInfo(void) const;
  int PrintBalance(R3KdtreeNode<PtrType> *node, int depth) const;

  // Internal point extraction function
  const R3Point Position(PtrType point) const { 
    if (position_offset >= 0) return *((R3Point *) ((unsigned char *) point + position_offset)); 
    else if (position_callback) return (*position_callback)(point, position_callback_data);
    else { fprintf(stderr, "Invalid position callback\n"); abort(); return R3null_point; }
  } ;

public:
  // Internal data
  R3Box bbox;
  int position_offset;
  R3Point (*position_callback)(PtrType, void *);
  void *position_callback_data;
  R3KdtreeNode<PtrType> *root;
  int nnodes;
};



// Include templated definitions

#include "R3Kdtree.C"


#endif
