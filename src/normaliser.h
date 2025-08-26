#ifndef AMP_NORMALISER_H_
#define AMP_NORMALISER_H_

class normaliser_denormaliser : public dsp_block
{
	public:
	normaliser_denormaliser() : dsp_block(3), loudness{0.0}, gain{1.0}, peak_connection{new AudioConnection(normaliser, peak)}
	{
		normaliser.gain(1.0);
		denormaliser.gain(1.0);
	}
	
	
	float loudness;
	
	void refresh();
	
	AudioStream *input_stream (int n = 0);
	AudioStream *output_stream(int n = 0);
	
	void connect_input(AudioStream &stream, int n = 0, int stream_out_channel = 0, int stream_in_channel = 0) override;
	
	AudioAmplifier normaliser;
	AudioAmplifier denormaliser;
	private:
	float gain;
	AudioAnalyzePeak peak;
	AudioConnection *peak_connection;
};

#endif
