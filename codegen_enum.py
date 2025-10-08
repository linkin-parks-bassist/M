import yaml

enum_fname = "shared/m_transformer_enum.h"

generated_initial = ["// Code generated from transformer_config.yaml by codegen_enum.py"]

enum_initial = [
	"#ifndef M_TRANSFORMER_ENUM_H_",
	"#define M_TRANSFORMER_ENUM_H_",
	""
]

enum_final = ["",
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

def main():
	with open("transformer_config.yaml") as f:
		data = yaml.safe_load(f)
	
	enum_output = generated_initial + enum_initial
	
	def_strings = []
	max_len = 0
	
	for transformer in data['transformers']:
		def_string = f"#define {transformer_enum_name(transformer['name'])} "
		if len(def_string) > max_len:
			max_len = len(def_string)
		def_strings.append(def_string)
	
	i = 0
	for def_string in def_strings:
		padding = " " * (max_len - len(def_string))
		enum_output.append(f"{def_string}{padding}{i}")
		i += 1
	
	enum_output += enum_final
	
	with open(enum_fname, "w") as f:
		f.writelines('\n'.join(enum_output) + '\n')
		f.close()

if __name__ == "__main__":
	main()

