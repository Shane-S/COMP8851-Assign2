#ifndef LAZY_BINARY_SEARCH_TREE_H
#define LAZY_BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;

template <typename Comparable>
class LazyBinarySearchTree
{
public:
	LazyBinarySearchTree() : root{ nullptr }
	{
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Copy constructor.</summary>
    ///
    ///<param name="rhs"> The source object from which to create a copy.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	LazyBinarySearchTree(const LazyBinarySearchTree & rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Move constructor.</summary>
    ///
    ///<param name="rhs"> [in,out] The source object from which to create a copy.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	LazyBinarySearchTree(LazyBinarySearchTree && rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Destructor.</summary>
    ///
    ///<remarks> Shane, 2/19/2016.</remarks>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	~LazyBinarySearchTree()
	{
		makeEmpty();
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Assignment operator.</summary>
    ///
    ///<param name="rhs"> The source object (passed by value; uses appropriate copy constructor and
    ///                   does copy-and-swap idiom).</param>
    ///
    ///<returns> A deep copy of this object.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	LazyBinarySearchTree & operator=(LazyBinarySearchTree rhs)
	{
		std::swap(*this, rhs);
		return *this;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary>Find the smallest item in the tree.</summary>
    ///
    ///<exception cref="UnderflowException">Thrown when the tree is empty.</exception>
    ///
    ///<returns>The minimum element in the tree.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	const Comparable & findMin() const
	{
        if (isEmpty())
			throw UnderflowException{};
		return findMin(root)->element;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary>Finds the largest item in the tree.</summary>
    ///
    ///<exception cref="UnderflowException">Thrown when the tree is empty.</exception>
    ///
    ///<returns> The maximum element in the tree.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	const Comparable & findMax() const
	{
		if (isEmpty())
			throw UnderflowException{};
		return findMax(root)->element;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Query if this tree contains the given object.</summary>
    ///
    ///<param name="x"> The object for which to search.</param>
    ///
    ///<returns> true if the object is in this tree, false if not.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Determine whether the tree is logically empty.</summary>
    ///
    ///<returns> true if empty, false if not.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	bool isEmpty() const
	{
		return root == nullptr;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Print the contents of the tree.</summary>
    ///
    ///<param name="out"> [in,out] (Optional) The output stream to which to print.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void printTree(ostream & out = cout) const
	{
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Empty the tree.</summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void makeEmpty()
	{
		makeEmpty(root);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Inserts x into the tree; duplicates are ignored.</summary>
    /// 
    ///<param name="x">The Comparable object to insert.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void insert(const Comparable & x)
	{
		insert(x, root);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Inserts x into the tree; duplicates are ignored.</summary>
    /// 
    ///<param name="x">The Comparable object to insert.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void insert(Comparable && x)
	{
		insert(std::move(x), root);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Removes x from the tree (no effect if x isn't found).</summary>
    ///
    ///<param name="x"> The Comparable object to find and remove.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void remove(const Comparable & x)
	{
		remove(x, root);
	}

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

        bool deleted;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ theElement }, left{ lt }, right{ rt }, deleted{ false } { }

		BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
			: element{ std::move(theElement) }, left{ lt }, right{ rt }, deleted{ false } { }
	};

	BinaryNode *root;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Inserts an object into the given sub-tree and sets the new root if necessary.</summary>
    ///
    ///<param name="x"> The item to insert.</param>
    ///<param name="t"> The root of the subtree into which to insert.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void insert(const Comparable & x, BinaryNode * & t)
	{
		if (t == nullptr)
			t = new BinaryNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
        else if (t->deleted)
            t->deleted = false;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Inserts an object into the given sub-tree and sets the new root if necessary.</summary>
    /// 
    ///<remarks> Shane, 2/20/2016.</remarks>
    ///
    ///<param name="x"> The item to insert.</param>
    ///<param name="t"> The root of the subtree into which to insert.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void insert(Comparable && x, BinaryNode * & t)
	{
		if (t == nullptr)
			t = new BinaryNode{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);
        else if (t->deleted)
            t->deleted = false;
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Removes the given object from the specified sub-tree.</summary>
    /// 
    ///<param name="x"> The item to remove.</param>
    ///<param name="t"> The root node of the sub-tree from which to remove.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void remove(const Comparable & x, BinaryNode * & t)
	{
		if (t == nullptr)
			return;   // Item not found; do nothing
		if (x < t->element)
			remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else
            t->deleted = true; // Mark element as deleted; shouldn't need to do any swapping as with non-lazy deletion
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Searches for the smallest item in the given sub-tree.</summary>
    ///
    ///<param name="t"> The root node of the sub-tree to search.</param>
    ///
    ///<returns> The node containing the smallest item in the given sub-tree.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	BinaryNode * findMin(const BinaryNode *t) const
	{
        if (nullptr == t)
            return nullptr;

        if (!t->left && !t->right)
        {
            if (t->deleted)
                return nullptr;
            return t;
        }

        BinaryNode* here = nullptr;
        BinaryNode* minLeft = nullptr;
        BinaryNode* minRight = nullptr;

        if (!t->deleted) here = t;
        if (t->left) minLeft = findMin(t->left);
        if (!minLeft && t->right) minRight = findMin(t->right);

        return minLeft ? minLeft : (here ? here : minRight);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Searches for the largest item in the given sub-tree.</summary>
    ///
    ///<param name="t"> The root node of the sub-tree to search.</param>
    ///
    ///<returns> The node containing the largest item in the given sub-tree.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	BinaryNode * findMax(const BinaryNode *t) const
	{
        if (nullptr == t)
            return nullptr;

        if (!t->left && !t->right)
        {
            if (t->deleted)
                return nullptr;
            return t;
        }

        BinaryNode* here = nullptr;
        BinaryNode* maxLeft = nullptr;
        BinaryNode* maxRight = nullptr;

        if (!t->deleted) here = t;
        if (t->right) maxRight = findMax(t->right);
        if (!maxRight && t->left) maxLeft = findMax(t->left);

        return maxRight ? maxRight : (here ? here : maxLeft);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Query if this tree contains the given item.</summary>
    ///
    ///<param name="x"> The item for which to search.</param>
    ///<param name="t"> [in,out] The root node of the tree to search.</param>
    ///
    ///<returns> true if the object is in this sub-tree, false if not.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	bool contains(const Comparable & x, const BinaryNode *t) const
	{
        if (t == nullptr)
            return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return t->deleted;    // Elements match, but the node might be deleted
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Empties the given sub-tree (by actually deleting nodes).</summary>
    ///
    ///<param name="t"> The root node of the tree to empty.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void makeEmpty(BinaryNode * t)
	{
        if (nullptr != t)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Prints the given sub-tree in sorted order.</summary>
    ///
    ///<param name="t">   The root node of the sub-tree to print.</param>
    ///<param name="out"> The output stream to which to print.</param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	void printTree(const BinaryNode *t, ostream & out) const
	{
		if (nullptr != t)
		{
			printTree(t->left, out);
			if(!t->deleted) out << t->element << endl;
			printTree(t->right, out);
		}
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///<summary> Makes a deep copy of this object.</summary>
    ///
    ///<param name="t"> The root of the sub-tree to clone.</param>
    ///
    ///<returns> nullptr if the given root node is nullptr or a memory allocation fails, or a new
    ///          BinaryNode on success.</returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	BinaryNode * clone(BinaryNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
	}
};

#endif
