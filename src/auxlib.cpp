/**
 * PDS Project 2
 * 
 * Copyright 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#include "auxlib.hpp"


/**
 * Each external variable should
 * be defined both in .c and .h files.
 **/

/**
 * Print timing information.
 * Default: true.
 **/
extern bool _TIMER_PRINT = true ;


void exportCOOVectorP(vector<pair<int,int>>* v, Runtime rt, string title){

    /**
     * Create File Name
     **/
    char *name1, *name2, *name1_, *name2_;
    char * token;
    token = strtok(strdup(rt.URIa), "/");
    while (token != NULL)
    {
        name1 = token;
        token = strtok(NULL, "/");
    }
    token = strtok(name1, ".");
    while (token != NULL)
    {
        name1_ = token;
        break;
    }
    token = strtok(strdup(rt.URIb), "/");
    while (token != NULL)
    {
        name2 = token;
        token = strtok(NULL, "/");
    }
    token = strtok(name2, ".");
    while (token != NULL)
    {
        name2_ = token;
        break;
    }
    stringstream ss;
    ss <<  name1_ << "_" << name2_ << "_" << title << ".txt";

    FILE *f = fopen(ss.str().c_str(), "wb");
    if (f == NULL)
    {
        printf("[Error] Couldn't open file (%d)!\n", ss.str());
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<v->size(); i++){
        fprintf(f, "%d,%d\n", (*v)[i].first+1, (*v)[i].second+1 );
    }

    fclose(f);
}


/** 
 * Auxiliary
 **/
int aux_sort_idx(double** C, int** nidx, double** ndist, int N, int M, int m, int k)
{
	// M: all query points
	// m: current query point
	// N: all corpus points
	// k: neighbors
	// C: distances in m*n format (Transposed)
	// nidx: indexes m*k
	// ndist: distances m*k
	
	// Fill the distances and indexes
	double * distm 	= (double *) malloc(N*sizeof(double));
	int * idxm 		= (int *)    malloc(N*sizeof(int));

	for(int i=0; i<N; i++)
	{
		distm[i] = (double) *((*C)+ N * m + i);
		idxm[i] = (int) i;
	}
	
	aux_mergeSort(&distm, &idxm, N);

    for(int i=0; i<k; i++)
    {
        *( *ndist + k*m + i ) = (double) distm[i];
        *( *nidx  + k*m + i ) = (int)     idxm[i];
    }

	return 0;
	
}



/*************
 *  Sorting 
 *************/


// in-place merge sort
void aux_mergeSort(double ** _I, int ** _J, int len)
{
    if (len <= 1)
    {
        return;
    }


    double *left_I = (double *)  aux_slice_d(_I, 0, len / 2 + 1);
    double *right_I = (double *) aux_slice_d(_I, len / 2, len);

    int *left_J = (int *)  aux_slice_i(_J, 0, len / 2 + 1);
    int *right_J = (int *)  aux_slice_i(_J, len / 2, len);

    // cilk_sync;

    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        aux_mergeSort(&left_I, &left_J, len / 2);

        #pragma omp task
        aux_mergeSort(&right_I, &right_J, len - (len / 2));
    }

    aux_merge(_I, _J, &left_I, &left_J, &right_I, &right_J, len / 2, len - (len / 2));

}

int * aux_slice_i(int **arr, int start, int end)
{
    int *result = (int *) malloc((end - start) * sizeof(int));
    if(result==NULL)
    {
        printf("Failed Allocating memory (aux_slice_i).\n");
    }
    int i;
    for (i = start; i < end; i++)
    {
        result[i - start] = (int) *(*arr +i);
    }
    return result;
}

double * aux_slice_d(double **arr, int start, int end)
{
    double *result = (double *) malloc((end - start) * sizeof(double));
    if(result==NULL)
    {
        printf("Failed Allocating memory (aux_slice_d).\n");
    }
    int i;
    for (i = start; i < end; i++)
    {
        result[i - start] = (double) *(*arr +i);
    }
    return result;
}


