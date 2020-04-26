#pragma once
#include "Tree.h"
#include "Node.h"
#include <istream>
#include <ostream>

template <typename T = Node>
class Any_Tree : protected Tree<T>
{
private:
	T* p_root;

public:
	// initializers
	Any_Tree();
	Any_Tree(T* t_r);
	Any_Tree(Any_Tree& t);
	Any_Tree& operator= (const Any_Tree& rhs);
	virtual ~Any_Tree();

	virtual void AddNode(int val, unsigned int max_siblings = 3);
	virtual T* GetRoot();
	virtual int SetNodeCount(size_t c = 1);
	virtual int GetNodeCount();
	virtual int GetTreeHeight() override ;
	virtual std::vector<T> GetNodes() override;

	template <typename T = Node>
	friend std::istream& operator>>(std::istream& input, Any_Tree<T>& t);
	template <typename T = Node>
	friend std::ostream& operator<<(std::ostream& output, const Any_Tree<T>& t);
};

