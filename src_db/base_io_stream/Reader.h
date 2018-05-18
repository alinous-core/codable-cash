/*
 * Reader.h
 *
 *  Created on: 2018/05/15
 *      Author: iizuka
 */

#ifndef BASE_IO_STREAM_READER_H_
#define BASE_IO_STREAM_READER_H_

namespace alinous {

class Reader {
public:
	Reader();
	virtual ~Reader();

	virtual void close() = 0;
	virtual int read(wchar_t* b, int size) = 0;
};

} /* namespace alinous */

#endif /* BASE_IO_STREAM_READER_H_ */
