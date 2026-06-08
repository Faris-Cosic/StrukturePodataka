#pragma once
#include <iostream>

template <typename K, typename V>
class Map {
  public:
    Map() : root(nullptr), size_(0) {};
    Map(const Map&);
    Map(Map&&);
    Map& operator=(const Map&);
    Map& operator=(Map&&);
    ~Map() {
      destroy(root);
    };
    bool empty() const {
      return root == nullptr;
    };
    size_t size() const {
      return size_;
    };
    // Metod baza iznimku ako element sa datim kljucem ne postoji
    V& at(const K&);
    const V& at(const K&) const;
    // Matod vraca nullptr ako element nije pronadjen
    V* find(const K&);
    const V* find(const K&) const;
    // Metod vraca referencu na element u stablu. Ako element ne
    // postoji potrebno je ubaciti novi cvor pod kljucem k, sa default
    // konstruisanom vrijednosti v (stoga ovaj metod ne moze biti const)
    V& operator[](const K&);
    // Ubacuje novi cvor u stablo pod kljucem k. Vrijednost se konstruise
    // koristeci forward referencu. Potrebno je baciti iznimku ako vrijednost
    // pod tim kljucem vec postoji.
    template <typename F>
      void insert(const K&, F&&);
    // Vraca true ako je vrijednost obrisana, false
    // ako ne postoji
    bool erase(const K&);
    void clear();
  private:
    struct node {
      K key;
      V value;
      node *left, *right;

      template <typename F>
      node(const K& k, F&& v) : key(k), value(std::forward<F>(v)), left(nullptr), right(nullptr) {};
    };
    size_t size_;
    node* root = nullptr;


    node* copy(node* n) {
      if(!n)
        return nullptr;
      node* l = new node(n->key, n->value);
      l->left = copy(n->left);
      l->right = copy(n->right);
      return l;
    }

    void destroy(node* n) {
      if(!n)
        return;
      destroy(n->left);
      destroy(n->right);
      delete n;
    }

  void eraseNode(node* toDelete, node*& connection);
};

template <typename K, typename V>
Map<K, V>::Map(const Map& other){
  root = copy(other.root);
  size_ = other.size_;
}

template <typename K, typename V>
Map<K, V>::Map(Map&& other) : size_(other.size_), root(other.root){
  other.size_ = 0;
  other.root = nullptr;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& other){
  if(this == &other){
    return *this;
  }
  destroy(root);
  root = copy(other.root);
  size_ = other.size_;
  return *this;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map<K, V>&& other){
  if(this == &other){
    return *this; 
  }
  destroy(root);
  root = other.root;
  size_ = other.size_;

  other.root = nullptr;
  other.size_ = 0;

  return *this;
}

template <typename K, typename V>
V* Map<K, V>::find(const K& k) {
  node* thisNode = root;
  while(thisNode != nullptr) {
    if(k > thisNode->key) {
      thisNode = thisNode->right;
    }
    else if(k < thisNode->key) {
      thisNode = thisNode->left;
    }
    else 
      return &thisNode->value;
  }
  return nullptr;
}

template <typename K, typename V>
const V* Map<K, V>::find(const K& k) const {
  const node* thisNode = root;
  while(thisNode != nullptr) {
    if(k > thisNode->key) {
      thisNode = thisNode->right;
    }
    else if(k < thisNode->key) {
      thisNode = thisNode->left;
    }
    else 
      return &thisNode->value;
  }
  return nullptr;
}

template <typename K, typename V>
V& Map<K, V>::at(const K& k) {
  auto* foundNode = find(k);
  if (!foundNode)
    throw std::out_of_range("Element nije pronadjen");
  return *foundNode;
}

template <typename K, typename V>
const V& Map<K, V>::at(const K& k) const {
  auto* foundNode = find(k);
  if (!foundNode)
    throw std::out_of_range("Element nije pronadjen");
  return *foundNode;
}


template <typename K, typename V>
template <typename F>
void Map<K, V>::insert(const K& key, F&& value){
  if(find(key))
    throw std::invalid_argument("Element sa tim ključem već postoji");
  if(!root){
    root = new node(key, std::forward<F>(value));
    size_++;
    return;
  }
  size_++;
  node* currentNode = root;
  while(currentNode){
    auto& childNode = key > currentNode->key ? currentNode->right : currentNode->left;
    if(!childNode){
      childNode = new node(key, std::forward<F>(value));
      break;
    }
    else {
      currentNode = childNode;
    }
  }
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key){
  auto foundNode = find(key);
  if(foundNode)
    return *foundNode;
  V value;
  insert(key, value);
  return *find(key);
}

template <typename K, typename V>
void Map<K, V>::eraseNode(node* toDelete, node*& connection){
  node* leftChild = toDelete->left;
  node* rightChild = toDelete->right;
  if(!leftChild && !rightChild){
    connection = nullptr; 
    delete toDelete;
    return;
  }
  if(!leftChild) {
    connection = toDelete->right;
    delete toDelete;
    return;
  }
  if(!rightChild){
    connection = toDelete->left;
    delete toDelete;
    return;
  }

  node* inOrderSuccesor = toDelete->right;
  node* parentNodeSuccesor = nullptr;

  while(inOrderSuccesor->left != nullptr){
    parentNodeSuccesor = inOrderSuccesor;
    inOrderSuccesor = inOrderSuccesor->left;
  }

  toDelete->value = inOrderSuccesor->value;
  toDelete->key = inOrderSuccesor->key;

  if(!parentNodeSuccesor){
    toDelete->right = inOrderSuccesor->right;
    delete inOrderSuccesor;
    return;
  }

  if(inOrderSuccesor->right)
    parentNodeSuccesor->left = inOrderSuccesor->right;
  else 
    parentNodeSuccesor->left = nullptr;
  delete inOrderSuccesor;
  return;
  
}


template <typename K, typename V>
bool Map<K, V>::erase(const K& key){
  if(!find(key))
    return false;
  node* currentNode = root;
  node* parentNode = nullptr;
  while(currentNode->key != key){
    parentNode = currentNode;
    if(key > currentNode->key) {
      currentNode = currentNode->right;
    }
    else if(key < currentNode->key) {
      currentNode = currentNode->left;
    }
  }

  if(!parentNode){
    eraseNode(currentNode, root);
    size_--;
    return true;
  }
  node*& parentChildConnection = parentNode->left == currentNode ? parentNode->left : parentNode->right;
  size_--;
  eraseNode(currentNode, parentChildConnection);
  return true;
}

template <typename K, typename V>
void Map<K, V>::clear(){
  destroy(root);
  size_ = 0;
  root = nullptr;
}


