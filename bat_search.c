#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>

#include "crane.h" 
#include "nn.h" 
#include "bat.h"

//normal random number
float rand_n(void)
{
    return sqrt(-2.0*log(drand48()))*cos(2.0*PI*drand48());
}

float sigma(float beta)
{
    float nume,denom;
    nume = tgamma(1.0+beta)*sin(PI*beta/2.0);
    denom = tgamma((1.0+beta)/2.0)*beta*pow(2.0,
    (beta-1.0)/2);
             return pow(nume/denom,1.0/beta);
}

//initial weights　　型が構造体　　initがNC１コ　rand_wが全体
INDIVIDUAL rand_w(void)
{
    int i,j,k;
    INDIVIDUAL init;

    for(j=0;j<J_MAX;j++){
        for(i=0;i<I_MAX;i++){

    init.pji[J][I]=(float)(drand48()*(2.0*XMAX)-XMAX);
                          }
                }
                for(k=0;k<K_MAX;k++){
                         for(j=0;j<J_MAX;j++){
    init.pkj[K][J]=(float)(drand48()*(2.0*XMAX)-XMAX);
                          }
                }

                return init;
}

//selection(ranking method)
void sort(INDIVIDUAL kotai[IND_SIZE])
{
          int i,j,k,o,m;
          INDIVIDUAL tmp;

          for(o=0;o<IND_SIZE-1;o++){
              for(m=IND_SIZE-1;m>0;m--){
                  if(kotai[m-1].E>kotai[m].E){
                      tmp=kotai[m-1];
                      kotai[m-1]=kotai[m];
                      kotai[m]=tmp;
                  }
              }
          }
}

//convert CS into NC weights
NEURON_w convert_weight(INDIVIDUAL CS)
{
    int i,j,k;
    NEURON_w NCw;
    for(j=0;j<J_MAX;j++)
             for(i=0;i<I_MAX;i++)
                       NCw.n_ij[i][j]=CS.pji[J][I];
    for(j=0;j<J_MAX;j++){
             for(k=0;k<K_MAX;k++){
                       NCw.n_jk[j][k]=CS.pkj[K][J];
             }
    }
    return NCw;
}

//最良,良い,ランダムの方向に移動するコウモリ
INDIVIDUAL bat_algorithm(int generation, double aveLoud, float Pulse_r1)
{
	int i, j, k;
	INDIVIDUAL new_NC1, new_NC2, tmp_NC;
    //最良のコウモリ
	new_NC1.freq=(Freq_Max-Freq_Min)*rand()/RAND_MAX;
    //入力層から中間層
	for(j=0;j<J;j++) {
		for(i=0;i<I;i++) {
			new_NC1.vji[j][i]+=(new_NC2.pji[j][i]-new_NC2.pji[j][i])*new_NC1.freq;
			new_NC1.pji[j][i]+=new_NC1.vji[j][i];
			//NC1.freq=*(best_NC.freq);
			
		}
	}
    //中間層から出力層
	for(k=0;k<K;k++) {
		for(j=0;j<J;j++) {
			new_NC1.vkj[k][j]+=(new_NC2.pkj[k][j]-new_NC2.pkj[k][j])*new_NC1.freq;
			new_NC1.pkj[k][j]+=new_NC1.vkj[k][j];
			//NC1.freq=(best_NC.freq);
		}
	}
    
	// NC1=control_simulation(NC1);
	// if(isnan(NC1.E)) {
	// 	NC1.E=DBL_MAX;
	// }
	
    //良いコウモリ
	//if(0.01> NC1.pulse) {
	if(rand()/RAND_MAX > new_NC1.pulse) {		
		// new_NC1=init_NC1();
		new_NC1.loudness=Loud_0*pow(Loud_r,0.1*(double)generation);	
		new_NC1.pulse=Pulse_0*(1.0-exp(-Pulse_r*(double)Pulse_r1*(double)generation));
		//中間層
		for(j=0;j<J;j++) {
			for(i=0;i<I;i++) {
				new_NC1.pji[j][i]=new_NC2.pji[j][i]+(rand()/(RAND_MAX/2.0)-1)*aveLoud;
				new_NC1.vji[j][i]=new_NC2.vji[j][i];
				//new_NC1.freq=NC2.freq;
				//new_NC1.pulse=NC2.pulse;
				//new_NC1.loudness=(NC2.loudness);
			}
		}
		//出力層
		for(k=0;k<K;k++) {
			for(j=0;j<J;j++) {
				new_NC1.pkj[k][j]=new_NC2.pkj[k][j]+(rand()/(RAND_MAX/2.0)-1)*aveLoud;
				new_NC1.vji[k][j]=new_NC2.vji[k][j];
				//new_NC1.freq=NC2.freq;
				//new_NC1.pulse=NC2.pulse;
				//new_NC1.loudness=(NC2.loudness);
			}
		}
		// new_NC1=control_simulation(new_NC1);
		// if(isnan(new_NC1.E)) {
		// 	new_NC1.E=DBL_MAX;
		// }
	} else {
		// new_NC1.E=DBL_MAX;
		// new_NC1.Ey=DBL_MAX;
		// new_NC1.Et=DBL_MAX;
	}
	// new_NC2=init_NC1();
	new_NC2.loudness=Loud_0*pow(Loud_r,0.1*(double)generation);	
	new_NC2.pulse=Pulse_0*(1.0-exp(-Pulse_r*Pulse_r1*(double)generation));
	// new_NC2=control_simulation(new_NC2);
	if(isnan(new_NC2.E)) {
		new_NC2.E=TMP_MAX;
	}
	
    //パルス率を更新
	// if(((new_NC1.E<NC1.E) || (new_NC2.E<NC1.E)) && ((rand()/RAND_MAX)<NC1.loudness)) {
	// 		if(new_NC1.E<new_NC2.E) {
	// 			tmp_NC=NC1;
	// 		NC1=new_NC1;
	// 		new_NC1=tmp_NC;
	// 	} else {
	// 		tmp_NC=NC1;
	// 		NC1=new_NC2;
	// 		new_NC2=tmp_NC;
	// 	}
	// 	//NC1.pulse=Pulse_0*(1.0-exp(-Pulse_r*(double)generation));
	// 	//NC1.loudness*=Loud_r;
	// }
	return new_NC1;
}
