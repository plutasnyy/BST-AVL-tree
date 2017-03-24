// bst_avl_tree.cpp : Defines the entry point for the console application.
//

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

void wyswietl(vector<int> array)
{
	for (int i = 0; i < array.size(); i++)
		cout << array[i] << " ";
	cout << endl << endl;
}
struct leaf
{
	int key;
	leaf *left;
	leaf *right;
}root,root_avl;

void random(int size, vector<int> &array)
{
	for (int i = 0; i < size; i++)
		array.push_back(rand() % 100);
}

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
void clear(leaf *root, int pom)
{
	if ((*root).left != NULL)
		clear((*root).left,1);

	if ((*root).right != NULL)
		clear((*root).right,1);

	if(pom==1)
		delete root;
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
	if (start == end) {
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
int main()
{
	srand(time(NULL));
	int size = 10;
	vector<int> array, sort_array;
	random(size, array);
	sort_array = array;
	sort(sort_array.begin(), sort_array.end());

	wyswietl(array); wyswietl(sort_array);

	root.key = array[0];
	root.left = NULL;
	root.right = NULL;

	int center = (0 + size) % 2 ? (0 + size + 1) / 2 : (0 + size) / 2;
	root_avl.key = array[center];

	create_bst(&root, size, array);
	create_avl(&root_avl, 0, center-1, sort_array);
	create_avl(&root_avl, center + 1, array.size() - 1, sort_array);

	cout << "PRE:\n";
	pre_order(&root);
	cout << "\nIN:\n";
	in_order(&root);
	cout << "\nPOST:\n";
	post_order(&root);

	cout << "\n\nMIN: " << min_leaf(&root);

	cout << "\n\nAVL:\n";
	in_order(&root_avl);

awfawfwafwafwa
	clear(&root, 0);
	clear(&root_avl, 0);
	_getch();
    return 0;
}
