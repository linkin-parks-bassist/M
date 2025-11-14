import operator
import yaml
import os

from dataclasses import dataclass, field

generated_initial = ["// Code generated from config/transformer/*.yaml by codegen.py"]

enum_header_fname = "shared/m_transformer_enum.h"
enum_source_fname = "shared/m_transformer_enum.c"

enum_header_initial = [
	"#ifndef M_TRANSFORMER_ENUM_H_",
	"#define M_TRANSFORMER_ENUM_H_",
	"",
	"#define TRANSFORMER_MODE_FULL_SPECTRUM  0",
	"#define TRANSFORMER_MODE_UPPER_SPECTRUM	1",
	"#define TRANSFORMER_MODE_LOWER_SPECTRUM	2",
	"#define TRANSFORMER_MODE_BAND			3",
	"",
	"#define TRANSFORMER_WET_MIX_PID	0xFFFF",
	"",
	"#define TRANSFORMER_BAND_LP_CUTOFF_PID 0xFFFE",
	"#define TRANSFORMER_BAND_HP_CUTOFF_PID 0xFFFD",
	"",
	"#define TRANSFORMER_BAND_MODE_SID 0xFFFF",
	""
]

enum_header_final = ["",
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
	"const char *transformer_type_to_string(uint16_t type);",
	"int transformer_type_valid(uint16_t type);",
	"",
	"#endif"
]

enum_source_initial = [
	"#ifdef __cplusplus",
	"#include <cstdint>",
	"#else",
	"#include <stdint.h>",
	"#endif",
	"",
	"#include \"m_transformer_enum.h\"",
	"",
	"static const char *FNAME = \"m_transformer_enum.c\";",
	""
]

m_eng_init_fname = "./M_engine/src/m_eng_transformer_init.c"
m_eng_init_initial = ["#include \"m_eng.h\"", "", "static const char *FNAME = \"m_eng_transformer_init.c\";", ""]

m_int_init_fname = "./M_interface/main/m_int_transformer_init.c"
m_int_init_transformer_initial = [
	"#include \"m_int.h\"",
	"",
	"static const char *unit_string_    = \"\";",
	"static const char *unit_string_hz  = \" Hz\";",
	"static const char *unit_string_ms  = \" ms\";",
	"static const char *unit_string_db  = \" dB\";",
	"static const char *unit_string_bpm = \" bpm\";",
	"",
	"static const char *FNAME = \"m_int_transformer_init.c\";"
]

m_int_table_fname = "./M_interface/main/m_int_transformer_table.c"
m_int_table_initial = ["#include \"m_int.h\"", "", "static const char *FNAME = \"m_int_transformer_table.c\";", ""]

def enum_sanitize(s):
	return s.upper().replace(' ', '_')

def normal_sanitize(s):
	return s.lower().replace(' ', '_')

def transformer_enum_name(name):
	return "TRANSFORMER_" + enum_sanitize(name)

def scale_rectify(scale):
	if scale == "log":
		return "PARAMETER_SCALE_LOGARITHMIC"
	elif scale == "linear":
		return "PARAMETER_SCALE_LINEAR"
	else:
		return "PARAMETER_SCALE_LINEAR"

trans_null_ptr_guard =  ["	if (!trans)", "		return ERR_NULL_PTR;", ""]
ret_val_guard = ["	if (ret_val != NO_ERROR)", "		return ret_val;", ""]

m_eng_trans_null_ptr_guard =  ["	if (!trans)", "	{", "		RETURN_ERR_CODE(ERR_NULL_PTR);", "	}", ""]
m_eng_ret_val_guard = ["	if (ret_val != NO_ERROR)", "	{", "		RETURN_ERR_CODE(ret_val);", "	}", ""]


class parameter_desc:
	name: 		str = ""
	default: 	float = 0.0
	min_val: 	float = 0.0
	max_val: 	float = 0.0
	max_jump:	float = 0.0
	location:	str = ""
	p_type:		str = ""
	scale:		str = ""
	units:		str = ""
	group:		int = 0
	widget:		str = ""

@dataclass
class setting_desc:
	name: 		str = ""
	s_type:		str = ""
	default: 	int = 0
	max_val:	int = 0
	min_val:	int = 0
	location:	str = ""
	options:	list = field(default_factory=list)
	group:		int = 0
	widget: 	str = ""
	units:		str = ""
	page:		str = ""

@dataclass
class setting_option:
	name:		str = ""
	value:		int = 0

