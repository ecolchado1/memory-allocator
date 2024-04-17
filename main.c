/*      Erik Colchado     */
/* Lab 3 - Mem. Allocator */
/*         main.c         */

//Import Statements
#include "umem.c"

//Defined values


//Main
int main (int argc, char** argv)  {
    umeminit(0, BEST_FIT);
    umeminit(2222, WORST_FIT);  
    umeminit(1234, BUDDY);  
}
