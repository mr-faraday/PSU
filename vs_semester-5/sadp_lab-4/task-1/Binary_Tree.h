#pragma once

#include<algorithm>
#include<set>

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
  Node<T>* findNode(size_t key) {
    return findNode(treeRoot, key);
  }
  Node<T>* getParent(Node<T>* root, size_t key) {
    if (root->key == key) return nullptr;
    if (root->left)
      if (root->left->key == key) return root;
      else if (root->key > key) return getParent(root->left, key);
    if (root->right)
      if (root->right->key == key) return root;
      else if (root->key < key) return getParent(root->right, key);
    return nullptr;
  }
  Node<T>* getParent(Node<T>* node) {
    return getParent(treeRoot, node->key);
    return nullptr;
  }
  int whatIS(Node<T>* node) {
    if (node == treeRoot) return 0;  // Корень
    if (getParent(treeRoot, node->key)->left == node) return 1;  // Потомок левой ветки
    if (getParent(treeRoot, node->key)->right == node) return 2;  // Потомок правой ветки
    return -1;
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
      Node<T>*
        L = r->left,
        R = r->left;
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
  void printTreeSymm() {
    symmetric(treeRoot, &Binary_Tree::printNode);
  }
  void insert(T data, size_t key) {
    //Node<T>* newNode = new Node<T>(data, key);
    //treeRoot = push(newNode, treeRoot);
    treeRoot = insert(treeRoot, key, data);
  }
  void deleteNode(size_t key) {
    Node<T>* toDel = findNode(treeRoot, key);
    if (!toDel) {
      std::wcout << L"Node not found: " << key << L"\n\r";
      return;
    }

    treeRoot = removeNode(treeRoot, key);

    // Если это лист
    if (!toDel->left && !toDel->right) {
      switch (whatIS(toDel)) {
      case 0:
        treeRoot = nullptr;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      case 1:
        getParent(treeRoot, key)->left = nullptr;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      case 2:
        getParent(treeRoot, key)->right = nullptr;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      default:
        break;
      }
    }
    // Если узел с одной левой веткой
    if (toDel->left && !toDel->right) {
      switch (whatIS(toDel)) {
      case 0:
        treeRoot = toDel->left;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      case 1:
        getParent(treeRoot, key)->left = toDel->left;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      case 2:
        getParent(treeRoot, key)->right = toDel->left;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      default:
        break;
      }
    }
    // Если узел с одной правой веткой
    if (!toDel->left && toDel->right) {
      switch (whatIS(toDel)) {
      case 0:
        treeRoot = toDel->right;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      case 1:
        getParent(treeRoot, key)->left = toDel->right;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      case 2:
        getParent(treeRoot, key)->right = toDel->right;
        delete toDel;
        //treeRoot = balance(treeRoot);
        return;
      default:
        break;
      }
    }

    // Если узел с двумя потомками
    Node<T>* nodeToMove;
    // Получение потомка для перемещения
    nodeToMove = toDel->right;
    if (nodeToMove->left)
      while (nodeToMove->left) nodeToMove = nodeToMove->left;
    // Перенапрвление родительского узла
    switch (whatIS(nodeToMove)) {
    case 1:
      if (nodeToMove->right) getParent(nodeToMove)->left = nodeToMove->right;
      else getParent(nodeToMove)->left = nullptr;
      break;
    case 2:
      if (nodeToMove->right) getParent(nodeToMove)->right = nodeToMove->right;
      else getParent(nodeToMove)->right = nullptr;
      break;
    default:
      break;
    }
    // В завиимсти от наследования удаляемого узла
    switch (whatIS(toDel)) {
      // Если это корень
    case 0: {
      treeRoot = nodeToMove;
      treeRoot->left = toDel->left;
      treeRoot->right = toDel->right;
      //treeRoot = balance(treeRoot);
      delete toDel;
      return;
    }
      // Если потомок левой ветви
    case 1: {
      getParent(toDel)->left = nodeToMove;
      nodeToMove->left = toDel->left;
      nodeToMove->right = toDel->right;
      //treeRoot = balance(treeRoot);
      delete toDel;
      return;
    }
      // Если потомок правой ветви
    case 2: {
      getParent(toDel)->right = nodeToMove;
      nodeToMove->left = toDel->left;
      nodeToMove->right = toDel->right;
      //treeRoot = balance(treeRoot);
      delete toDel;
      return;
    }
    default:
      break;
    }
  }
  size_t getLevel(size_t key) {
    size_t counter = 0;
    return getLevel(findNode(treeRoot, key), treeRoot, counter);
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
  size_t sumAtLevel(size_t level) {
    size_t sum = 0;
    for (size_t i = getMinKey(); i <= getMaxKey(); i++)
      if (isNode(i) && getLevel(i) == level)
        sum += findNode(i)->key;
    return sum;
  }
  void delTree_lab6Func(std::set<wchar_t>& vowels) {
    if (!treeRoot) return;
    findVowel_lab6Func(vowels, treeRoot);
  }
};
