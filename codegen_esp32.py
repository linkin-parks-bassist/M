import yaml

generated_initial = ["// Code generated from transformer_config.yaml by codegen_esp32.py"]

em_init_fname = "./M_esp32/main/em_transformer_init.c"
em_init_initial = ["#include \"em.h\"", ""]

em_table_fname = "./M_esp32/main/em_transformer_table.c"
em_table_initial = ["#include \"em.h\"", ""]

def enum_sanitize(s):
	return s.upper().replace(' ', '_')

def normal_sanitize(s):
	return s.lower().replace(' ', '_')

def transformer_enum_name(name):
	return "TRANSFORMER_" + enum_sanitize(name)

def trans_null_ptr_guard():
	return ["	if (!trans)", "		return ERR_NULL_PTR;", ""]

def init_function_name(name):
	return f"init_transformer_{normal_sanitize(name)}"

def em_big_switch(data):
	output = ["int init_transformer_of_type(em_transformer *trans, uint16_t type)", "{"]
	output += trans_null_ptr_guard()
	
	output += ["	int ret_val = init_transformer(trans);", "	", "	if (ret_val != NO_ERROR)", "		return ret_val;"]
	
	output += ["", "	em_parameter *param;"]
	
	output.append("	switch (type)")
	output.append("	{")

	cases = []
	max_len = 0

	for transformer in data['transformers']:
		name = transformer['name']
		transformer_type = transformer_enum_name(name)
		fn_name = init_function_name(name)
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

def em_init_function(transformer):
	output = []
	name = transformer['name']
	transformer_type = transformer_enum_name(name)
	fn_name = init_function_name(name)

	output.append(f"int {fn_name}(em_transformer *trans)")
	output.append("{")
	output += trans_null_ptr_guard()
	output.append(f"	trans->type = {transformer_type};")

	if len(transformer.get('parameters', [])) > 0:
		output += ["", "	em_parameter *param;", ""]

	i = 0
	for param in transformer.get('parameters', []):
		pname = param['name']
		minval = param.get('min', -10000000)
		maxval = param.get('max',  10000000)
		default = param.get('default', 1.0)
		
		output.append("	param = transformer_add_parameter_rp(trans);")
		
		ppid = param.get('id', i)
		output.append(f"	param->id.parameter_id = {ppid};")

		ptype = param.get('type', "")
		
		if ptype == "mix":
			output.append(f"	init_parameter(param, \"{pname}\", {default}, 0.0, 1.0);")
		else:
			output.append(f"	init_parameter(param, \"{pname}\", {default}, {minval}, {maxval});")
		
		output.append("")
		i += 1
	
	return output + ["	return NO_ERROR;", "}", "\n"]

def generate_transformer_table(data):
	output = []
	
	pstrings = []
	
	max_len = 0
	
	i = 0
	transformers = data['transformers']
	
	n_transformers = 0
	for transformer in transformers:
		hidden = transformer.get('hidden', False)
		if hidden == False:
			n_transformers += 1
	
	output.append(f"const int N_TRANSFORMER_TYPES = {n_transformers};")
	output.append("")
	output.append("em_trans_desc transformer_table[] = {")
	
	for transformer in transformers:
		hidden = transformer.get('hidden', False)
		if hidden == False:
			name = transformer['name']
			transformer_type = transformer_enum_name(name)
			instring = f"	(em_trans_desc){{\"{name}\", "
			if len(instring) > max_len:
				max_len = len(instring)
			
			fnstring = f"{transformer_type}}}"
			if i != len(transformers) - 1:
				fnstring += ","
			pstrings.append((instring, fnstring))
			i += 1
	
	for (instring, fnstring) in pstrings:
		padding = " " * (max_len - len(instring))
		output.append(instring + padding + fnstring)
	
	return output + ["};"]

def main():
	with open("transformer_config.yaml") as f:
		data = yaml.safe_load(f)
	
	em_init_output  = generated_initial + em_init_initial
	em_table_output = generated_initial + em_table_initial
	
	for transformer in data['transformers']:
		em_init_output = em_init_output + em_init_function(transformer)
	
	em_table_output += generate_transformer_table(data)
	
	em_init_output = em_init_output + em_big_switch(data)
	
	with open(em_init_fname, "w") as f:
		f.writelines('\n'.join(em_init_output) + '\n')
		f.close()
	with open(em_table_fname, "w") as f:
		f.writelines('\n'.join(em_table_output) + '\n')
		f.close()

if __name__ == "__main__":
	main()
