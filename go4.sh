#!/bin/bash
#SBATCH --job-name=cuda
#SBATCH --ntasks=4
#SBATCH --nodes=4
#SBATCH --cpus-per-task=2
#SBATCH --partition=gpu
#SBATCH --gres=gpu:1
#SBATCH --mem=10G
#SBATCH --time=0-1:00       # time (D-HH:MM)

make
 
  
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./FC_cuda 100 



 