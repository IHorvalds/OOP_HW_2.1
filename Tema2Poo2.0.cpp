#include "Binary_Tree.cpp"
//#include "Any_Tree.cpp"
#include <iostream>
#include <fstream>

template <typename T = int>
struct ExceptionTests // Simulates the interface of Node, but is not convertible.
{
	ExceptionTests** leg = { NULL };
	T AddChild(int i, int j, int k) { return T(); };
	std::vector<ExceptionTests> GetChildren() { return std::vector<ExceptionTests>(); };

};

int main() {
	std::cout << "Fml...\n";

	std::ifstream in("Text.txt");

	std::cout << "1. Some ordinary tree\n\n";

	Any_Tree<Node> a_t;

	in >> a_t;

	std::cout << a_t << "\n";
	std::cout << a_t.GetNodeCount() << ' ' << a_t.GetTreeHeight() << "\n";
	
	for (auto& t : a_t.GetNodes()) {
		std::cout << t << " ";
	}
	std::cout << "\n\n";

	in.close();


	std::ifstream in2("Text.txt");
	std::cout << "2. Some binary tree\n\n";

	Binary_Tree<Node> b_t;

	in2 >> b_t;

	std::cout << b_t << "\n";
	std::cout << b_t.GetNodeCount() << " " << b_t.GetTreeHeight() << "\n";

	std::cout << "\n\n\n3. Exception example\n\n";

	try {
		Any_Tree<ExceptionTests<int>> will_fail;
	} catch (StrangeTypeException ste) {
		std::cout << ste.what() << "\n";
	}

	std::cin.get();
}