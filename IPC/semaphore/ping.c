#include "semaphore.h"

int main(int argc, char **argv)
{

    Input input;
    ParseInput(&input, argc, argv);
    BePing(&input);
    
    return 0;
}