void aux_merge( double ** _I, int ** _J, 
    double ** left_I, int ** left_J, 
    double ** right_I, int ** right_J, 
    int leftLen, int rightLen)
{

    int i, j;

    i = 0;
    j = 0;
    while(i < leftLen && j < rightLen)
    {
        if ( *(*left_I +i) < *(*right_I +j) ) 
        
        {
            *(*_I + i + j) = *(*left_I +i);
            *(*_J + i + j) = *(*left_J+ i);
            i++;
        }
        else
        {
            *(*_I +i + j) = *(*right_I + j);
            *(*_J+ i + j) = *(*right_J + j);
            j++;
        }

    }

    for(; i < leftLen; i++)
    {
        *(*_I +i + j) = *(*left_I + i);
        *(*_J +i + j) = *(*left_J + i);
    }
    for(; j < rightLen; j++)
    {
		*(*_I +i + j) = *(*right_I +j);
        *(*_J +i + j) = *(*right_J +j);
    }

    free(*left_I);
    free(*right_I);
    free(*left_J);
    free(*right_J);

}


Runtime startup(int argc, char** argv)
{

    if(argc < 4){
        printf("[Error] Not enough arguments!\n");
        printf("Available Arguments:\n");
        printf(" -t <int>           Threads\n");
        printf(" -a <uri>           Matrix A file\n");
        printf(" --a-transpose      Transpose Matrix A\n");
        printf(" --a-twocolumncoo   MM file of Matrix A doesn't contain values\n");
        printf(" -b <uri>           Matrix B file\n");
        printf(" --b-transpose      Transpose Matrix B\n");
        printf(" --b-twocolumncoo   MM file of Matrix B doesn't contain values\n");
        printf(" -f <uri>           Matrix F file\n");
        printf(" --f-transpose      Transpose Matrix F\n");
        printf(" --f-twocolumncoo   MM file of Matrix F doesn't contain values\n");
        printf(" --opt-csr-a        Optimization: Uses CSR storage for Matrix A\n");
        printf(" --opt-csr-f        Optimization: Uses CSR storage for Matrix F\n");
        printf(" --v1               Sequential algorithm (V1)\n");
        printf(" --v2               Parallelized algorithm (V2)\n");
        exit(EXIT_FAILURE);
    }


    char _a_filename[1024];
    bool _a_three_column_coo = true;
    bool _a_transpose = false;
    bool a_ready;

    char _b_filename[1024];
    bool _b_three_column_coo = true;
    bool _b_transpose = false;
    bool b_ready;

    char _f_filename[1024];
    bool _f_three_column_coo = true;
    bool _f_transpose = false;
    bool f_ready;

    // int _n = 1000;
    // int _m = 100;
    // int _d = 10;
    // int _k = 5;
    int _threads = 1;

    // bool _rand = false;



    /***************************************
     * Set up Environment Parameters
     * and debugging modes
     ***************************************/

    char *s_tmp;

    s_tmp = getenv( _TIMER_PRINT_VAR );
    _TIMER_PRINT = (s_tmp!=NULL)? ( strchr(s_tmp,'1')!=NULL? true : false  ) : false;

    /***************************************/

    Runtime rt = Runtime();

    /** 
    * For each argument given,
    * find the respective configuration
    * parameter and change it
    **/
    for(int i=0; i<argc; i++){


        int _tmp_int = NULL;   // Temporary placeholder
        char _tmp_str[1024];

        /**
         * " -t <THREADS> "
         */
        if(strcmp(argv[i],"-t")==0)
        {
            if(i<argc-1)
            {
                _tmp_int = atoi(argv[i+1]);
                if(_tmp_int>0 && _tmp_int<=64)
                {
                    _threads = _tmp_int;
                    rt.threads = _threads;
                    continue;
                }else{
                    printf("[Warning] Threads should be between 1 and 64!\n");
                }
                a_ready = true;
                continue;
            }
            
            // printf("-t Parameter Deprecated: Use 'export CILK_NWORKERS=___' instead.\n");
        }


        /**
         * " -a < Path > "
         */
        if(strcmp(argv[i],"-a")==0)
        {
            if(i<argc-1)
            {
                strcpy(_a_filename, argv[i+1]);
                a_ready = true;
                continue;
            }
        }

        /**
         * " -b < Path > "
         */
        if(strcmp(argv[i],"-b")==0)
        {
            if(i<argc-1)
            {
                strcpy(_b_filename, argv[i+1]);
                b_ready = true;
                continue;
            }
        }

        /**
         * " -f < Path > "
         */
        if(strcmp(argv[i],"-f")==0)
        {
            if(i<argc-1)
            {
                strcpy(_f_filename, argv[i+1]);
                f_ready = true;
                continue;
            }
        }

        /**
         * " --a-transpose"
         */
        if(strcmp(argv[i],"--a-transpose")==0)
        {
            _a_transpose = true;
            continue;
        }

        /**
         * " --b-transpose"
         */
        if(strcmp(argv[i],"--b-transpose")==0)
        {
            _b_transpose = true;
            continue;
        }

        /**
         * " --f-transpose"
         */
        if(strcmp(argv[i],"--f-transpose")==0)
        {
            _f_transpose = true;
            continue;
        }

        /**
         * " --a-twocolumncoo"
         */
        if(strcmp(argv[i],"--a-twocolumncoo")==0)
        {
            _a_three_column_coo = false;
            continue;
        }

        /**
         * " --b-twocolumncoo"
         */
        if(strcmp(argv[i],"--b-twocolumncoo")==0)
        {
            _b_three_column_coo = false;
            continue;
        }

        /**
         * " --f-twocolumncoo"
         */
        if(strcmp(argv[i],"--f-twocolumncoo")==0)
        {
            _f_three_column_coo = false;
            continue;
        }

        /**
         * " --opt-csr-a"
         */
        if(strcmp(argv[i],"--opt-csr-a")==0)
        {
            rt.opt_csr_a = true;
            continue;
        }

        /**
         * " --opt-csr-f"
         */
        if(strcmp(argv[i],"--opt-csr-f")==0)
        {
            rt.opt_csr_f = true;
            continue;
        }

        /**
         * " --v1"
         */
        if(strcmp(argv[i],"--v1")==0)
        {
            rt.v1 = true;
            continue;
        }

        /**
         * " --v2"
         */
        if(strcmp(argv[i],"--v2")==0)
        {
            rt.v2 = true;
            continue;
        }

    }

    if (!a_ready){
        printf("[Error] Matrix A wasn't specified!\n Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (!b_ready){
        printf("[Error] Matrix B wasn't specified!\n Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (!f_ready){
        printf("[Error] Matrix F wasn't specified!\n Exiting...\n");
        exit(EXIT_FAILURE);
    }

    strcpy(rt.URIa, _a_filename);
    strcpy(rt.URIb, _b_filename);
    strcpy(rt.URIf, _f_filename);

    // Convert Matrix A to CSR for Optimization
    if(rt.opt_csr_a)
        _a_transpose = !_a_transpose;
    if(rt.opt_csr_f)
        _f_transpose = !_f_transpose;

    /**
    * Configure threads on system runtime level
    **/

    // OpenMP
    omp_set_num_threads(_threads); // Set maximum thread count
    //omp_set_dynamic(0);     // Explicitly disable dynamic teams

    /*********************
     ** Import Matrices **
    **********************/

    rt.A = new CSCMatrix();
    rt.B = new CSCMatrix();
    rt.F = new CSCMatrix();

    mmarket_import(_a_filename, rt.A, _a_transpose, _a_three_column_coo); // Import MM
    
    mmarket_import(_b_filename, rt.B, _b_transpose, _b_three_column_coo); // Import MM

    mmarket_import(_f_filename, rt.F, _f_transpose, _f_three_column_coo); // Import MM
    
    return  rt;

}



extern int tmp_node_id=-1;

int n_per_node(int node_id, int cluster_size, int n)
{

    int ret = (n/cluster_size);
    if(node_id == cluster_size-1)
    {
        return ret + n%cluster_size;
    }
    return ret;
}
