#include "stdafx.h"
#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
struct leaf
{
	int key;
	leaf *left;
	leaf *right;
}root, root_avl;

//BASIC 
double in_order(leaf *root);
double pre_order(leaf *root);
double post_order(leaf *root);
void wyswietl(vector<int> array);
void random(int size, vector<int> &array);
void clear(leaf *root, int pom);

void add_leaf(leaf *root, leaf *new_leaf)
{
	if ((*root).key > (*new_leaf).key)
	{
		if ((*root).left == NULL)
			(*root).left = &(*new_leaf);
		else
			add_leaf((*root).left, new_leaf);
	}
	else
	{
		if ((*root).right == NULL)
			(*root).right = &(*new_leaf);
		else
			add_leaf((*root).right, new_leaf);
	}
}
double create_bst(leaf *root, int size, vector<int> array)
{
	for (int i = 1; i < size; i++)
	{
		leaf *new_leaf = new leaf;
		new_leaf->key = array[i];
		new_leaf->left = NULL;
		new_leaf->right = NULL;
		add_leaf(root, new_leaf);
	}
	return 1;
}
double create_avl(leaf *root_avl, int start, int end, vector<int> array)
{
	leaf *new_leaf = new leaf;
	new_leaf->left = NULL;
	new_leaf->right = NULL;
	if (start == end) 
	{
		new_leaf->key = array[start];
		add_leaf(root_avl, new_leaf);
	}
	else
	{
		int center = (start + end) % 2 ? (start + end + 1) / 2 : (start + end) / 2; // w przypadku parzystej zwraca srodek w przypadku nieparzystej polowe+0.5
		new_leaf->key = array[center];
		add_leaf(root_avl, new_leaf);
		if(center-1>=start) create_avl(root_avl, start, center - 1, array);
		if(center+1<=end) create_avl(root_avl, center + 1, end, array);
	}
	return 1;
}
int min_leaf(leaf *root)
{
	return (*root).left == NULL ? (*root).key : min_leaf((*root).left);
}
leaf* return_parent(leaf *root, int index)
{
	leaf *temp, *parent, over;
	over.key = -1;
	temp = root;
	parent = root;
	while (temp->key != index)
	{
		parent = temp;
		if (temp->key < index)
		{
			if (temp->right == NULL)return &over;
			else temp = temp->right;
		}
		else
		{
			if (temp->left == NULL)return &over;
			else temp = temp->left;
		}
	}
	return parent;
}
void remove(leaf *root, int index)
{
	int counter = 0,lcapture=0;
	leaf *parent,*main,*temp;
	parent = main = root;
	if (root->key != index)
	{
		parent = return_parent(root, index);
		if (parent->key == -1)return;
		if (index > parent->key) main = parent->right;
		else main = parent->left;
	}
	if (main->left != NULL)
	{
		counter++;
		lcapture = 1;
	}
	if (main->right != NULL)counter++;

	if (root->key == index && counter == 1)
	{
		if (main->left == NULL)root = main->right;
		else root = main->left;
	}
	else if (root->key == index || counter == 2)
	{
		temp = main;
		main->key = min_leaf(temp->right);
		remove(main->right, main->key);
	}
	else if (counter == 1)
	{
		if (parent->key > index)
		{
			if (lcapture == 1) parent->left = parent->left->left;
			else parent->left = parent->left->right;
		}
		else
		{
			if (lcapture == 1)parent->right = parent->right->left;
			else parent->right = parent->right->right;
		}
		delete main;
	}
	else if (counter == 0)
	{
		if (parent->key > index)parent->left = NULL;
		else parent->right = NULL;
		delete main;
	}
	cout << endl;
}
int main()
{
	srand(time(NULL));
	int size = 100000, index;
	vector<int> array, sort_array;
	random(size, array);
	index = 8;
	sort_array = array;
	sort(sort_array.begin(), sort_array.end());
	//wyswietl(array); wyswietl(sort_array);

	root.key = array[0];
	root.left = NULL;
	root.right = NULL;

	int center = (0 + size) % 2 ? (0 + size + 1) / 2 : (0 + size) / 2;

	root_avl.key = sort_array[center];
	root_avl.left = NULL;
	root_avl.right = NULL;

	create_bst(&root, size, array);

	/*
	create_avl(&root_avl, 0, center-1, sort_array);
	create_avl(&root_avl, center + 1, array.size() - 1, sort_array);

	cout << "PRE:\n";
	pre_order(&root);
	cout << "\nIN:\n";
	in_order(&root);
	cout << "\nPOST:\n";
	post_order(&root);

	cout << "\n\nMIN: " << min_leaf(&root);
	cout << endl;
	cout << "\n\nAVL:\n";
	in_order(&root_avl);

	

	//cout << "\nPodaj wartosc: "; cin >> index;
	//in_order(&root);
	//remove(&root, index);
	//cout << endl;
	//in_order(&root);


	clear(&root, 0);
	//clear(&root_avl, 0);
	*/
	_getch();
    return 0;
}
void clear(leaf *root, int pom)
{
	if ((*root).left != NULL)
		clear((*root).left, 1);

	if ((*root).right != NULL)
		clear((*root).right, 1);

	if (pom == 1)
		delete root;
	else cout << "\nKORZEN: " << root->key << endl;
}
double in_order(leaf *root)
{
	if (root->left != NULL)
		in_order(root->left);
	cout << root->key << " ";
	if (root->right != NULL)
		in_order(root->right);
	return 1;
}
double pre_order(leaf *root)
{
	cout << root->key << " ";
	if (root->left != NULL)
		pre_order(root->left);
	if (root->right != NULL)
		pre_order(root->right);
	return 1;
}
double post_order(leaf *root)
{
	if (root->left != NULL)
		post_order(root->left);
	if (root->right != NULL)
		post_order(root->right);
	cout << root->key << " ";
	return 1;
}
void wyswietl(vector<int> array)
{
	for (int i = 0; i < array.size(); i++)
		cout << array[i] << " ";
	cout << endl << endl;
}
void random(int size, vector<int> &array)
{
	for (int i = 0; i < size; i++)
		array.push_back(rand() % 990000);
}
