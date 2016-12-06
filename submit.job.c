#!/bin/bash
#SBATCH -p gpu
#SBATCH --gres=gpu:4
#SBATCH --nodes=1

#SBATCH --job-name="cuda-demo"
#SBATCH --output="gpucuda%j.%N.out"
#SBATCH -t 03:30:00
#cd ~/lanliu/CS240Fall16/Finalproject
./main.cu