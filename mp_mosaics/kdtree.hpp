/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim] < second[curDim]) {
       return true;
     }
     if(first[curDim] > second[curDim]) {
       return false;
     }
     if(first[curDim] == second[curDim]) {
       return first < second;
     }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double sumPotential = 0;
     double sumCurrBest = 0;
     for(int i = 0; i < Dim; i++){
       sumPotential += pow((target[i] - potential[i]), 2.0);
       sumCurrBest += pow((target[i] - currentBest[i]), 2.0);
     }
     sumPotential = sqrt(sumPotential);
     sumCurrBest = sqrt(sumCurrBest);
     if(sumPotential < sumCurrBest) {
       return true;
     }
     if(sumCurrBest > sumPotential) {
       return false;
     }
     if(sumCurrBest == sumPotential) {
       return (potential < currentBest);
     }
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    for(const Point<Dim>&point : newPoints) {
      sortedList.push_back(point);
    }
    size = 0;
    int beginDim = 0;
    int start = 0;
    int end = (sortedList.size() - 1);
    root = KDTreeHelper(start, end, beginDim);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTreeHelper(int startIndex, int endIndex, int curDim)
{
  if(sortedList.empty() || startIndex < 0 || endIndex < 0 || startIndex > endIndex) {
    return NULL;
  }
  int listSize = sortedList.size();
  if(startIndex >= listSize || endIndex >= listSize) {
    return NULL;
  }
  int temp = (endIndex - startIndex);
  temp++;
  int pivotPoint;
  if(temp % 2 != 0) {
    pivotPoint = (int)((temp / 2) + 1);
  }
  else {
    pivotPoint = (int)temp / 2;
  }
  int middle = quickSelect(startIndex, endIndex, pivotPoint, curDim);
  size++;
  KDTreeNode* newSubroot = new KDTreeNode(sortedList[middle]);
  newSubroot->right = KDTreeHelper(middle + 1, endIndex, (curDim + 1) % Dim);
  newSubroot->left = KDTreeHelper(startIndex, middle - 1, (curDim + 1) % Dim);
  return newSubroot;
}

template <int Dim>
int KDTree<Dim>::quickSelect(int left, int right, int pivotPoint, int curDim) {
  if(left == right) {
    return left;
  }
  int pivotIndex;
  pivotIndex = partition(left, right, curDim);
  int diffPivot1 = pivotIndex - left;
  int diffPivot2 = pivotPoint - 1;
  int temp = pivotPoint - pivotIndex;
  if(diffPivot1 == diffPivot2) {
    return pivotIndex;
  }
  if(diffPivot1 > diffPivot2) {
    return quickSelect(left, pivotIndex - 1, pivotPoint, curDim);
  }
  temp--;
  return quickSelect(pivotIndex + 1, right, temp + left, curDim);
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int curDim) {
  Point<Dim> temp;
  Point<Dim> pivotPoint = sortedList[right];
  int storeIndex = (left - 1);
  int i = left;
  while(i < right) {
    if(smallerDimVal(sortedList[i], pivotPoint, curDim)) {
      storeIndex++;
      temp = sortedList[storeIndex];
      sortedList[storeIndex] = sortedList[i];
      sortedList[i] = temp;
    }
    i++;
  }
  storeIndex++;
  temp = sortedList[right];
  sortedList[right] = sortedList[storeIndex];
  sortedList[storeIndex] = temp;
  return storeIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copyFunction(other);
}

template <int Dim>
void KDTree<Dim>::copyFunction(const KDTree<Dim>& other) {
  this = new KDTree(other.sortedList);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(*this == rhs) {
    return *this;
  }
  destroyFunction(root);
  copyFunction(rhs);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroyFunction(root);
}

template <int Dim>
void KDTree<Dim>::destroyFunction(KDTreeNode* subRoot) {
  if(subRoot == NULL) {
    return;
  }
  else {
    KDTreeNode* leftNode = subRoot->left;
    KDTreeNode* rightNode = subRoot->right;
    delete subRoot;
    subRoot = NULL;
    destroyFunction(leftNode);
    destroyFunction(rightNode);
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     if(root == NULL) {
       return Point<Dim>();
     }
    int beginDim = 0;
    return (findNearestNeighborHelper(query, root, beginDim))->point;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query, typename KDTree<Dim>::KDTreeNode* subroot, int curDim) const {

  KDTreeNode* curr = NULL;
  KDTreeNode* next = NULL;

  if(subroot->left == NULL && subroot->right == NULL) {
    return subroot;
  }

  if(!smallerDimVal(query, subroot->point, curDim)) {
    if(subroot->right != NULL) {
      curr = findNearestNeighborHelper(query, subroot->right, ((curDim + 1) % Dim));
    }
    else {
      curr = findNearestNeighborHelper(query, subroot->left, ((curDim + 1) % Dim));
    }
    next = subroot->left;
    if(shouldReplace(query, curr->point, subroot->point)) {
      curr = subroot;
    }
  }
  else {
    if(subroot->left != NULL) {
      curr = findNearestNeighborHelper(query, subroot->left, ((curDim + 1) % Dim));
    }
    else {
      curr = findNearestNeighborHelper(query, subroot->right, ((curDim + 1) % Dim));
    }
    next = subroot->right;
    if(shouldReplace(query, curr->point, subroot->point)) {
      curr = subroot;
    }
  }

  double currDist = calculateDist(query, curr->point);
  double currDimDist = sqrt(pow((query[curDim] - subroot->point[curDim]), 2.0));

  if(currDimDist <= currDist) {
    if(next != NULL) {
      next = findNearestNeighborHelper(query, next, ((curDim + 1) % Dim));
      if(shouldReplace(query, curr->point, next->point)) {
        curr = next;
      }
    }
  }
  return curr;
}

template <int Dim>
double KDTree<Dim>::calculateDist(Point<Dim> p1, Point<Dim> p2) const {
  double sum = 0;
  for(int i = 0; i < Dim; i++) {
    sum += pow((p1[i] - p2[i]), 2.0);
  }
  sum = sqrt(sum);
  return sum;
}
