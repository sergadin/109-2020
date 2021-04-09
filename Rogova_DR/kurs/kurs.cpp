
#include <math.h>
#include <iostream>
#include <cstdio>
#include "List.h"
template <class T>
class Graf
{
private:
 
   struct GrafNode
   {
      T value;
      List<GrafNode*> parents;
      List<GrafNode*> sons;
   };
 
   GrafNode first;
public:
   Graf<T> ();
  ~Graf ();
};

template<class T>
class GrafIterator
{
public:
  Graf<T>* tree;

  GrafIterator ();
  GrafIterator (Graf<T>*);

  void Root ();
  void CreateParent();
  void NextParent();
  void PreviousPar ();
  void FirstParent ();
  void LastParent ();
  void CreateSon (); 
  void NextSon();
  void PreviousSon (); 
  void FirstSon (); 
  void LastSon ();
  void InsertValue (T d); 
};



