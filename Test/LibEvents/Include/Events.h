/** @file
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
#ifndef __ILUStateMachine_Events__H__
#define __ILUStateMachine_Events__H__

#include "CCreateState.h"

/**********************************************************************************
 **
 ** This is the event machine
 **
 ** This can be for example a LibOsCommunication::CServerTimer extension
 ** which can already deliver messages and timers as events and call
 ** registered functions for them.
 **
 ** The event machine has to be aware of the root-state machine it has to call
 ** (all events enter the root-state machine, from which they are potentially
 ** propagated to other state machines, depending on the current state).
 ** This has to be done by an initialization call.
 ** 
 ** Since all events (also events generated by state threads) are delivered by
 ** the one and only event machine, the state machines themselves to not have to
 ** be thread safe.
 ** The only location where thread safety has to be considdered is inside a state
 ** (which stronly limits the scope and frequency of locking) and only when that
 ** state starts worker threads which share data with the state class itself 
 ** (apart for some simple stop-flag).
 **
 ** This should be generic and not dependent on MyStateMachine, since it will be
 ** a generic extension on CMbxServer.
 **
 **********************************************************************************/
namespace LibEvents {
   //events, similar to message ID's
   enum EEvents {
      EEvent1 = 1,
      EEvent2 = 2,
      EEvent3 = 3,
      EEvent4 = 4,
      EEvent5 = 5,
      EEvent6 = 6,
      EEvent7 = 7,
      EEvent8 = 8,
      EEvent9 = 9,
   };

   //data belonging to the event, provided to the handler,
   //similar to the IMbx* for messages
   //one event machine implementation can have multiple event types,
   //all with their own ID's and their dedicated data classes,
   //no casts will be required!
   class CEventData {
      public:
         CEventData(const int iVal)
            : m_iVal(iVal)
         {
         };

      public:
         int m_iVal;
   };
};

#define GUARD_EVT(cl,f)   GUARD(LibEvents::CEventData, cl,f)
#define HANDLER_EVT(cl,f) HANDLER(LibEvents::CEventData, cl,f)

#endif //__ILUStateMachine_Events__H__

