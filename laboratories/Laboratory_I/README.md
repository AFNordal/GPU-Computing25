# Laboratory I

Cluster usage, ssh/scp connection and SLURM usage.

## Exercise 1

log on the Marzola log-in node and run the “hostname” command. Save them on a file and copy the result back to the local machine.

```
pico_wslu22@Pico-SamsungPC:~$ ssh lorenzo.pichetti@marzola.disi.unitn.it
lorenzo.pichetti@marzola.disi.unitn.it's password:
Welcome on deeplearning cluster.
Please note that deeplearning03 node has been designed for educational purposes: hyper threading is enabled and it should not be used for benchmarking
Web console: https://marzola:9090/ or https://192.168.159.151:9090/

Last login: Mon Mar  4 14:17:41 2024 from 10.196.195.123
[lorenzo.pichetti@marzola ~]$ hostname
marzola
[lorenzo.pichetti@marzola ~]$ hostname > result.txt
[lorenzo.pichetti@marzola ~]$ exit
logout
Connection to marzola.disi.unitn.it closed.
pico_wslu22@Pico-SamsungPC:~$ scp -i ~/.ssh/wslWin11 lorenzo.pichetti@marzola.disi.unitn.it :~/result.txt ./
```

## Exercise 2

Run "hostname" on the compute node deeplearning03

```
[lorenzo.pichetti@marzola ~]$ srun --nodes=1 --ntasks=1 --cpus-per-task=1 --gres=gpu:0 --partition=edu5 --pty bash 
[lorenzo.pichetti@deeplearning03 ~]$ hostname
deeplearning03
[lorenzo.pichetti@deeplearning03 ~]$ exit
exit
[lorenzo.pichetti@marzola ~]$
```

Run "nvidia-smi" on both marzola and deeplearning03 with ‘--gres=gpu:0’ as srun parameter. What’s happend?

## Exercise 3

Write and compile a hello world program directly on the Marzola node and run it on the deeplearning03 compute node.

```
pico_wslu22@Pico-SamsungPC:~$ ssh -i ~/.ssh/wslWin11 lorenzo.pichetti@marzola.disi.unitn.it
[…]
[lorenzo.pichetti@marzola ~]$ vi helloworld.c
[lorenzo.pichetti@marzola ~]$ gcc helloworld.c –o helloworld
[lorenzo.pichetti@marzola ~]$ srun --nodes=1 --ntasks=1 --cpus-per-task=1 --gres=gpu:0 --partition=edu5 --pty bash 
[lorenzo.pichetti@deeplearning03 ~]$ ./helloworld
Hello world!
[lorenzo.pichetti@deeplearning03 ~]$ exit
[lorenzo.pichetti@marzola ~]$
```

## Exercise 4

Compile and run the following code on the DISI cluster:

```C
#include <stdio.h>
#include <cblas.h>

int main() {
    int m = 2, n = 2, k = 2;
    double A[4] = {1.0, 2.0, 3.0, 4.0};
    double B[4] = {5.0, 6.0, 7.0, 8.0};
    double C[4] = {0.0, 0.0, 0.0, 0.0};

    // Perform C = A * B using BLAS
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, 1.0, A, k, B, n, 0.0, C, n);

    // Print result
    printf("Result matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", C[i * n + j]);
        }
        printf("\n");
    }
    return 0;
}
```

Since it require the OpenBLAS library, you need to load the module and link the library:

```
[lorenzo.pichetti@marzola ~]$  module load OpenBLAS/
Loading OpenBLAS/0.3.23-GCC-12.3.0
  Loading requirement: GCCcore/12.3.0 zlib/1.2.13-GCCcore-12.3.0 binutils/2.40-GCCcore-12.3.0 GCC/12.3.0[lorenzo.pichetti@marzola ~]$ gcc -o program program.c -L/opt/shares/openfoam/software/OpenBLAS/0.3.23-GCC-12.3.0/lib -I/opt/shares/openfoam/software/OpenBLAS/0.3.23-GCC-12.3.0/include/ -lopenblas
[lorenzo.pichetti@marzola ~]$
```

Once you done, write a makefile to compile the source automatically.

Do you run on the log-in node or on the compute node? Write a sbatch script to run on the compute node ;)
