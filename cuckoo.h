// Cuckoo parameters 
#define ITERATION 10000  //iteration
#define ABA_RATE 0.1      //abandon rate
#define IND_SIZE 100    //INDIVIDUAL size
#define ALPHA2 0.1        //step length parameter
#define BETA2 1.5         //scaling index 
#define XMAX 1.0

// individual of cuckoo(NC)
typedef struct{ 
           float whid[I_MAX][J_MAX]; 
           float wout[J_MAX][K_MAX]; 
    float E;
}INDIVIDUAL;git