@dataclass
class transformer_desc:
    name:           	str = ""
    enum_name:      	str = ""
    code_name:      	str = ""
    init_fn:        	str = ""
    init_str_fn:    	str = ""
    reconfigure:		bool = False
    reconfigure_fn:		str = ""
    clone_str_fn:		str = ""
    has_clone:			bool = False
    struct_name:    	str = ""
    linear:         	bool = True
    has_struct:     	bool = True
    has_free:       	bool = False
    calc_fn:        	str = ""
    n_inputs:       	int = 1
    n_outputs:      	int = 1
    parameters:     	list = field(default_factory=list)
    n_settings:      	int = 0
    settings:        	list = field(default_factory=list)
    transition:     	str = ""


def load_parameter(parameter):
	param = parameter_desc()
	
	param.name     = parameter['name']
	param.location = parameter.get('location', normal_sanitize(param.name))

	param.p_type = parameter.get('type', "")
	
	if param.p_type == "mix":
		param.min_val   = parameter.get('min', 0.0)
		param.max_val  	= parameter.get('max', 2.0)
		param.default   = parameter.get('default', 1.0)
		param.scale 	= scale_rectify(parameter.get('scale', "linear"))
		param.max_jump 	= parameter.get('max_jump', abs(param.max_val - param.min_val) * 0.0005)
		param.units	   	= parameter.get('units', "")
	elif param.p_type == "freq":
		param.min_val  	= parameter.get('min', 1.0)
		param.max_val  	= parameter.get('max',  10000.0)
		param.default  = parameter.get('default', 440.0)
		param.scale 	= scale_rectify(parameter.get('scale', "log"))
		param.max_jump 	= parameter.get('max_jump', abs(param.max_val - param.min_val) * 0.00005)
		param.units	   	= parameter.get('units', 'Hz')
	elif param.p_type == "gain":
		param.min_val  	= parameter.get('min', -12)
		param.max_val  	= parameter.get('max',  12)
		param.default  = parameter.get('default', 0)
		param.scale 	= scale_rectify(parameter.get('scale', "linear"))
		param.max_jump 	= parameter.get('max_jump', abs(param.max_val - param.min_val) * 0.0005)
		param.units	   	= parameter.get('units', 'dB')
	else:
		param.min_val   = parameter.get('min', 0.0)
		param.max_val  	= parameter.get('max', 100.0)
		param.default  = parameter.get('default', param.min_val)
		param.scale 	= scale_rectify(parameter.get('scale', "linear"))
		param.max_jump 	= parameter.get('max_jump', abs(param.max_val - param.min_val) * 0.0005)
		param.units	   	= parameter.get('units', "")
	
	# Floating point errors were giving me silly "0.______00000000003" kind of things. Round those off
	param.max_jump = round(param.max_jump, 6)
	
	param.group = parameter.get('group', -1)
	param.widget = "PARAM_WIDGET_" + enum_sanitize(parameter.get('widget', "virtual_pot"))
	
	return param

def load_setting(setting):
	s = setting_desc()
	
	s.name     = setting['name']
	s.location = setting.get('location', normal_sanitize(s.name))

	s.s_type = "TRANSFORMER_SETTING_" + enum_sanitize(setting.get('type', "ENUM"))
	
	s.default = setting.get("default", 0)
	s.units   = setting.get("units", "")
	s.page    = setting.get("page", "settings")
	
	s.group = setting.get('group', -1)
	s.widget = "SETTING_WIDGET_" + enum_sanitize(setting.get('widget', "dropdown"))
	
	i = 0
	for option in setting.get('options', []):
		o = setting_option()
		o.name = option.get('name', f"Option {i + 1}")
		o.value = option.get('value', i)
		s.options.append(o)
		i = i + 1
	
	return s

