#include "library.h"
#include <cstdlib>

int main(int argv, char** argc){
  int CALORIES, FAT, CARBS, SODIUM, PROTEIN;
  int ic; //1 - haploidal, 2 - diploidal
  int N = 50; //in generation

  ic = 1;
  CALORIES = 2285;
  FAT = 76;
  SODIUM = 6000;
  CARBS = 314;
  PROTEIN = 86;
  N = 50;

  if(argv > 1){
    N = atoi(argc[1]);
  }
  if(argv > 2){
    ic = atoi(argc[2]);
  }
  if(argv > 3){
    CALORIES = atoi(argc[3]);
  }
  if(argv > 4){
    FAT = atoi(argc[4]);
  }
  if(argv > 5){
    SODIUM = atoi(argc[5]);
  }
  if(argv > 6){
    CARBS = atoi(argc[6]);
  }
  if(argv > 7){
    PROTEIN = atoi(argc[7]);
  }

  printf("N=%d, ic=%d, CAL=%d, FAT=%d, SOD=%d, CARB=%d, PROT=%d, GEN_MAX=%d\n", N, ic, CALORIES, FAT, SODIUM, CARBS, PROTEIN, GEN_MAX);

  int nProducts; //number of products (length of a chromosome)
  std::vector<Product*> *products = new std::vector<Product*>();

  srand(time(NULL));

  nProducts = defineProducts(products);
  // std::cout<<"Defined products"<<std::endl;

  Chromosome **c;
  c = new Chromosome*[N];
  for(int i=0; i<N; i++){
    c[i] = new Chromosome(nProducts, ic);
    goalFunction(CALORIES, FAT, SODIUM, CARBS, PROTEIN, c[i], products);
    //if(i%1000==0)c[i]->print();
  }
  // std::cout<<"Creating chromosomes"<<std::endl;

  // Chromosome *c1;
  // std::cout<<"Testing ------------------------"<<std::endl;
  // for(int i=0; i<1; i++){
  //   c1 = new Chromosome(nProducts, ic, i, 1);
  //   goalFunction(CALORIES, FAT, SODIUM, CARBS, PROTEIN, c1, products);
  //   c1->print();
  //   delete c1;
  // }
  // std::cout<<"-------------------testing ended"<<std::endl;

  const clock_t begin_time = clock();
  int i=0;
  int no_change = 0;
  do{

    // std::cout<<i<<"------------------"<<no_change<<std::endl;
    int nCross = rand() % N; //number of crossings to perfom
    for(int ij=0;ij<nCross;ij++){ //crossing loop
      int iCross1 = rand() % N;
      int iCross2 = rand() % N;
      cross(nProducts, ic, c, iCross1, iCross2, CALORIES, FAT, SODIUM, CARBS, PROTEIN, products);
      //goalFunction(CALORIES, FAT, SODIUM, CARBS, PROTEIN, c[q], products);
    }
    // int nMutate = rand() % N;//number of mutations to perform
    for(int ij=0; ij<N; ij++){//mutation loop
      std::cout<<i;
      c[ij]->mutate();
      std::cout<<" "<<ij<<" goalFunction ";
      goalFunction(CALORIES, FAT, SODIUM, CARBS, PROTEIN, c[ij], products);
      std::cout<<" done"<<std::endl;
    }
    std::cout<<"Selection";
    selection(c, N);
    std::cout<<"\tdone"<<std::endl;

    no_change++;
    for(int ij=0; ij<N-1; ij++){
      if(abs(c[ij]->getGoalFunction() - c[ij+1]->getGoalFunction()) > 0.0001){
        no_change = 0;
        // std::cout<<j<<std::endl;
        break;
      }
    }
    i++;
  }while(i<50000 && no_change<10);

  std::cout<<std::endl<<"After AG ("<<i<<"-iterations):"<<std::endl;
  for(int i=0;i<1;i++){
    c[i]->print(products);
  }

  std::cout<<"AG time: "<<float( clock() - begin_time ) / CLOCKS_PER_SEC<<"s"<<std::endl;
  return 0;
}
