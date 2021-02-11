/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:38:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/11 16:58:59 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>

#include "../templates/stl_like.hpp"
#include "../avl_binary_tree_lib/binary_tree.hpp"

#include "../iterators/map_iterator.hpp"

namespace ft
{
	
	template < class Key,                                  		 	// map::key_type
			class T,                           	       			    // map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
	> class map
	{
		private:

			struct Node
			{
				ft::pair<const Key,T>	content;
				Node*					parent;
				Node*					left;
				Node*					right;
			};

		public:

			/* ------------------------------------------------------------- */
			/* -------------------------- ALIASES -------------------------- */

			typedef Key												key_type;
			typedef Compare											key_compare;
			typedef	Alloc											allocator_type;
			typedef	T												mapped_type;
			
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef	long int										difference_type;
			typedef	size_t											size_type;

			typedef	T&												reference;
			typedef	const T&										const_reference;
			typedef	T*												pointer;
			typedef	const T*										const_pointer;
			
			typedef typename ft::map_iterator<Key, T, Compare, Node, false>		iterator;
			typedef typename ft::map_iterator<Key, T, Compare, Node, true>		const_iterator;

			// typedef typename ft::rev_map_iterator<T, Node, false>	reverse_iterator;
			// typedef typename ft::rev_map_iterator<T, Node, true>	const_reverse_iterator;

			/* ------------------------------------------------------------- */
			/* ------------------------ COPLIEN FORM ----------------------- */

			
			// empty (1)	
			explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) :
				_size(0), _allocPair(alloc), _comp(comp)
			{
				_lastElem = createNode(ft::pair<const key_type, mapped_type>());
				_root = _lastElem;
			}

// range (2)	
// template <class InputIterator>
//   map (InputIterator first, InputIterator last,
//        const key_compare& comp = key_compare(),
//        const allocator_type& alloc = allocator_type());
// copy (3)	
// map (const map& x);

// ~map();
// copy (1)	
//  map& operator= (const map& x);



			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			iterator begin()	{ return iterator(_lastElem->right, _lastElem); }
// const_iterator begin() const;
			iterator end()		{ return iterator(_lastElem, _lastElem); }
// const_iterator end() const;
// reverse_iterator rbegin();
// const_reverse_iterator rbegin() const;
//  reverse_iterator rend();
// const_reverse_iterator rend() const;

			/* ------------------------------------------------------------- */
			/* -------------------------- CAPACITY ------------------------- */

			/**
			*	@return		True if the list' size is equal to 0.
			*/
			bool empty() const				{ return _size == 0; }

			/**
			*	@return		The size of the list.
			*/
			size_type size() const			{ return _size; }
			
			/**
			*	@return		The max possible size to be allocated.
			*/
			size_type		max_size() const
			{
				if (sizeof(value_type) == 1)
					return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
				return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
			}


			/* ------------------------------------------------------------- */
			/* ---------------------- ELEMENTS ACCESS ---------------------- */	
			// mapped_type& operator[] (const key_type& k);

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */
			// single element (1)	
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				// Searches in the tree if val's key is already present and returns 
				// an iterator to the key inside the tree if it's the case
				Node* elemIsPresent = 0;
				if ((elemIsPresent = searchNode(_root, val.first)))
					return ft::pair<iterator, bool>(elemIsPresent, false);