def load_transformer(transformer):
	trans = transformer_desc()
	
	trans.name 				= transformer['name']
	trans.code_name 		= normal_sanitize(transformer.get('code_name', normal_sanitize(trans.name)))
	trans.enum_name 		= "TRANSFORMER_" + enum_sanitize(trans.code_name)
	trans.init_fn 			= f"init_{trans.code_name}"
	trans.calc_fn 			= f"calc_{trans.code_name}"
	trans.calc_nl_fn 		= f"calc_{trans.code_name}"
	trans.init_str_fn 		= f"init_{trans.code_name}_str"
	trans.free_str_fn 		= f"free_{trans.code_name}_str"
	trans.reconfigure_fn 	= f"reconfigure_{trans.code_name}"
	
	trans.struct_name = transformer.get('struct_name', "m_eng_" + trans.code_name + "_str")
	
	trans.linear = transformer.get('non_linear', True)
	
	if not trans.linear:
		trans.calc_fn = "NULL"
		trans.n_inputs  = transformer.get('n_inputs',  1)
		trans.n_outputs = transformer.get('n_outputs', 1)
	else:
		trans.calc_nl_fn = "NULL"
		trans.n_inputs  = 1
		trans.n_outputs = 1
	
	trans.transition = enum_sanitize(transformer.get('transition_policy', 'monoblock linear'))
	
	trans.has_struct   = transformer.get('has_struct',  		True)
	trans.has_free     = transformer.get('has_free',   			False)
	trans.has_clone    = transformer.get('has_clone',   		False)
	trans.reconfigure  = transformer.get("has_reconfigure", 	True)
	trans.clone_str_fn = transformer.get('clone_str', 			'NULL')
	
	if not trans.reconfigure:
		trans.reconfigure_fn = "NULL"
	if not trans.has_free:
		trans.free_str_fn = "NULL"
	
	if trans.has_clone and trans.clone_str_fn == 'NULL':
		trans.clone_str_fn = f"clone_{trans.struct_name}"
	
	for param in transformer.get('parameters', []):
		trans.parameters.append(load_parameter(param))
	
	for setting in transformer.get('settings', []):
		trans.settings.append(load_setting(setting))
	
	return trans

def m_eng_transformer_init_function(trans):
	output  = []
	output += [f"int {trans.init_fn}(m_transformer *trans)", "{"]
	output += ["	if (!trans)", "	{", "		RETURN_ERR_CODE(ERR_NULL_PTR);", "	}", ""]
	output += ["	int ret_val = transformer_init_controls(trans);", "	if (ret_val != NO_ERROR)", "	{", "		RETURN_ERR_CODE(ret_val);", "	}", "", f"	trans->type = {trans.enum_name};", ""]
	
	if trans.linear:
		output += [f"	trans->compute_transformer    = {trans.calc_fn};", f"	trans->compute_transformer_nl = NULL;"]
	else:
		output += [f"	trans->compute_transformer    = NULL;",  f"	trans->compute_transformer_nl = {trans.calc_fn};"]
	
	#output += ["	trans->bypass = 0;"]

	output += [f"	trans->transition_policy = TRANSFORMER_TRANSITION_{trans.transition};", ""]
	#output += [f"	trans->n_inputs  = {trans.n_inputs};", f"	trans->n_inputs  = {trans.n_outputs};", ""]
	output += [f"	ret_val = transformer_init_parameter_array(trans, {len(trans.parameters)});"]
	output += ["	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }"]
	output += [f"	ret_val = transformer_init_setting_array(trans, {len(trans.settings)});"]
	output += ["	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }"]

	if not trans.has_struct:
		output += [f"	trans->data_struct = NULL;", f"	trans->reconfigure = NULL;", f"	trans->free_struct = NULL;"]
		output += [f"	trans->clone_struct = NULL;", f"	trans->struct_size = 0;"]
		return output + ["", "	RETURN_ERR_CODE(NO_ERROR);", "}", ""]
		
	output += [f"	{trans.struct_name} *str = ({trans.struct_name}*)m_alloc(sizeof({trans.struct_name}));"]
	output += [f"	trans->data_struct = (void*)str;", "", f"	if (!str)", "	{", f"		RETURN_ERR_CODE(ERR_ALLOC_FAIL);", "	}", ""]
	output += [f"	trans->reconfigure = {trans.reconfigure_fn};"]
	output += [f"	trans->free_struct = {trans.free_str_fn};", ""]

	for param in trans.parameters:
		output += [f"	init_parameter(&str->{param.location}, {param.default}, {param.min_val}, {param.max_val}, {param.max_jump}, {param.scale});"]
		output += [f"	if ((ret_val = transformer_add_parameter(trans, &str->{param.location})) != NO_ERROR)", "	{", "		RETURN_ERR_CODE(ret_val);", "	}", ""]

	for setting in trans.settings:
		output += [f"	init_setting(&str->{setting.location}, {setting.default});"]
		output += [f"	if ((ret_val = transformer_add_setting(trans, &str->{setting.location})) != NO_ERROR)", "	{", "		RETURN_ERR_CODE(ret_val);", "	}", ""]
	
	output += [f"	trans->clone_struct = {trans.clone_str_fn};"]
	output += [f"	trans->struct_size = sizeof({trans.struct_name});"]

	output += [f"	ret_val = {trans.init_str_fn}(str);"]

	return output + [f"	RETURN_ERR_CODE(ret_val);", "}", ""]

