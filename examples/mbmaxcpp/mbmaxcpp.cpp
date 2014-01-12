#include "../../maxcpp/maxcpp/maxcpp6.h"

class mbmaxcpp : public MaxCpp6<mbmaxcpp> 
{
public:
  mbmaxcpp(t_symbol * sym, long ac, t_atom * av) { 
    setupIO(2, 2);
  }
  
  ~mbmaxcpp() {}   
  
  // methods:
  void bang(long inlet) { 
    outlet_bang(m_outlets[0]);
  }
  void testfloat(long inlet, double v) { 
    outlet_float(m_outlets[0], v);
  }
  void testint(long inlet, long v) { 
    outlet_int(m_outlets[0], v);
  }
  void test(long inlet, t_symbol * s, long ac, t_atom * av) { 
    outlet_anything(m_outlets[1], gensym("test"), ac, av); 
  }
};

extern "C" int C74_EXPORT main(void) {
  // create a class with the given name:
  mbmaxcpp::makeMaxClass("mbmaxcpp");
  REGISTER_METHOD(mbmaxcpp, bang);
  REGISTER_METHOD_FLOAT(mbmaxcpp, testfloat);
  REGISTER_METHOD_LONG(mbmaxcpp, testint);
  REGISTER_METHOD_GIMME(mbmaxcpp, test);
}