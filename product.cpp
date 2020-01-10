#include "library.h"
#include <algorithm>

Product::Product(){
}

Product::Product(int iCal,int iFat, int iSod, int iCar, int iProt, double iPrice, std::string iName){
  calories = iCal;
  fat  = iFat;
  sodium = iSod;
  carbs = iCar;
  protein = iProt;
  price = iPrice;
  name = iName;
}

Product::Product(Product* p){
  name = p->getName();
  price = p->getPrice();
  calories = p->getCal();
  fat = p->getFat();
  carbs = p->getCarb();
  sodium = p->getSod();
  protein = p->getProt();
}
int Product::getCal(){
  return calories;
}

int Product::getFat(){
  return fat;
}

int Product::getSod(){
  return sodium;
}

int Product::getCarb(){
  return carbs;
}

int Product::getProt(){
  return protein;
}

std::string Product::getName(){
  return name;
}

double Product::getPrice(){
  return price;
}

Chromosome::Chromosome(){
}

Chromosome::Chromosome(int iN, int iC){
  N = iN;
  ic = iC;
  c = new int*[ic];
  for(int i=0; i<ic; i++){
    c[i] = new int[N];
    for(int ij=0;ij<N;ij++){
      int tmp = (int)GEN_MAX;
      c[i][ij] = rand() % tmp;
    }
  }
  goal = 0;
}

Chromosome::Chromosome(int iN, int iC, int item, int t){
  N = iN;
  ic = iC;
  c = new int*[ic];
  for(int i=0; i<ic; i++){
    c[i] = new int[N];
    for(int ij=0;ij<N;ij++){
      if(ij==item) c[i][ij] = t;
      else c[i][ij] = 0;
    }
  }
  goal = 0;
}

Chromosome::Chromosome(Chromosome* chrom){
  N = chrom->N;
  ic = chrom->ic;
  c = new int*[ic];
  for(int i=0; i<ic; i++){
    c[i] = new int[N];
    for(int ij=0;ij<N;ij++){
      c[i][ij] = chrom->get(i,ij);
    }
  }
  goal = chrom->goal;
}

int Chromosome::get(int i, int j){
  return c[i][j];
}

int** Chromosome::getC(){
  return c;
}

double Chromosome::getGoalFunction(){
  return goal;
}

void Chromosome::print(){
  for(int i=0; i<N; i++){
    for(int ij=0; ij<ic; ij++){
      std::cout<<c[ij][i]<<" ";
    }
    std::cout<<std::endl;
  }
  std::cout<<"f="<<goal<<std::endl<<std::endl;
}

void Chromosome::print(std::vector<Product*>* products){
  for(int i=0; i<N; i++){
    for(int ij=0; ij<ic; ij++){
      std::cout<<c[ij][i]<<" ";
    }
    std::cout<<"\t"<<products->at(i)->getName()<<std::endl;
  }
  std::cout<<"f="<<goal<<std::endl<<std::endl;
}

int Chromosome::mutate(){
  if(1.0*rand()/RAND_MAX <= MUTATION){
    int i = rand() % N;
    int j = rand() % ic;
    // std::cout<<j<<" "<<i;
    if(rand() % 2){
      c[j][i]++;
      if(c[j][i] > GEN_MAX-1){
        c[j][i] = 0;
      }
    }
    else{
      c[j][i]--;
      if(c[j][i] < 0){
        c[j][i] = GEN_MAX-1;
      }
    }
    return 1;
  }
  return 0;
}
