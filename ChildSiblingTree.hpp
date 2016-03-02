#ifndef CHILD_SIBLING_TREE_HPP
#define CHILD_SIBLING_TREE_HPP

#include <iostream>

template<typename Comparable>
class ChildSiblingTree
{

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform a traversal of the tree and print the elements as they're visited.</summary>
	///
	///<param name="out">[optional] The stream to which to print. Defaults to std::cout.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void print(std::ostream &out = std::cout) const
	{
		print(_root, out);
	}

private:
	struct ChildSibNode
	{
		Comparable element;
		ChildSibNode<Comparable> * child;
		ChildSibNode<Comparable> * sib;
	};

	ChildSibNode* _root;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform traversal of the tree and print the elements as they're visited.</summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void print(ChildSibNode* start, std::ostream & out) const
	{
		if (nullptr == start)
			return;

		out << start->element;
		print(start->sib, out);
		print(start->child, out);
	}
};

#endif // #ifndef CHILD_SIBLING_TREE_HPP