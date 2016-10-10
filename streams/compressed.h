#ifndef _ATR_STREAM_COMPRESSED_H
#define _ATR_STREAM_COMPRESSED_H

namespace atr {

namespace streams {

  class compressed {
  public: 
    virtual bool open(const char* fname) = 0;
    virtual bool close() = 0;
    virtual std::streamsize read(char* buffer, std::size_t buffer_size) = 0;
  };

}

}

#endif
