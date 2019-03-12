
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>
#include <fstream>

using namespace std;

#define SYSTEMTIME clock_t

#define NUBMBER_OF_RUNS 10
#define start_1_2 600
#define end_1_2 3000
#define start_2_3 4000
#define end_2_3 10000
#define increment_1_2 400
#define increment_2_3 2000
#define block_size_1 64
#define block_size_2 128
#define block_size_3 256
#define block_size_4 512
#define block_size_5 1024




int papi_config();
void papi_start(int EventSet);
void papi_reset(int EventSet, long long values[]);
void papi_remove(int EventSet);
void consoleProgram();

double OnMult(int m_ar, int m_br)
{

	SYSTEMTIME Time1, Time2;

	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;

	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for (i = 0; i < m_ar; i++)
		for (j = 0; j < m_ar; j++)
			pha[i * m_ar + j] = (double)1.0;

	for (i = 0; i < m_br; i++)
		for (j = 0; j < m_br; j++)
			phb[i * m_br + j] = (double)(i + 1);

	Time1 = clock();

	for (i = 0; i < m_ar; i++)
	{
		for (j = 0; j < m_br; j++)
		{
			temp = 0;
			for (k = 0; k < m_ar; k++)
			{
				temp += pha[i * m_ar + k] * phb[k * m_br + j];
			}
			phc[i * m_ar + j] = temp;
		}
	}

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	cout << "Result matrix: " << endl;
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < min(10, m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;


	free(pha);
	free(phb);
	free(phc);

	return (double)(Time2 - Time1) / CLOCKS_PER_SEC;
}

double OnMultLine(int m_ar)
{
	SYSTEMTIME Time1, Time2;

	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;

	// Creates matrix a, b and the result matrix c
	pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Initialize values of matrix a
	for (i = 0; i < m_ar; i++)
		for (j = 0; j < m_ar; j++)
			pha[i * m_ar + j] = (double)1.0;

	//Initialize values of matrix b
	for (i = 0; i < m_ar; i++)
		for (j = 0; j < m_ar; j++)
			phb[i * m_ar + j] = (double)(i + 1);

	//Start the clock
	Time1 = clock();

	for (i = 0; i < m_ar; i++)
	{
		for (k = 0; k < m_ar; k++)
		{
			for (j = 0; j < m_ar; j++)
			{
				phc[i * m_ar + j] += pha[i * m_ar + k] * phb[k * m_ar + j];
			}
		}
	}

	//Stop the clock
	Time2 = clock();

	//Show results
	printf("%3.3f ", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	fflush(stdout);

	//Print Result matrix (c)
	
	cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,m_ar); j++)
			cout << phc[j] << " ";
	}
	cout << endl;
	
	//unallocate space of the matrices
	free(pha);
	free(phb);
	free(phc);

	return (double)(Time2 - Time1) / CLOCKS_PER_SEC;
}

/*float produtoInterno(float *v1, float *v2, int col)
{
	int i;
	float soma = 0.0;

	for (i = 0; i < col; i++)
		soma += v1[i] * v2[i];

	return (soma);
}*/

/*void handle_error(int retval)
{
	printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
	exit(1);
}*/

/*void init_papi()
{
	int retval = PAPI_library_init(PAPI_VER_CURRENT);
	if (retval != PAPI_VER_CURRENT && retval < 0)
	{
		printf("PAPI library version mismatch!\n");
		exit(1);
	}
	if (retval < 0)
		handle_error(retval);

	std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
			  << " MINOR: " << PAPI_VERSION_MINOR(retval)
			  << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}*/

