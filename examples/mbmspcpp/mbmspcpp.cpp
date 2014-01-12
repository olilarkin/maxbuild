#include "../../maxcpp/maxcpp/maxcpp6.h"

class mbmspcpp : public MspCpp6<mbmspcpp> 
{
public:
	mbmspcpp(t_symbol * sym, long ac, t_atom * av) {
		setupIO(1, 1); 
	}
	
	~mbmspcpp() {}	
  
	//void dsp(t_object * dsp64, short *count, double samplerate, long maxvectorsize, long flags) {
		//setSampleRate(sys_getsr());
	//}

	void perform(double **ins, long numins, double **outs, long numouts, long sampleframes) {
		for (long channel = 0; channel < numouts; channel++) {
			double * in = ins[channel];
			double * out = outs[channel];
			for (long i=0; i < sampleframes; i++) {
				out[i] = in[i];
			}
		}
	}
};

extern "C" int C74_EXPORT main(void) {
	mbmspcpp::makeMaxClass("mbmspcpp~");
}