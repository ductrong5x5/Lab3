/*  
  Name            : Duc Trong Nguyen
  NetId           : 000 657421
  DOB             : Nov 20 1998
  Lab description : Sorting the multi-column data. Data will now be stored in single linked list. A smart pointer subclass within the single linked list class 
  will be embed
*/
// include header file(s) needed
#ifndef SLIST_H
#define SLIST_H
#include <vector>

template <class T>
class slist {
  private: 
    struct node { 
      node() { data = T(); next = NULL; }
      node(const T &key) {data=key;}
      //;
      // add overloaded operator< code
      bool operator<( const node &li){
        return data<li.data;
    }
    
      T data;
      node *next;
    };

   // add class sptr { write this for node data }
  private:
  class sptr {
    public:
     sptr(node *_ptr=NULL) { ptr = _ptr; }
      bool operator< (const sptr &rhs) {
        return *ptr < *rhs.ptr;
      }
      operator node* () const { return ptr; }
    private:
      node *ptr;
  };
  public:
    class iterator {
      public:
        iterator() { p = NULL; }
        T & operator*() { return p->data ;}
        iterator & operator++() { p = p->next; return *this; }
        bool operator!=(const iterator & rhs) const { return p != rhs.p; }

      private:
        iterator(node *n_p) { p = n_p; }
        node *p;

      friend class slist<T>;
    };

  public:
    slist(); 
    ~slist(); 

    void push_back(const T &);
    void sort(const string &);

    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(NULL); }

  private:
    node *head;
    node *tail;
};

template <typename T>
slist<T>::slist() {
  head = new node();
  tail = head;
}

template <typename T>
slist<T>::~slist() {
  while (head->next != NULL) {
    node *p = head->next;
    head->next = p->next;
    delete p;
  }
  delete head;

  head = NULL;
  tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
  tail->next = new node(din);
  tail = tail->next;
}

template <typename T>
void slist<T>::sort(const string &algname) {
  // determine number of list elements
  int n=0;
    for (iterator it = begin();it != end(); ++it){
      n++;
  }
  // set up smart pointer array called Ap
  vector<sptr> Ap;
  node *p= head;
  for (int i=0;i<n;i++){
    p=p->next;
    Ap.push_back(sptr(p));
  }
  // if quicksort, apply std::sort(...)
  if(strcmp(algname.c_str(),"-quicksort")==0){
      std::sort(Ap.begin(),Ap.end());
  }
    // if mergesort, apply std::stable_sort(...)
  if(strcmp(algname.c_str(),"-mergesort")==0){
    std::stable_sort(Ap.begin(),Ap.end());
  }
    // if qsort_r3, apply qsort_r3(...)
    if(strcmp(algname.c_str(),"-qsort_r3")==0){
      quicksort(Ap,0,n-1);
  }
// use sorted Ap array to relink list */
 node *l;
  l=head;
  for(int j=0;j<n;j++){
    l->next=Ap[j];
    l=l->next;
  }
  l->next=NULL;
}
#endif // SLIST_H