void runBenchmark(){

	long long values[3];
	std::ofstream myfile;
    myfile.open ("Benchmark.csv");
    myfile << "Algorithm, Run Number, Matrix size, Time, PAPI_L1_DCM, PAPI_L2_DCM,\n";
    
	int EventSet = papi_config();
		for(int j=start_1_2;j<=end_1_2; j+=increment_1_2)
			for(int i=0; i<NUBMBER_OF_RUNS; i++){
				papi_start(EventSet);
				double time=OnMult(j,j);
				papi_reset(EventSet,values);
				myfile << "1," <<i <<"," << j<< "," <<time << "," << values[0]<< "," << values[1]<< ",\n";
			}

		for(int j=start_1_2;j<=end_1_2; j+=increment_1_2)
			for(int i=0; i<NUBMBER_OF_RUNS; i++){
				papi_start(EventSet);
				double time=OnMultLine(j);
				papi_reset(EventSet,values);
				myfile << "2," <<i <<"," << j<< "," <<time << "," << values[0]<< "," << values[1]<< ",\n";
			}

		for(int j=start_2_3;j<=end_2_3; j+=increment_2_3)
			for(int i=0; i<NUBMBER_OF_RUNS; i++){
				papi_start(EventSet);
				double time=OnMultLine(j);
				papi_reset(EventSet,values);
				myfile << "2," <<i <<"," << j<< "," <<time << "," << values[0]<< "," << values[1]<< ",\n";
			}

		for(int j=start_2_3;j<=end_2_3; j+=increment_2_3)
			for(int i=0; i<NUBMBER_OF_RUNS; i++){
				papi_start(EventSet);
				//TODO IMPLEMENT//double time=OnMultLine(j);
				papi_reset(EventSet,values);
				myfile << "3," <<i <<"," << j<< "," <<time << "," << values[0]<< "," << values[1]<< ",\n";
			}
	papi_remove(EventSet);			
	

    myfile.close();
}

int main(int argc, char *argv[])
{
	runBenchmark();
	//consoleProgram();
	return 0;
}

void consoleProgram()
{
	int lin, col;
	int op;

	op = 1;

	int EventSet = papi_config();
	long long values[3];
	do
	{
		cout << endl
			 << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "Selection?: ";
		cin >> op;
		if (op == 0)
			break;
		printf("Dimensions: lins cols ? ");
		cin >> lin >> col;

		// Start counting
		papi_start(EventSet);
		switch (op)
		{
		case 1:
			OnMult(lin, col);
			break;
		case 2:
			OnMultLine(lin);

			break;
		}

		papi_reset(EventSet,values);

	} while (op != 0);

	papi_remove(EventSet);
}

int papi_config()
{
	int EventSet = PAPI_NULL;

	int ret;

	ret = PAPI_library_init(PAPI_VER_CURRENT);
	if (ret != PAPI_VER_CURRENT)
		std::cout << "FAIL" << endl;

	ret = PAPI_create_eventset(&EventSet);
	if (ret != PAPI_OK)
		cout << "ERRO: create eventset" << endl;

	ret = PAPI_add_event(EventSet, PAPI_L1_DCM);
	if (ret != PAPI_OK)
		cout << "ERRO: PAPI_L1_DCM" << endl;

	ret = PAPI_add_event(EventSet, PAPI_L2_TCM);
	if (ret != PAPI_OK)
		cout << "ERRO: PAPI_L2_DCM" << endl;

	return EventSet;
}

void papi_start(int EventSet)
{
	int ret;
	ret = PAPI_start(EventSet);
	if (ret != PAPI_OK)
		cout << "ERRO: Start PAPI" << endl;
}

void papi_reset(int EventSet, long long values[])
{
	int ret;
	ret = PAPI_stop(EventSet, values);
	if (ret != PAPI_OK)
		cout << "ERRO: Stop PAPI" << endl;

	printf("L1 DCM: %lld \n", values[0]);
	printf("L2 DCM: %lld \n", values[1]);

	ret = PAPI_reset(EventSet);
	if (ret != PAPI_OK)
		std::cout << "FAIL reset" << endl;
}

void papi_remove(int EventSet)
{
	int ret;
	ret = PAPI_remove_event(EventSet, PAPI_L1_DCM);
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event1 " << endl;

	ret = PAPI_remove_event(EventSet, PAPI_L2_DCM);
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event2 " << endl;

	ret = PAPI_destroy_eventset(&EventSet);
	if (ret != PAPI_OK)
		std::cout << "FAIL destroy" << endl;
}