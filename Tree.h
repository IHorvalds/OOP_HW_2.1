#pragma once
#include <vector>

template <typename T>
class Tree
{
protected:
	int m_nr_noduri;

public:
	virtual ~Tree() = default;
	virtual int GetTreeHeight() = 0;
	virtual std::vector<T> GetNodes() = 0;
};