				// Inserts the pair in the tree and returns an iterator to its position
				return ft::pair<iterator, bool>(insertNode(_root, val), true);
			}
			
			// with hint (2)	
			// iterator insert (iterator position, const value_type& val);
			// range (3)	
			// template <class InputIterator>
			// void insert (InputIterator first, InputIterator last);

			// (1)	
			// 	void erase (iterator position);
			// (2)	
			// size_type erase (const key_type& k);
			// (3)	
			// 	void erase (iterator first, iterator last);

			// 	void swap (map& x);
			// void clear();


			/* ------------------------------------------------------------- */
			/* ------------------------- OBSERVERS ------------------------- */
			
			// key_compare key_comp() const;
			// value_compare value_comp() const;
			
			
			/* ------------------------------------------------------------- */
			/* ------------------------ OPERATIONS ------------------------- */

			// iterator find (const key_type& k);
			// const_iterator find (const key_type& k) const;
			// size_type count (const key_type& k) const;
			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;

			//  iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;

			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// pair<iterator,iterator>             equal_range (const key_type& k);


		private:

			Node*					_root;			// Pointer to the first element of the tree (root)
			Node*					_lastElem;		// Pointer to the last elem of the tree
			size_type				_size;			// Number of T values inside the list
			Alloc					_allocPair;		// Copy of allocator_type object
			Compare					_comp;			// Copy of comp key_compare predicate
			std::allocator<Node>	_allocNode;		// Node's allocator


			/* ------------------------------------------------------------- */
			/* ------------------ AVL BINARY SEARCH TREE ------------------- */

			/**
			*	Creates a new node and assign pair. left and right node ptr are NULL.
			*
			*	@param pair		The content (as a pair) of the created node.
			*	@return			The newly created node.
			*/
			Node* createNode(const value_type& pair)
			{
				Node* newNode = _allocNode.allocate(1);

				_allocPair.construct(&newNode->content, pair);
				newNode->parent = 0;
				newNode->left = 0;
				newNode->right = 0;

				return newNode;
			}

			/**
			*	Searches key in the tree and returns the element if it finds key.
			*
			*	@param root		Will start to look in the tree for the element from this node.
			*	@param key		The key to search.
			*	@param return	The element containing the key in the tree. NULL if no match occured for key.
			*/
			Node* searchNode(Node* root, int key)
			{
				// We reached a leaf
				if (!root)
					return 0;
				
				if (root->content.first == key)
					return root;
				
				// Recursive loop until we find key
				if (root->content.first > key && root->left && root->left != _lastElem)
					return searchNode(root->left, key);
				else if (root->content.first < key && root->right && root->right != _lastElem)
					return searchNode(root->right, key);

				// If we reach this step in the first searchNode func that was called
				// with root (first node of the tree), then element is missing.
				return 0;
			}

			/**
			*	Searches for the element with the highest key in the tree.
			*
			*	@param root		First node of the tree.
			*	@param return	The element containing the highest key in the tree.
			*/
			Node* searchMaxNode(Node *root)
			{
				// Until we meet tree's right extremity and circular link _lastElem
				if (root->right && root->right != _lastElem)
					return searchMaxNode(root->right);
				return root;
			}

			/**
			*	Searches for the element with the lowest key in the tree.
			*
			*	@param root		First node of the tree.
			*	@param return	The element containing the lowest key in the tree.
			*/
			Node* searchMinNode(Node *root)
			{
				// Until we meet tree's left extremity and circular link _lastElem
				if (root->left && root->left != _lastElem)
					return searchMinNode(root->left);
				return root;
			}

			/**
			*	Inserts a pair in the tree or a specific subtree by adding a new element, and 
			*	then equilibrates the AVL tree if necessary. If element is already present, 
			*	does nothing and return NULL.
			*
			*	@param insertPos	The starting node for the insertion in a specific subtree (will start to look for
			*						a place for data from this node). If insertPos is root node, then it's an insertion
			*						in the whole tree.
			*	@param data			The pair to insert in the tree.
			*	@param return		The element inserted in the tree. NULL if the element already exist in the tree. 
			*/
			Node* insertNode(Node* insertPos, const value_type& pair)
			{
				// Case creating first node of the tree
				if (_root == _lastElem)
				{
					_root = createNode(pair);
					
					_root->left = _lastElem;
					_root->right = _lastElem;
					_lastElem->left = _root;
					_lastElem->right = _root;

					return _root;
				}

				// Case key already exist in the tree
				if (insertPos->content.first == pair.first)
					return 0;

				// Recursive loop until we reach a leaf or fake last node (_lastElem)
				if (insertPos->content.first > pair.first && 
						insertPos->left && insertPos->left != _lastElem)
					return insertNode(insertPos->left, pair);
				else if (insertPos->content.first < pair.first && 
						insertPos->right && insertPos->right != _lastElem)
					return insertNode(insertPos->right, pair);

				// If we reach this step, we arrived to a leaf or to the max node / min node 
				// of the tree (they're both linked to _lastElem): inserting new node to his correct position
				Node *newNode = createNode(pair);

				// Case we reached a left or right leaf
				if (insertPos->content.first > newNode->content.first && !insertPos->left)
					insertPos->left = newNode;
				else if (insertPos->content.first < newNode->content.first && !insertPos->right)
					insertPos->right = newNode;

				// Case we reach min node or max node, inserting the node between min / max
				// and lastElem
				else if (insertPos->left && insertPos->content.first > newNode->content.first)
				{
					newNode->left = _lastElem;
					_lastElem->right = newNode;
					insertPos->left = newNode;
				}
				else if (insertPos->right && insertPos->content.first < newNode->content.first)
				{
					newNode->right = _lastElem;
					_lastElem->left = newNode;
					insertPos->right = newNode;
				}
					
				newNode->parent = insertPos;
				++_size;

// A DECOMMENTER
				// // Equilibrating the tree from newNode to root node
				// balanceTheTree(root, newNode);

				return newNode;
			}

			// void unlinkLastElem()
			// {
			// 	_lastElem->parent->right = 0;
			// }

			// void updateLastElem(Node* newNode)
			// {
			// 	// If _root is pointing to _lastElem, means the last node was just deleted 
			// 	// (so the root of the tree), and _lastElem is now the only element in the tree. 
			// 	// It has then no parent, and it's pointing to himself.
			// 	if (_lastElem == _root)
			// 	{
			// 		_lastElem->parent = 0;
			// 		_lastElem->right = _lastElem;
			// 		_lastElem->left = _lastElem;
			// 	}

			// 	// Case 1:	If _lastElem has no parent and _root is pointing to a node,  
			// 	// 			means the tree was empty and his first elem was just added.
			// 	// Case 2:	_lastElem's parent should be the max node in the tree. If newNode got an 
			// 	// 			higher key, means max node has changed and need to update _lastElem position
			// 	else if ((!_lastElem->parent && _root != _lastElem) || 
			// 			_lastElem->parent->content.first < newNode->content.first)
			// 	{
			// 		// std::cout << "on update\n";
			// 		newNode->right = _lastElem;
			// 		_lastElem->parent = newNode->right;
					
			// 		// For being able to copy const values inside the pair
			// 		_allocPair.destroy(&_lastElem->content);
			// 		_allocPair.construct(&_lastElem->content, newNode->content);
			// 	}
			// }

	};
} // namespace ft

#endif