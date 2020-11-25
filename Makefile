

 serial:
	g++ -o FC_serial FC_serial.cpp  -lm  
	
cuda: 
	nvcc FC_CUDA.cu -o FC_cuda  
 
hybrid: 
	nvcc -Xcompiler -fopenmp  FC_cuda_openmp.cu -o FC_cuda_openmp

clean: 
	rm -f *.o
	rm -f *.d 
