/*
ABOUT: 

FULLY CONNECTED NEURAL NETWORK 
3-Layer (784 * 15 * 10) 

*/ 

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#define ROW 28 
#define COL 28
#define number_hlayers 3

#include "mnist_cpp_2.h" 
#include <iostream>
#include <string> 
#include <iomanip> 
#include<cstdlib> 

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

double sample_normal_distribution(){
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sample_normal_distribution();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
} 

double sigmoid(double x) { return 1.0f / (1.0f + exp(-x)); }

double dSigmoid(double x) { return x * (1.0 - x); }


// Initialise 2D array
void intialiseweights(int m, int n, double * arr) 
{ 
    int i, j; 
    for (i = 0; i < m; i++) 
      for (j = 0; j < n; j++) {
       arr[ (m*i)+ j]  = sample_normal_distribution(); 
    } 
} 
  
//Intialise 1D array 
void intialisebias(int m,  double * arr) 
{ 
    int i; 
    for (i = 0; i < m; i++) 
        arr[i] = sample_normal_distribution(); 
} 
   

// Set 2D array to zero
void reseteweights(int m, int n, double * arr) 
{ 
    int i, j; 
    for (i = 0; i < m; i++) 
      for (j = 0; j < n; j++) {
       arr[(m*i)+ j]  =  0; 
    } 
} 

// Set 1D array to zero
void resetbias(int m,  double * arr) 
{ 
    int i; 
    for (i = 0; i < m; i++) 
        arr[i] = 0.0; 
} 

// Calculate the forward pass 
void forwardpass (int m, int n, double * weight , double * bias, double * image_data ,double * output)
{
    int i,j;
    double kdash;
    for (i=0; i < m ; i++){
    kdash = 0.0; 
    for(j=0; j < n; j++){
        kdash += weight[(m*i)+ j] * image_data[j];
    }
    output[i] = sigmoid(kdash + bias[i]);
    }
}
 
//Calculate the change in weight/bais
void changewb(int m , int n, double * weight, double * bias, double * deltaweight, double * deltabias){
    int i,j;
	double lr = 0.01/10.0;    
    for (i=0; i < m ; i++){
        for(j = 0;  j < n ; j++)
        {
            weight[ (m*i)+ j] = (weight[ (m*i)+ j] - (lr * deltaweight[(m*i)+ j]));  
        }
     bias[i] = (bias[i]  - (lr * deltabias[i]));
    }
}
 

int hiddden_layer = 0; 

