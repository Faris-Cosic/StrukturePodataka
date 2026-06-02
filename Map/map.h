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
    bool empty() const;
    size_t size() const;
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

      node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {};
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
};

template <typename K, typename V>
Map<K, V>::Map(const Map& other){
  root = other.root;
  auto node = root;
  copy(node);
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
