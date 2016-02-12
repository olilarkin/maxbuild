#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_common.h"

typedef struct _mbmaxc 
{
  t_object  c_box;
  void  *c_outlet;
  
  double m_value;
} t_mbmaxc;

void* mbmaxc_new(t_symbol *s, long argc, t_atom *argv);
void  mbmaxc_free(t_mbmaxc* x);
void  mbmaxc_assist(t_mbmaxc *x, void *b, long m, long a, char *s);
void  mbmaxc_bang(t_mbmaxc *x);
void  mbmaxc_clear(t_mbmaxc *x);
void  mbmaxc_int(t_mbmaxc *x, long value);
void  mbmaxc_float(t_mbmaxc *x, double value);
void  mbmaxc_list(t_mbmaxc *x, t_symbol *msg, long argc, t_atom *argv);

static t_class  *s_mbmaxc_class = NULL;

int C74_EXPORT main(void)
{
  t_class *c = class_new("mbmaxc",
                         (method)mbmaxc_new,
                         (method)mbmaxc_free,
                         sizeof(t_mbmaxc),
                         (method)NULL,
                         A_GIMME,
                         0);
  
  common_symbols_init();
  
  class_addmethod(c, (method)mbmaxc_bang, "bang", 0);
  class_addmethod(c, (method)mbmaxc_int, "int", A_LONG, 0);
  class_addmethod(c, (method)mbmaxc_float, "float", A_FLOAT,0);
  class_addmethod(c, (method)mbmaxc_list, "list", A_GIMME,0);
  class_addmethod(c, (method)mbmaxc_assist, "assist", A_CANT, 0);
  class_addmethod(c, (method)stdinletinfo, "inletinfo", A_CANT, 0);
  
  CLASS_ATTR_FLOAT(c, "myvalue", 0, t_mbmaxc, m_value);
  
  class_register(_sym_box, c);
  s_mbmaxc_class = c;
  
  return 0;
}

void *mbmaxc_new(t_symbol *s, long argc, t_atom *argv)
{
  t_mbmaxc  *x;
  
  x = (t_mbmaxc*)object_alloc(s_mbmaxc_class);
  
  if (x) 
  {
    x->c_outlet = outlet_new(x, NULL);
  }
  
  return(x);
}

void mbmaxc_free(t_mbmaxc *x){}

void mbmaxc_assist(t_mbmaxc *x, void *b, long msg, long arg, char *dst)
{
  if (msg==1)
    strcpy(dst, "input");
  else if (msg==2)
    strcpy(dst, "output");
}

void mbmaxc_bang(t_mbmaxc *x)
{
  post("bang");
}

void mbmaxc_int(t_mbmaxc *x, long value)
{
  post("int val: %i", value);
}

void mbmaxc_float(t_mbmaxc *x, double value)
{
  post("float val: %f", value);
}

void mbmaxc_list(t_mbmaxc *x, t_symbol *msg, long argc, t_atom *argv)
{
  long i;
  t_atom *ap;
  
  post("message selector is %s", msg->s_name);
  post("there are %ld arguments", argc);
  
  for (i = 0, ap = argv; i < argc; i++, ap++) 
  {
    switch (atom_gettype(ap)) {
      case A_LONG:
        post("%ld: %ld",i+1,atom_getlong(ap));
        break;
      case A_FLOAT:
        post("%ld: %.2f",i+1,atom_getfloat(ap));
        break;
      case A_SYM:
        post("%ld: %s",i+1, atom_getsym(ap)->s_name);
        break;
      default:
        post("%ld: unknown atom type (%ld)", i+1, atom_gettype(ap));
        break;
    }
  }
}