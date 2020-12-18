/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]>second[curDim])
      return false;
    else if(first[curDim] < second[curDim])
      return true;
    return (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    if(getDistance(target, currentBest) < getDistance(target, potential))
      return false;
    else if(getDistance(target, currentBest) > getDistance(target, potential))
      return true;
    else
      return currentBest > potential;
}

template <int Dim>
int KDTree<Dim>::getDistance(const Point<Dim> & f, const Point<Dim> & s) const {
    int temp = 0;
    for(int i = 0; i < Dim; i++)
      temp += pow((f[i] - s[i]),2);
    return temp;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = newPoints.size();
    if(size == 0)
      root = NULL;
    else {
      for(const Point<Dim>& i: newPoints)
        vPoint.push_back(i);
      root = makeKDTree(0, size-1, 0);
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::makeKDTree(int l, int r, int im) {
  if (l == r)
    return new KDTreeNode(vPoint[l]);
  else if(l > r)
    return NULL;
  else {
    select(l, r, (l+r)/2, im);
    KDTreeNode * temp = new KDTreeNode(vPoint[(l+r)/2]);
    temp->left = makeKDTree(l, (l+r)/2 - 1, ((im+1)%Dim));
    temp->right = makeKDTree((l+r)/2+1, r, ((im+1)%Dim));
    
    return temp;
  } 
}

template <int Dim>
void KDTree<Dim>::select(int l, int r, int index, int im) {
  while(l!=r) {
    Point<Dim> pp = vPoint[index];
    vPoint[index] = vPoint[r];
    vPoint[r] = pp;
    int count = l;
    int temp = l;
    while(temp<r) {
      if(smallerDimVal(vPoint[temp], pp, im) || vPoint[temp] == pp) {
	Point<Dim> store = vPoint[count];
	vPoint[count] = vPoint[temp];
	vPoint[temp] = store;
	count++;
      }
	temp++;
    }

    Point<Dim> store = vPoint[count];
    vPoint[count] = vPoint[r];
    vPoint[r] = store;
    if(index == count)
      return;
    else if(index < count) 
      r = count - 1;
    else
      l = count + 1;
  }
}  



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(other); 
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this==&rhs)
    return *this;
  else {
    delete *this;
    copy(rhs);
  }
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& other) {
  this = new KDTree(other.treepoints);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode *s) {
  if (!s)
    return;
  destroy(s->right);
  destroy(s->left);
  delete s;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    return FNNHelper(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::FNNHelper(const Point<Dim>& query, KDTreeNode * s, int dim) const {
    if(s->left==NULL && s->right==NULL)
      return s->point;

    Point<Dim> temp = s->point;
    Point<Dim> temp2 = temp;

    bool check = smallerDimVal(query, temp, dim);
    if(!check && s->right != NULL)
      temp2 = FNNHelper(query, s->right, (dim+1)%Dim);
    if(check && s->left != NULL) 
      temp2 = FNNHelper(query, s->left, (dim+1)%Dim);

    if(shouldReplace(query, temp, temp2))
      temp = temp2;

    if(pow((query[dim]-s->point[dim]),2)<=getDistance(query, temp)) {
      if(!check && s->left != NULL) {
	temp2 = FNNHelper(query, s->left, (dim+1)%Dim);
	if(shouldReplace(query, temp, temp2))
	  temp = temp2;
      } 
      if (check && s->right != NULL) {
	temp2 = FNNHelper(query, s->right, (dim+1)%Dim);
        if(shouldReplace(query, temp, temp2))
          temp = temp2;
      }
    }
    return temp;
}

