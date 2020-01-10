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

  return n;
}

void cross(int iN, int iC, int **a, int **b){
	//wybor chromosomu

	int x = (rand() % iC) ;
	int y = (rand() % iC) ;
	//wybor miejsca
	int i = (rand() % (iN-1)) +1;
  int c = 0;
	for(int j=0; j<i; j++){
    c = a[x][j];
		a[x][j]=b[y][j];
		b[y][j]=c;
	}
}

double goalFunction(int iCal, int iFat, int iSod, int iCarb, int iProt, Chromosome* c, std::vector<Product*>* products){
  double f_min = 0;
  double* f = new double[c->ic];

  for(int i=0; i<c->ic;i++){
    int cal = 0, fat = 0, sod = 0, carb = 0, prot = 0;
    double price = 0, k = 0;
    double wMinus = 5.0, wPlus = 2.0; //weights for punishment for case bellow given value (minus) and above given value (plus)
    f[i] = 0;
    for(int ij=0; ij<c->N; ij++){
      cal += c->get(i,ij) * products->at(ij)->getCal();
      fat += c->get(i,ij) * products->at(ij)->getFat();
      sod += c->get(i,ij) * products->at(ij)->getSod();
      carb += c->get(i,ij) * products->at(ij)->getCarb();
      prot += c->get(i,ij) * products->at(ij)->getProt();
      price += c->get(i,ij) * products->at(ij)->getPrice();
    }

    f[i] = sqrt( pow(1.0*(iCal-cal)/iCal,2) + pow(1.0*(iFat-fat)/iFat,2) +
                 pow(1.0*(iSod-sod)/iSod,2) + pow(1.0*(iCarb-carb)/iCal,2) +
                 pow(1.0*(iProt-prot)/iProt,2) + pow(price,2));

    if(cal-iCal < 0){
      if( 1.0*(iCal-cal)/iCal > 0.1){
        k += wMinus*(iCal-cal)/iCal;
      }
    }else if(1.0*(cal-iCal)/iCal > 0.2){
      k += wPlus*(cal-iCal)/iCal;
    }

    if(fat-iFat < 0){
      if( 1.0*(iFat-fat)/iFat > 0.1){
        k += wMinus*(iFat-fat)/iFat;
      }
    }else if(1.0*(fat-iFat)/iFat > 0.2){
      k += wPlus*(fat-iFat)/iFat;
    }

    if(sod-iSod < 0){
      if( 1.0*(iSod-sod)/iSod > 0.1){
        k += wMinus*(iSod-sod)/iSod;
      }
    }else if(1.0*(sod-iSod)/iSod > 0.2){
      k += wPlus*(sod-iSod)/iSod;
    }

    if(carb-iCarb < 0){
      if( 1.0*(iCarb-carb)/iCarb > 0.1){
        k += wMinus*(iCarb-carb)/iCarb;
      }
    }else if(1.0*(carb-iCarb)/iCarb > 0.2){
      k += wPlus*(carb-iCarb)/iCarb;
    }

    if(prot-iProt < 0){
      if( 1.0*(iProt-prot)/iProt > 0.1){
        k += wMinus*(iProt-prot)/iProt;
      }
    }else if(1.0*(prot-iProt)/iProt > 0.2){
      k += wPlus*(prot-iProt)/iProt;
    }
    f[i] += k;

    if(i==0) f_min = f[i];
    else if (f[i] < f_min) f_min = f[i];
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
    int j = 0;
    while(rnd>D[j]){
      j++;
    }
    j--;
    //std::cout<<pop[i]->getGoalFunction();
    pop[i] = new Chromosome(tmp[j]);
    //std::cout<<" "<<pop[i]->getGoalFunction()<<std::endl;
  }
}
