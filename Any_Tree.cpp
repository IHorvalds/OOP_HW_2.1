#include "Any_Tree.h"
#include <queue>
#include <type_traits>
#include "StrangeTypeException.h"

template<typename T>
Any_Tree<T>::Any_Tree() {
	if (std::is_base_of<Node, T>::value) {
		p_root = new T;
		this->m_nr_noduri = 1;
	} else {
		const char* wrong_type = typeid(T).name();
		throw StrangeTypeException(wrong_type);
	}
}

template<typename T>
Any_Tree<T>::Any_Tree(T* t_r) {
	p_root = t_r;
	this->m_nr_noduri = 1;
}

template<typename T>
Any_Tree<T>::Any_Tree(Any_Tree& t) {

	p_root = T(t.p_root);
	p_root->leg[0] = t.p_root->CopyChildren();

	this->m_nr_noduri = 1 + p_root->GetChildren().size();
}

template<typename T>
Any_Tree<T>& Any_Tree<T>::operator=(const Any_Tree& rhs) {
	// TODO: insert return statement here

	this->p_root->DeleteChildren();
	this->p_root = T(rhs.p_root);
	this->p_root->leg[0] = rhs.p_root->CopyChildren();

	this->m_nr_noduri = 1 + p_root->GetChildren().size();
}

template<typename T>
Any_Tree<T>::~Any_Tree() {
	delete this->p_root;
	this->p_root = NULL;
}

template<typename T>
void Any_Tree<T>::AddNode(int val, unsigned int max_siblings) {
	unsigned int _NodeCount = this->SetNodeCount();
	this->GetRoot()->AddChild(val, max_siblings, -1);
}

template<typename T>
T* Any_Tree<T>::GetRoot() {
	return p_root;
}

template<typename T>
int Any_Tree<T>::SetNodeCount(size_t c) {
	this->m_nr_noduri += c;
	return this->m_nr_noduri;
}

template<typename T>
int Any_Tree<T>::GetNodeCount() {
	return this->m_nr_noduri;
}

template<typename T>
int Any_Tree<T>::GetTreeHeight() {
	if (this->p_root->leg[0]) {
		T* n = this->p_root->leg[0];
		int r = 2; // p_root is level 1
		while (n->leg[0]) {
			n = n->leg[0];
			r++;
		}
		return r;
	}
	return 1;
}

template<typename T>
std::vector<T> Any_Tree<T>::GetNodes() {
	std::vector<T> l;
	std::vector<T> c = this->p_root->GetChildren();
	l.push_back(*this->p_root);
	l.insert(l.end(), c.begin(), c.end());
	return l;
}

template<typename T>
std::istream& operator>>(std::istream& input, Any_Tree<T>& t) {
	t.p_root->DeleteChildren();
	input >> *t.p_root;

	int i;
	while (!input.eof()) {
		input >> i;
		t.AddNode(i, 4);
	}

	return input;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const Any_Tree<T>& t) {

	t.p_root->bfs(output);


	return output;
}
