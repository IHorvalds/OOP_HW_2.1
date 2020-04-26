#pragma once
#include "Any_Tree.cpp"

template <typename T = Node>
class Binary_Tree : public Any_Tree<T>
{
public:
	// inits
	Binary_Tree();
	Binary_Tree(T* t_r);
	Binary_Tree(Binary_Tree& t);
	Binary_Tree& operator= (const Binary_Tree& rhs);
	virtual ~Binary_Tree();

	void AddNode(int val, unsigned int max_siblings = 0) override;

	template <typename T = Node>
	friend std::istream& operator>>(std::istream& input, Binary_Tree<T>& t);
	template <typename T = Node>
	friend std::ostream& operator<<(std::ostream& output, Binary_Tree<T>& t);

};
