#include "QReg.h"
#include <cmath>

namespace SimKet {

QReg::QReg(size_t n)
: _width(n)
{
  size_t ketSize = 0x1 << n;
  double prob = sqrt(1.0 / ketSize);
  _probs.assign(ketSize, prob);
}

Kets<char>
QReg::kets() const
{
  std::vector<Ket<char>> kets;
  for (size_t i=0; i<_probs.size(); ++i) {
    kets.push_back(Ket<char>(_probs[i], _width, i));
  }
  return Kets<char>(kets);
}

std::string
QReg::ketsStr() const
{
  return kets().str();
}


}
