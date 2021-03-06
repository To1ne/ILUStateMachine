/** @file
 ** @brief The TCreateState template function defintions.
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
#ifndef __ILULibStateMachine_TCreateState__H__
#define __ILULibStateMachine_TCreateState__H__

#include "CCreateState.h"
#include "CStateMachine.h"
#include "Types.h"

namespace ILULibStateMachine {
   /** @brief Templates to ease implementation of the state creation functions.
    **
    ** The templates assume a simple state class type that has 2 parameters:
    ** - a weak pointer to the state machine the class belongs to;
    ** - a raw pointer to a state machine data class.
    **/
   template<class CStateType, class CDataType> CState* TCreateStateInstance(WPStateMachine wpStateMachine, CDataType* pData)
   {
      return new CStateType(wpStateMachine, pData);
   }
   
   /** Wrapper template around TCreateStateInstance that binds
    ** the state create function as expected by the state machine
    ** CCreateState.
    **/
   template<class CStateType, class CDataType> CCreateState TCreateState(CDataType* pData)
   {
      return CCreateState(
         TYPESEL::bind(
            &TCreateStateInstance<CStateType,CDataType>, 
            TYPESEL_PLACEHOLDERS_1,
            pData
            )
         );
   }
}

#endif //__ILULibStateMachine_TCreateState__H__

