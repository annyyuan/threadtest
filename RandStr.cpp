
#include "RandStr.h"


const static int MAX_STR_SIZE = 12;


std::string RandStr::GenerateRandomString() {
  std::string str;

  for( int i=0;i<MAX_STR_SIZE;i++ ){
    if( rand() % 36 < 26 ){
      str += static_cast<char>(('a' + (rand() % 26)));
    } else {
      str += static_cast<char>(('0' + (rand() % 10)));
    }
  }
  return str;
}
