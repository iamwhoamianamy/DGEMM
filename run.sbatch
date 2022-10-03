#!/bin/bash
#SBATCH --job-name=mult                    # Название задачи 
#SBATCH --output=results_simple/mult-%j.log       # Файл для вывода результатов 
#SBATCH --nodes=1                      # Количество используемых узлов
#SBATCH --ntasks=1                     # Количество MPI процессов
#SBATCH --cpus-per-task=1              # Количество ядер CPU, выделенных для одного процесса
#SBATCH --ntasks-per-socket=1          # Количество процессов на одном сокете узла

export OMP_NUM_THREADS=1
srun ./main 1024 8192 1024 1                        # Выполнение расчёта