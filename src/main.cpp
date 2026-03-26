#include <cstdio>
#include "QReg.h"

int main(int argc, char** argv)
{
  SimKet::QReg q(2);
  const std::string& str = q.ketsStr();
  printf("%s\n", str.data());
  return 0;
}
