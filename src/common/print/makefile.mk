local_dir    :=src/common/print
local_module :=$(notdir $(local_dir))
local_src    :=$(addprefix $(local_dir)/, $(addsuffix .c, $(local_module)))

src_c        +=$(local_src)
