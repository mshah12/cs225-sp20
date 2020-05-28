/* Your code here! */
#include "dsets.h"
#include <vector>

using namespace std;

void DisjointSets::addelements(int num) {
  int count = 0;
  while(count < num) {
    v.push_back(-1);
    count++;
  }
}

int DisjointSets::find(int elem) {
  if(v[elem] < 0) {
    return elem;
  }
  int temp = find(v[elem]);
  v[elem] = temp;
  return temp;
}

void DisjointSets::setunion(int a, int b) {
  if(find(a) == find(b)) {
    return;
  }
  int first = find(a);
  int second = find(b);
  int firstSize = v[first];
  int secondSize = v[second];
  if(firstSize > secondSize) {
    v[first] = second;
    v[second] = (firstSize + secondSize);
    return;
  }
  v[second] = first;
  v[first] = (firstSize + secondSize);
}

int DisjointSets::size(int elem) {
  return (v[find(elem)] * -1);
}
