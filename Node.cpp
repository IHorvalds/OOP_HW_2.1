#include "Node.h"
#include <stdlib.h>
#include <queue>

Node::Node() : m_info(INT_MIN), m_nr_copii(0) {}

Node::Node(int val) {
	m_info = val;
	m_nr_copii = 0;
}

Node::Node(Node& n) { // copies only the value. New node's children will be null.
	m_info = n.m_info;
	m_nr_copii = 0;
}

Node::Node(const Node& n) {
	this->m_info = n.m_info;
}

Node& Node::operator=(const Node& n) { // copies only the value. Children remain the same on both nodes.
	this->m_info = n.m_info;
	return *this;
}

Node::~Node() {
	for (int i = 9; i >= 0; i--) {
		if (leg[i]) {
			delete leg[i];
			leg[i] = NULL;
		}
	}
}

//void Node::AddChild(int new_val, unsigned short max_siblings, unsigned int level) {
//	unsigned int _LevelToInsert = (level == -1) ? this->m_nr_copii / max_siblings + 1 : level;
//
//	int i = _LevelToInsert;
//	Node* _Cursor = this;
//	while (_Cursor->leg[0] && i > 0) {
//		_Cursor->m_nr_copii++;
//		_Cursor = _Cursor->leg[0];
//		i--;
//	}
//
//	if (_Cursor->leg[0] == NULL && i > 0) {
//		_Cursor->leg[0] = new Node(new_val);
//		_Cursor->m_nr_copii++;
//		return;
//	}
//
//	i = max_siblings - 1;
//	while (_Cursor->leg[1] && i >= 0) {
//		_Cursor = _Cursor->leg[1];
//		i--;
//	}
//
//	if (!_Cursor->leg[1]) {
//		_Cursor->leg[1] = new Node(new_val);
//
//		Node* _Cursor2 = this;
//		int l2 = _LevelToInsert - 1;
//		while (_Cursor2->leg[0] && l2 > 0) {
//			_Cursor2 = _Cursor2->leg[0];
//			l2--;
//		}
//
//		int _ToLeftMoves = max_siblings - i;
//		while (_Cursor2->leg[1] && _ToLeftMoves > 0) {
//			_Cursor2 = _Cursor2->leg[1];
//			_ToLeftMoves--;
//		}
//
//		if (!_Cursor2->leg[0]) {
//			_Cursor2->leg[0] = _Cursor->leg[1];
//		}
//
//		return;
//	}
//}

void Node::AddChild(int new_val, unsigned short max_siblings, unsigned int level) {
	if (!leg[0]) {
		m_nr_copii++;
		leg[0] = new Node(new_val);
		return;
	} else {
		if ((unsigned int)leg[0]->GetSiblings().size() < max_siblings - 1) { // if it should be a child of the same parent
			leg[0]->leg[leg[0]->GetSiblings().size() + 1] = new Node(new_val);
			m_nr_copii++;
			return;
		} else {

			//get the sibling with the minimum number of children. If all are queal, just get the first one
			unsigned int _MinChildren = (unsigned int)-1;
			Node* p_NodeMinChildren = NULL;
			for (size_t i = 1; i < max_siblings; i++) {
				if (leg[0]->leg[i] && leg[0]->leg[i]->m_nr_copii <= _MinChildren) {
					_MinChildren = leg[0]->leg[i]->m_nr_copii;
					p_NodeMinChildren = leg[0]->leg[i];
				}
			}

			if (leg[0]->m_nr_copii <= _MinChildren) {
				p_NodeMinChildren = leg[0];
			}


			p_NodeMinChildren->AddChild(new_val, max_siblings, level);
			m_nr_copii++;
			return;
		}
	}
}

Node* Node::GetFirstChild() {
	return (leg[0]) ? leg[0] : NULL;
}

std::vector<Node> Node::GetSiblings() {
	std::vector<Node> s;

	Node* _Cursor = this;
	int i = 1;
	while (_Cursor->leg[i] && i < 10) {
		s.push_back(Node(*_Cursor->leg[i]));
		i++;
	}

	return s;
}

std::vector<Node> Node::GetChildren() {
	std::vector<Node> l;
	std::queue<Node*> q;

	q.push(this);

	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();

		l.push_back(Node(*tmp));
		auto siblings = tmp->GetSiblings();
		l.insert(l.end(), siblings.begin(), siblings.end());

		if (tmp->GetFirstChild()) {
			q.push(tmp->GetFirstChild());
		}

		int i = 1;
		while (tmp->leg[i] && tmp->leg[i]->leg[0]) {
			q.push(tmp->leg[i]->leg[0]);
			i++;
		}
	}

	return l;
}

Node* Node::CopyChildren() {

	if (this->leg[0]) {
		Node* new_n = new Node(*this->leg[0]);

		int i = 1;
		while (this->leg[i]) {
			new_n->leg[i] = new Node(*this->leg[i]);
			i++;
		}

		if (this->leg[0]->leg[0]) {
			new_n->leg[0] = this->leg[0]->CopyChildren();
		}

		return new_n;
	}

	return NULL;
	
}

void Node::DeleteChildren() {
	if (leg[0]) {
		delete leg[0];
		leg[0] = NULL;
	}
}

void Node::inorder(std::ostream& output) {
	if (this->leg[0]) {
		this->leg[0]->inorder(output);
	}

	output << *this << " ";

	if (this->leg[0] && this->leg[0]->leg[1]) {
		this->leg[0]->leg[1]->inorder(output);
	}
}

void Node::preorder(std::ostream& output) {

	output << *this << " ";

	if (this->leg[0]) {
		this->leg[0]->preorder(output);
	}

	if (this->leg[0] && this->leg[0]->leg[1]) {
		this->leg[0]->leg[1]->preorder(output);
	}
}

void Node::postorder(std::ostream& output) {

	if (this->leg[0]) {
		this->leg[0]->postorder(output);
	}

	if (this->leg[0] && this->leg[0]->leg[1]) {
		this->leg[0]->leg[1]->postorder(output);
	}

	output << *this << " ";
}

void Node::bfs(std::ostream& output) {

	std::queue<Node*> q;

	q.push(this);

	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();

		output << *tmp << "   ";

		for (auto& n : tmp->GetSiblings()) {
			output << n << " ";
		}

		if (tmp->GetFirstChild()) {
			q.push(tmp->GetFirstChild());
		}

		int i = 1;
		while (tmp->leg[i] && tmp->leg[i]->leg[0]) {
			q.push(tmp->leg[i]->leg[0]);
			i++;
		}
	}

}

int Node::GetInfo() {
	return m_info;
}

std::ostream& operator<<(std::ostream& output, const Node& n) {

	output << n.m_info;

	return output;
}

std::istream& operator>>(std::istream& input, Node& n) {

	input >> n.m_info;
	n.DeleteChildren();

	return input;
}
