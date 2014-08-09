//
//  BST.h
//  Algoritmen
//
//  Created by Jonas Anseeuw on 15/08/13.
//  Copyright (c) 2013 Jonas Anseeuw. All rights reserved.
//

#include <iostream>

// -------------------------------------------------------------------
// ---------------------------- interface ----------------------------
// -------------------------------------------------------------------

// Tree

template <class T>
class Node;

template <class T>
class Tree{
public:
	Tree();
	~Tree();
	void insert(const T &d);
	T& search(const T&d);
	void remove(const T&d);
	T& min();
	T& max();
	void inorder(std::ostream &os);
	void levelorder(std::ostream &os);
	void printRange(std::ostream &os, int a, int b);
private:
	Node<T>* k; // Empty tree: nullpointer
	T nullItem;
	Node<T>** searchR(const T&d);
	Node<T>** searchNR(const T &d);
	Node<T>** minR();
	Node<T>** minNR();
	Node<T>** maxR();
	Node<T>** maxNR();
};

// Node

template <class T>
class Node{
	friend class Tree<T>;
public:
	Node(const T &d = T());
	~Node();
private:
	T data;
	Tree<T> left, right;
	void show(std::ostream &os);
};

// -------------------------------------------------------------------
// -------------------------- implementation -------------------------
// -------------------------------------------------------------------

// Tree

template<class T>
Tree<T>::Tree(){
	k = 0;
}

template<class T>
Tree<T>::~Tree(){
	//delete k;
}

template<class T>
void Tree<T>::insert(const T &d){
	Node<T>** position = searchR(d);
	if((*position)==0)
		(*position) = new Node<T>(d);
}

template<class T>
T& Tree<T>::search(const T&d){
	Tree<T>* position = searchR(d);
	if(position->k != 0){
		return position->k->data;
	}else{
		return nullItem;
	}
}

template<class T>
void Tree<T>::remove(const T&d){
	Node<T>** del = searchR(d);
	if((*del)->left.k == 0 && (*del)->right.k == 0){
		delete *del;
		*del = 0;
	}else if((*del)->left.k == 0 || (*del)->right.k == 0){
		Node<T>* temp = (*del);
		if((*del)->left.k == 0){
			*del = (*del)->right.k;
			temp->right.k = 0;
		}else if((*del)->right.k == 0){
			*del = (*del)->left.k;
			temp->left.k = 0;
		}
		delete temp;
	}else{
		Node<T>* temp = (*del);
		Node<T>** min = temp->right.minR();
		Node<T>** h = &((*min)->right.k);
		while((*h)!=0){
			h = &((*h)->right.k);
		}
		*h = temp->right.k;
		(*min)->left.k = temp->left.k;
		(*del) = (*min);
		(*min) = 0;
		temp->left.k = 0;
		temp->right.k = 0;
		delete temp;
	}
}

template<class T>
T& Tree<T>::min(){
	Node<T>** pos = minR();
	if(*pos != 0){
		return (*pos)->data;
	}else{
		return nullItem;
	}
}

template<class T>
T& Tree<T>::max(){
	Node<T>** pos = maxR();
	if(*pos != 0){
		return (*pos)->data;
	}else{
		return nullItem;
	}
}

template<class T>
Node<T>** Tree<T>::searchR(const T &d){
	if(k == 0 || k->data == d) return &(this->k);
	if(k->data > d){
		return k->left.searchR(d);
	}else{
		return k->right.searchR(d);
	}
	return 0;
}

template<class T>
Node<T>** Tree<T>::searchNR(const T &d){
	Node<T>** start = &(this->k);
	while((*start)!=0 && (*start)->data != d){
		if((*start)->data > d)
			start = &((*start)->left.k);
		else
			start = &((*start)->right.k);
	}
	return start;
}

template<class T>
Node<T>** Tree<T>::minR(){
	if(k->left.k ==  0){
		return &(this->k);
	}else{
		return k->left.minR();
	}
}

template<class T>
Node<T>** Tree<T>::minNR(){
	Node<T>** start = &(this->k);
	while((*start)->left.k != 0){
		start = &(start->k->left);
	}
	return start;
}

template<class T>
Node<T>** Tree<T>::maxR(){
	if(k->right.k ==  0){
		return &(this->k);
	}else{
		return k->right.maxR();
	}
}

template<class T>
Node<T>** Tree<T>::maxNR(){
	Node<T>** start = &(this->k);
	while((*start)->right.k != 0){
		start = &(start->k->right);
	}
	return start;
}

template<class T>
void Tree<T>::inorder(std::ostream &os){
	if(k!=0){
		k->left.inorder(os);
		k->show(os);
		k->right.inorder(os);
	}
}

template<class T>
void Tree<T>::levelorder(std::ostream &os){
	std::queue<Node<T>> q;
	if(k != 0){
		q.push(*k);
		while(!q.empty()){
			Node<T> n = q.front();
			n.show(os);
			if(n.left.k != 0) q.push(*(n.left.k));
			if(n.right.k != 0) q.push(*(n.right.k));
			q.pop();
		}
	}
}

template<class T>
void Tree<T>::printRange(std::ostream &os, int a, int b){
	if(k == 0) return;
	if(k->data >= a && k->data < b){
		k->show(os);
		k->left.printRange(os, a, b);
		k->right.printRange(os, a, b);
	}else if(k->data < a){
		k->right.printRange(os, a, b);
	}else if(k->data >= b){
		k->left.printRange(os, a, b);
	}
}

// Node

template<class T>
Node<T>::Node(const T &d){
	data = d;
}

template<class T>
Node<T>::~Node(){
}

template<class T>
void Node<T>::show(std::ostream &os){
	os<<data<<" ";
}
