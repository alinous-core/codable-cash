/*
 * ParserReaderStream.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_PARSERREADERSTREAM_H_
#define SC_PARSERREADERSTREAM_H_

#include "alinous_lang/JavaCC.h"

namespace alinous {
class InputStream;

class ParserReaderStream : public ReaderStream {
public:
	ParserReaderStream(InputStream* inputStream, int size);
	virtual ~ParserReaderStream();

	virtual size_t read(JAVACC_CHAR_TYPE *buffer, int offset, size_t len);
	virtual bool endOfInput();

private:
	InputStream* inputStream;
	size_t cur_;
	size_t max_;
};

} /* namespace codablecash */

#endif /* SC_PARSERREADERSTREAM_H_ */
