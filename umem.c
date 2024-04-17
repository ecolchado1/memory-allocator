/*      Erik Colchado     */
/* Lab 3 - Mem. Allocator */
/*         umem.c         */

#include "umem.h"

//Other include statements
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

/* ------------- Local functions (START) ------------- */
size_t roundUpPageSize(size_t sizeOfRegion) {
    size_t roundedSize = 0;
    size_t pageSize = getpagesize();
    size_t pageCount = 0;

    //Once we have the system page size, we can calculate how many are needed
    pageCount = (sizeOfRegion + pageSize - 1)/pageSize;
    roundedSize = pageCount * pageSize;

    printf("Size Requested: %ld, Pages Needed: %ld, Total Page Size Allocated: %ld\n", sizeOfRegion, pageCount, roundedSize);
    return roundedSize;
}

/* ------------- Local functions ( END ) ------------- */

//Local Variables
unsigned int memoryInitilized = 1;
unsigned int allocationAlgorithmVal = 0;

//Initilize Data Structs to be used by the allocator
    //Header that will be assigned to each block of memory
    /*
    typedef struct {
        int size;
     int magic;
    } Header;         
    */
    //Node will manage the head, searching for blocks to allocate to
    typedef struct Node {
        int          size;
        struct Node *next;
    } Node;

/* ----- Required Functions for Memory Allocator ----- */

//Create zero'd pages into address space of calling process
int umeminit(size_t sizeOfRegion, int allocationAlgo) {

    //Check if function call is valid, otherwise exit 
    if (memoryInitilized == 0) {
        perror("Error: memory already initilized");
        return -1;
    }
    if (sizeOfRegion <= 0) {
        perror("Error: sizeOfRegion is less than or equal to 0");
        return -1;
    }

    //If valid call, initilize memory
    //Starting with the allocation algorithm
    switch (allocationAlgo) {
        case BEST_FIT:
            allocationAlgorithmVal = BEST_FIT;
            break;
        case WORST_FIT:
            allocationAlgorithmVal = WORST_FIT;
            break;
        case FIRST_FIT:
            allocationAlgorithmVal = FIRST_FIT;
            break;
        case NEXT_FIT:
            allocationAlgorithmVal = NEXT_FIT;
            break;
        case BUDDY:
            allocationAlgorithmVal = BUDDY;
            break;
        //ERROR - INVALID ALLOCATION ALGORITHM
        default: 
            perror("Invalid Allocation Algorithm Value");
            exit(EXIT_FAILURE);
            break;
    }

    //If a vaild algorithm was given, continue by finding the number of pages (bytes) are requested
    //round up region size provided
    size_t roundedSizeOfRegion = roundUpPageSize(sizeOfRegion);

    int fd = open("/dev/zero", O_RDWR);
    Node *head = mmap(NULL, roundedSizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    //mmap failed
    if (head == MAP_FAILED) {
        perror("Error: mmap failed");
        return -1;
    }

    //Remove the size of the head from available memory 
    head->size = roundedSizeOfRegion - sizeof(Node);
    head->next = NULL;

    //If all else has succeded -- close fd & exit 0
    close(fd);
    memoryInitilized = 0;
    return 0;
}

//User is requesting a block of memory from initilized list
void *umalloc(size_t size) {
    //If memory has not been allocated yet
    if (memoryInitilized = 1) {
        perror("Cannot allocate uninitialized memory");
        return;
    }

    //Based on the allocation algorithm, determine how we allocate memory
        switch (allocationAlgorithmVal) {
        //Best Fit
        case BEST_FIT:

            break;

        //Worst Fit
        case WORST_FIT:

            break;

        //First Fit
        case FIRST_FIT:

            break;

        //Next Fit
        case NEXT_FIT:

            break;

        //ERROR - INVALID ALLOCATION ALGORITHM (Proabably won't happen here, but needed)
        default: 
            perror("Invalid Allocation Algorithm Value");
            exit(EXIT_FAILURE);
            break;
    }

}
/*
int ufree(void *ptr) {

}
*/

//Debugging Routine
void umemdump() {
    
}


/* END OF PROGRAM */