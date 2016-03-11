#ifndef DT3_LATENTCALL
#define DT3_LATENTCALL
//==============================================================================
///	
///	File: LatentCall.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Utility/Callback.hpp"
#include <memory>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

class LatentCall {
    public:
        DEFINE_TYPE_BASE(LatentCall)

                        LatentCall          (void)                      {}
                        LatentCall          (const LatentCall &rhs)     {}
        LatentCall&     operator =          (const LatentCall& rhs)     {	return (*this);     }
                        ~LatentCall         (void)                      {}

    public:
        virtual void    fire            (void) = 0;
};

//==============================================================================
//==============================================================================

class LatentCall0: public LatentCall {
    public:		         
        DEFINE_TYPE(LatentCall0,LatentCall)
        
        LatentCall0 (std::shared_ptr<Callback0> cb) 
        	:	_cb(cb)
        {}
        
        LatentCall0  (const LatentCall0 &rhs)
            :   LatentCall(rhs),
            	_cb(rhs._cb)
        {}
        
        LatentCall0&     operator =          (const LatentCall0& rhs)
        {
            LatentCall::operator = (rhs);
            _cb = rhs._cb;
            
            return (*this);
        }
        
        ~LatentCall0         (void)
        {
        
        }


        void fire       () {
            (*_cb)();
        }

    private:
        std::shared_ptr<Callback0>     _cb;
};

//==============================================================================
//==============================================================================

template <typename T0>
class LatentCall1: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall1,LatentCall)

		LatentCall1 (std::shared_ptr<Callback1<T0> > cb,
			const typename TypeTraits<T0>::NonRefType &t0
		)
			:	_cb(cb),
				_t0(t0)
		{}

		LatentCall1 (const LatentCall1<T0>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0)
		{}

		LatentCall1<T0>& operator = (const LatentCall1<T0>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			return (*this);
		}

		~LatentCall1 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0);
		}

	private:
		std::shared_ptr<Callback1<T0> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
};

template <typename T0,typename T1>
class LatentCall2: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall2,LatentCall)

		LatentCall2 (std::shared_ptr<Callback2<T0,T1> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1)
		{}

		LatentCall2 (const LatentCall2<T0,T1>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1)
		{}

		LatentCall2<T0,T1>& operator = (const LatentCall2<T0,T1>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			return (*this);
		}

		~LatentCall2 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1);
		}

	private:
		std::shared_ptr<Callback2<T0,T1> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
};

template <typename T0,typename T1,typename T2>
class LatentCall3: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall3,LatentCall)

		LatentCall3 (std::shared_ptr<Callback3<T0,T1,T2> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2)
		{}

		LatentCall3 (const LatentCall3<T0,T1,T2>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2)
		{}

		LatentCall3<T0,T1,T2>& operator = (const LatentCall3<T0,T1,T2>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			return (*this);
		}

		~LatentCall3 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2);
		}

	private:
		std::shared_ptr<Callback3<T0,T1,T2> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
};

template <typename T0,typename T1,typename T2,typename T3>
class LatentCall4: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall4,LatentCall)

		LatentCall4 (std::shared_ptr<Callback4<T0,T1,T2,T3> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3)
		{}

		LatentCall4 (const LatentCall4<T0,T1,T2,T3>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3)
		{}

		LatentCall4<T0,T1,T2,T3>& operator = (const LatentCall4<T0,T1,T2,T3>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			return (*this);
		}

		~LatentCall4 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3);
		}

	private:
		std::shared_ptr<Callback4<T0,T1,T2,T3> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4>
class LatentCall5: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall5,LatentCall)

		LatentCall5 (std::shared_ptr<Callback5<T0,T1,T2,T3,T4> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4)
		{}

		LatentCall5 (const LatentCall5<T0,T1,T2,T3,T4>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4)
		{}

		LatentCall5<T0,T1,T2,T3,T4>& operator = (const LatentCall5<T0,T1,T2,T3,T4>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			return (*this);
		}

		~LatentCall5 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4);
		}

	private:
		std::shared_ptr<Callback5<T0,T1,T2,T3,T4> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
class LatentCall6: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall6,LatentCall)

		LatentCall6 (std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5)
		{}

		LatentCall6 (const LatentCall6<T0,T1,T2,T3,T4,T5>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5)
		{}

		LatentCall6<T0,T1,T2,T3,T4,T5>& operator = (const LatentCall6<T0,T1,T2,T3,T4,T5>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			return (*this);
		}

		~LatentCall6 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5);
		}

	private:
		std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
