//main関数　コンソールに表示

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "crane.h"
#include "nn.h"
#include "bat.h"

//my file structure(myfopen.c)
extern FILE *myfopen(char *fname, char *mode);

//control simulation(crane_control.c)
extern float crane_control_simulation(NEURON_w NCw);

//initial weights(cuckoo_search.c)
extern INDIVIDUAL rand_w(void);

// selection (ranking method)(cuckoo_search.c)
extern void sort(INDIVIDUAL kotai[]);

extern void bat_algorithm(INDIVIDUAL NC1, INDIVIDUAL NC2, INDIVIDUAL best_NC, int generation, double aveLoud,float Pulse_r1);

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
  INDIVIDUAL CS[IND_SIZE], new_BA, tmp;

  fp1=myfopen("e-cuckoo.dat","w");
  fpw=myfopen("w-cuckoo.dat","w");

  seed=8000;
  printf("seed=%d\n",seed);
  srand48(seed);
  
    for(ind=0;ind<IND_SIZE;ind++) {
      //init weights　ここでNS全体になる
      CS[ind]=rand_w();
      NCw=convert_weight(CS[ind]);
      // Control start
      CS[ind].E=crane_control_simulation(NCw);
    } 
    for(iteration=1;iteration<ITERATION;iteration++) {
      new_BA = bat_algorithm(int generation, double aveLoud, float Pulse_r1);
      NCw = convert_weight(new_BA);
      new_BA.E = crane_control_simulation(NCw);

    sort(CS);
    fprintf(fp1, "%.12f\n", CS[0].E);

    //表示している部分コンソールに
    printf("iteration=%d E[0]=%.12f\n", iteration, CS[0].E);
    }//end iteration
    //save conection weights
    for(j=0;j<J_MAX;j++)
      for(i=0;i<I_MAX;i++)
        fprintf(fpw, "%lf\n", CS[0].pji[J][I]);
    for(k=0;k<K_MAX;k++)
      for(j=0;j<J_MAX;j++)
        fprintf(fpw, "%lf\n", CS[0].pkj[K][J]);
    fclose(fp1);
    fclose(fpw);

    return 0;
  }
