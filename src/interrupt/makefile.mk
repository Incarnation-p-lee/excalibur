local_dir    :=src/interrupt
local_module :=$(notdir $(local_dir))
local_src    :=$(addprefix $(local_dir)/, $(addsuffix .s, $(local_module)))

src_asm      +=$(local_src)