class LatentCall7: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall7,LatentCall)

		LatentCall7 (std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6)
		{}

		LatentCall7 (const LatentCall7<T0,T1,T2,T3,T4,T5,T6>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6)
		{}

		LatentCall7<T0,T1,T2,T3,T4,T5,T6>& operator = (const LatentCall7<T0,T1,T2,T3,T4,T5,T6>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			return (*this);
		}

		~LatentCall7 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6);
		}

	private:
		std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
class LatentCall8: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall8,LatentCall)

		LatentCall8 (std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7)
		{}

		LatentCall8 (const LatentCall8<T0,T1,T2,T3,T4,T5,T6,T7>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7)
		{}

		LatentCall8<T0,T1,T2,T3,T4,T5,T6,T7>& operator = (const LatentCall8<T0,T1,T2,T3,T4,T5,T6,T7>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			return (*this);
		}

		~LatentCall8 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7);
		}

	private:
		std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
class LatentCall9: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall9,LatentCall)

		LatentCall9 (std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8)
		{}

		LatentCall9 (const LatentCall9<T0,T1,T2,T3,T4,T5,T6,T7,T8>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8)
		{}

		LatentCall9<T0,T1,T2,T3,T4,T5,T6,T7,T8>& operator = (const LatentCall9<T0,T1,T2,T3,T4,T5,T6,T7,T8>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			return (*this);
		}

		~LatentCall9 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8);
		}

	private:
		std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
class LatentCall10: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall10,LatentCall)

		LatentCall10 (std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8,
			const typename TypeTraits<T9>::NonRefType &t9
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8),
				_t9(t9)
		{}

		LatentCall10 (const LatentCall10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8),
				_t9(rhs._t9)
		{}

		LatentCall10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>& operator = (const LatentCall10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			_t9 = rhs.t9;
			return (*this);
		}

		~LatentCall10 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8,_t9);
		}

	private:
		std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
		typename TypeTraits<T9>::BaseType _t9;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
class LatentCall11: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall11,LatentCall)

		LatentCall11 (std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8,
			const typename TypeTraits<T9>::NonRefType &t9,
			const typename TypeTraits<T10>::NonRefType &t10
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8),
				_t9(t9),
				_t10(t10)
		{}

		LatentCall11 (const LatentCall11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8),
				_t9(rhs._t9),
				_t10(rhs._t10)
		{}

		LatentCall11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>& operator = (const LatentCall11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			_t9 = rhs.t9;
			_t10 = rhs.t10;
			return (*this);
		}

		~LatentCall11 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8,_t9,_t10);
		}

	private:
		std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
		typename TypeTraits<T9>::BaseType _t9;
		typename TypeTraits<T10>::BaseType _t10;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
class LatentCall12: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall12,LatentCall)

		LatentCall12 (std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8,
			const typename TypeTraits<T9>::NonRefType &t9,
			const typename TypeTraits<T10>::NonRefType &t10,
			const typename TypeTraits<T11>::NonRefType &t11
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8),
				_t9(t9),
				_t10(t10),
				_t11(t11)
		{}

		LatentCall12 (const LatentCall12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8),
				_t9(rhs._t9),
				_t10(rhs._t10),
				_t11(rhs._t11)
		{}

		LatentCall12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>& operator = (const LatentCall12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			_t9 = rhs.t9;
			_t10 = rhs.t10;
			_t11 = rhs.t11;
			return (*this);
		}

		~LatentCall12 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8,_t9,_t10,_t11);
		}

	private:
		std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
		typename TypeTraits<T9>::BaseType _t9;
		typename TypeTraits<T10>::BaseType _t10;
		typename TypeTraits<T11>::BaseType _t11;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
