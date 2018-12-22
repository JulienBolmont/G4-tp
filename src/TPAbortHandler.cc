#include "TPAbortHandler.hh"

#include "G4ApplicationState.hh"
#include "G4RunManager.hh"
#include "G4StateManager.hh"
#include <csignal>


G4int TPAbortHandler::Install()
{
  // Install the signal handler for SIGQUIT only
  if (signal(SIGINT,AbortSignalHandler) == SIG_ERR) {
    G4cerr << G4endl << "Warning! Could not install handler for CTRL-(SIGINT)!" << G4endl << G4endl;
    return -1;
  }
  return 0;
}


void TPAbortHandler::AbortSignalHandler(int sig)
{
  // Print that we received the signal to G4cerr
  G4cerr << G4endl;
  psignal(sig,"Received signal");

  // Process the signal
  G4ApplicationState state = G4StateManager::GetStateManager()->GetCurrentState();
  switch (state)
  {
    case G4State_GeomClosed:
    case G4State_EventProc:
      // If a beamOn/StartDAQ is running, launch abort sequence
      G4cerr << "--- Aborting run! (Ctrl-C) ---" << G4endl << G4endl;
      G4RunManager::GetRunManager()->AbortRun(true);
      break;
    default:
      // In other modes, ignore the signal
      G4cerr << "Signal received in state '" <<
        G4StateManager::GetStateManager()->GetStateString(state) << "' "
             << " --> ignored!" << G4endl << G4endl;
      break;
  }
}
