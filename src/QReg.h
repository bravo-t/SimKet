#ifndef _QSTATE_H_
#define _QSTATE_H_

#include "Eigen/Dense"
#include "Utils.h"
#include <string>

namespace SimKet {

template <typename T = char>
class Ket {
  public:
    Ket(double prob, size_t width, size_t state)
    : _prob(prob) 
    {
      _bits.reserve(width);
      for (size_t i=0; i<width; ++i) {
        T x = state & 0x1;
        _bits.push_back(x);
        state = state >> 1;
      }
      std::reverse(_bits.begin(), _bits.end());
    }
    std::string str() const
    {
      std::string stat;
      for (T bit : _bits) {
        stat += std::to_string(bit);
      }
      return formatString("%G*|%s>", _prob, stat.data());
    }
  private:
    double         _prob;
    std::vector<T> _bits;
};

template <typename T = char>
class Kets {
  public:
    Kets(const std::vector<Ket<T>>& kets)
    : _kets(kets) {}

    std::string str() const
    {
      std::string string;
      if (_kets.empty()) {
        return string;
      }
      string = _kets[0].str();
      for (size_t i=1; i<_kets.size(); ++i) {
        string += " + ";
        string += _kets[i].str();
      }
      return string;
    }
  private:
    std::vector<Ket<T>> _kets;
};

class QReg {
  public:
    QReg(size_t width);
    Kets<char> kets() const;
    std::string ketsStr() const;
  private:
    size_t              _width;
    std::vector<double> _probs;
};



}

#endif
