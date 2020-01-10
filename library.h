#ifndef LIBRARY_H_
#define LIBRARY_H_

#define MUTATION 0.02
#define GEN_MAX 2 //values for gen <0,MAX_GEN)

#include <vector>
#include <string>
#include <iostream>

class Product{ //class for each product
private:
  int calories,fat,sodium,carbs,protein;
  double price;
  std::string name;
public:
  Product();
  Product(Product* p);
  Product(int iCal,int iFat, int iSod, int iCar, int iProt, double iPrice, std::string iName);
  //getters
  int getCal();
  int getFat();
  int getSod();
  int getCarb();
  int getProt();
  std::string getName();
  double getPrice();
};

class Chromosome{
private:
  int **c;
  int ic;
  int N;
  double goal;

public:
  //constructors
  Chromosome();
  Chromosome(int iN, int iC);
  Chromosome(int iN, int iC, int item, int t);
  Chromosome(Chromosome* c);
  //getters:
  int get(int i, int j);
  int** getC();
  double getGoalFunction();
  //functions
  void print();
  int mutate();
  //befriended functions
  friend void cross(int iN, int ic, int **a, int **b);
  friend double goalFunction(int iCal, int iFat, int iSod, int iCarb, int iProt, Chromosome* c, std::vector<Product*>* products);
  //friend void selection(Chromosome **pop, int N);

};

//other functions
int defineProducts(std::vector<Product*> *products);
void cross(int iN, int iC, int **a, int **b);
void selection(Chromosome **pop, int N);

#endif /* end of include guard: LIBRARY_H_ */
