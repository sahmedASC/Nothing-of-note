#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}
  void p_down( std::vector<T> &test){
      int x=0;
      int y=0;
      while((2*x+1)<test.size()){

          if((2*x+2)<test.size() and test[2*x+2]<test[2*x+1]){
              y=2*x+2;
          }
          else y = 2*x+1;
          if(test[y]<test[x]){
              T s1= test[y];
              T s2= test[x];
              test[x]=s1;
              test[y]=s2;
              x=y;
          }
          else break;
      }
  }

  priority_queue( std::vector<T> const& values )
  {
      for(int i =0; i <values.size();i++){
          this->push(values[i]);
      }
  }
  void p_up(std::vector<T> &test){
      int x = test.size()-1;
      while (x>0){
          if(test[x]< test[(x-1)/2]){
              T s1=test[x];
              T s2= test[(x-1)/2];
              test[x]=s2;
              test[(x-1)/2]=s1;
              x=(x-1)/2;
          }
          else break;
      }
  }



  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
      m_heap.push_back(entry);
      p_up(m_heap);
  }

  void pop() 
  {
      m_heap[0]=m_heap[m_heap.size()-1];
      m_heap.pop_back();
      p_down(m_heap);
      return;
    assert( !m_heap.empty() );
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }

  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  { int x= 0;
    while (x<heap.size()){
        int left = 2*x +1;
        int right = 2*x +2;
        if(left> heap.size() and right>heap.size()){
            x++;
            continue;
        }
        if(left> heap.size()){
            if(heap[x]<heap[right]){ x++; continue;}
            else return false;
        }
        if(right> heap.size()){
            if(heap[x]<heap[left]){ x++; continue;}
            else return false;
        }
        if(heap[x]<heap[left] and heap[x]<heap[right]){ x++; continue;}
        else return false;

    }
    return true;

  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};

template <class T>
void make_heap(std::vector<T> &v, int n, int i){
    int parent = i;

    int left_child = 2*i + 1;
    int right_child = 2*i + 2;

    if (left_child < n && v[left_child] > v[parent])
    {
        parent = left_child;
    }

    if (right_child < n && v[right_child] > v[parent])
    {
        parent = right_child;
    }

    if (parent != i)
    {

        T large = v[parent];
        T root = v[i];

        v[i] = large;
        v[parent] = root;

        make_heap(v, n, parent);
    }
}

template <class T>
void heap_sort( std::vector<T> & v )
{
    int n = v.size();

    for (int i = (n/2) - 1; i >= 0; i--)
        make_heap(v, n, i);


    for (int i = n-1; i >= 0; i--)
    {

        T current = v[0];
        T end = v[i];

        v[0] = end;
        v[i] = current;

        make_heap(v, i, 0);
    }
}

#endif
