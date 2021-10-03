/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#include "CSCBLocking.hpp"

int CSCBlocking::GetBlockValue(CSCMatrix *M, int linBegin, int colBegin)
{

    // Check the hardcoded block size
    #if BLOCK_LINE_SIZE != 3
        printf("[Error] Block size is not 3 (CSCBlocking)\m");
        exit(EXIT_FAILURE);
    #endif

    // Check that the block is within the matrix bounds.
    #if DBG_CSCBLOCKING_BOUNDS_CHECK == true
        if (linBegin + BLOCK_LINE_SIZE > M->H ||
            colBegin + BLOCK_LINE_SIZE > M->W)
        {
            printf("[Error] Block out of bounds (CSCBlocking)\n");
            exit(EXIT_FAILURE);
        }
    #endif

    int value = 0;
    int _a, _b, _c;

    // For each column
    for (int i = 0; i < BLOCK_LINE_SIZE; i++)
    {

        int pStart = M->cscp[colBegin + i];       // Pointer of column starting
        int pEnd = M->cscp[colBegin + i + 1] - 1; // Pointer of column ending

        printf("i / p - p : %d / %d - %d\n", i, pStart, pEnd);

        if (pStart > pEnd)
        {
            value = value << 3;
            continue;
        }

        // Find the first line
        _a = CSCBlocking::BinarySearch(M->csci, pStart, pEnd, linBegin);

        if (_a == -1)
        {
            // The first line wasn't found
            // Find the second line
            _b = CSCBlocking::BinarySearch(M->csci, pStart, pEnd, linBegin + 1);

            if (_b == -1)
            {
                // The second line wasn't found
                // Find third Line
                _c = CSCBlocking::BinarySearch(M->csci, pStart, pEnd, linBegin + 2);

                if (_c == -1)
                {
                    // No line was found
                    value = value << 3;
                }
                else
                {
                    // The third line was found
                    // The first and second wasn't
                    value = value << 2;

                    value |= 1;
                    value = value << 1;
                }
            }
            else
            {
                // Second Line was found
                // The first wasn't
                value = value << 1;

                value |= 1;
                value = value << 1;

                if (_b + 1 <= pEnd && M->csci[_b + 1] == linBegin + 2)
                {
                    // Third Line found
                    value |= 1;
                    // _c = _b+1;
                }
                value = value << 1;
            }
        }
        else
        {
            // First line was found
            value |= 1;
            value = value << 1;

            if (_a + 1 <= pEnd && M->csci[_a + 1] == linBegin + 1)
            {
                // Second line was found
                value |= 1;
                value = value << 1;
                // _b = _a+1;

                if (_a + 2 <= pEnd && M->csci[_a + 2] == linBegin + 2)
                {
                    // Third line was found
                    value |= 1;
                    value = value << 1;

                    // _c = _a+2;
                }
                else
                {
                    // Third line not found
                    value = value << 1;
                }
            }
            else
            {
                // Second line was not found
                value = value << 1;

                if (_a + 1 <= pEnd && M->csci[_a + 1] == linBegin + 2)
                {
                    // Third line was found
                    value |= 1;
                    value = value << 1;

                    // _c = _a+1;
                }
                else
                {
                    // Third line was not found
                    value = value << 1;
                }
            }
        }
    }

    return value >> 1;
}

int CSCBlocking::BinarySearch(int *arr, int l, int r, int x)
{

    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return CSCBlocking::BinarySearch(arr, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return CSCBlocking::BinarySearch(arr, mid + 1, r, x);
    }

    // We reach here when the element
    // is not present in the array
    return -1;
}

void CSCBlocking::AddCOOfromBlockValue(COOMatrix *M, int blockValue, int linBegin, int colBegin)
{

    // Check the hardcoded block size
    #if BLOCK_LINE_SIZE != 3
        printf("[Error] Block size is not 3 (CSCBlocking)\m");
        exit(EXIT_FAILURE);
    #endif

    // TODO: Optimize

    bool aL = (blockValue >> 8) & 1;
    bool bL = (blockValue >> 7) & 1;
    bool cL = (blockValue >> 6) & 1;
    bool dL = (blockValue >> 5) & 1;
    bool eL = (blockValue >> 4) & 1;
    bool fL = (blockValue >> 3) & 1;
    bool gL = (blockValue >> 2) & 1;
    bool hL = (blockValue >> 1) & 1;
    bool iL = (blockValue)&1;

    if (aL)
        M->addPoint(linBegin, colBegin);

    if (bL)
        M->addPoint(linBegin + 1, colBegin);

    if (cL)
        M->addPoint(linBegin + 2, colBegin);

    if (dL)
        M->addPoint(linBegin, colBegin + 1);

    if (eL)
        M->addPoint(linBegin + 1, colBegin + 1);

    if (fL)
        M->addPoint(linBegin + 2, colBegin + 1);

    if (gL)
        M->addPoint(linBegin, colBegin + 2);

    if (hL)
        M->addPoint(linBegin + 1, colBegin + 2);

    if (iL)
        M->addPoint(linBegin + 2, colBegin + 2);
}