def m_eng_init_transformer_switch(transformers):
	output = ["int init_transformer(m_transformer *trans, uint16_t type)", "{"]
	output += m_eng_trans_null_ptr_guard
	output += ["	switch (type)", "	{"]

	cases = []
	max_len = 0
	
	for trans in transformers:
		case_str = f"		case {trans.enum_name}: "
		cases.append((case_str, trans.init_fn))
		if len(case_str) > max_len:
			max_len = len(case_str)
	
	for case_str, fn_name in cases:
		padding = " " * (max_len - len(case_str))
		output.append(f"{case_str}{padding}return {fn_name}(trans);")
	
	return output + ["		default: RETURN_ERR_CODE(ERR_BAD_ARGS);", "	}", "", "	RETURN_ERR_CODE(NO_ERROR);", "}"]

def m_int_init_transformer_switch(transformers):
	output = ["int init_transformer_of_type(m_transformer *trans, uint16_t type)", "{"]
	output += trans_null_ptr_guard
	
	output += ["	int ret_val = init_transformer(trans);", "	", "	if (ret_val != NO_ERROR)", "		return ret_val;"]
	
	output.append("	switch (type)")
	output.append("	{")

	cases = []
	max_len = 0

	for trans in transformers:
		case_str = f"		case {trans.enum_name}:"
		cases.append((case_str, trans.init_fn))
		if len(case_str) > max_len:
			max_len = len(case_str)

	max_len += 1

	for case_str, fn_name in cases:
		padding = " " * (max_len - len(case_str))
		output.append(f"{case_str}{padding}return {fn_name}(trans);")

	return output + ["		default: return ERR_BAD_ARGS;", "	}", "", "	return NO_ERROR;", "}"]

def m_int_transformer_init_function(trans):
	output = [f"int {trans.init_fn}(m_transformer *trans)", "{"]
	output += trans_null_ptr_guard
	output.append(f"	trans->type = {trans.enum_name};")
	output.append(f"	trans->view_page = NULL;")

	if len(trans.parameters) > 0:
		output += ["", "	m_parameter *param;", ""]

	i = 0
	for param in trans.parameters:
		output.append( "	param = transformer_add_parameter(trans);")
		output.append( "")
		output.append( "	if (!param)")
		output.append( "		return ERR_ALLOC_FAIL;")
		output.append( "")
		output.append(f"	param->id.parameter_id = {i};")
		output.append("")
		output.append(f"	param->value   = {param.default};")
		output.append(f"	param->max   = {param.max_val};")
		output.append(f"	param->min   = {param.min_val};")
		output.append(f"	param->name  = \"{param.name}\";")
		output.append(f"	param->units = unit_string_{param.units.lower()};")
		output.append(f"	param->scale = {param.scale};")
		output.append(f"	param->group = {param.group};")
		output.append(f"	param->widget_type = {param.widget};")
			
		output.append("")
		i += 1
	
	if len(trans.settings) > 0:
		output += ["", "	m_setting *setting;", ""]
	
	for setting in trans.settings:
		output.append( "	setting = transformer_add_setting(trans);")
		output.append( "")
		output.append( "	if (!setting)")
		output.append( "		return ERR_ALLOC_FAIL;")
		output.append( "")
		output.append(f"	setting->id.setting_id = {i};")
		output.append("")
		output.append(f"	setting->value   = {setting.default};")
		output.append(f"	setting->max   = {setting.max_val};")
		output.append(f"	setting->min   = {setting.min_val};")
		output.append(f"	setting->name  = \"{setting.name}\";")
		output.append(f"	setting->units = unit_string_{setting.units.lower()};")
		output.append(f"	setting->group = {setting.group};")
		output.append(f"	setting->widget_type = {setting.widget};")
		output.append(f"	setting->page = TRANSFORMER_SETTING_PAGE_{setting.page.upper()};")
		
		n_options = len(setting.options)
		output.append(f"	setting->n_options = {n_options};")
		
		if n_options > 0:
			output.append(f"	setting->options = m_alloc(sizeof(m_setting) * {n_options});")
			output.append(f"	if (!setting->options) return ERR_ALLOC_FAIL;")
			output.append("")
			
			i = 0
			for option in setting.options:
				output.append(f"	setting->options[{i}].value = {option.value};")
				output.append(f"	setting->options[{i}].name = \"{option.name}\";")
				output.append("")
				i = i + 1
				
		else:
			output.append(f"	setting->options = NULL;")
		
		i += 1
		
	
	return output + ["	return NO_ERROR;", "}", "\n"]

