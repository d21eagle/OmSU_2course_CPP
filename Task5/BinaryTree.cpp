#include "BinaryTree.h"

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(int x) : root(new Node)
{
    root -> data = x;
    root -> left = nullptr;
    root -> right = nullptr;
}

BinaryTree::BinaryTree(const BinaryTree& obj)
{
    std::cout << "Конструктор копирования" << endl;
    root = copyTree(obj.root);
}

BinaryTree::BinaryTree(BinaryTree&& obj) noexcept : root(obj.root)
{
    std::cout << "Конструктор перемещения" << endl;
    obj.root = nullptr;
}

BinaryTree::~BinaryTree()
{
    clear();
}

BinaryTree& BinaryTree::operator=(const BinaryTree& obj)
{
    if (this != &obj)
    {
        delete root;
        root = copyTree(obj.root);
    }
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& obj) noexcept
{
    if (this != &obj)
    {
        delete root;
        root = obj.root;
        obj.root = nullptr;
    }
    return (*this);
}

bool BinaryTree::operator==(const BinaryTree& obj)
{
    return isEqual(root, obj.root);
}

bool BinaryTree::operator!=(const BinaryTree& obj)
{
    return !(*this == obj);
}

void BinaryTree::clear()
{
    if (root != nullptr)
    {
        clear(root);
        root = nullptr;
    }
}

void BinaryTree::clear(PNode node) {
    if (node != nullptr)
    {
        clear(node -> left);
        clear(node -> right);
        delete node;
    }
}

void BinaryTree::insert(int x, const vector<bool>& boolArr)
{
    if (root == nullptr)
    {
        if (!boolArr.empty())
            throw exception();

        root = new Node;
        root -> data = x;
    }
    else
    {
        PNode current = root;
        unsigned arrSize = boolArr.size();
        for (unsigned i = 0; i < arrSize; i++)
        {
            if (i == arrSize - 1)
            {
                PNode old = current;
                current = new Node;
                boolArr[i] ? old -> right = current : old -> left = current;
                current -> left = nullptr;
                current -> right = nullptr;
            }
            else if (boolArr[i] && current -> right != nullptr) {
                current = current -> right;
            }
            else if (!boolArr[i] && current -> left != nullptr) {
                current = current -> left;
            }
            else throw exception();
        }
        current -> data = x;
    }
}

ostream& operator<<(ostream& out, BinaryTree& obj)
{
    obj.levelPrint(out);
    return out;
}

unsigned BinaryTree::countOfEven()
{
    return countOfEven(root);
}

unsigned BinaryTree::countOfEven(BinaryTree::PNode elem)
{
    return (elem == nullptr ? 0 :
            (elem -> data % 2 == 0) + countOfEven(elem -> left) + countOfEven(elem -> right));
}

bool BinaryTree::allPositive()
{
    return allPositive(root);
}

bool BinaryTree::allPositive(const BinaryTree::PNode elem)
{
    return elem == nullptr || elem -> data > 0 && allPositive(elem -> left) && allPositive(elem -> right);
}

void BinaryTree::deleteLeaves()
{
    deleteLeaves(root);
}

bool BinaryTree::deleteLeaves(BinaryTree::PNode elem)
{
    if (elem == nullptr)
        return false;

    else
    {
        if (elem -> right == nullptr && elem -> left == nullptr)
        {
            delete elem;
            return true;
        }
        if (deleteLeaves(elem -> left))
            elem -> left = nullptr;

        if (deleteLeaves(elem -> right))
            elem -> right = nullptr;

        return false;
    }
}

double BinaryTree::average()
{
    pair<long, int> res(0, 0);
    average(root, res);
    return ((double)res.first) / res.second;
}

void BinaryTree::average(const BinaryTree::PNode elem, pair<long, int>& values)
{
    if (elem != nullptr) {
        values.first += elem -> data;
        values.second += 1;
        average(elem -> left, values);
        average(elem -> right, values);
    }
}

vector<bool> BinaryTree::searchElem(int x) {
    vector<bool> res{};
    if (!searchElem(root, res, x))
        throw exception();

    return res;
}

bool BinaryTree::searchElem(BinaryTree::PNode const elem, vector<bool>& arr, int x) {
    if (elem != nullptr) {
        if (elem -> data == x) {
            return true;
        }
        arr.push_back(false);
        if (searchElem(elem -> left, arr, x)) {
            return true;
        }
        arr.pop_back();
        arr.push_back(true);
        if (searchElem(elem -> right, arr, x)) {
            return true;
        }
        arr.pop_back();
    }
    return false;
}

BinaryTree::PNode BinaryTree::copyTree(BinaryTree::PNode obj)
{
    if (obj != nullptr)
        return new Node(obj -> data, copyTree(obj -> left), copyTree(obj -> right));

    return nullptr;
}

bool BinaryTree::isEqual(BinaryTree::PNode const elem, BinaryTree::PNode const elem1)
{
    if (elem == nullptr)
        return elem1 == nullptr;

    else {
        return elem -> data == elem1 -> data && elem -> right == elem1 -> right && elem -> left == elem1 -> left
               && isEqual(elem -> left, elem1 -> left) && isEqual(elem -> right, elem1 -> right);
    }
}

void BinaryTree::levelPrint(ostream& out)
{
    levelPrint(root, 0, out);
}

void BinaryTree::levelPrint(BinaryTree::PNode elem, unsigned int level, ostream& out)
{
    if (elem != nullptr)
    {
        for (unsigned i = 0; i != level; i++) {
            out << "\t";
        }
        out << elem->data << "\n";
        levelPrint(elem -> left, level + 1, out);
        levelPrint(elem -> right, level + 1, out);
    }
}


