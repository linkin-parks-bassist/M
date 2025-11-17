#include "m_eng.h"

static const char *FNAME = "m_eng_debugging.c";

void print_binary(int v, int bits)
{
	m_printf("0b");
	for (int i = 0; i < bits; i++)
		m_printf("%d", (int)((v >> (bits - i - 1)) & 1));
}

void full_debug_print(m_eng_context *cxt)
{
	print_context_info(cxt, -1);
	print_mempool_info();
	//m_eng_print_flush_log();
}

void print_context_info(m_eng_context *cxt, int depth)
{
	FUNCTION_START();
	
	m_printf("\n~~~CONTEXT INFO~~~\n");
	
	m_printf("Memory address: %p\n", cxt);
	if (!cxt)
	{
		RETURN_VOID();
	}
	
	m_printf("Flags: ");
	
	print_binary(cxt->status_flags, 16);
	
	m_printf("\n");
	
	m_printf("Profiles: %d\n", cxt->n_profiles);
	
	m_printf("Current profile: %d\n", cxt->active_profile);
	
	if (depth)
	{
		for (int i = 0; i < cxt->n_profiles; i++)
		{
			m_printf("Profile %d:\n", i);
			print_profile_info(&cxt->profiles[i], depth - 1);
			m_printf("~~~ END PROFILE %d ~~~\n", i);
		}
	}
	
	if (!depth || depth < 0)
		m_printf("\n");
	
	RETURN_VOID();
}

void print_profile_info(m_eng_profile *profile, int depth)
{
	FUNCTION_START();
	
	m_printf("\n~~~PROFILE INFO~~~\n");
	
	m_printf("Memory address: %p\n", profile);
	
	if (!profile)
	{
		RETURN_VOID();
	}
	
	if (depth)
	{
		m_printf("Pipelines (front/back):\n");

		print_pipeline_info(profile->front_pipeline, depth - 1);
		print_pipeline_info(profile->back_pipeline, depth - 1);
	}
	
	if (!depth)
		m_printf("\n");
	
	RETURN_VOID();
}


void print_pipeline_info(m_pipeline *pipeline, int depth)
{
	FUNCTION_START();
	
	m_printf("\n~~~PIPELINE INFO~~~\n");
	
	m_printf("Memory address: %p\n", pipeline);
	
	if (!pipeline)
	{
		RETURN_VOID();
	}
	
	m_printf("Transformers: %d\n", pipeline->n_transformers);
	
	if (depth)
	{
		for (int i = 0; i < pipeline->n_transformers; i++)
		{
			m_printf("Transformer %d:\n", i);
			print_transformer_info(pipeline->transformers[i], depth - 1);
		}
	}
	
	if (!depth)
		m_printf("\n");
	
	RETURN_VOID();
}

void print_transformer_info(m_transformer *trans, int depth)
{
	FUNCTION_START();
	
	m_printf("\n~~~TRANSFORMER INFO~~~\n");
	
	m_printf("Memory address: %p\n", trans);
	
	if (!trans)
	{
		RETURN_VOID();
	}
	
	m_printf("Transformer ID: %d, type: %d (%s)\n", trans->id, trans->type, transformer_type_to_string(trans->type));
	
	m_printf("Data struct address: %p\n", trans->data_struct);
	
	m_printf("PARAMETERS:\n");
	for (int i = 0; i < trans->n_parameters; i++)
	{
		if (trans->parameters[i])
			m_printf("Parameter %d: %f\n", i, trans->parameters[i]->value);
		else
			m_printf("Parameter %d: NULL\n", i);
	}
	
	if (!depth)
		m_printf("\n");
	
	RETURN_VOID();
}
