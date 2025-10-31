#include "tm.h"

static const char *FNAME = "tm_debugging.c";

void print_binary(int v, int bits)
{
	tm_printf("0b");
	for (int i = 0; i < bits; i++)
		tm_printf("%d", (int)((v >> (bits - i - 1)) & 1));
}

void full_debug_print(tm_context *cxt)
{
	print_context_info(cxt, -1);
	print_mempool_info();
	//tm_print_flush_log();
}

void print_context_info(tm_context *cxt, int depth)
{
	FUNCTION_START();
	
	tm_printf("\n~~~CONTEXT INFO~~~\n");
	
	tm_printf("Memory address: %p\n", cxt);
	if (!cxt)
	{
		RETURN_VOID();
	}
	
	tm_printf("Flags: ");
	
	print_binary(cxt->status_flags, 16);
	
	tm_printf("\n");
	
	tm_printf("Profiles: %d\n", cxt->n_profiles);
	
	tm_printf("Current profile: %d\n", cxt->active_profile);
	
	if (depth)
	{
		for (int i = 0; i < cxt->n_profiles; i++)
		{
			tm_printf("Profile %d:\n", i);
			print_profile_info(&cxt->profiles[i], depth - 1);
			tm_printf("~~~ END PROFILE %d ~~~\n", i);
		}
	}
	
	if (!depth || depth < 0)
		tm_printf("\n");
	
	RETURN_VOID();
}

void print_profile_info(tm_profile *profile, int depth)
{
	FUNCTION_START();
	
	tm_printf("\n~~~PROFILE INFO~~~\n");
	
	tm_printf("Memory address: %p\n", profile);
	
	if (!profile)
	{
		RETURN_VOID();
	}
	
	if (depth)
	{
		tm_printf("Pipelines (front/back):\n");

		print_pipe_line_info(profile->front_pipeline, depth - 1);
		print_pipe_line_info(profile->back_pipeline, depth - 1);
	}
	
	if (!depth)
		tm_printf("\n");
	
	RETURN_VOID();
}

void print_pipeline_info(tm_pipeline *pipeline, int depth)
{
	FUNCTION_START();
	
	tm_printf("\n~~~PIPELINE INFO~~~\n");
	
	tm_printf("Memory address: %p\n", pipeline);
	
	if (!pipeline)
	{
		RETURN_VOID();
	}
	
	tm_printf("Flags: ");
	
	print_binary(pipeline->err_flags, 16);
	
	tm_printf("\n");
	
	tm_printf("Width: %d, height: %d\n", pipeline->width, pipeline->height);
	
	tm_printf("Transformers: %d\n", pipeline->n_transformers);
	
	if (depth)
	{
		for (int i = 0; i < pipeline->n_transformers; i++)
		{
			tm_printf("Transformer %d:\n", i);
			print_transformer_info(pipeline->transformers[i], depth - 1);
		}
	}
	
	if (!depth)
		tm_printf("\n");
	
	RETURN_VOID();
}

void print_pipe_line_info(tm_pipe_line *pipeline, int depth)
{
	FUNCTION_START();
	
	tm_printf("\n~~~PIPE_LINE INFO~~~\n");
	
	tm_printf("Memory address: %p\n", pipeline);
	
	if (!pipeline)
	{
		RETURN_VOID();
	}
	
	tm_printf("Transformers: %d\n", pipeline->n_transformers);
	
	if (depth)
	{
		for (int i = 0; i < pipeline->n_transformers; i++)
		{
			tm_printf("Transformer %d:\n", i);
			print_transformer_info(pipeline->transformers[i], depth - 1);
		}
	}
	
	if (!depth)
		tm_printf("\n");
	
	RETURN_VOID();
}

void print_transformer_info(tm_transformer *trans, int depth)
{
	FUNCTION_START();
	
	tm_printf("\n~~~TRANSFORMER INFO~~~\n");
	
	tm_printf("Memory address: %p\n", trans);
	
	if (!trans)
	{
		RETURN_VOID();
	}
	
	tm_printf("Transformer ID: %d, type: %d (%s)\n", trans->id, trans->type, transformer_type_to_string(trans->type));
	
	tm_printf("Data struct address: %p\n", trans->data_struct);
	
	tm_printf("PARAMETERS:\n");
	for (int i = 0; i < trans->n_parameters; i++)
	{
		if (trans->parameters[i])
			tm_printf("Parameter %d: %f\n", i, trans->parameters[i]->value);
		else
			tm_printf("Parameter %d: NULL\n", i);
	}
	
	if (!depth)
		tm_printf("\n");
	
	RETURN_VOID();
}
