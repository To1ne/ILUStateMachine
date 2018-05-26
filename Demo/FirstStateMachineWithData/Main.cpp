/** @file
 ** @brief 1-file state machine demo using a state machine data instance
 **
 ** ILUStateMachine is a library implementing a generic state machine engine.
 ** Copyright (C) 2018 Ivo Luyckx
 **
 ** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, write to the Free Software Foundation, Inc.,
 ** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **
 **/
//include the statemachine library and make using it easy
#include "StateMachine.h"
using namespace ILULibStateMachine;

/****************************************************************************************
 ** 
 ** State machine data class declaration.
 ** One instance of this class is created and provided to all states in their 
 ** constructors.
 **
 ***************************************************************************************/
class CData : public CStateMachineData {
public:
  CData(void)
    : CStateMachineData()
    , m_strMsg("no message yet")
  {
  }

public:
  std::string GetMsg(void) const
  {
    return m_strMsg;
  }

  void SetMsg(const std::string& strMsg)
  {
    m_strMsg = strMsg;
  }
  
private:
  std::string m_strMsg;
};

/****************************************************************************************
 ** 
 ** State create function declarations.
 ** These are used during event registration to define the next state after the handler
 ** returned.
 **
 ***************************************************************************************/
CCreateState CreateState1(CData* pData);
CCreateState CreateState2(CData* pData);

/****************************************************************************************
 ** 
 ** First state
 **
 ** This state has 1 event handler. The event ID is an integer (value 1). It calls the
 ** registered handler and then switches to the second state.
 **
 ***************************************************************************************/
/** Class definition of state-1
 **/
class CState1 : public ILULibStateMachine::CStateEvtId {
public:
  CState1(WPStateMachine wpStateMachine, CData* pData)
    : CStateEvtId("state-1", wpStateMachine)
    , m_pData(pData)
  {
    //register event handlers
    EventRegister(
		  HANDLER(int, CState1, HandlerEvt1), //< the event handler
		  CreateState2(pData),                //< the state transition: switch to state-2 when the handler returns
		  1                                   //< the event ID (type integer)
		  );
    LogInfo(boost::format("[%1%][%2%] [%3%] created (current message: [%4%])\n") % __FUNCTION__ % __LINE__ % GetName() % m_pData->GetMsg());
  }
  
  ~CState1(void)
  {
    LogInfo(boost::format("[%1%][%2%] [%3%] destructed (current message: [%4%])\n") % __FUNCTION__ % __LINE__ % GetName() % m_pData->GetMsg());
  }
  
public:
  void HandlerEvt1(const int* const pEvtData)
  {
    LogInfo(boost::format("[%1%][%2%] [%3%] handle first event with data [%4%]\n") % __FUNCTION__ % __LINE__ % GetName() % *pEvtData);
    m_pData->SetMsg((boost::format("first event handled with data [%1%]") % *pEvtData).str());
  }

private:
  CData* const m_pData;
};

/** State transition function for state-1
 **/
CCreateState CreateState1(CData* pData)
{
  return TCreateState<CState1, CData>(pData);
}

/****************************************************************************************
 ** 
 ** Second state.
 **
 ** This state has no event handlers.
 **
 ***************************************************************************************/
/** Class definition of state-2
 **/
class CState2 : public ILULibStateMachine::CStateEvtId {
public:
  CState2(WPStateMachine wpStateMachine, CData* pData)
    : CStateEvtId("state-2", wpStateMachine)
    , m_pData(pData)
  {
    //no event handlers
    LogInfo(boost::format("[%1%][%2%] [%3%] created (current message: [%4%])\n") % __FUNCTION__ % __LINE__ % GetName() % m_pData->GetMsg());
  }
  
  ~CState2(void)
  {
    LogInfo(boost::format("[%1%][%2%] [%3%] destructed (current message: [%4%])\n") % __FUNCTION__ % __LINE__ % GetName() % m_pData->GetMsg());
  }

private:
  CData* const m_pData;
};

/** State transition function for state-2
 **/
CCreateState CreateState2(CData* pData)
{
  return TCreateState<CState2, CData>(pData);
}

/****************************************************************************************
 ** 
 ** State machine.
 **
 ***************************************************************************************/
/** Function returning the state machine.
 **/
SPStateMachine CreateStateMachine(void)
{
  CData* pData = new CData();
  return CStateMachine::ConstructStateMachine(
         "state-machine",     //< name used for logging
         CreateState1(pData), //< used by the state machine to create the initial state
	 pData                //< state machine takes ownership of the data instance and will destruct it
         );
}

/****************************************************************************************
 ** 
 ** This is the main function.
 ** It instantiates the state machine and
 ** sends 1 event to it.
 **
 ***************************************************************************************/
int main (void)
{
   LogInfo(boost::format("[%1%][%2%] first-statemachine-with-data demo in\n") % __FUNCTION__ % __LINE__);

   //create a local scope so that the state machine is
   //destructed when it has handled the event
   {
     //create the state machine
     SPStateMachine spStateMachine = CreateStateMachine();

     //handle event
     //(local scoping event data)
     {
       int iEvtData = 5;
       spStateMachine->EventHandle(&iEvtData, 1);
     }
   }
   
   LogInfo(boost::format("[%1%][%2%] first-statemachine-with-data demo out\n") % __FUNCTION__ % __LINE__);
   return 0;
}