int main(int argc, char** argv)
{
   // get the input size from the command line
   if (argc < 2)
   {
      std::cerr << "expected: hidden layer size <hiddden_layer>\n";
      return 1;
   }
   hiddden_layer = std::atoi(argv[1]); 

    double time_spent; 
    clock_t begin = clock();    
    /*
    ---------------------------------------------------------------------------- 
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------
    */ 

   	/*
   		Load Data 
	*/

    int i = 0; 
    int row_test = 10000;   
    int row_train = 60000;
    int input_size = 784; 

    double ** train_image = new double*[row_train];
    for(int i = 0; i < row_train; ++i) {
        train_image[i] = new double[input_size];
    }  

    int ** train_label = new int*[row_train];
    for(int i = 0; i < row_train; ++i) {
        train_label[i] = new int[10];
    }   

    double ** test_image = new double*[row_test];
    for(int i = 0; i < row_test; ++i) {
        test_image[i] = new double[input_size];
    }  

    int ** test_label = new int*[row_test];
    for(int i = 0; i < row_test; ++i) {
        test_label[i] = new int[10];
    }    


    ReadMNIST(row_train,input_size,train_image);
    ReadMNISTTest(row_test,input_size,test_image);

    ReadMNISTTrainlabel(row_train, input_size ,train_label); 
    ReadMNISTTestlabel(row_test, input_size ,test_label);
    
        
    /*
    ---------------------------------------------------------------------------- 
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------
    */  
	/*
		Set Variables 
	*/ 

    const int epochs  = 1;
    int j; 
    double kdash;

    // weights
    int layers[number_hlayers]=  {784, hiddden_layer, 10};
 
    double * weight1 = new double[layers[1] * layers[0]];
    double * weight2 = new double[layers[2] * layers[1]];;  
    double * bias1 = new double[layers[1]];
    double * bias2 = new double[layers[2]];  

    // forward propogation 
    double * hideenlayerSigmoid = new double[layers[1]];
    double * outputSigmoid = new double[layers[2]];  
	
	// Backward propogation 
    double * deltaweight1 = new double[layers[1] * layers[0]];
    double * deltaweight2 = new double[layers[2] * layers[1]];  
    double * deltaHidden = new double[layers[1]];
    double * deltaOutput = new double[layers[2]];   

	// Testing 
	int largest_index;
	double largest; 
	int index_label;
	int number_test_passed = 0; 
	double accuracy;
 

    /*
    ---------------------------------------------------------------------------- 
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------
    */  

	/*
		Initialise Weights and Bias 
    */ 

    intialiseweights(layers[1] , layers[0] , weight1); 
    printf("weight 1, first element %f \n", weight1[0]);
    

    intialiseweights(layers[2] , layers[1] , weight2); 
    printf("weight 2, first element %f \n", weight2[0]);
      
    intialisebias(layers[1] ,  bias1); 
    printf("bias 1, first element %f \n", bias1[0]);

    intialisebias(layers[2] ,  bias2); 
    printf("bias 2, first element %f \n", bias2[0]); 
 

    // Intialise trainingSetOrder for shuffleing of data 
    int numTrainingSets = 60000; 

    int trainingSetOrder[numTrainingSets];
	
    for(i = 0; i < numTrainingSets; i++){
         trainingSetOrder[i] = i;
    }

     /*
    ---------------------------------------------------------------------------- 
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------
    */
    /*
    	Train
    */ 
 
    int epoch, iterate,index_train,index_test; 
    for( epoch = 0 ; epoch < epochs; epoch++){ 
        // Shuffle the data 
		shuffle(trainingSetOrder,numTrainingSets);  
	    
        for(iterate = 0; iterate < row_train; iterate = iterate + 10){

 			// Reset the bakward propogation to zero 
            resetbias(layers[2],  deltaOutput); 

            resetbias(layers[1],  deltaHidden); 
       
            reseteweights(layers[2], layers[1], deltaweight2); 

            reseteweights(layers[1], layers[0], deltaweight1);  
            
            for( index_train = 0 ; index_train < 10; index_train++){   
 
                
                int k; 
                double temp[layers[0]];
                for(k = 0; k < layers[0]; k++){
                    temp[k] = train_image[trainingSetOrder[index_train]][k];
                }

                double temp_lable[10];
                for(k = 0; k < 10; k++){
                    temp_lable[k] = train_label[trainingSetOrder[index_train]][k]; 
                }

                //Forward Bias
                forwardpass(layers[1], layers[0], weight1, bias1,temp, hideenlayerSigmoid);
                forwardpass(layers[2], layers[1], weight2, bias2, hideenlayerSigmoid, outputSigmoid); 

                //Backward Bias

				for(i = 0; i< layers[2]; i++){
					deltaOutput[i] += (outputSigmoid[i]  - temp_lable[i])*dSigmoid(outputSigmoid[i]);  
				}


				for(i=0; i< layers[2]; i++){
					for(j=0; j < layers[1]; j++){
						deltaweight2[i* layers[2] + j] += deltaOutput[i]* hideenlayerSigmoid[j];
					}
				}
 
			    for ( i = 0; i< layers[1]; i++) {
			    	kdash = 0.0;
			        for( j=0; j< layers[2]; j++) {
			        	kdash += deltaOutput[j]* weight2[j * layers[2] + i];  
			        }
			        deltaHidden[i] += kdash * dSigmoid(hideenlayerSigmoid[i]);
			    }



			    for ( i=0; i<layers[1]; i++) {
			        for ( j=0; j<layers[0]; j++) {
			            deltaweight1[i * layers[1] + j] += temp[j] * deltaHidden[i];
			        }
			    }
   
            }

            // Based on this, change the weight and the bias
            changewb(layers[1]  , layers[0] , weight1, bias1, deltaweight1, deltaHidden);              
            changewb(layers[2]  , layers[1] , weight2, bias2, deltaweight2, deltaOutput);    
        }

 		/*
	    ---------------------------------------------------------------------------- 
		----------------------------------------------------------------------------
		----------------------------------------------------------------------------
	    */
	    /*
	    	Test

        */   
		number_test_passed = 0;
        int index_test,k; 
 
		if(epoch % 10 == 0){

		    for( index_test = 0; index_test < row_test ;index_test++){

                double temp_test[layers[0]];
                for(k = 0; k < layers[0]; k++){
                    temp_test[k] = test_image[index_train][k]; 
                }

				//Forward Bias
                forwardpass(layers[1], layers[0], weight1, bias1,temp_test, hideenlayerSigmoid);
                
                forwardpass(layers[2], layers[1], weight2, bias2, hideenlayerSigmoid, outputSigmoid); 

                // Checking the reult 
                largest_index = 0;
                largest = outputSigmoid[0]; 
                for (i = 0; i < 10 ; i++){
                    if (largest < outputSigmoid[i]){
                        largest_index = i;
                        largest = outputSigmoid[i];
                    }
                    if (test_label[index_test][i] == 1){
                        index_label = i;
                    }
                }
                if (largest_index == index_label){
                    number_test_passed += 1; 
                }
			} 
            printf("epoch %d\n", epoch);
            printf("number_test_passed %d\n", number_test_passed);
            printf("row_test %d\n",  row_test); 

        }  	
    }
    
    clock_t end = clock();
    time_spent = (double) (end - begin)/ (double) CLOCKS_PER_SEC ; 
    printf(" Time spent %f \n" , time_spent);     

} 












 