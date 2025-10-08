#include "em.h"

void init_amplifier(em_transformer *trans)
{
	trans->type = TRANSFORMER_AMPLIFIER;
	b->transition_policy = TRANSITION_POLICY_;
	b->param_level.name = "level";
	b->param_level.min = 0.0f;
	b->param_level.max = 2.0f;
	b->param_level.default_val = 1.0f;
	b->param_level.smoothing = SMOOTHING_LINEAR;
}


