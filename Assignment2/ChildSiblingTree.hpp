#ifndef CHILD_SIBLING_TREE_HPP
#define CHILD_SIBLING_TREE_HPP

#include <iostream>

template<typename Comparable>
class ChildSiblingTree
{

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform a pre-order traversal of the tree and print the elements as they're 
	///          visited.</summary>
	///
	///<param name="out">[optional] The stream to which to print. Defaults to std::cout.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void preorderPrint(std::ostream &out = std::cout) const
	{
		preorderPrint(_root);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform an in-order traversal of the tree and print the elements as they're
	///          visited.</summary>
	///
	///<param name="out">[optional] The stream to which to print. Defaults to std::cout.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void inorderPrint(std::ostream &out = std::cout) const
	{
		inorderPrint(_root);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform a post-order traversal of the tree and print the elements as they're
	///          visited.</summary>
	///
	///<param name="out">[optional] The stream to which to print. Defaults to std::cout.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void postorderPrint(std::ostream &out = std::cout) const
	{
		postorderPrint(_root);
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
	///<summary> Perform a pre-order traversal of the tree and print the elements as they're 
	///          visited.</summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void preorderPrint(ChildSibNode* start, std::ostream & out) const
	{
		if (nullptr == start)
			return;
		
		// Data, left, right
		out << start->element;
		preorderPrint(start->child, out);
		preorderPrint(start->sib, out);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform an in-order traversal of the tree and print the elements as they're
	///          visited.</summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void inorderPrint(ChildSibNode* start, std::ostream & out) const
	{
		if (nullptr == start)
			return;

		// Left, data, right
		inorderPrint(start->child, out);
		out << start->element;
		inorderPrint(start->sib, out);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///<summary> Perform a post-order traversal of the tree and print the elements as they're
	///          visited.</summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void postorderPrint(ChildSibNode* start, std::ostream & out) const
	{
		if (nullptr == start)
			return;

		// Left, right, data
		postorderPrint(start->child, out);
		postorderPrint(start->sib, out);
		out << start->element;
	}
};

#endif // #ifndef CHILD_SIBLING_TREE_HPP