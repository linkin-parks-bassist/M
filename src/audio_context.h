#ifndef AUDIO_FRAMEWORK_H_
#define AUDIO_FRAMEWORK_H_

#define AUDIO_SAMPLE_RATE_EXACT 44117.64706

typedef struct
{
	i2s_input_struct i2s_input;
	i2s_output_struct i2s_output;
	sgtl5000_str sgtl5000;
}  audio_context;

int init_audio_context(audio_context *cxt);

#endif
