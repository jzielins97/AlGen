#include "library.h"
#include <cmath>
//function defines all available products and returns number of products defined
int defineProducts(std::vector<Product*> *products){
  products->clear();
  // std::cout<<"Adding products"<<std::endl;
  int n = 0;
  products->push_back(new Product(660,39,690,49,29,18.59,"WHOOPER"));
  n++;
  products->push_back(new Product(740,46,1080,50,34,20.19,"WHOOPER with Cheese"));
  n++;
  products->push_back(new Product(810,50,1710,53,37,20.89,"BBQ Bacon WHOOPER"));
  n++;
  products->push_back(new Product(830,52,1390,50,41,23.59,"Bacon and Cheese WHOOPER"));
  n++;
  products->push_back(new Product(900,57,760,49,49,21.59,"Double WHOOPER"));
  n++;
  products->push_back(new Product(980,64,1150,50,53,24.59,"Double WHOOPER with Cheese"));
  n++;
  products->push_back(new Product(1140,75,840,49,68,24.89,"Triple WHOOPER"));
  n++;
  products->push_back(new Product(1220,81,1220,50,73,25.89,"Triple WHOOPER with Cheese"));
  n++;
  products->push_back(new Product(320,19,400,27,14,15.59,"WHOOPER JR."));
  n++;
  products->push_back(new Product(380,23,710,27,16,26.59,"WHOOPER JR. with Cheese"));
  n++;
  products->push_back(new Product(310,12,290,46,3,2.59,"Fries small"));
  n++;
  products->push_back(new Product(400,16,380,60,4,5.90,"Fries medium"));
  n++;
  products->push_back(new Product(500,20,470,75,5,6.90,"Fries big"));
  n++;
  products->push_back(new Product(380,22,860,31,2,6.50,"Mozzarella Sticks (4 pieces)"));
  n++;
  products->push_back(new Product(230,16,530,8,18,10.48,"BLT Garden Salad"));
  n++;
  products->push_back(new Product(330,24,730,14,1,8.75,"Caesar Garden Fresh Salad"));
  n++;


  return n;
}

void cross(int iN, int iC, Chromosome** ch, int t1, int t2, int iCal, int iFat, int iSod, int iCarb, int iProt, std::vector<Product*>* products){
  Chromosome *tmp1 = new Chromosome(ch[t1]);
  Chromosome *tmp2 = new Chromosome(ch[t2]);
  //wybor chromosomu
  int x = (rand() % iC) ;
  int y = (rand() % iC) ;
	//wybor miejsca
	int i = (rand() % (iN-1)) +1;
  int c = 0;

  int **a = tmp1->getC();
  int **b = tmp2->getC();
	for(int j=0; j<i; j++){
    c = a[x][j];
		a[x][j]=b[y][j];
		b[y][j]=c;
	}
  double f1 = goalFunction(iCal, iFat, iSod, iCarb, iProt, tmp1, products);
  double f2 = goalFunction(iCal, iFat, iSod, iCarb, iProt, tmp2, products);

  if(f1 < ch[t1]->getGoalFunction() && f1 < ch[t2]->getGoalFunction()){
    ch[t1] = new Chromosome(tmp1);
    ch[t2] = new Chromosome (tmp2);
  }else if(f2 < ch[t1]->getGoalFunction() && f2 < ch[t2]->getGoalFunction()){
    ch[t1] = new Chromosome(tmp1);
    ch[t2] = new Chromosome (tmp2);
  }
}

double goalFunction(int iCal, int iFat, int iSod, int iCarb, int iProt, Chromosome* c, std::vector<Product*>* products){
  double f_min = 0;
  double* f = new double[c->ic];

  for(int i=0; i<c->ic;i++){
    int cal = 0, fat = 0, sod = 0, carb = 0, prot = 0;
    int sum=0; //sum of all products in the chromosome to see if it is not empty
    double price = 0, k = 0;
    double wMinus = 8, wPlus = 5; //weights for punishment for case bellow given value (minus) and above given value (plus)
    double lower = 0.95, upper = 1.1; //treshold for the weights
    f[i] = 0;
    for(int ij=0; ij<c->N; ij++){
      cal += c->get(i,ij) * products->at(ij)->getCal();
      fat += c->get(i,ij) * products->at(ij)->getFat();
      sod += c->get(i,ij) * products->at(ij)->getSod();
      carb += c->get(i,ij) * products->at(ij)->getCarb();
      prot += c->get(i,ij) * products->at(ij)->getProt();
      price += c->get(i,ij) * products->at(ij)->getPrice();
      sum += c->get(i,ij);
    }

    f[i] = sqrt( pow(1.0*(iCal-cal)/iCal,2) + pow(1.0*(iFat-fat)/iFat,2) +
                 pow(1.0*(iSod-sod)/iSod,2) + pow(1.0*(iCarb-carb)/iCal,2) +
                 pow(1.0*(iProt-prot)/iProt,2) + pow(price,2));

    if(1.0*cal/iCal < lower){
      k += wMinus*(iCal-cal)/iCal;
    }else if(1.0*cal/iCal > upper){
      k += wPlus*(cal-iCal)/iCal;
    }

    if(1.0*fat/iFat < lower){
      k += wMinus*(iFat-fat)/iFat;
    }else if(1.0*fat/iFat > upper){
      k += wPlus*(fat-iFat)/iFat;
    }

    if(1.0*sod/iSod < lower){
      k += wMinus*(iSod-sod)/iSod;
    }else if(1.0*sod/iSod > upper){
      k += wPlus*(sod-iSod)/iSod;
    }

    if(1.0*carb/iCarb < lower){
      k += wMinus*(iCarb-carb)/iCarb;
    }else if(1.0*carb/iCarb > upper){
      k += wPlus*(carb-iCarb)/iCarb;
    }

    if(1.0*prot/iProt < lower){
      k += wMinus*(iProt-prot)/iProt;
    }else if(1.0*prot/iProt > upper){
      k += wPlus*(prot-iProt)/iProt;
    }

    if(sum == 0) k+=50;
    f[i] += k;

    std::cout<<"\tif "<<i;
    if(i==0) f_min = f[i];
    else if (f[i] < f_min) f_min = f[i];
    std::cout<<" ..."<<std::endl;
  }



  c->goal = f_min;
  return f_min;

}

void selection(Chromosome **pop, int N){
  double A=0;
  double sum=0;
  double * D = new double[N+1];
  Chromosome **tmp = new Chromosome *[N];

  D[0]=0;
  D[N]=1;
  for(int i=0;i<N;i++){
    if(pop[i]->getGoalFunction() > A) A=pop[i]->getGoalFunction() + 5;
  }
  // std::cout<<A<<std::endl;
  for(int i=0;i<N;i++){
    tmp[i] = new Chromosome(pop[i]);
    D[i+1] = A-pop[i]->getGoalFunction();
    sum+=pop[i]->getGoalFunction();
  }
  for(int i=1;i<N;i++){
    D[i] = D[i-1] + D[i] / sum;
  }
  for(int i=0;i<N;i++){
    double rnd= 1.0*rand()/RAND_MAX;
    int j = 1 ;
    while(rnd>D[j]){
      j++;
    }
    j--;
    //std::cout<<pop[i]->getGoalFunction();
    pop[i] = new Chromosome(tmp[j]);
    //std::cout<<" "<<pop[i]->getGoalFunction()<<std::endl;
  }
}
