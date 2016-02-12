#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_common.h"

#include "z_dsp.h"

typedef struct _mbmspc
{
  t_pxobject  c_box;
  void  *c_outlet;
  
  double m_value;
} t_mbmspc;

t_int*  mbmspc_perform(t_int *w);
void* mbmspc_new(t_symbol *s, long argc, t_atom *argv);
void  mbmspc_assist(t_mbmspc *x, void *b, long m, long a, char *s);
void  mbmspc_bang(t_mbmspc *x);
void  mbmspc_dsp64(t_mbmspc *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void  mbmspc_perform64(t_mbmspc *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

static t_class  *s_mbmspc_class = NULL;

int C74_EXPORT main(void)
{
  t_class *c = class_new("mbmspc~",
                         (method)mbmspc_new,
                         //(method)mbmspc_free,
                         (method)dsp_free,
                         sizeof(t_mbmspc),
                         (method)NULL,
                         A_GIMME,
                         0);
  
  common_symbols_init();
  
  class_addmethod(c, (method)mbmspc_dsp64,  "dsp64",	A_CANT, 0);
  class_addmethod(c, (method)mbmspc_bang, "bang",     0);
  class_addmethod(c, (method)mbmspc_assist,"assist",    A_CANT, 0);
  
  CLASS_ATTR_FLOAT(c, "myvalue", 0, t_mbmspc, m_value);
  
  class_dspinit(c);
  class_register(_sym_box, c);
  s_mbmspc_class = c;
  
  return 0;
}

// this is the 64-bit perform method audio vectors
void mbmspc_perform64(t_mbmspc *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
  t_double *inL = ins[0];
  t_double *outL = outs[0];
  int n = sampleframes;
  
  while (n--)
    *outL++ = *inL++;
}

void mbmspc_dsp64(t_mbmspc *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
  object_method(dsp64, gensym("dsp_add64"), x, mbmspc_perform64, 0, NULL);
}

void *mbmspc_new(t_symbol *s, long argc, t_atom *argv)
{
  t_mbmspc  *x;
  
  x = (t_mbmspc*)object_alloc(s_mbmspc_class);
  
  dsp_setup((t_pxobject *)x, 1);
  
  if (x)
  {
    x->c_outlet = outlet_new(x, "signal");
  }
  
  return(x);
}
void mbmspc_assist(t_mbmspc *x, void *b, long msg, long arg, char *dst)
{
  if (msg==1)
    strcpy(dst, "input");
  else if (msg==2)
    strcpy(dst, "output");
}

void mbmspc_bang(t_mbmspc *x)
{
  post("bang");
}