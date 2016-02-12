#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_common.h"

#include "z_dsp.h"

typedef struct _mbmspcc
{
  t_pxobject      c_box;
  void        *c_outlet;
  
  double m_value;
} t_mbmspcc;

t_int*  mbmspcc_perform(t_int *w);
void  mbmspcc_dsp(t_mbmspcc *x, t_signal **sp, short *count);
void* mbmspcc_new(t_symbol *s, long argc, t_atom *argv);
void  mbmspcc_assist(t_mbmspcc *x, void *b, long m, long a, char *s);
void  mbmspcc_bang(t_mbmspcc *x);

static t_class  *s_mbmspcc_class = NULL;

int C74_EXPORT main(void)
{
  t_class *c = class_new("mbmspcc~",
                         (method)mbmspcc_new,
                         //(method)mbmspcc_free,
                         (method)dsp_free,
                         sizeof(t_mbmspcc),
                         (method)NULL,
                         A_GIMME,
                         0);
  
  common_symbols_init();
  
  class_addmethod(c, (method)mbmspcc_dsp, "dsp", A_CANT, 0);
  class_addmethod(c, (method)mbmspcc_bang, "bang",     0);
  class_addmethod(c, (method)mbmspcc_assist,"assist",    A_CANT, 0);
  
  CLASS_ATTR_FLOAT(c, "myvalue", 0, t_mbmspcc, m_value);
  
  class_dspinit(c);
  class_register(_sym_box, c);
  s_mbmspcc_class = c;
  
  return 0;
}

t_int *mbmspcc_perform(t_int *w)
{
  t_float *in = (t_float *)(w[1]);
  t_float *out = (t_float *)(w[2]);
  t_mbmspcc *x = (t_mbmspcc *)(w[3]);
  //    t_float min = x->w_connected[0]? (*(t_float *)(w[4])) : x->w_start;
  //   t_float max = x->w_connected[1]? (*(t_float *)(w[5])) : x->w_end;
  int n = w[4];
  
  if (x->c_box.z_disabled)
    goto out;
  
  
  while (n--)
  {
    *out++ = *in++;
  }
  
  return (w + 5);
  
out:
  return (w + 5);
  
}

void mbmspcc_dsp(t_mbmspcc *x, t_signal **sp, short *count)
{
  dsp_add(mbmspcc_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void *mbmspcc_new(t_symbol *s, long argc, t_atom *argv)
{
  t_mbmspcc  *x;
  
  x = (t_mbmspcc*)object_alloc(s_mbmspcc_class);
  
  dsp_setup((t_pxobject *)x, 1);
  
  if (x)
  {
    x->c_outlet = outlet_new(x, "signal");
  }
  return(x);
}
void mbmspcc_assist(t_mbmspcc *x, void *b, long msg, long arg, char *dst)
{
  if (msg==1)
    strcpy(dst, "input");
  else if (msg==2)
    strcpy(dst, "output");
}

void mbmspcc_bang(t_mbmspcc *x)
{
  post("bang");
}