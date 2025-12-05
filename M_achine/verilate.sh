verilator src/pipeline.v --top-module pipeline -Isrc -Iinclude -cc --trace-fst -exe verilator/sim_main.cpp && make -C obj_dir -j -f Vpipeline.mk Vpipeline
