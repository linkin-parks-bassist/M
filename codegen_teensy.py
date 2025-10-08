import yaml

generated_initial = ["// Code generated from transformer_config.yaml by codegen_teensy.py"]

tm_fname = "./M_teensy/src/tm_transformer_init.cpp"
tm_initial = ["#include \"tm.h\"", ""]

enum_initial = [
	"#ifndef M_TRANSFORMER_ENUM_H_",
	"#define M_TRANSFORMER_ENUM_H_",
	""
]

enum_final = [
	"typedef enum",
	"{",
	"\tlow_pass		= 0,",
	"\thigh_pass		= 1,",
	"\tband_pass 		= 2,",
	"\tnotch 			= 3,",
	"\tpeaking_band_eq = 4,",
	"\tlow_shelf 		= 5,",
	"\thigh_shelf 		= 6",
	"} biquad_type;",
	"",
	"#define DISTORTION_SOFT_FOLD 	0",
	"#define DISTORTION_ARCTAN		1",
	"#define DISTORTION_TANH			2",
	"#define DISTORTION_CLIP			3",
	"",
	"#endif"
]

def enum_sanitize(s):
	return s.upper().replace(' ', '_')

def normal_sanitize(s):
	return s.lower().replace(' ', '_')

def transformer_enum_name(name):
	return "TRANSFORMER_" + enum_sanitize(name)

def trans_null_ptr_guard():
	return ["	if (!trans)", "		return ERR_NULL_PTR;", ""]

def tm_big_switch(data):
	output = ["int init_transformer_of_type(tm_transformer *trans, uint16_t type)", "{"]
	output += trans_null_ptr_guard()
	output.append("	switch (type)")
	output.append("	{")

	cases = []
	max_len = 0

	for transformer in data['transformers']:
		name = transformer['name']
		transformer_type = transformer_enum_name(name)
		fn_name = f"init_{normal_sanitize(name)}_default"
		case_str = f"		case {transformer_type}:"
		cases.append((case_str, fn_name))
		if len(case_str) > max_len:
			max_len = len(case_str)

	max_len += 1

	for case_str, fn_name in cases:
		padding = " " * (max_len - len(case_str))
		output.append(f"{case_str}{padding}return {fn_name}(trans);")

	output += ["	}", "", "	return NO_ERROR;", "}"]
	return output

def tm_transformer_init_function(transformer):
	output = []
	name = transformer['name']
	transformer_type = transformer_enum_name(name)
	fn_name = f"init_{normal_sanitize(name)}_default"

	output.append(f"int {fn_name}(tm_transformer *trans)")
	output.append("{")
	
	output = output + trans_null_ptr_guard()
	
	output.append(f"	trans->type = {transformer_type};")
	output.append(f"	trans->compute_transformer = calc_{normal_sanitize(name)};")
	output.append("")
	output.append("	trans->bypass = 0;")

	transition_policy = enum_sanitize(transformer.get('transition_policy', 'monoblock linear'))
	output.append(f"	trans->transition_policy = TRANSFORMER_TRANSITION_{enum_sanitize(transition_policy)};")
	output.append("")
	
	n_inputs = transformer.get('n_inputs', 1)
	n_outputs = transformer.get('n_inputs', 1)
	
	output.append(f"	trans->n_inputs  = {n_inputs};")
	output.append(f"	trans->n_outputs = {n_outputs};")
	output.append("")

	no_struct = transformer.get('no_struct', 0)
	
	n_parameters = len(transformer.get('parameters', []))
	
	output.append(f"	transformer_init_parameter_array(trans, {n_parameters});")
	output.append("")

	if no_struct == 0:
		str_type = "tm_" + name.lower() + "_str"
		output.append(f"	{str_type} *str = ({str_type}*)malloc(sizeof({str_type}));")
		output.append(f"	trans->data_struct = (void*)str;")
		output.append("")
		output.append(f"	if (!str)")
		output.append(f"		return ERR_ALLOC_FAIL;")
		output.append("")
	else:
		output.append(f"	trans->data_struct = NULL;")
		return output + ["", "	return NO_ERROR;", "}", ""]
		

	output.append("	tm_parameter *param;")
	i = 0
	for param in transformer.get('parameters', []):
		pname = param['name']
		minval = param.get('min', -10000000)
		maxval = param.get('max',  10000000)
		default = param.get('default', 1.0)
		location = param.get('location', normal_sanitize(pname))
		update_policy = "PARAMETER_UPDATE_" + enum_sanitize(param.get('smoothing', 'monoblock linear'))
		
		output.append(f"	param = &str->{location};")

		ptype = param.get('type', "")
		
		if ptype == "mix":
			output.append(f"	init_parameter(param, {default}, 0.0, 1.0, {update_policy});")
		else:
			output.append(f"	init_parameter(param, {default}, {minval}, {maxval}, {update_policy});")
		
		output.append(f"	transformer_add_parameter(trans, param);")
		output.append("")
		i = i + 1

	output.append(f"	init_{normal_sanitize(name)}_struct_default(str);")

	return output + ["	return NO_ERROR;", "}", ""]

def main():
	with open("transformer_config.yaml") as f:
		data = yaml.safe_load(f)
	
	tm_output = generated_initial + tm_initial
	enum_output = enum_initial
	
	for transformer in data['transformers']:
		tm_output = tm_output + tm_transformer_init_function(transformer)
	
	tm_output = tm_output + tm_big_switch(data)
	
	with open(tm_fname, "w") as f:
		f.writelines('\n'.join(tm_output) + '\n')
		f.close()

if __name__ == "__main__":
	main()