class LatentCall13: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall13,LatentCall)

		LatentCall13 (std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8,
			const typename TypeTraits<T9>::NonRefType &t9,
			const typename TypeTraits<T10>::NonRefType &t10,
			const typename TypeTraits<T11>::NonRefType &t11,
			const typename TypeTraits<T12>::NonRefType &t12
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8),
				_t9(t9),
				_t10(t10),
				_t11(t11),
				_t12(t12)
		{}

		LatentCall13 (const LatentCall13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8),
				_t9(rhs._t9),
				_t10(rhs._t10),
				_t11(rhs._t11),
				_t12(rhs._t12)
		{}

		LatentCall13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>& operator = (const LatentCall13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			_t9 = rhs.t9;
			_t10 = rhs.t10;
			_t11 = rhs.t11;
			_t12 = rhs.t12;
			return (*this);
		}

		~LatentCall13 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8,_t9,_t10,_t11,_t12);
		}

	private:
		std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
		typename TypeTraits<T9>::BaseType _t9;
		typename TypeTraits<T10>::BaseType _t10;
		typename TypeTraits<T11>::BaseType _t11;
		typename TypeTraits<T12>::BaseType _t12;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
class LatentCall14: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall14,LatentCall)

		LatentCall14 (std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8,
			const typename TypeTraits<T9>::NonRefType &t9,
			const typename TypeTraits<T10>::NonRefType &t10,
			const typename TypeTraits<T11>::NonRefType &t11,
			const typename TypeTraits<T12>::NonRefType &t12,
			const typename TypeTraits<T13>::NonRefType &t13
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8),
				_t9(t9),
				_t10(t10),
				_t11(t11),
				_t12(t12),
				_t13(t13)
		{}

		LatentCall14 (const LatentCall14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8),
				_t9(rhs._t9),
				_t10(rhs._t10),
				_t11(rhs._t11),
				_t12(rhs._t12),
				_t13(rhs._t13)
		{}

		LatentCall14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>& operator = (const LatentCall14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			_t9 = rhs.t9;
			_t10 = rhs.t10;
			_t11 = rhs.t11;
			_t12 = rhs.t12;
			_t13 = rhs.t13;
			return (*this);
		}

		~LatentCall14 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8,_t9,_t10,_t11,_t12,_t13);
		}

	private:
		std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
		typename TypeTraits<T9>::BaseType _t9;
		typename TypeTraits<T10>::BaseType _t10;
		typename TypeTraits<T11>::BaseType _t11;
		typename TypeTraits<T12>::BaseType _t12;
		typename TypeTraits<T13>::BaseType _t13;
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
class LatentCall15: public LatentCall {
	public:
		DEFINE_TYPE(LatentCall15,LatentCall)

		LatentCall15 (std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> > cb,
			const typename TypeTraits<T0>::NonRefType &t0,
			const typename TypeTraits<T1>::NonRefType &t1,
			const typename TypeTraits<T2>::NonRefType &t2,
			const typename TypeTraits<T3>::NonRefType &t3,
			const typename TypeTraits<T4>::NonRefType &t4,
			const typename TypeTraits<T5>::NonRefType &t5,
			const typename TypeTraits<T6>::NonRefType &t6,
			const typename TypeTraits<T7>::NonRefType &t7,
			const typename TypeTraits<T8>::NonRefType &t8,
			const typename TypeTraits<T9>::NonRefType &t9,
			const typename TypeTraits<T10>::NonRefType &t10,
			const typename TypeTraits<T11>::NonRefType &t11,
			const typename TypeTraits<T12>::NonRefType &t12,
			const typename TypeTraits<T13>::NonRefType &t13,
			const typename TypeTraits<T14>::NonRefType &t14
		)
			:	_cb(cb),
				_t0(t0),
				_t1(t1),
				_t2(t2),
				_t3(t3),
				_t4(t4),
				_t5(t5),
				_t6(t6),
				_t7(t7),
				_t8(t8),
				_t9(t9),
				_t10(t10),
				_t11(t11),
				_t12(t12),
				_t13(t13),
				_t14(t14)
		{}

		LatentCall15 (const LatentCall15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>& rhs)
			:	LatentCall(rhs),
				_cb(rhs._cb),
				_t0(rhs._t0),
				_t1(rhs._t1),
				_t2(rhs._t2),
				_t3(rhs._t3),
				_t4(rhs._t4),
				_t5(rhs._t5),
				_t6(rhs._t6),
				_t7(rhs._t7),
				_t8(rhs._t8),
				_t9(rhs._t9),
				_t10(rhs._t10),
				_t11(rhs._t11),
				_t12(rhs._t12),
				_t13(rhs._t13),
				_t14(rhs._t14)
		{}

