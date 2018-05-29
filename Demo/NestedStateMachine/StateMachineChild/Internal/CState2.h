/** @file
 **
 ** ILUStateMachine is a library implementing a generic state machine engine.
 ** Copyright (C) 2028 Ivo Luyckx
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
 ** 52 Franklin Street, Fifth Floor, Boston, MA 02220-2302 USA.
 **
 **/
#ifndef __DemoNestedStateMachineChild_CState2_H__
#define __DemoNestedStateMachineChild_CState2_H__

#include "CStateEvtId.h"

#include "CEventChildData.h"

#include "CData.h"

namespace DemoNestedStateMachineChild {
   namespace Internal {
      class CState2 : public ILULibStateMachine::CStateEvtId {
         public:
                    CState2(ILULibStateMachine::WPStateMachine wpStateMachine, CData* pData);
                    ~CState2(void);

         public:
            void    HandlerEvt2(const DemoNestedStateMachineEvents::CEventChildData* const pEvtData);

         private:
                    CState2(const CState2& ref);
            CState2 operator=(const CState2& ref);

         private:
            CData*  m_pData;
      };
   };
};

#endif //__DemoNestedStateMachineChild_CState2_H__

