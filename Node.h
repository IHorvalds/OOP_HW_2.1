#pragma once
#include <istream>
#include <ostream>
#include <vector>

class Node
{
private:
	int m_info;
	int m_nr_copii;
	Node* leg[10] = { NULL }; // first element points to left-most child, the other 9 to siblings.

public:
	Node();
	Node(int val);
	Node(Node& n);
	Node(const Node& n);
	Node& operator= (const Node& n);
	~Node();

	int GetInfo();
	void AddChild(int new_val, unsigned short max_siblings = 9, unsigned int level = -1); // -1 is actually the max value of u int
	Node* GetFirstChild();
	std::vector<Node> GetSiblings();
	std::vector<Node> GetChildren();
	Node* CopyChildren();
	void DeleteChildren();
	void inorder(std::ostream& output);
	void preorder(std::ostream& output);
	void postorder(std::ostream& output);

	void bfs(std::ostream& output);

	friend std::ostream& operator<<(std::ostream& output, const Node& n);
	friend std::istream& operator>>(std::istream& input, Node& n);

	template <typename U>
	friend class Any_Tree;
};
