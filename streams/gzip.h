#ifndef _ATR_STREAM_GZIP__H
#define _ATR_STREAM_GZIP__H

#include <zlib.h>

#include "streams/compressed.h"

namespace atr {

namespace streams {

 class gzip : public compressed {
 public:
   gzip() : _file(0) { }

   ~gzip() {
     close();
   }

   bool open(const char* fname) {
     open(fname, "r"); 
   }

   bool open(const char* fname, const char* mode) {
     if(_file)
      return false;

     _file = gzopen(fname, mode);
     if(!_file)
       return false;

     return true;
   }

   bool close() {
     if(!_file)
       return false;

     gzclose(_file);
     _file = 0;
     return true;
   }

   std::streamsize read(char* buffer, std::size_t buffer_size) {
     return gzread(_file, buffer, buffer_size); 
   } 

 private:
  gzFile _file;

 };

}

}

#endif
