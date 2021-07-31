#include <math.h>
#include <iostream>
#include <cstdio>
#include <utility>
#include "List.h"

template <class T>
class Graf
{
private:
 
   struct GrafNode
   {
      T value;
      List<GrafNode*> parents;
      List<pair<int, GrafNode*>> sons;
   };
   GrafNode first;
public:
   Graf()
   {	   
   };
  ~Graf ();
  int EdgeValueL(GrafNode * first, GrafNode * second);

};

template<class T>
class GrafIterator
{
public:
  Graf<T>* g;

  GrafIterator ();
  GrafIterator (Graf<T>*);

  void Root ();
  void CreateParent(T value, int Edge);
  void NextParent();
  void PreviousPar ();
  void FirstParent ();
  void LastParent ();
  void CreateSon (T value, int Edge); 
  void NextSon();
  void PreviousSon (); 
  void FirstSon (); 
  void LastSon ();
  void InsertValue (T d); 
};

template <class T>
class M
{
private:
	Graf<T> *G;
        List<T> value;
	M * prev;
public:
	M();
	M(Graf<T> * G, M *prev, int t);
	~M();
	List<T> * getValue();
};


