#ifndef _BVHTREE_H
#define _BVHTREE_H

#include <assert.h>
#include <vector>
#include "../vector3.h"
#include "../Aabb.h"
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)>(b) ? (a) : (b))

#define MAX_SPLITPOS_RETRIES 15

struct BVHNode {
	Aabb aabb;
	
	/* if triIndicesStart == 0 then not leaf,
	 * kids[] valid */
	int numTris;
	int *triIndicesStart;
	
	BVHNode *kids[2];

	BVHNode() {
		kids[0] = 0;
		triIndicesStart = 0;
	}
	bool IsLeaf() const {
		return triIndicesStart != 0;
	}
};

class BVHTree {
public:
	typedef int objPtr_t;
	BVHTree(int numObjs, const objPtr_t *objPtrs, const Aabb *objAabbs);
	~BVHTree() {
		delete [] m_objPtrAlloc;
		delete [] m_bvhNodes;
	}
	BVHNode *GetRoot() { return m_root; }
private:
	void BuildNode(BVHNode *node,
			const objPtr_t *objPtrs,
			const Aabb *objAabbs,
			std::vector<objPtr_t> &activeObjIdxs);
	void MakeLeaf(BVHNode *node, const objPtr_t *objPtrs, std::vector<objPtr_t> &objs);
	BVHNode *AllocNode() {
		assert(m_nodeAllocPos < m_nodeAllocMax);
		return &m_bvhNodes[m_nodeAllocPos++];
	}
	BVHNode *m_root;
	objPtr_t *m_objPtrAlloc;
	int m_objPtrAllocPos;
	int m_objPtrAllocMax;

	BVHNode *m_bvhNodes;
	int m_nodeAllocPos;
	int m_nodeAllocMax;
};


#endif /* _BVHTREE_H */