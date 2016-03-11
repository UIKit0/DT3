#ifndef DT3_CALLBACK
#define DT3_CALLBACK
//==============================================================================
///	
///	File: Callback.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Utility/CheckedCast.hpp"
#include <memory>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

class Callback0 {
    public:
        DEFINE_TYPE_BASE(Callback0)
        virtual ~Callback0(void)    {}
        virtual void        operator ()(void) = 0;
		virtual DTboolean	operator ==	(const Callback0& rhs) const = 0;
};

template <typename CLASS>
class Callback0Impl: public Callback0 {
    public:		         
        DEFINE_TYPE(Callback0Impl,Callback0)

        Callback0Impl	(CLASS *c, void (CLASS::*fn)(void))
        {
            _obj = c;
            _fn = fn;
        }

        virtual void    operator ()(void)
        {
            if (_obj && _fn)
                (_obj->*_fn)();
        }
        
		virtual DTboolean	operator ==	(const Callback0& rhs) const
        {
            const Callback0Impl<CLASS> *rhs_type = checkedCast<const Callback0Impl<CLASS> *>(&rhs);
            return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
        }

	public:
        CLASS           *_obj;
        void            (CLASS::*_fn)(void);
};

class CallbackStatic0Impl: public Callback0 {
    public:		         
        DEFINE_TYPE(CallbackStatic0Impl,Callback0)

        CallbackStatic0Impl	(void (*fn)(void))
        {
            _fn = fn;
        }

        virtual void    operator ()(void)
        {
            if (_fn)
                (_fn)();
        }
        
		virtual DTboolean	operator ==	(const Callback0& rhs) const
        {
            const CallbackStatic0Impl *rhs_type = checkedCast<const CallbackStatic0Impl *>(&rhs);
            return rhs_type && (_fn == rhs_type->_fn);
        }

	public:
        void            (*_fn)(void);
};

//==============================================================================
//==============================================================================


template <typename T0>
class Callback1 {
	public:
		DEFINE_TYPE_BASE(Callback1)
		virtual ~Callback1(void)    {}
		virtual void operator ()(T0 t0) = 0;
		virtual DTboolean	operator ==	(const Callback1& rhs) const = 0;
};

template <typename CLASS,typename T0>
class Callback1Impl: public Callback1<T0> {
	public:
		typedef Callback1<T0> CBT;
		DEFINE_TYPE(Callback1Impl,CBT)

		Callback1Impl (CLASS *c, void (CLASS::*fn)(T0 t0))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback1Impl<CLASS,T0> *rhs_type = checkedCast<const Callback1Impl<CLASS,T0> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0);
};

template <typename T0>
class CallbackStatic1Impl: public Callback1<T0> {
	public:
		typedef Callback1<T0> CBT;
		DEFINE_TYPE(CallbackStatic1Impl,CBT)

