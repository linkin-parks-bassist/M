#ifndef DISTORTION_H_
#define DISTORTION_H_

#define DISTORTION_TABLE_LENGTH 32769

class distortion_block : public dsp_block
{
	public:
		distortion_block();
		
		AudioStream *input_stream (int n = 0);
		AudioStream *output_stream(int n = 0);
		
		void refresh();
		
		//void connect_input(AudioStream &stream, int n = 0, int stream_out_channel = 0, int stream_in_channel = 0) override;
		
		void shape(float *table);
		normaliser_denormaliser nd;
	private:
		AudioEffectWaveshaper waveshaper;
		AudioConnection *normaliser_to_waveshaper;
};

class arctan_distortion : public distortion_block
{
	public:
		arctan_distortion() : arctan_distortion(1.0){}
		arctan_distortion(float c);
		
		void set_strength();
	private:
		float strength;
		
		void update_table();
};

#endif
