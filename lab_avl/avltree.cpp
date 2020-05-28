/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* croot = t;
    Node* temp = t->right;
    Node* temp2 = temp->left;
    t->right = temp2;
    temp->left = croot;
    if(heightOrNeg1(t->left) >= heightOrNeg1(t->right)) {
      t->height = heightOrNeg1(t->left) + 1;
    }
    else {
      t->height = heightOrNeg1(t->right) + 1;
    }
    t = temp;
    if(heightOrNeg1(t->left) >= heightOrNeg1(t->right)) {
      t->height = heightOrNeg1(t->left) + 1;
    }
    else {
      t->height = heightOrNeg1(t->right) + 1;
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* croot = t;
    Node* temp = t->left;
    Node* temp2 = temp->right;
    t->left = temp2;
    temp->right = croot;
    if(heightOrNeg1(t->left) >= heightOrNeg1(t->right)) {
      t->height = heightOrNeg1(t->left) + 1;
    }
    else {
      t->height = heightOrNeg1(t->right) + 1;
    }
    t = temp;
    if(heightOrNeg1(t->left) >= heightOrNeg1(t->right)) {
      t->height = heightOrNeg1(t->left) + 1;
    }
    else {
      t->height = heightOrNeg1(t->right) + 1;
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL) {
      return;
    }
    int deltaHeightTree = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(deltaHeightTree == 2) {
      int deltaHeightLeftSubtree = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if(deltaHeightLeftSubtree != 1) {
        rotateRightLeft(subtree);
      }
      else {
        rotateLeft(subtree);
      }
    }
    if(deltaHeightTree == -2) {
      int deltaHeightRightSubtree = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if(deltaHeightRightSubtree != -1) {
        rotateLeftRight(subtree);
      }
      else {
        rotateRight(subtree);
      }
    }
    if(heightOrNeg1(subtree->left) >= heightOrNeg1(subtree->right)) {
      subtree->height = heightOrNeg1(subtree->left) + 1;
      return;
    }
    subtree->height = heightOrNeg1(subtree->right) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) {
      Node* temp = new Node(key, value);
      subtree = temp;
    }
    else if(subtree->key > key) {
      insert(subtree->left, key, value);
    }
    else if(subtree->key < key) {
      insert(subtree->right, key, value);
    }
    else if(subtree->key == key) {
      insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            K tempKey;
            V tempVal;
            Node* curr = subtree->left;
            while(curr->right != NULL) {
              curr = curr->right;
              tempKey = curr->key;
              tempVal = curr->value;
            }
            curr->key = subtree->key;
            curr->value = subtree->value;
            subtree->key = tempKey;
            subtree->value = tempVal;
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* temp = subtree->left;
            Node* temp2 = subtree->right;
            delete subtree;
            if(temp != NULL) {
              subtree = temp;
              return;
            }
            subtree = temp2;
        }
        // your code here
    }
    rebalance(subtree);
}
