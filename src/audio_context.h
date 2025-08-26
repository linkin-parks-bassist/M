#ifndef AUDIO_FRAMEWORK_H_
#define AUDIO_FRAMEWORK_H_

class m_audio_context
{
	public:
	
	int init();
	
	AudioInputI2S	 line_in;
	AudioOutputI2S	 line_out;
	AudioAnalyzePeak peak_analyzer;
	
	AudioConnection *line_out_connection;
	AudioConnection *monitor_connection;
	
	AudioControlSGTL5000 shield;
	
	void update_controls();
};

#endif
