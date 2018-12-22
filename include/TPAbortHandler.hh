#ifndef TPAbortHandler_H
#define TPAbortHandler_H 1

#include "globals.hh"

namespace TPAbortHandler
{

    G4int Install(void);

    void AbortSignalHandler(int sig);

}


#endif
