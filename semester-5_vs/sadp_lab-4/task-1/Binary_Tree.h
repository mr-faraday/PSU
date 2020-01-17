#pragma once

#include<algorithm>
#include<set>  // Для лабораторной работы

/// <summary>
/// Узел бинарного дерева
/// </summary>

template <class T>
struct Node {
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;
  size_t key;
  T data;

  Node(T data, size_t key) {
    this->data = data;
    this->key = key;
  }
};

/// <summary>
/// Класс, представляюий бинарное дерево
/// </summary>

template <class T>
class Binary_Tree {
private:
  Node<T>* treeRoot = nullptr;

  void straight(Node<T>* root, void (Binary_Tree::*toDo)(Node<T>*)) {
    if (!root) return;
    (this->*toDo)(root);
    straight(root->left, toDo);
    straight(root->right, toDo);
  }
  void symmetric(Node<T>* root, void (Binary_Tree::* toDo)(Node<T>*)) {
    if (!root) return;
    symmetric(root->left, toDo);
    (this->*toDo)(root);
    symmetric(root->right, toDo);
  }
  void reverse(Node<T>* root, void (Binary_Tree::* toDo)(Node<T>*)) {
    if (!root) return;
    reverse(root->left, toDo);
    reverse(root->right, toDo);
    (this->*toDo)(root);
  }

  void printNode(Node<T>* node) {
    std::wcout << node->key << L" : ";
    std::wcout << node->data << L"\n\r";
  }
  void popNode(Node<T>* node) {
    delete node;
  }
  Node<T>* findNode(Node<T>* r, size_t key) {
    if (!r) return nullptr;
    if (r->key == key) return r;
    if (key < r->key) return findNode(r->left, key);
    else return findNode(r->right, key);
  }
  size_t getLevel(Node<T>* node, Node<T>* r, size_t counter) {
    if (r == node) return counter;
    counter++;
    if (node->key < r->key) return getLevel(node, r->left, counter);
    if (node->key > r->key) return getLevel(node, r->right, counter);
    return -1;
  }
  Node<T>* insert(Node<T>* r, size_t key, T data) {
    if (r == nullptr) {
      r = new Node<T>(data, key);
      return r;
    } else if (r->key == key) {
      Node<T>* newN = new Node<T>(data, key);
      newN->left = r->left;
      newN->right = r->right;
      delete r;
      return newN;
    } else if (key < r->key) {
      r->left = insert(r->left, key, data);
      r = balance(r);
    } else if (key > r->key) {
      r->right = insert(r->right, key, data);
      r = balance(r);
    }
    return r;
  }

  // Удаление
  Node<T>* removeNode(Node<T>* r, size_t key) {
    if (!r) return nullptr;
    if (key < r->key) r->left = removeNode(r->left, key);
    else if (key > r->key) r->right = removeNode(r->right, key);
    else {
      Node<T>* L = r->left;
      Node<T>* R = r->right;
      delete r;
      if (!R) return L;
      Node<T>* min = findMin(R);
      min->right = removeMin(R);
      min->left = L;
      return balance(min);
    }

    return balance(r);
  }
  Node<T>* findMin(Node<T>* r) {
    return r->left ? findMin(r->left) : r;
  }
  Node<T>* removeMin(Node<T>* r) {
    if (!r->left) return r->right;
    r->left = removeMin(r->left);
    return balance(r);
  }

  // Балансировка
  int height(Node<T>* node) {
    int h = 0;
    if (node) {
      int l_height = height(node->left);
      int r_height = height(node->right);
      int max_height = std::max(l_height, r_height);
      h = max_height + 1;
    }
    return h;
  }
  int difference(Node<T>* node) {
    int l_height = height(node->left);
    int r_height = height(node->right);
    int b_factor = l_height - r_height;
    return b_factor;
  }
  Node<T>* rr_rotat(Node<T>* parent) {
    Node<T>* node;
    node = parent->right;
    parent->right = node->left;
    node->left = parent;
    return node;
  }
  Node<T>* ll_rotat(Node<T>* parent) {
    Node<T>* node;
    node = parent->left;
    parent->left = node->right;
    node->right = parent;
    return node;
  }
  Node<T>* lr_rotat(Node<T>* parent) {
    Node<T>* node;
    node = parent->left;
    parent->left = rr_rotat(node);
    return ll_rotat(parent);
  }
  Node<T>* rl_rotat(Node<T>* parent) {
    Node<T>* node;
    node = parent->right;
    parent->right = ll_rotat(node);
    return rr_rotat(parent);
  }
  Node<T>* balance(Node<T>* node) {
    int bal_factor = difference(node);
    if (bal_factor > 1) {
      if (difference(node->left) > 0)
        node = ll_rotat(node);
      else
        node = lr_rotat(node);
    } else if (bal_factor < -1) {
      if (difference(node->right) > 0)
        node = rl_rotat(node);
      else
        node = rr_rotat(node);
    }
    return node;
  }

  // Для лабораторной №6 задания 3
  Node<T>* delRTree_lab6Func(Node<T>* r) {
    if (!r) return nullptr;
    r->left = delRTree_lab6Func(r->left);
    r->right = delRTree_lab6Func(r->right);
    delete r;
    return nullptr;
  }
  void findVowel_lab6Func(std::set<wchar_t>& vowels, Node<T>* r) {
    if (!r) return;
    if (vowels.find(r->data) != vowels.end()) r->right = delRTree_lab6Func(r->right);
    findVowel_lab6Func(vowels, r->left);
    findVowel_lab6Func(vowels, r->right);
  }

public:
  Binary_Tree() {}
  ~Binary_Tree() {
    reverse(treeRoot, &Binary_Tree::popNode);
  }

  bool empty() {
    return !treeRoot;
  }
  void printTree() {
    symmetric(treeRoot, &Binary_Tree::printNode);
  }
  void insert(T data, size_t key) {
    treeRoot = insert(treeRoot, key, data);
  }
  void deleteNode(size_t key) {
    Node<T>* toDel = findNode(treeRoot, key);
    if (!toDel) {
      std::wcout << L"Node not found: " << key << L"\n\r";
      return;
    }

    treeRoot = removeNode(treeRoot, key);
  }
  bool isNode(size_t key) {
    return findNode(treeRoot, key);
  }
  size_t getMinKey() {
    if (!treeRoot) return -1;
    Node<T>* p = treeRoot;
    size_t min;
    while (p != nullptr) {
      min = p->key;
      p = p->left;
    }
    return min;
  }
  size_t getMaxKey() {
    if (!treeRoot) return -1;
    Node<T>* p = treeRoot;
    size_t max;
    while (p != nullptr) {
      max = p->key;
      p = p->right;
    }
    return max;
  }
  T& getData(size_t key) {
    Node<T>* node = findNode(treeRoot, key);
    if (node)
      return node->data;
    else exit(-1);
  }

  // Для лаборатоных
  size_t getLevel(size_t key) {
    size_t counter = 0;
    return getLevel(findNode(treeRoot, key), treeRoot, counter);
  }
  size_t sumAtLevel(size_t level) {
    size_t sum = 0;
    for (size_t i = getMinKey(); i <= getMaxKey(); i++)
      if (isNode(i) && getLevel(i) == level)
        sum += findNode(treeRoot, i)->key;
    return sum;
  }

  // Лабораторная №6 Задание 3
  void delTree_lab6Func(std::set<wchar_t>& vowels) {
    if (!treeRoot) return;
    findVowel_lab6Func(vowels, treeRoot);
  }
};