		LatentCall15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>& operator = (const LatentCall15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>& rhs)
		{
			LatentCall::operator = (rhs);
			_cb = rhs._cb;
			_t0 = rhs.t0;
			_t1 = rhs.t1;
			_t2 = rhs.t2;
			_t3 = rhs.t3;
			_t4 = rhs.t4;
			_t5 = rhs.t5;
			_t6 = rhs.t6;
			_t7 = rhs.t7;
			_t8 = rhs.t8;
			_t9 = rhs.t9;
			_t10 = rhs.t10;
			_t11 = rhs.t11;
			_t12 = rhs.t12;
			_t13 = rhs.t13;
			_t14 = rhs.t14;
			return (*this);
		}

		~LatentCall15 (void)
		{
		}

		void fire (void) {
			(*_cb)(_t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7,_t8,_t9,_t10,_t11,_t12,_t13,_t14);
		}

	private:
		std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> > _cb;
		typename TypeTraits<T0>::BaseType _t0;
		typename TypeTraits<T1>::BaseType _t1;
		typename TypeTraits<T2>::BaseType _t2;
		typename TypeTraits<T3>::BaseType _t3;
		typename TypeTraits<T4>::BaseType _t4;
		typename TypeTraits<T5>::BaseType _t5;
		typename TypeTraits<T6>::BaseType _t6;
		typename TypeTraits<T7>::BaseType _t7;
		typename TypeTraits<T8>::BaseType _t8;
		typename TypeTraits<T9>::BaseType _t9;
		typename TypeTraits<T10>::BaseType _t10;
		typename TypeTraits<T11>::BaseType _t11;
		typename TypeTraits<T12>::BaseType _t12;
		typename TypeTraits<T13>::BaseType _t13;
		typename TypeTraits<T14>::BaseType _t14;
};

//==============================================================================
//==============================================================================

template<typename CLASS>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(void))
{
    return  std::shared_ptr<LatentCall>(
                new LatentCall0(
                    std::shared_ptr<Callback0>(new ("Callback0") Callback0Impl<CLASS>(c, fn))
                )
            );
}

template<typename CLASS, typename T0>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0),
		typename TypeTraits<T0>::NonRefType t0
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall1<T0>(
					std::shared_ptr<Callback1<T0> >(new ("Callback1") Callback1Impl<CLASS,T0>(c, fn)),
					t0
				)
			);
}

