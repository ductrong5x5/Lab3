/*  
  Name            : Duc Trong Nguyen
  NetId           : 000 657421
  DOB             : Nov 20 1998
  Lab description : Sorting the multi-column data. Data will now be stored in single linked list. A smart pointer subclass within the single linked list class 
  will be embed
*/
//header will be used
#include <iostream>
#include <cstring>
#include <iomanip> 
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#include "Slist.h"
//declare class data
class data { 
  public:
    //overloaded operator>> and operator<<
    friend istream & operator>>(istream &, data &);
    friend ostream & operator<<(ostream &, const data &);
    // operator< using lastname, firstname, phone number
    friend bool operator< ( const data& a,const data& b) {
      if(a.lastname==b.lastname){
        if(a.firstname==b.firstname)
          return a.phonenum<b.phonenum;
        else 
          return a.firstname<b.firstname;
      }
      else
        return a.lastname<b.lastname;
    }
    
  private:
    string firstname;
    string lastname;
    string phonenum; 
    int ID;
  };
istream & operator>> (istream &in, data &r) {   
  string firstname;
  string lastname;
  string phonenum;
  in>>firstname>>lastname>>phonenum;
  //check eof()
  if(!in.eof()){
    r.firstname=firstname;
    r.lastname=lastname;
    r.phonenum=phonenum;
    r.ID+=1;
  }
  return in; 
  }
ostream & operator<< (ostream &out, const data &r) {   
  out<<" "<<setw(25)<<left<<r.lastname +" "+ r.firstname;
  out<<setw(8)<<right<<r.phonenum<<setw(9)<<right<<r.ID;
  return out;
}

template <typename T>
void quicksort(std::vector<T> &A, int left,int right) {
  if (left < right) {
   
    //create random index
    int random = left + rand() % (right - left+1);
    //cout<<"randoM:"<<random<<endl;
    //swap data at random index to the right
    swap(A[random], A[right]);
    //make pivot to the rightmake
    T pivot = A[right]; 
    int i = left - 1;
    int j = right;
    //condition for while loop
    while(left<right){
      //find the first larger data than pivot from the left
      while(A[++i]<pivot){}
      //find the first smaller data than pivot from the right
      while(pivot<A[--j])
        //Stop this loop if j go out of bound
        if(j==left)
          break;
      //stop bigger loop when i >= j
      if(i>=j)
        break;
      swap(A[i], A[j]);
    }
    //swap pivot to it proper place
    swap(A[i],A[right]);
    //traverse from left to pivot, move all data equal to pivot next to pivot
    int m=left;
    for(int a=left;a<i;a++){
      if(A[a]<A[i]){
        swap(A[a],A[m]);
        m++;
      }
    }
    //traverse from right to pivot, move all data equal to pivot next to pivot
    int n=right;
    for(int b=right;b>i;b--){
      if(A[i]<A[b]){
        swap(A[b],A[n]);
        n--;
      }
    }
    //recursion quicksort from left to data < pivot
    quicksort(A, left, m-1);
    //recursion quicksort from data > pivot to right
    quicksort(A, n+1, right);
  }
}
//print the list
template <typename T>
void printlist(T p0, T p1) { 
  for (T it = p0;it != p1; ++it){
  cout<<(*it)<<endl;
  }
}  
int main(int argc, char *argv[]) {
  //Testing usage for invalid arguments
  if(argc != 3 ){
    cerr << "usage: " << argv[0]
    << " -mergesort|-quicksort|-qsort_r3 file.txt\n";
    return 0;
  }
  else if ( strcmp(argv[1],"-mergesort" )!=0  &&  strcmp(argv[1],"-quicksort")!=0  &&  strcmp(argv[1],"-qsort_r3")!=0 ) {
    cerr << "usage: " << argv[0]
    << " -mergesort|-quicksort|-qsort_r3 file.txt\n";
    return 0;
  }
  ifstream fin;
   // open input file
  fin.open(argv[argc-1]);
  //declare single-linked list
  slist<data> A;
  data din;
  //put data from input file into list
  while (fin >> din){
    A.push_back(din);
  }
  // close input file
  fin.close();
  //call sort
  A.sort(argv[1]);
  //print list
  printlist(A.begin(), A.end());
}
