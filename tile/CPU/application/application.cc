#include "application.h"
#include "defs.h"

#include "control_defs.h"

void Application::initialize()
{

  tile_id = par("tile_id");
  
  fromProc = gate("fromProc");
  toProc = gate("toProcessor");
  
  processor_control_in = gateHalf("processor_control",cGate::INPUT);
  processor_control_out = gateHalf("processor_control",cGate::OUTPUT);

  state = APP_STATE_BLOCKED; //the application starts being blocked.

  return;
}

void Application::handleMessage(cMessage* msg)
{
  if(INCOMING_GATE(msg,fromProc)){
    //CAST_MSG(res,msg,Instruction);
    //TODO: how do i start???
  }
  if(INCOMING_GATE(msg,processor_control_in)){
    CAST_MSG(cntl,msg,ControlMessage);
    switch(cntl->getResponse_code())
    {
      case APP_PROCESSOR_STATE_RUN:
        if(isBlocked()){
          wakeup();
        }
        break;
      case APP_PROCESSOR_STATE_BLOCKED:
        if(isRunning()){
          block();
        }
        break;
    }
  }
  //chuck the msg. we don't need it anymore, since this was generated by
  //this app in anycase
  delete msg;
  return;
}

bool Application::isBlocked()
{
  return (state == APP_STATE_BLOCKED);
}

bool Application::isRunning()
{
  return (state == APP_STATE_RUNNING);
}

void Application::wakeup()
{
  state = APP_STATE_RUNNING;
  return;
}

void Application::block()
{
  state = APP_STATE_BLOCKED;
  return;
}
