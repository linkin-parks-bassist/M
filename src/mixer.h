#ifndef MIXER_H_
#define MIXER_H_

class audio_mixer : public dsp_block
{
	public:
	audio_mixer() : audio_mixer(0.5) {}
	
	audio_mixer(float r) : dsp_block(2), ratio{r}
	{
		mixer.gain(0, r);
		mixer.gain(1, 1.0 - r);
	}
	
	AudioStream *input_stream (int n = 0) override;
	AudioStream *output_stream(int n = 0) override;
	
	float ratio;
	
	private:
	AudioMixer4 mixer;
};

#endif

