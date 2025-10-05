#include "tm.h"

void print_binary(int v, int bits)
{
	tm_printf("0b");
	for (int i = 0; i < bits; i++)
		tm_printf("%d", (int)((v >> (bits - i - 1)) & 1));
}

void print_context_info(tm_context *cxt, int depth)
{
	tm_printf("\n~~~CONTEXT INFO~~~\n");
	
	tm_printf("Memory address: %p\n", cxt);
	if (!cxt)
		return;
	
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
		}
	}
	
	if (!depth || depth < 0)
		tm_printf("\n");
}

void print_profile_info(tm_profile *profile, int depth)
{
	tm_printf("\n~~~PROFILE INFO~~~\n");
	
	tm_printf("Memory address: %p\n", profile);
	
	if (!profile)
		return;
	
	if (depth)
	{
		tm_printf("Pipeline:\n");

		print_pipe_line_info(&profile->pipe_line, depth - 1);
	}
	
	if (!depth)
		tm_printf("\n");
}

void print_pipeline_info(tm_pipeline *pipeline, int depth)
{
	tm_printf("\n~~~PIPELINE INFO~~~\n");
	
	tm_printf("Memory address: %p\n", pipeline);
	
	if (!pipeline)
		return;
	
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
}

void print_pipe_line_info(tm_pipe_line *pipeline, int depth)
{
	tm_printf("\n~~~PIPE_LINE INFO~~~\n");
	
	tm_printf("Memory address: %p\n", pipeline);
	
	if (!pipeline)
		return;
	
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
}

void print_transformer_info(tm_audio_transformer *trans, int depth)
{
	tm_printf("\n~~~TRANSFORMER INFO~~~\n");
	
	tm_printf("Memory address: %p\n", trans);
	
	if (!trans)
		return;
	
	tm_printf("Transformer type: %d (", trans->type);
	switch (trans->type)
	{
		case TRANSFORMER_BUFFER:
			tm_printf("buffer");
			break;
			
		case TRANSFORMER_AMPLIFIER:
			tm_printf("amplifier");
			break;
		
		case TRANSFORMER_MIXER:
			tm_printf("mixer");
			break;
		
		case TRANSFORMER_BIQUAD:
			tm_printf("biquad");
			break;
		
		case TRANSFORMER_DISTORTION:
			tm_printf("arctan distortion");
			break;
		
		case TRANSFORMER_WAVESHAPER:
			tm_printf("compression");
			break;
		
		case TRANSFORMER_COMPRESSOR:
			tm_printf("compression");
			break;
		
		default:
			tm_printf("unknown !\n");
			break;
	}
	
	tm_printf(")\n");
	
	tm_printf("Data struct address: %p\n", trans->transformer_data);
	
	if (!depth)
		tm_printf("\n");
}
