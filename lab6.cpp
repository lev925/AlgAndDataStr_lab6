#include <iostream>
#include <string>
#include <cmath>
using namespace std;
 
struct AVLNode {
    int elem;
    struct AVLNode* lc;
    struct AVLNode* rc;
    struct AVLNode* parent;
    int balance; // показатель баланса 
};
int MAX(int a, int b)
{
    return a > b ? a : b;
}
int GetHeight(AVLNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + MAX(GetHeight(node->lc), GetHeight(node->rc));
    }
 
}
AVLNode* rotate_from_right(AVLNode* node) {
    AVLNode* p = node->rc;
    p->balance = 0;
    node->balance = 0;
    p->parent = node->parent;
    node->rc = p->lc;
    if (p->lc != NULL) p->lc->parent = node;
    p->lc = node;
    node->parent = p;
    node = p;
    return node;
}
AVLNode* rotate_from_left(AVLNode* node) {
    AVLNode* p = node->lc;
    p->balance = 0;
    node->balance = 0;
    p->parent = node->parent;
    node->lc = p->rc;
    if (p->rc != NULL) p->rc->parent = node;
    p->rc = node;
    node->parent = p;
    node = p;
    return node;
}
AVLNode* double_rotate_from_right(AVLNode* node) {
    // ??? две строки ??? – упражнение
    node->rc = rotate_from_left(node->rc);
    return rotate_from_right(node);
}
AVLNode* double_rotate_from_left(AVLNode* node) {
    // ??? две строки ??? – упражнение
    node->lc = rotate_from_right(node->lc);
    return rotate_from_left(node);
}
AVLNode* insert(AVLNode* root, int x, AVLNode* par = NULL)
{
    if (root == NULL) {
        root = new AVLNode;
        root->elem = x;
        root->lc = NULL;
        root->rc = NULL;
        root->parent = par;
        root->balance = 0;
        return root;
    }
    if (x < root->elem) {
        root->lc = insert(root->lc, x, root);
        root->balance = GetHeight(root->rc) - GetHeight(root->lc);
        if (abs(root->balance) > 1) {
            if (root->lc->elem > x) // внешний случай
                root = rotate_from_left(root);
            else // внутренний случай
                root = double_rotate_from_left(root);
        }
        return root;
    }
    else {
        if (x == root->elem) return root;
        root->rc = insert(root->rc, x, root);
        root->balance = GetHeight(root->lc) - GetHeight(root->rc);
        // «симметричный» код
        if (abs(root->balance) > 1) {
            if (root->rc->elem < x) // внешний случай
                root = rotate_from_right(root);
            else // внутренний случай
                root = double_rotate_from_right(root);
        }
        return root;
    }
}
AVLNode* Search(AVLNode* root, int el)
{
    while (root->elem != el)
    {
        if (root == NULL) return root;
        if (root->elem > el) root = root->lc;
        if (root->elem < el) root = root->rc;
    }
    return root;
}
void balance(AVLNode* root)
{
    while (root != NULL && root->balance != GetHeight(root->rc) - GetHeight(root->lc))
    {
        root->balance = GetHeight(root->rc) - GetHeight(root->lc);
        int bal = GetHeight(root->rc) - GetHeight(root->lc);
        if (bal > 1 && root->lc->balance >= 0)
            root = rotate_from_right(root);
        if (bal > 1 && root->lc->balance < 0)
        {
            root = double_rotate_from_right(root);
        }
        if (bal < -1 && root->lc->balance >= 0)
        {
 
            root = rotate_from_left(root);
        }
        if (bal < -1 && root->lc->balance < 0)
        {
 
            root = double_rotate_from_left(root);
        }
        root = root->parent;
    }
}
bool Del(AVLNode* root, int a)
{
    root = Search(root, a);
    if (root == NULL) return false;
    if ((root->lc == NULL) || (root->rc == NULL))
    {
        AVLNode* temp = root->lc ? root->lc : root->rc;
        if (temp == NULL)
        {
            if (root->parent != NULL)
            {
                temp = root->parent;
                if (root->elem > temp->elem) temp->rc = NULL;
                else temp->lc = NULL;
            }
            root = NULL;
            balance(temp);
            return true;
        }
        else
        {
            AVLNode* par = root->parent;
            *root = *temp;
            root->parent = par;
            balance(root->parent);
            temp=NULL;
            return true;
        }
 
 
    }
    else
    {
        AVLNode* temp = root->rc;
        while (temp->lc != NULL)
        {
            temp = temp->lc;
        }
        int zmen = temp->elem;
        Del(temp, temp->elem);
        root->elem = zmen;
    }
 
}
void  Print1(AVLNode* root)
{
    if (root != NULL)
    {
        cout << root->elem << " ";
        Print1(root->lc);
        Print1(root->rc);
    }
}
void print_Tree(AVLNode* p, int level=0)
{
    if (p)
    {
        print_Tree(p->lc, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->elem << endl;
        print_Tree(p->rc, level + 1);
    }
}
void main()
{
    AVLNode* tree = NULL;
 
 
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, -10);
    tree = insert(tree, 14);
    tree = insert(tree, 18);
    tree = insert(tree, 30);
    tree = insert(tree, 6);
    tree = insert(tree, 5);
    tree = insert(tree, 4);
    tree = insert(tree, 7);
    tree = insert(tree, -15);
 
    print_Tree(tree);
    cout << endl;
    Del(tree, 18);
    print_Tree(tree);
}
