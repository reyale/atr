#ifndef _ATR_STREAM_BZ2__H
#define _ATR_STREAM_BZ2__H

#include <bzlib.h>

namespace atr {

namespace streams {

 class bz2 : public compressed {
 public:
   bz2() : _fd(0), _file(0) { }

   ~bz2() {
     close();
   }

   bool open(const char* fname) {
     _fd = fopen(fname, "rb");
     if(!_fd)
       return false;

     _file = BZ2_bzReadOpen(&_bzError, _fd, 0, 0, NULL, 0);
     if (_bzError != BZ_OK)
       return false;
     return true;
   }
 
   bool close() {
     BZ2_bzReadClose(&_bzError, _file);
     if(_bzError != BZ_OK)
       return false;

     fclose(_fd);
     _fd = 0; 
     _file = 0; 
     return true;
   }

   std::streamsize read(char* buffer, std::size_t buffer_size) {
     auto read_size = BZ2_bzRead(&_bzError, _file, buffer, buffer_size);
     //if(_bzError != BZ_OK)
     return read_size;
   } 
 
 private:
   FILE* _fd;
   BZFILE* _file; 
   int _bzError;
 };

}

}

#endif
