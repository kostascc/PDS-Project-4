/**
 * PDS Project 4
 * 
 * Copyright 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#include "mmarket.hpp"


void mmarket_import(char* filename, CSCMatrix* mx, bool transpose, bool three_column_coo){

    bool __show_info = true; // Show Progress

    // Start Clock
    utils::Clock clock = utils::Clock();
    clock.startClock();


    int ret_code;
    MM_typecode matcode;
    FILE *f;
    int M, N, nz;   
    int i;


    /**************
    ** Open File **
    **************/

    if(__show_info)
        printf("[Info] Begin Reading File...\n");

    if ((f = fopen(filename, "r")) == NULL) {
        printf("[Error] Couldn't Open the specified file: \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("[Error] Could not process Matrix Market banner.\n");
        exit(EXIT_FAILURE);
    }

    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) )
    {
        printf("[Error] Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(EXIT_FAILURE);
    }

    /* find out size of sparse matrix .... */

    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0){
        printf("[Error] mm_read_mtx_crd_size failed.\n");
        exit(EXIT_FAILURE);
    }
        

    /* reseve memory for matrices */

    // COO Row index
    int* I = (int *) malloc(nz * sizeof(int));
    if(I==NULL) exit(EXIT_FAILURE);

    // COO Column index
    int* J = (int *) malloc(nz * sizeof(int));
    if(J==NULL) exit(EXIT_FAILURE);


    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    int xx, yy;
    float vv;

    // Scan File
    if(three_column_coo)
    {
        for (i=0; i<nz; i++)
        {
            fscanf(f, "%d %d %f\n", &yy, &xx, &vv);

            I[i] = yy - 1;
            J[i] = xx - 1;
        }
    }
    else
    {
        for (i=0; i<nz; i++)
        {
            fscanf(f, "%d %d\n", &yy, &xx);

            I[i] = yy - 1;
            J[i] = xx - 1;
        }
    }
    

    if (f !=stdin) fclose(f);
    
    if(transpose){
        int* JI;
        JI = I;
        I = J;
        J = JI;

        int NM;
        NM = M;
        M = N;
        N = NM;
    }



    /********************
    ** Sort COO Matrix **
    ********************/

    if(__show_info)
        printf("[Info] Sorting COO Matrix...\n");

    mergeSort(J, I, nz);

    if(__show_info)
        printf("[Info] Finished Sorting.\n");

    /************************
    **  Convert COO to CSC **
    ************************/

    if(__show_info)
        printf("[Info] Creating CSC Matrix...\n");

    // CSC Pointers
    mx->cscp = (int*) calloc(N+1, sizeof(int));
    
    for (int i = 0; i < nz; i++)
    {
        mx->cscp[J[i] + 1] += 1;
    }

    for (int i = 0; i < N; i++)
    {
        mx->cscp[i + 1] += (*mx).cscp[i];
    }

    mx->csci = I;

    sparseSortMtx(mx);

    mx->H = M;
    mx->W = N;
    mx->NZ = nz;

    if(__show_info)
        printf("[Info] Imported H: %d, W: %d, nz: %d.\n", M, N, nz);

    /***************
    ** Clean Up ! **
    ***************/

    // I is used in the resulting Matrix! We are not freeing it up.

    free(J);
    J = NULL;

    fflush(stdin);
    fflush(stdout);

    if(__show_info)
        printf("[Info] MMARKET Import Took %s\n", clock.stopClock());

}


