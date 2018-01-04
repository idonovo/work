#include "semaphore.h"

int main(int argc, char **argv)
{

    Input input;
    ParseInput(&input, argc, argv);
    BePong(&input);
    
    return 0;
}
