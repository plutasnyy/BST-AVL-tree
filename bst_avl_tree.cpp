#include <string>
#include <algorithm>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include <stack>
using namespace std;
string cr, cl, cp;      // ³añcuchy do znaków ramek

struct leaf
{
	int key;
	leaf *left;
	leaf *right;
}root, root_avl;

void printBT(string sp, string sn, leaf * v)
{
	string s;

	if (v)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT(s + cp, cr, v->right);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << v->key << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT(s + cp, cl, v->left);
	}
}
//BASIC
double in_order(leaf *root);
double pre_order(leaf *root);
double post_order(leaf *root);
void wyswietl(vector<int> array);
void random(int size, vector<int> &array);
void clear(leaf *root, int pom);
bool isNumber(string c);
int toNumber(string c);
int wprowadz();
void delete_function(stack<int> &stos);


void add_leaf(leaf *root, leaf *new_leaf)
{
	if ((*root).key >= (*new_leaf).key)
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
	//TODO: remember parent`s node to main node in pointer, remove all unnecesary ifs..
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
int depth(leaf *root)
{
    return root->right!=NULL? depth(root->right)+1:0;
}
int return_diff(leaf *root, int pom)
{
	int left = 0;
	if (root->left != NULL)left = return_diff(root->left,1);

	int right = 0;
	if (root->right != NULL)right = return_diff(root->right,1);

	if (pom == 0)return left - right;
	return max(left,right) + 1;
}
void r_rotation(leaf **edge)
{

	leaf *top = *edge;

  //  cout<<"r rotuje: "<<top->key<<endl;
	assert(edge);
	assert(top->left);
	if (top->left != NULL)
	{
		leaf *left_node = top->left;
		top->left = left_node->right;
		*edge = left_node;
		left_node->right = top;
	}
}
void l_rotation(leaf **edge)
{
	leaf *top = *edge;

  //  cout<<"l rotuje: "<<top->key<<endl;
	assert(edge);
	assert(top->right);

	if (top->right != NULL)
	{
		leaf *right_node = top->right;
		top->right = right_node->left;
		*edge = right_node;
		right_node->left = top;
	}
}
void to_list(leaf **root)
{
    leaf *top=*root;
    while(top->left!=NULL)r_rotation(&top);
    *root=top;
    if(top->right!=NULL)to_list(&top->right);
}
void rotation_queue(leaf **root, int m)
{
    leaf *temp=*root;
    l_rotation(&temp);
    if(m>0)rotation_queue(&temp->right,m-1);
    *root=temp;
}
void list_to_avl(leaf **root,int n)
{
    rotation_queue(root,n/2-1);
    while(abs(return_diff(*root,0))>1)
    {
        rotation_queue(root,(depth(*root)-1)/2);
    }
}
void ustal(leaf *wsk)
{
    wsk->key=return_diff(wsk,0);
    if(wsk->left!=NULL)ustal(wsk->left);
    if(wsk->right!=NULL)ustal(wsk->right);
}
int main()
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	srand(time(NULL));
	int size = 10,count=0;
	vector<int> array, sort_array, to_remove;
	random(size, array);
	sort_array = array;
	sort(sort_array.begin(), sort_array.end());
	cout<<"TABLICA:\n";
	wyswietl(array);
	cout<<"TABLICA POSORTOWANA:\n";
	wyswietl(sort_array);

	root.key = array[0];
	root.left = NULL;
	root.right = NULL;

	int center = (0 + size) % 2 ? (0 + size + 1) / 2 : (0 + size) / 2;

	root_avl.key = sort_array[center];
	root_avl.left = NULL;
	root_avl.right = NULL;

	create_bst(&root, size, array);
	create_avl(&root_avl, 0, center-1, sort_array);
	create_avl(&root_avl, center + 1, array.size() - 1, sort_array);

	leaf *wsk;
	wsk = &root_avl;
    cout<<"\n\nDRZEWO AVL:\n";
    printBT("","",wsk);
    wsk=&root;

    cout<<"\n\nDRZEWO BST:\n";
    printBT("","",wsk);

    cout<<"\nMINIMUM AVL: "<<min_leaf(&root_avl)<<"\nMINIMUM BST: "<<min_leaf(&root)<<endl<<endl;

	cout << "\nPRE:\n";
	pre_order(&root);
	cout << "\nIN:\n";
	in_order(&root);
	cout << "\nPOST:\n";
	post_order(&root);
	cout<<endl<<endl;

    cout<<"PODAJ ILE LISCI CHCESZ USUNAC <0;9>: ";
    stack<int>stos;
    delete_function(stos);
    int pom;

	while(!stos.empty())
	{
	    pom=stos.top();
	    stos.pop();
		remove(&root,pom);
	}
	cout<<"\nPO USUNIECIU, A POTEM ZROWNOWAZONE:\n";
     printBT("","",&root);

    wsk=&root;
    to_list(&wsk);
    list_to_avl(&wsk,size);
    printBT("","",wsk);
    cout<<endl;

	clear(&root, 0);
	clear(&root_avl,0);

	_getch();
    return 0;
}
bool isNumber(string c)
{
    for(int i=0;i<c.size();i++)
        if(c[i]<=47||c[i]>=58)return false;
    return true;
}
int toNumber(string c)
{
    int pom=0;
    int licz=1;
    for(int i=c.size()-1;i>=0;i--)
    {
        pom+=(c[i]-48)*licz;
        licz*=10;
    }
    return pom;
}
int wprowadz()
{
    string c;
    cin>>c;
    while(!isNumber(c))
    {
        cout<<"\nJESZCZE RAZ\n";
        cin>>c;
    }
    return toNumber(c);
}
void delete_function(stack<int> &stos)
{
    int pom;
    pom=wprowadz();
    cout<<"\nTERAZ PODAJ ZNAKI:\n";
    for(int i=0;i<pom;i++)
        stos.push(wprowadz());
}
void clear(leaf *root, int pom)
{
	if ((*root).left != NULL)
		clear((*root).left, 1);

	if ((*root).right != NULL)
		clear((*root).right, 1);

	if (pom == 1)
		delete root;
	else cout << "KORZEN: " << root->key << endl;
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
		array.push_back(rand() % 100);
}
