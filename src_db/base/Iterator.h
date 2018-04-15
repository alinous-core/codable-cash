/*
 * Copyright (c) Tomohiro Iizuka. All rights reserved.
 * Licensed under the MIT license.
 */

#ifndef BASELIB_ITERATOR_H_
#define BASELIB_ITERATOR_H_


namespace alinous {


template <typename T>
class Iterator {
public:
	Iterator() noexcept
	{

	}
	virtual ~Iterator() throw() {}

	virtual bool hasNext() {return false;}
	virtual T* next() {return nullptr;}
	virtual void remove() {};
};

} /* namespace alinous */

#endif /* BASELIB_ITERATOR_H_ */
