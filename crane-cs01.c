/* ########################################
   ### Rotary crane system 
   ### NC optimized by Cuckoo Search(CS) method.
   ### Evolution simulation in 1 trial.
   ### Compile: gcc -O2 -o crane-cs01 crane-cs01.c myfopen.c 
   crane_3dmodel.C neural_network.c cuckoo_search.c crane_control.c -lm
   ### programmed by nakazono. [2021/09/17]
   ######################################## */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "crane.h"
#include "nn.h"
#include "cuckoo.h"

//my file structure(myfopen.c)
extern FILE *myfopen(char *fname, char *mode);

//control simulation(crane_control.c)
extern float crane_control_simulation(NEURON_w NCw);

//initial weights(cuckoo_search.c)
extern INDIVIDUAL rand_w(void);

// selection (ranking method)(cuckoo_search.c)
extern void sort(INDIVIDUAL kotai[]);

//levy flight(cuckoo_search.c)
extern INDIVIDUAL levy_flight(INDIVIDUAL CS_r1, float alpha, float beta);

// convert CS into NC weights(cuckoo_search.c)
extern NEURON_w convert_weight(INDIVIDUAL CS);

int main(void)
{
  FILE *fp1, *fpw;
  int seed, iteration, ind, i, j, k, r1, r2;
  float alpha=0.1, beta=1.5;
  NEURON_w NCw;
  INDIVIDUAL CS[IND_SIZE], new_CS, tmp;

  fp1=myfopen("e-cuckoo.dat","w");
  fpw=myfopen("w-cuckoo.dat","w");

  seed=8000;
  printf("seed=%d\n",seed);
  srand48(seed);
  
 //Evolution simulation start
 //initial connection weights
    for(ind=0;ind<IND_SIZE;ind++) {
      //init weights
      CS[ind]=rand_w();
      NCw=convert_weight(CS[ind]);
      // Control start
      CS[ind].E=crane_control_simulation(NCw);
  } // end individual
  // selection (ranking method)
  sort(CS);
  for(iteration=1;iteration<ITERATION;iteration++) {
    //Sceduled CS
    if(iteration<=2000)
            beta=0.5;
    else if(iteration<=4000)
      beta=1.0;
    else if(iteration<=6000)
      beta=1.5;
    else
      beta=2.0;
    //brood parasitism
    r1=(int)drand48() % IND_SIZE;
    r2=(int)(r1+(drand48()/(IND_SIZE-1)+1))%IND_SIZE;
    new_CS=levy_flight(CS[r1],alpha,beta);
    NCw=convert_weight(new_CS);
    new_CS.E=crane_control_simulation(NCw);
    if(new_CS.E<CS[r2].E){
      tmp=CS[r2];
      CS[r2]=new_CS;
      new_CS=tmp;
    }
    //abondan
    for(ind=(int)(IND_SIZE*(1-ABA_RATE));ind<IND_SIZE;ind++){
      CS[ind]=rand_w();
      NCw=convert_weight(CS[ind]);
      CS[ind].E=crane_control_simulation(NCw);
    }
    sort(CS);
    fprintf(fp1, "%.12f\n", CS[0].E);
    printf("iteration=%d E[0]=%.12f\n", iteration, CS[0].E);
    }//end iteration
    //save conection weights
    for(j=0;j<J_MAX;j++)
      for(i=0;i<I_MAX;i++)
        fprintf(fpw, "%lf\n", CS[0].whid[i][j]);
    for(k=0;k<K_MAX;k++)
      for(j=0;j<J_MAX;j++)
        fprintf(fpw, "%lf\n", CS[0].wout[j][k]);
    fclose(fp1);
    fclose(fpw);

    return 0;
  }//end main