def m_int_generate_transformer_table(transformers):
	output = []
	
	pstrings = []
	
	max_len = 0
	
	i = 0

	n_transformers = 0
	for trans in transformers:
		if trans.linear:
			n_transformers += 1
	
	output.append(f"const int N_TRANSFORMER_TYPES = {n_transformers};")
	output.append("")
	output.append("m_int_trans_desc transformer_table[] = {")
	
	for trans in transformers:
		if trans.linear:
			instring = f"	(m_int_trans_desc){{\"{trans.name}\", "
			if len(instring) > max_len:
				max_len = len(instring)
			
			fnstring = f"{trans.enum_name}}}"
			if i != len(transformers) - 1:
				fnstring += ","
			pstrings.append((instring, fnstring))
			i += 1
	
	for (instring, fnstring) in pstrings:
		padding = " " * (max_len - len(instring))
		output.append(instring + padding + fnstring)
	
	return output + ["};"]

def load_all_yaml_in_dir(dirname):
	data = []
	for fname in os.listdir(dirname):
		if fname.endswith((".yaml", ".yml")):
			path = os.path.join(dirname, fname)
			with open(path, "r") as f:
				try:
					obj = yaml.safe_load(f)
					data.append(obj)
				except yaml.YAMLError as e:
					print(f"Error parsing {fname}: {e}")
	return data

def main():
	transformer_config = load_all_yaml_in_dir("config/transformers")
	
	transformers = []
	
	for transformer in transformer_config:
		transformers.append(load_transformer(transformer))
	
	transformers.sort(key=operator.attrgetter('name'))
	
	m_eng_init = generated_initial + m_eng_init_initial
	
	for trans in transformers:
		m_eng_init = m_eng_init + m_eng_transformer_init_function(trans)
	
	m_eng_init = m_eng_init + m_eng_init_transformer_switch(transformers)
	
	with open(m_eng_init_fname, "w") as f:
		f.writelines('\n'.join(m_eng_init) + '\n')
		f.close()
	
	m_int_init = m_int_init_transformer_initial
	
	for trans in transformers:
		m_int_init = m_int_init + m_int_transformer_init_function(trans)
	
	m_int_init += m_int_init_transformer_switch(transformers)
	
	with open(m_int_init_fname, "w") as f:
		f.writelines('\n'.join(m_int_init) + '\n')
		f.close()
	
	m_int_table = m_int_table_initial + m_int_generate_transformer_table(transformers)
	
	with open("./M_interface/main/m_int_transformer_table.c", "w") as f:
		f.writelines('\n'.join(m_int_table) + '\n')
		f.close()
	
	enum_header_output = generated_initial + enum_header_initial
	
	enum_source_output = generated_initial + enum_source_initial
	enum_nam_eng_function = ["const char *transformer_type_to_string(uint16_t type)", "{", "\t switch(type)", "\t{"]
	enum_typecheck_function = ["int transformer_type_valid(uint16_t type)", "{", "\t switch(type)", "\t{"]
	
	def_strings = []
	case_strings = []
	max_def_len  = 0
	max_case_len = 0
	
	for trans in transformers:
		def_string = f"#define {trans.enum_name} "
		case_string = f"case {trans.enum_name}: "
		if len(def_string) > max_def_len:
			max_def_len = len(def_string)
		def_strings.append(def_string)
		
		if len(case_string) > max_case_len:
			max_case_len = len(case_string)
		case_strings.append([case_string, trans.enum_name])
	
	i = 0
	for def_string in def_strings:
		def_padding = " " * (max_def_len - len(def_string))
		enum_header_output.append(f"{def_string}{def_padding}{i}")
		i += 1
	
	for case_string, name in case_strings:
		case_padding = " " * (max_case_len - len(case_string))
		enum_nam_eng_function.append(f"\t\t{case_string}{case_padding}return \"{name}\";")
		enum_typecheck_function.append(f"\t\t{case_string}")
	
	enum_nam_eng_function += ["\t\tdefault: return \"UNKNOWN\";", "\t}", "}"]
	enum_typecheck_function += ["\t\t\treturn 1;", "\t\tdefault:", "\t\t\treturn 0;", "\t}", "}"]
	
	enum_header_output += enum_header_final
	enum_source_output += enum_nam_eng_function + [""] + enum_typecheck_function
	
	with open(enum_header_fname, "w") as f:
		f.writelines('\n'.join(enum_header_output) + '\n')
		f.close()
	
	with open(enum_source_fname, "w") as f:
		f.writelines('\n'.join(enum_source_output) + '\n')
		f.close()
	
if __name__ == "__main__":
	main()
