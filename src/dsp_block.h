#ifndef DSP_BLOCK_H_
#define DSP_BLOCK_H_

#define DSP_BLOCK_MAX_OUTPUTS 8

class dsp_block
{
	public:
		dsp_block() 	 : inputs{new AudioConnection*[1]}{};
		dsp_block(int n) : inputs{new AudioConnection*[n_inputs]}{};
		
		~dsp_block();
		
		virtual void connect_input(AudioStream &stream, int n = 0, int stream_out_channel = 0, int stream_in_channel = 0);
		
		virtual AudioStream *input_stream(int n = 0);
		virtual AudioStream *output_stream(int n = 0);
		
		unsigned int n_inputs = 1;
	protected:
		AudioConnection **inputs;
};

#endif

