#ifndef M_HW_CTRL_H_
#define M_HW_CTRL_H_

#define N_POTS 		3
#define N_SWITCHES 	2

//#define PRINT_HW_CTRL_DATA

typedef struct
{
	int pot;
	int active;
	m_parameter *param;
	float min;
	float max;
} m_pot_link;

#define SWITCH_PIPELINE 			0
#define SWITCH_BYPASS_TRANSFORMER 	1

typedef struct
{
	int type;
	int active;
	
	m_pipeline *pipeline;
	m_audio_transformer *transformer;
} m_switch_link;

typedef struct
{
	float pots[N_POTS];
	int switch_states[N_SWITCHES];
	
	int switch_changed[N_SWITCHES];
	
	int pot_pins[N_POTS];
	int switch_pins[N_SWITCHES];
	
	m_pot_link pot_links[N_POTS];
	m_switch_link switch_links[N_SWITCHES];
} m_hw_ctrl_context;

int init_hardware_controls(m_hw_ctrl_context *cxt);
int poll_hardware_controls(m_hw_ctrl_context *cxt);
int execute_hw_ctrl_links(m_hw_ctrl_context *cxt);

int link_pot_to_parameter(m_hw_ctrl_context *cxt, int pot_n, m_parameter *param, float min_value, float max_value);
int link_switch_to_pipeline(m_hw_ctrl_context *cxt, int switch_n, m_pipeline *pipeline);
int link_switch_to_bypass_transformer(m_hw_ctrl_context *cxt, int switch_n, m_audio_transformer *transformer);

extern float   pots[N_POTS];
extern int switches[N_SWITCHES];

extern int switch_changed[N_SWITCHES];

#endif
