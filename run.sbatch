#!/bin/bash
#SBATCH --job-name=dgemm                    # Название задачи 
#SBATCH --error=results/dgemm-%j.err        # Файл для вывода ошибок 
#SBATCH --output=results/dgemm-%j.log       # Файл для вывода результатов 
#SBATCH --time=1:00:00                      # Максимальное время выполнения
#SBATCH --nodes=1                      # Количество используемых узлов
#SBATCH --ntasks=1                     # Количество MPI процессов
#SBATCH --cpus-per-task=24              # Количество ядер CPU, выделенных для одного процесса
#SBATCH --ntasks-per-socket=1          # Количество процессов на одном сокете узла

export OMP_NUM_THREADS=24
srun ./main 500 500 500 24                         # Выполнение расчёта