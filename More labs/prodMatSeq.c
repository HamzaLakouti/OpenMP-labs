#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#ifndef VAL_M
#define VAL_M 301
#endif
#ifndef VAL_N
#define VAL_N 501
#endif
void init_matrice(int m,int n, double a[m][n],double b[n][m], double c[m][m]);
void prod_matrice(int m,int n, double a[m][n],double b[n][m], double c[m][m]);
int main(){

	int m=VAL_M,n=VAL_N;
	double a[m][n],b[n][m],c[m][m];
	struct timeval t_elapsed_0, t_elapsed_1;
	double t_elapsed;
	clock_t t_cpu_0, t_cpu_1;
	double t_cpu;
	
	t_cpu_0=clock();
	gettimeofday(&t_elapsed_0,NULL);
	init_matrice(m,n,a,b,c);
	prod_matrice(m,n,a,b,c);
	gettimeofday(&t_elapsed_1,NULL);

	t_elapsed=(t_elapsed_1.tv_sec-t_elapsed_0.tv_sec)+(t_elapsed_1.tv_usec - t_elapsed_0.tv_usec)/(double)1000000;
	t_cpu_1=clock();
	t_cpu=(t_cpu_1 - t_cpu_0)/(double)CLOCKS_PER_SEC;
	fprintf(stdout,"\n\n""Valeur de m et n : %5d %5d \n""Temps elapsed : %10.3E sec .\n""Temps CPU : %10.3E sec .\n""Resultat partiel : %10.3E %10.3E .... %10.3E %10.3E \n\n",
		m,n,t_elapsed,t_cpu,c[1][1],c[2][2],c[m-3][m-3],c[m-2][m-2]);
return EXIT_SUCCESS;
}

void init_matrice(int m, int n, double a[m][n],double b[n][m], double c[m][m])
{
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
	a[i][j]=(i+1)+(j+1);}
}
for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
        b[i][j]=(i+1)-(j+1);}
}
for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
        c[i][j]=0;}
}
}

void prod_matrice(int m, int n, double a[m][n],double b[n][m], double c[m][m])
{	
	for(int i=0;i<m;i++){
       	for(int j=0;j<n;j++){
       		for(int k=0;k<n;k++){ c[i][j]=c[i][j]+a[i][k]*b[k][j];}
		}	
	}
}

// compile with -p then execute executable.o then use: gprof -b executable gmon.out