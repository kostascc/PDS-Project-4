/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "MPIUtil.hpp"


MPIUtil::MPIUtil(){
    // Initiate MPI
    MPI_Init(NULL, NULL);

    // Get Cluster Size
    MPI_Comm_size(MPI_COMM_WORLD, &clusterSize);

    // Get Node ID
    MPI_Comm_rank(MPI_COMM_WORLD, &nodeIdx);

    nextNode =  nodeIdx >= clusterSize ? 
                0 : nodeIdx + 1;

    prevNode =  nodeIdx == 0 ? 
                clusterSize - 1 : nodeIdx - 1;
    
    #if DBG_MPI_INIT == true
        printf("[Info] MPI node:%d, cluster: %d, master: %d, prev: %d, next: %d\n", 
            nodeIdx, clusterSize, MPI_MASTER_NODE_IDX, prevNode, nextNode);
    #endif
}


void MPIUtil::Send_t(int tag, void* buffer, int length, int partner, MPI_Datatype type, MPI_Request request[])
{

    #if DBG_MPI_COMM == true
        printf("[Info] MPI Node %d Sending to %d (length: %d, tag: %d)\n", nodeIdx, partner, length, tag);
    #endif

    MPI_Isend(
        buffer,         // *Buffer
        length,          // Count
        type,     // Type
        partner,   // Destination
        tag,    // Tag
        MPI_COMM_WORLD,   // Comm
        &(request[1])   // *Request
    );
    
}


void MPIUtil::Receive_t(int tag, void* buffer, int length, int partner, MPI_Datatype type, MPI_Request request[])
{

    #if DBG_MPI_COMM == true
        printf("[Info] MPI Node %d receiving from %d (length: %d, tag: %d)\n", nodeIdx, partner, length, tag);
    #endif

    MPI_Irecv(
        buffer,         // *Buffer
        length,          // Count
        type,     // Type
        partner,   // Destination
        tag,    // Tag
        MPI_COMM_WORLD,   // Comm
        &(request[0])   // *Request
    );

}


void MPIUtil::Send(int tag, int* buffer, int length, int partner, MPI_Request request[])
{

    Send_t(tag, buffer, length, partner, MPI_INT, request);
    
}


void MPIUtil::Receive(int tag, int* buffer, int length, int partner, MPI_Request request[])
{

    Receive_t(tag, buffer, length, partner, MPI_INT, request);

}


void MPIUtil::SendWait(MPI_Request request[])
{

    MPI_Status status;
    MPI_Wait(&(request[1]), &status);
    
}


void MPIUtil::ReceiveWait(MPI_Request request[])
{

    MPI_Status status;
    MPI_Wait(&(request[0]), &status);

}


void MPIUtil::Abort()
{
    // #if DBG_MPI_COMM == true
        printf("[Error] MPI Abort\n");
    // #endif

    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
}


void MPIUtil::AbortMsg(char* msg)
{
    // #if DBG_MPI_COMM == true
        printf("[Error] MPI Abort (%s)\n", msg);
    // #endif

    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
}


void MPIUtil::FinishLocal()
{
    #if DBG_MPI_INIT == true
        printf("[Info] MPI node %d finished\n", nodeIdx);
    #endif

    MPI_Finalize();
    exit(EXIT_SUCCESS);
}


void MPIUtil::Finalize()
{
    #if DBG_MPI_INIT == true
        printf("[Info] MPI node %d finalized\n", nodeIdx);
    #endif

    MPI_Finalize();
}


// void MPIUtil::Send_b(int tag, void* buffer, int length, int partner, MPI_Request request[])
// {

//     Send_nb(tag, buffer, length, partner, request);
//     SendWait(request);
    
// }


// void MPIUtil::Receive_b(int tag, void* buffer, int length, int partner, MPI_Request request[])
// {

//     Receive_nb(tag, buffer, length, partner, request);
//     ReceiveWait(request);

// }


// void MPIUtil::Send_b_t(int tag, void* buffer, int length, int partner, MPI_Datatype type, MPI_Request request[])
// {

//     Send_nb_t(tag, buffer, length, partner, type, request);
//     SendWait(request);
    
// }


// void MPIUtil::Receive_b_t(int tag, void* buffer, int length, int partner, MPI_Datatype type, MPI_Request request[])
// {

//     Receive_nb_t(tag, buffer, length, partner, type, request);
//     ReceiveWait(request);

// }