template<typename CLASS, typename T0,typename T1>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall2<T0,T1>(
					std::shared_ptr<Callback2<T0,T1> >(new ("Callback2") Callback2Impl<CLASS,T0,T1>(c, fn)),
					t0,t1
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall3<T0,T1,T2>(
					std::shared_ptr<Callback3<T0,T1,T2> >(new ("Callback3") Callback3Impl<CLASS,T0,T1,T2>(c, fn)),
					t0,t1,t2
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall4<T0,T1,T2,T3>(
					std::shared_ptr<Callback4<T0,T1,T2,T3> >(new ("Callback4") Callback4Impl<CLASS,T0,T1,T2,T3>(c, fn)),
					t0,t1,t2,t3
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall5<T0,T1,T2,T3,T4>(
					std::shared_ptr<Callback5<T0,T1,T2,T3,T4> >(new ("Callback5") Callback5Impl<CLASS,T0,T1,T2,T3,T4>(c, fn)),
					t0,t1,t2,t3,t4
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall6<T0,T1,T2,T3,T4,T5>(
					std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> >(new ("Callback6") Callback6Impl<CLASS,T0,T1,T2,T3,T4,T5>(c, fn)),
					t0,t1,t2,t3,t4,t5
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall7<T0,T1,T2,T3,T4,T5,T6>(
					std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> >(new ("Callback7") Callback7Impl<CLASS,T0,T1,T2,T3,T4,T5,T6>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall8<T0,T1,T2,T3,T4,T5,T6,T7>(
					std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> >(new ("Callback8") Callback8Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall9<T0,T1,T2,T3,T4,T5,T6,T7,T8>(
					std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> >(new ("Callback9") Callback9Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>(
					std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> >(new ("Callback10") Callback10Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(
					std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> >(new ("Callback11") Callback11Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(
					std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> >(new ("Callback12") Callback12Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11,
		typename TypeTraits<T12>::NonRefType t12
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(
					std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> >(new ("Callback13") Callback13Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11,
		typename TypeTraits<T12>::NonRefType t12,
		typename TypeTraits<T13>::NonRefType t13
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(
					std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> >(new ("Callback14") Callback14Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13
				)
			);
}

template<typename CLASS, typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline std::shared_ptr<LatentCall> makeLatentCall(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11,
		typename TypeTraits<T12>::NonRefType t12,
		typename TypeTraits<T13>::NonRefType t13,
		typename TypeTraits<T14>::NonRefType t14
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(
					std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> >(new ("Callback15") Callback15Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(c, fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14
				)
			);
}

//==============================================================================
//==============================================================================

inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(void))
{
    return  std::shared_ptr<LatentCall>(
                new LatentCall0(
                    std::shared_ptr<Callback0>(new ("Callback0") CallbackStatic0Impl(fn))
                )
            );
}

template<typename T0>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0),
		typename TypeTraits<T0>::NonRefType t0
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall1<T0>(
					std::shared_ptr<Callback1<T0> >(new ("Callback1") CallbackStatic1Impl<T0>(fn)),
					t0
				)
			);
}

template<typename T0,typename T1>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall2<T0,T1>(
					std::shared_ptr<Callback2<T0,T1> >(new ("Callback2") CallbackStatic2Impl<T0,T1>(fn)),
					t0,t1
				)
			);
}

template<typename T0,typename T1,typename T2>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall3<T0,T1,T2>(
					std::shared_ptr<Callback3<T0,T1,T2> >(new ("Callback3") CallbackStatic3Impl<T0,T1,T2>(fn)),
					t0,t1,t2
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall4<T0,T1,T2,T3>(
					std::shared_ptr<Callback4<T0,T1,T2,T3> >(new ("Callback4") CallbackStatic4Impl<T0,T1,T2,T3>(fn)),
					t0,t1,t2,t3
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall5<T0,T1,T2,T3,T4>(
					std::shared_ptr<Callback5<T0,T1,T2,T3,T4> >(new ("Callback5") CallbackStatic5Impl<T0,T1,T2,T3,T4>(fn)),
					t0,t1,t2,t3,t4
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall6<T0,T1,T2,T3,T4,T5>(
					std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> >(new ("Callback6") CallbackStatic6Impl<T0,T1,T2,T3,T4,T5>(fn)),
					t0,t1,t2,t3,t4,t5
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall7<T0,T1,T2,T3,T4,T5,T6>(
					std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> >(new ("Callback7") CallbackStatic7Impl<T0,T1,T2,T3,T4,T5,T6>(fn)),
					t0,t1,t2,t3,t4,t5,t6
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall8<T0,T1,T2,T3,T4,T5,T6,T7>(
					std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> >(new ("Callback8") CallbackStatic8Impl<T0,T1,T2,T3,T4,T5,T6,T7>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall9<T0,T1,T2,T3,T4,T5,T6,T7,T8>(
					std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> >(new ("Callback9") CallbackStatic9Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>(
					std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> >(new ("Callback10") CallbackStatic10Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(
					std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> >(new ("Callback11") CallbackStatic11Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(
					std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> >(new ("Callback12") CallbackStatic12Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11,
		typename TypeTraits<T12>::NonRefType t12
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(
					std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> >(new ("Callback13") CallbackStatic13Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11,
		typename TypeTraits<T12>::NonRefType t12,
		typename TypeTraits<T13>::NonRefType t13
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(
					std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> >(new ("Callback14") CallbackStatic14Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13
				)
			);
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline std::shared_ptr<LatentCall> makeLatentCall(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14),
		typename TypeTraits<T0>::NonRefType t0,
		typename TypeTraits<T1>::NonRefType t1,
		typename TypeTraits<T2>::NonRefType t2,
		typename TypeTraits<T3>::NonRefType t3,
		typename TypeTraits<T4>::NonRefType t4,
		typename TypeTraits<T5>::NonRefType t5,
		typename TypeTraits<T6>::NonRefType t6,
		typename TypeTraits<T7>::NonRefType t7,
		typename TypeTraits<T8>::NonRefType t8,
		typename TypeTraits<T9>::NonRefType t9,
		typename TypeTraits<T10>::NonRefType t10,
		typename TypeTraits<T11>::NonRefType t11,
		typename TypeTraits<T12>::NonRefType t12,
		typename TypeTraits<T13>::NonRefType t13,
		typename TypeTraits<T14>::NonRefType t14
)
{
	return std::shared_ptr<LatentCall>(
				new LatentCall15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(
					std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> >(new ("Callback15") CallbackStatic15Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(fn)),
					t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14
				)
			);
}

//==============================================================================
//==============================================================================

} // DT3

#endif
