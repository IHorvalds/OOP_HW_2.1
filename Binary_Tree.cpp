#include "Binary_Tree.h"
#include <queue>

template<typename T>
Binary_Tree<T>::Binary_Tree() {}

template<typename T>
Binary_Tree<T>::Binary_Tree(T* t_r) : Any_Tree{ t_r } {}

template<typename T>
Binary_Tree<T>::Binary_Tree(Binary_Tree& t) {
	
}

template<typename T>
Binary_Tree<T>& Binary_Tree<T>::operator=(const Binary_Tree& rhs) {
	this->GetRoot() = T(rhs.GetRoot());
	this->GetRoot()->GetFirstChild() = rhs.GetRoot()->CopyChildren();

	this->m_nr_noduri = 1 + this->GetRoot()->GetChildren().size();
}

template<typename T>
Binary_Tree<T>::~Binary_Tree() {}

template<typename T>
void Binary_Tree<T>::AddNode(int val, unsigned int max_siblings) {
	unsigned int _NodeCount = this->SetNodeCount();
	this->GetRoot()->AddChild(val, 2, -1);
}

template<typename T>
std::istream& operator>>(std::istream& input, Binary_Tree<T>& t) {
	t.GetRoot()->DeleteChildren();
	input >> *t.GetRoot();

	int i;
	while (!input.eof()) {
		input >> i;
		t.AddNode(i);
	}

	return input;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, Binary_Tree<T>& t) {

	output << "BFS: \n";

	t.GetRoot()->bfs(output);

	output << "\n\nDFS:\n";
	output << "1. Inorder\n\n";

	t.GetRoot()->inorder(output);


	output << "\n\n2.. Preorder\n\n";

	t.GetRoot()->preorder(output);

	output << "\n\n3. Postorder\n\n";

	t.GetRoot()->postorder(output);

	return output;
}