#ifndef BAND_SPLIT_H_
#define BAND_SPLIT_H_

class band_splitter : public dsp_block
{
	public:
	band_splitter(float c) : dsp_block(2), cutoff_freq{c}
	{
		low_in.setLowpass		(0, cutoff_freq, 0.7071);
		low_out.setLowpass		(0, cutoff_freq, 0.7071);
		high_in.setHighpass		(0, cutoff_freq, 0.7071);
		high_out.setHighpass	(0, cutoff_freq, 0.7071);
		
		low1_to_low2	= new AudioConnection(low_in, low_out);
		high1_to_high2 	= new AudioConnection(high_in, high_out);
	};
	
	AudioStream *input_stream (int n = 0) override;
	AudioStream *output_stream(int n = 0) override;
	
	float cutoff_freq;
	
	private:
	
	AudioFilterBiquad low_in;
	AudioFilterBiquad high_in;
	
	AudioFilterBiquad low_out;
	AudioFilterBiquad high_out;
	
	AudioConnection *low1_to_low2;
	AudioConnection *high1_to_high2;
};

#endif