		CallbackStatic1Impl (void (*fn)(T0 t0))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0)
		{
			if (_fn)
				(*_fn)(t0);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic1Impl<T0> *rhs_type = checkedCast<const CallbackStatic1Impl<T0> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1>
class Callback2 {
	public:
		DEFINE_TYPE_BASE(Callback2)
		virtual ~Callback2(void)    {}
		virtual void operator ()(T0 t0,T1 t1) = 0;
		virtual DTboolean	operator ==	(const Callback2& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1>
class Callback2Impl: public Callback2<T0,T1> {
	public:
		typedef Callback2<T0,T1> CBT;
		DEFINE_TYPE(Callback2Impl,CBT)

		Callback2Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback2Impl<CLASS,T0,T1> *rhs_type = checkedCast<const Callback2Impl<CLASS,T0,T1> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1);
};

template <typename T0,typename T1>
class CallbackStatic2Impl: public Callback2<T0,T1> {
	public:
		typedef Callback2<T0,T1> CBT;
		DEFINE_TYPE(CallbackStatic2Impl,CBT)

		CallbackStatic2Impl (void (*fn)(T0 t0,T1 t1))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1)
		{
			if (_fn)
				(*_fn)(t0,t1);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic2Impl<T0,T1> *rhs_type = checkedCast<const CallbackStatic2Impl<T0,T1> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2>
class Callback3 {
	public:
		DEFINE_TYPE_BASE(Callback3)
		virtual ~Callback3(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2) = 0;
		virtual DTboolean	operator ==	(const Callback3& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2>
class Callback3Impl: public Callback3<T0,T1,T2> {
	public:
		typedef Callback3<T0,T1,T2> CBT;
		DEFINE_TYPE(Callback3Impl,CBT)

		Callback3Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback3Impl<CLASS,T0,T1,T2> *rhs_type = checkedCast<const Callback3Impl<CLASS,T0,T1,T2> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2);
};

template <typename T0,typename T1,typename T2>
class CallbackStatic3Impl: public Callback3<T0,T1,T2> {
	public:
		typedef Callback3<T0,T1,T2> CBT;
		DEFINE_TYPE(CallbackStatic3Impl,CBT)

		CallbackStatic3Impl (void (*fn)(T0 t0,T1 t1,T2 t2))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2)
		{
			if (_fn)
				(*_fn)(t0,t1,t2);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic3Impl<T0,T1,T2> *rhs_type = checkedCast<const CallbackStatic3Impl<T0,T1,T2> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3>
class Callback4 {
	public:
		DEFINE_TYPE_BASE(Callback4)
		virtual ~Callback4(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3) = 0;
		virtual DTboolean	operator ==	(const Callback4& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3>
class Callback4Impl: public Callback4<T0,T1,T2,T3> {
	public:
		typedef Callback4<T0,T1,T2,T3> CBT;
		DEFINE_TYPE(Callback4Impl,CBT)

		Callback4Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback4Impl<CLASS,T0,T1,T2,T3> *rhs_type = checkedCast<const Callback4Impl<CLASS,T0,T1,T2,T3> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3);
};

template <typename T0,typename T1,typename T2,typename T3>
class CallbackStatic4Impl: public Callback4<T0,T1,T2,T3> {
	public:
		typedef Callback4<T0,T1,T2,T3> CBT;
		DEFINE_TYPE(CallbackStatic4Impl,CBT)

		CallbackStatic4Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic4Impl<T0,T1,T2,T3> *rhs_type = checkedCast<const CallbackStatic4Impl<T0,T1,T2,T3> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4>
class Callback5 {
	public:
		DEFINE_TYPE_BASE(Callback5)
		virtual ~Callback5(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4) = 0;
		virtual DTboolean	operator ==	(const Callback5& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4>
class Callback5Impl: public Callback5<T0,T1,T2,T3,T4> {
	public:
		typedef Callback5<T0,T1,T2,T3,T4> CBT;
		DEFINE_TYPE(Callback5Impl,CBT)

		Callback5Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback5Impl<CLASS,T0,T1,T2,T3,T4> *rhs_type = checkedCast<const Callback5Impl<CLASS,T0,T1,T2,T3,T4> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4>
class CallbackStatic5Impl: public Callback5<T0,T1,T2,T3,T4> {
	public:
		typedef Callback5<T0,T1,T2,T3,T4> CBT;
		DEFINE_TYPE(CallbackStatic5Impl,CBT)

		CallbackStatic5Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic5Impl<T0,T1,T2,T3,T4> *rhs_type = checkedCast<const CallbackStatic5Impl<T0,T1,T2,T3,T4> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
class Callback6 {
	public:
		DEFINE_TYPE_BASE(Callback6)
		virtual ~Callback6(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5) = 0;
		virtual DTboolean	operator ==	(const Callback6& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
class Callback6Impl: public Callback6<T0,T1,T2,T3,T4,T5> {
	public:
		typedef Callback6<T0,T1,T2,T3,T4,T5> CBT;
		DEFINE_TYPE(Callback6Impl,CBT)

		Callback6Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback6Impl<CLASS,T0,T1,T2,T3,T4,T5> *rhs_type = checkedCast<const Callback6Impl<CLASS,T0,T1,T2,T3,T4,T5> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
class CallbackStatic6Impl: public Callback6<T0,T1,T2,T3,T4,T5> {
	public:
		typedef Callback6<T0,T1,T2,T3,T4,T5> CBT;
		DEFINE_TYPE(CallbackStatic6Impl,CBT)

		CallbackStatic6Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic6Impl<T0,T1,T2,T3,T4,T5> *rhs_type = checkedCast<const CallbackStatic6Impl<T0,T1,T2,T3,T4,T5> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
class Callback7 {
	public:
		DEFINE_TYPE_BASE(Callback7)
		virtual ~Callback7(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6) = 0;
		virtual DTboolean	operator ==	(const Callback7& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
class Callback7Impl: public Callback7<T0,T1,T2,T3,T4,T5,T6> {
	public:
		typedef Callback7<T0,T1,T2,T3,T4,T5,T6> CBT;
		DEFINE_TYPE(Callback7Impl,CBT)

		Callback7Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback7Impl<CLASS,T0,T1,T2,T3,T4,T5,T6> *rhs_type = checkedCast<const Callback7Impl<CLASS,T0,T1,T2,T3,T4,T5,T6> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
class CallbackStatic7Impl: public Callback7<T0,T1,T2,T3,T4,T5,T6> {
	public:
		typedef Callback7<T0,T1,T2,T3,T4,T5,T6> CBT;
		DEFINE_TYPE(CallbackStatic7Impl,CBT)

		CallbackStatic7Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic7Impl<T0,T1,T2,T3,T4,T5,T6> *rhs_type = checkedCast<const CallbackStatic7Impl<T0,T1,T2,T3,T4,T5,T6> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
class Callback8 {
	public:
		DEFINE_TYPE_BASE(Callback8)
		virtual ~Callback8(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7) = 0;
		virtual DTboolean	operator ==	(const Callback8& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
class Callback8Impl: public Callback8<T0,T1,T2,T3,T4,T5,T6,T7> {
	public:
		typedef Callback8<T0,T1,T2,T3,T4,T5,T6,T7> CBT;
		DEFINE_TYPE(Callback8Impl,CBT)

		Callback8Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback8Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7> *rhs_type = checkedCast<const Callback8Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
class CallbackStatic8Impl: public Callback8<T0,T1,T2,T3,T4,T5,T6,T7> {
	public:
		typedef Callback8<T0,T1,T2,T3,T4,T5,T6,T7> CBT;
		DEFINE_TYPE(CallbackStatic8Impl,CBT)

		CallbackStatic8Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic8Impl<T0,T1,T2,T3,T4,T5,T6,T7> *rhs_type = checkedCast<const CallbackStatic8Impl<T0,T1,T2,T3,T4,T5,T6,T7> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
class Callback9 {
	public:
		DEFINE_TYPE_BASE(Callback9)
		virtual ~Callback9(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8) = 0;
		virtual DTboolean	operator ==	(const Callback9& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
class Callback9Impl: public Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> {
	public:
		typedef Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> CBT;
		DEFINE_TYPE(Callback9Impl,CBT)

		Callback9Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback9Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8> *rhs_type = checkedCast<const Callback9Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
class CallbackStatic9Impl: public Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> {
	public:
		typedef Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> CBT;
		DEFINE_TYPE(CallbackStatic9Impl,CBT)

		CallbackStatic9Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic9Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8> *rhs_type = checkedCast<const CallbackStatic9Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
class Callback10 {
	public:
		DEFINE_TYPE_BASE(Callback10)
		virtual ~Callback10(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9) = 0;
		virtual DTboolean	operator ==	(const Callback10& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
class Callback10Impl: public Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> {
	public:
		typedef Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> CBT;
		DEFINE_TYPE(Callback10Impl,CBT)

		Callback10Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback10Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> *rhs_type = checkedCast<const Callback10Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
class CallbackStatic10Impl: public Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> {
	public:
		typedef Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> CBT;
		DEFINE_TYPE(CallbackStatic10Impl,CBT)

		CallbackStatic10Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic10Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> *rhs_type = checkedCast<const CallbackStatic10Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
class Callback11 {
	public:
		DEFINE_TYPE_BASE(Callback11)
		virtual ~Callback11(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10) = 0;
		virtual DTboolean	operator ==	(const Callback11& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
class Callback11Impl: public Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> {
	public:
		typedef Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> CBT;
		DEFINE_TYPE(Callback11Impl,CBT)

		Callback11Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback11Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> *rhs_type = checkedCast<const Callback11Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
class CallbackStatic11Impl: public Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> {
	public:
		typedef Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> CBT;
		DEFINE_TYPE(CallbackStatic11Impl,CBT)

		CallbackStatic11Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic11Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> *rhs_type = checkedCast<const CallbackStatic11Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
class Callback12 {
	public:
		DEFINE_TYPE_BASE(Callback12)
		virtual ~Callback12(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11) = 0;
		virtual DTboolean	operator ==	(const Callback12& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
class Callback12Impl: public Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> {
	public:
		typedef Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> CBT;
		DEFINE_TYPE(Callback12Impl,CBT)

		Callback12Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback12Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> *rhs_type = checkedCast<const Callback12Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
class CallbackStatic12Impl: public Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> {
	public:
		typedef Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> CBT;
		DEFINE_TYPE(CallbackStatic12Impl,CBT)

		CallbackStatic12Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic12Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> *rhs_type = checkedCast<const CallbackStatic12Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
class Callback13 {
	public:
		DEFINE_TYPE_BASE(Callback13)
		virtual ~Callback13(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12) = 0;
		virtual DTboolean	operator ==	(const Callback13& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
class Callback13Impl: public Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> {
	public:
		typedef Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> CBT;
		DEFINE_TYPE(Callback13Impl,CBT)

		Callback13Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback13Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> *rhs_type = checkedCast<const Callback13Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
class CallbackStatic13Impl: public Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> {
	public:
		typedef Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> CBT;
		DEFINE_TYPE(CallbackStatic13Impl,CBT)

		CallbackStatic13Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic13Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> *rhs_type = checkedCast<const CallbackStatic13Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
class Callback14 {
	public:
		DEFINE_TYPE_BASE(Callback14)
		virtual ~Callback14(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13) = 0;
		virtual DTboolean	operator ==	(const Callback14& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
class Callback14Impl: public Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> {
	public:
		typedef Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> CBT;
		DEFINE_TYPE(Callback14Impl,CBT)

		Callback14Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback14Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> *rhs_type = checkedCast<const Callback14Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
class CallbackStatic14Impl: public Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> {
	public:
		typedef Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> CBT;
		DEFINE_TYPE(CallbackStatic14Impl,CBT)

		CallbackStatic14Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic14Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> *rhs_type = checkedCast<const CallbackStatic14Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13);
};

//==============================================================================
//==============================================================================

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
class Callback15 {
	public:
		DEFINE_TYPE_BASE(Callback15)
		virtual ~Callback15(void)    {}
		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14) = 0;
		virtual DTboolean	operator ==	(const Callback15& rhs) const = 0;
};

template <typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
class Callback15Impl: public Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> {
	public:
		typedef Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> CBT;
		DEFINE_TYPE(Callback15Impl,CBT)

		Callback15Impl (CLASS *c, void (CLASS::*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14))
		{
			_obj = c;
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14)
		{
			if (_obj && _fn)
				(_obj->*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const Callback15Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> *rhs_type = checkedCast<const Callback15Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> *>(&rhs);
			return rhs_type && (_obj == rhs_type->_obj) && (_fn == rhs_type->_fn);
		}

	public:
		CLASS *_obj;
		void (CLASS::*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14);
};

template <typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
class CallbackStatic15Impl: public Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> {
	public:
		typedef Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> CBT;
		DEFINE_TYPE(CallbackStatic15Impl,CBT)

		CallbackStatic15Impl (void (*fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14))
		{
			_fn = fn;
		}

		virtual void operator ()(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14)
		{
			if (_fn)
				(*_fn)(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14);
		}

		virtual DTboolean operator == (const CBT& rhs) const
		{
			const CallbackStatic15Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> *rhs_type = checkedCast<const CallbackStatic15Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> *>(&rhs);
			return rhs_type && (_fn == rhs_type->_fn);
		}

	public:
		void (*_fn)(T0 t0,T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,T9 t9,T10 t10,T11 t11,T12 t12,T13 t13,T14 t14);
};

//==============================================================================
//==============================================================================

template<typename CLASS>
inline std::shared_ptr<Callback0> makeCallback(CLASS *c, void (CLASS::*fn)(void))
{
	return std::shared_ptr<Callback0>(new ("Callback0") Callback0Impl<CLASS>(c, fn));
}

template<typename CLASS,typename T0>
inline std::shared_ptr<Callback1<T0> > makeCallback(CLASS *c, void (CLASS::*fn)(T0))
{
	return std::shared_ptr<Callback1<T0> >(new ("Callback1") Callback1Impl<CLASS,T0>(c, fn));
}

template<typename CLASS,typename T0,typename T1>
inline std::shared_ptr<Callback2<T0,T1> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1))
{
	return std::shared_ptr<Callback2<T0,T1> >(new ("Callback2") Callback2Impl<CLASS,T0,T1>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2>
inline std::shared_ptr<Callback3<T0,T1,T2> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2))
{
	return std::shared_ptr<Callback3<T0,T1,T2> >(new ("Callback3") Callback3Impl<CLASS,T0,T1,T2>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3>
inline std::shared_ptr<Callback4<T0,T1,T2,T3> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3))
{
	return std::shared_ptr<Callback4<T0,T1,T2,T3> >(new ("Callback4") Callback4Impl<CLASS,T0,T1,T2,T3>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4>
inline std::shared_ptr<Callback5<T0,T1,T2,T3,T4> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4))
{
	return std::shared_ptr<Callback5<T0,T1,T2,T3,T4> >(new ("Callback5") Callback5Impl<CLASS,T0,T1,T2,T3,T4>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
inline std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5))
{
	return std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> >(new ("Callback6") Callback6Impl<CLASS,T0,T1,T2,T3,T4,T5>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6))
{
	return std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> >(new ("Callback7") Callback7Impl<CLASS,T0,T1,T2,T3,T4,T5,T6>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7))
{
	return std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> >(new ("Callback8") Callback8Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8))
{
	return std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> >(new ("Callback9") Callback9Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9))
{
	return std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> >(new ("Callback10") Callback10Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10))
{
	return std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> >(new ("Callback11") Callback11Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11))
{
	return std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> >(new ("Callback12") Callback12Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12))
{
	return std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> >(new ("Callback13") Callback13Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13))
{
	return std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> >(new ("Callback14") Callback14Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(c, fn));
}

template<typename CLASS,typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> > makeCallback(CLASS *c, void (CLASS::*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14))
{
	return std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> >(new ("Callback15") Callback15Impl<CLASS,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(c, fn));
}

//==============================================================================
//==============================================================================

inline std::shared_ptr<Callback0> makeCallback(void (*fn)(void))
{
	return std::shared_ptr<Callback0>(new ("Callback0") CallbackStatic0Impl(fn));
}

template<typename T0>
inline std::shared_ptr<Callback1<T0> > makeCallback(void (*fn)(T0))
{
	return std::shared_ptr<Callback1<T0> >(new ("Callback1") CallbackStatic1Impl<T0>(fn));
}

template<typename T0,typename T1>
inline std::shared_ptr<Callback2<T0,T1> > makeCallback(void (*fn)(T0,T1))
{
	return std::shared_ptr<Callback2<T0,T1> >(new ("Callback2") CallbackStatic2Impl<T0,T1>(fn));
}

template<typename T0,typename T1,typename T2>
inline std::shared_ptr<Callback3<T0,T1,T2> > makeCallback(void (*fn)(T0,T1,T2))
{
	return std::shared_ptr<Callback3<T0,T1,T2> >(new ("Callback3") CallbackStatic3Impl<T0,T1,T2>(fn));
}

template<typename T0,typename T1,typename T2,typename T3>
inline std::shared_ptr<Callback4<T0,T1,T2,T3> > makeCallback(void (*fn)(T0,T1,T2,T3))
{
	return std::shared_ptr<Callback4<T0,T1,T2,T3> >(new ("Callback4") CallbackStatic4Impl<T0,T1,T2,T3>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4>
inline std::shared_ptr<Callback5<T0,T1,T2,T3,T4> > makeCallback(void (*fn)(T0,T1,T2,T3,T4))
{
	return std::shared_ptr<Callback5<T0,T1,T2,T3,T4> >(new ("Callback5") CallbackStatic5Impl<T0,T1,T2,T3,T4>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
inline std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5))
{
	return std::shared_ptr<Callback6<T0,T1,T2,T3,T4,T5> >(new ("Callback6") CallbackStatic6Impl<T0,T1,T2,T3,T4,T5>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6))
{
	return std::shared_ptr<Callback7<T0,T1,T2,T3,T4,T5,T6> >(new ("Callback7") CallbackStatic7Impl<T0,T1,T2,T3,T4,T5,T6>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7))
{
	return std::shared_ptr<Callback8<T0,T1,T2,T3,T4,T5,T6,T7> >(new ("Callback8") CallbackStatic8Impl<T0,T1,T2,T3,T4,T5,T6,T7>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8))
{
	return std::shared_ptr<Callback9<T0,T1,T2,T3,T4,T5,T6,T7,T8> >(new ("Callback9") CallbackStatic9Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9))
{
	return std::shared_ptr<Callback10<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> >(new ("Callback10") CallbackStatic10Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10))
{
	return std::shared_ptr<Callback11<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> >(new ("Callback11") CallbackStatic11Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11))
{
	return std::shared_ptr<Callback12<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11> >(new ("Callback12") CallbackStatic12Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12))
{
	return std::shared_ptr<Callback13<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12> >(new ("Callback13") CallbackStatic13Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13))
{
	return std::shared_ptr<Callback14<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13> >(new ("Callback14") CallbackStatic14Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13>(fn));
}

template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> > makeCallback(void (*fn)(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14))
{
	return std::shared_ptr<Callback15<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14> >(new ("Callback15") CallbackStatic15Impl<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14>(fn));
}

//==============================================================================
//==============================================================================

} // DT3

#endif
