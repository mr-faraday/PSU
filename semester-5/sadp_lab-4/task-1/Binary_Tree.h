#pragma once

#include<algorithm>

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

template <class T>
class Binary_Tree {
private:
  Node<T>* treeRoot = nullptr;
  std::wostream &out = std::wcout;  // Поток для вывода

  void straight(Node<T>* root, void (Binary_Tree::*toDo)(Node<T>*)) {
    if (!root) return;
    (this->*toDo)(root);
    straight(root->left, toDo);
    straight(root->right, toDo);
  }
  void reverse(Node<T>* root, void (Binary_Tree::* toDo)(Node<T>*)) {
    if (!root) return;
    reverse(root->left, toDo);
    reverse(root->right, toDo);
    (this->*toDo)(root);
  }

  void printNode(Node<T>* node) {
    out << node->key << L" : ";
    out << node->data << L"\n\r";
  }
  void popNode(Node<T>* node) {
    delete node;
  }
  Node<T>* findNode(Node<T>* root, size_t key) {
    if (!root) return nullptr;
    if (root->key == key) return root;
    if (key < root->key) return findNode(root->left, key);
    else return findNode(root->right, key);
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
  /*Node<T>* push(Node<T>* newNode, Node<T>* root) {
    if (root == nullptr) return newNode;
    if (root->key == newNode->key) {
      newNode->left = root->left;
      newNode->right = root->right;
      delete root;
      return newNode;
    }
    if (root->key > newNode->key) root->left = push(newNode, root->left);
    if (root->key < newNode->key) root->right = push(newNode, root->right);
    return root;
  }*/
  size_t getLevel(Node<T>* node, Node<T>* root, size_t counter) {
    if (root == node) return counter;
    counter++;
    if (node->key < root->key) return getLevel(node, root->left, counter);
    if (node->key > root->key) return getLevel(node, root->right, counter);
    return -1;
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
  Node<T>* insert(Node<T>* r, size_t key, T data) {
    if (r == nullptr) {
      r = new Node<T>(data, key);
      return r;
    } else if (key < r->key) {
      r->left = insert(r->left, key, data);
      r = balance(r);
    } else if (key >= r->key) {
      r->right = insert(r->right, key, data);
      r = balance(r);
    }
    return r;
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
    straight(treeRoot, &Binary_Tree::printNode);
  }
  void insert(T data, size_t key) {
    //Node<T>* newNode = new Node<T>(data, key);
    //treeRoot = push(newNode, treeRoot);
    treeRoot = insert(treeRoot, key, data);
  }
  void deleteNode(size_t key) {
    Node<T>* toDel = findNode(treeRoot, key);
    if (!toDel) {
      out << L"Node not found: " << key << L"\n\r";
      return;
    }
    // Если это лист
    if (!toDel->left && !toDel->right) {
      switch (whatIS(toDel)) {
      case 0:
        treeRoot = nullptr;
        delete toDel;
        treeRoot = balance(treeRoot);
        return;
      case 1:
        getParent(treeRoot, key)->left = nullptr;
        delete toDel;
        treeRoot = balance(treeRoot);
        return;
      case 2:
        getParent(treeRoot, key)->right = nullptr;
        delete toDel;
        treeRoot = balance(treeRoot);
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
        treeRoot = balance(treeRoot);
        return;
      case 1:
        getParent(treeRoot, key)->left = toDel->left;
        delete toDel;
        treeRoot = balance(treeRoot);
        return;
      case 2:
        getParent(treeRoot, key)->right = toDel->left;
        delete toDel;
        treeRoot = balance(treeRoot);
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
        treeRoot = balance(treeRoot);
        return;
      case 1:
        getParent(treeRoot, key)->left = toDel->right;
        delete toDel;
        treeRoot = balance(treeRoot);
        return;
      case 2:
        getParent(treeRoot, key)->right = toDel->right;
        delete toDel;
        treeRoot = balance(treeRoot);
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
      treeRoot = balance(treeRoot);
      delete toDel;
      return;
    }
      // Если потомок левой ветви
    case 1: {
      getParent(toDel)->left = nodeToMove;
      nodeToMove->left = toDel->left;
      nodeToMove->right = toDel->right;
      treeRoot = balance(treeRoot);
      delete toDel;
      return;
    }
      // Если потомок правой ветви
    case 2: {
      getParent(toDel)->right = nodeToMove;
      nodeToMove->left = toDel->left;
      nodeToMove->right = toDel->right;
      treeRoot = balance(treeRoot);
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
};
