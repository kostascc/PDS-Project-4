/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef MPI_UTIL_HPP__
#define MPI_UTIL_HPP__


#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


/**********************************************
 *            Debugging Options
 **********************************************/
#define DBG_MPI_INIT true
#define DBG_MPI_COMM true
/**********************************************/

#define MPI_MASTER_NODE_IDX 0

using namespace std;

class MPIUtil {

    private:

        int nodeIdx;
        int clusterSize;
        int prevNode;
        int nextNode;


    public:

        /**
         * Initializes MPI Communications
         **/
        MPIUtil();

        /*********************************************
         *                 Get/Set
         *********************************************/

        /**
         * Current node Index
         **/
        int NodeIdx(){return nodeIdx;}

        /**
         * Population of nodes in the cluster
         **/
        int ClusterSize(){return clusterSize;}

        /**
         * Index of next node (Round allocation)
         **/
        int NextNode(){return nextNode;}

        /**
         * Index of previous node (Round allocation)
         **/
        int PrevNode(){return prevNode;}

        /**
         * Returns true if the current node is the master
         **/
        bool IsMaster(){return nodeIdx==MPI_MASTER_NODE_IDX;};

        /*********************************************
         *            Program Utilities
         *********************************************/

        /**
         * Aborts MPI Execution in COMM_WORLD.
         * (The Whole job stops)
         **/
        void Abort();

        /**
         * Aborts MPI Execution in COMM_WORLD,
         * with an error message.
         * (The Whole job stops)
         * 
         * @param msg 
         */
        void AbortMsg(char* msg);

        /**
         * Finishes local job silently
         */
        void FinishLocal();

        /**
         * Finishes local job silently
         */
        void Finalize();


        /*********************************************
         *                MPI Calls
         *********************************************/

        /**
         * Usage:
         * 
         * For non blocking:
         *   Send_nb(MPI_MODE_DISTRIBUTING, X, n, node_send, mpi_request);
         *   SendWait(mpi_request); // call later
         * 
         * For blocking:
         *   Send_b(...)
         * 
         * Use wait at any time to block while receiving or sending:
         *   SendWait(mpi_request); // Wait for sending to finish
         * 
         **/

        /**
         * Non-Blocking Send with DataType.
         * 
         * @param tag 
         * @param buffer 
         * @param length 
         * @param partner 
         * @param type 
         * @param request 
         */
        void Send_t(int tag, void* buffer, int length, int partner, MPI_Datatype type, MPI_Request request[]);

        /**
         * Non-Blocking Receive with DataType.
         * 
         * @param tag 
         * @param buffer 
         * @param length 
         * @param partner 
         * @param type 
         * @param request 
         */
        void Receive_t(int tag, void* buffer, int length, int partner, MPI_Datatype type, MPI_Request request[]);

        /**
         * Non-Blocking Send,
         * with default DataType: integer.
         * 
         * @param tag 
         * @param buffer 
         * @param length 
         * @param partner 
         * @param request 
         */
        void Send(int tag, int* buffer, int length, int partner, MPI_Request request[]);

        /**
         * Non-Blocking Receive,
         * with default DataType: integer.
         * 
         * @param tag 
         * @param buffer 
         * @param length 
         * @param partner 
         * @param request 
         */
        void Receive(int tag, int* buffer, int length, int partner, MPI_Request request[]);

        /**
         * Blocks until send has finished.
         * 
         * @param request 
         */
        void SendWait(MPI_Request request[]);


        /**
         * Blocks until receive has finished.
         * 
         * @param request 
         */
        void ReceiveWait(MPI_Request request[]);

        // /**
        //  * Blocking Send,
        //  * with default DataType: Double.
        //  * 
        //  * @param code 
        //  * @param Y 
        //  * @param m 
        //  * @param partner 
        //  * @param request 
        //  */
        // void Send_b(int code, double* Y, int m, int partner, MPI_Request request[]);


        // /**
        //  * Blocking Receive,
        //  * with default DataType: Double.
        //  * 
        //  * @param code 
        //  * @param Z 
        //  * @param m 
        //  * @param partner 
        //  * @param request 
        //  */
        // void Receive_b(int code, double* Z, int m, int partner, MPI_Request request[]);

        // /**
        //  * Blocking Send with DataType.
        //  * 
        //  * @param code 
        //  * @param Y 
        //  * @param m 
        //  * @param partner 
        //  * @param type 
        //  * @param request 
        //  */
        // void Send_b_t(int code, double* Y, int m, int partner, MPI_Datatype type, MPI_Request request[]);

        // /**
        //  * Blocking Receive with DataType.
        //  * 
        //  * @param code 
        //  * @param Z 
        //  * @param m 
        //  * @param partner 
        //  * @param type 
        //  * @param request 
        //  */
        // void Receive_b_t(int code, double* Z, int m, int partner, MPI_Datatype type, MPI_Request request[]);

};

#endif
