CC                 :=$(if $(V), gcc, @gcc)
ASM                :=$(if $(V), nasm, @nasm)
LD                 :=$(if $(V), ld, @ld)
RM                 :=rm -f
MKDIR              :=$(if $(V), mkdir, @mkdir)
PERL               :=$(if $(V), perl, @perl)

out                :=bin
base               :=src
inc                :=$(base)/inc
script             :=script
script_module_decl :=$(script)/generate_declaration.pl
script_external    :=$(script)/generate_external.pl
external           :=$(inc)/external.h

CFLAG              =-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -Wall -Wextra -Werror -c
LD_SCRIPT          =link.ld
LFLAG              =-T$(script)/$(LD_SCRIPT) -m elf_i386
ASMFLAG            =-felf

src_c              :=
src_asm            :=
obj_c              =$(subst .c,.o, $(src_c))
obj_asm            =$(subst .s,.o, $(src_asm))
dep_c              =$(subst .c,.d, $(src_c))
dep_asm            =$(subst .s,.d, $(src_asm))
obj_partial        =$(filter-out %main.o, $(obj_c))
decl               =$(subst .o,_declaration.h, $(obj_partial))
obj                =$(obj_asm) $(obj_c)
dep                =$(dep_c) $(dep_asm)

#
# Make sure boot.o will locate at first 8KB of elf, grub will search multi-boot
# magic number in that range.
#
obj_tmp            =$(obj_c) $(obj_asm)
obj_boot           =$(filter %/boot.o, $(obj_tmp))
obj                =$(obj_boot) $(shell echo $(obj_tmp) | sed -e 's:$(obj_boot)::')

vpath %.h $(inc)

all:

include src/makefile.mk
include src/boot/makefile.mk
include src/boot/descriptor/makefile.mk
include src/boot/multiboot/makefile.mk
include src/bus/makefile.mk
include src/common/makefile.mk
include src/common/print/makefile.mk
include src/data_struct/makefile.mk
include src/interrupt/makefile.mk
include src/interrupt/isr/makefile.mk
include src/memory/makefile.mk
include src/screen/makefile.mk
include src/test/makefile.mk
include src/vfs/makefile.mk
include src/vfs/fs_initrd/makefile.mk

-include $(dep)

CF_DEBUG           :=-g
CF_RELEASE         :=-O3

CFLAG              +=$(addprefix -I,$(inc))
CFLAG              +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))
ASMFLAG            +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))
ASMFLAG            +=$(addprefix -I,$(dir $@))

.PHONY:all help clean initrd

TARGET             :=$(out)/kernel
TARGET_DEP         :=$(dep) $(external) $(decl)

all:$(out) $(TARGET_DEP) $(TARGET)

$(out):
	@echo "    MakeDir  $@"
	$(MKDIR) $@

$(external):$(decl)
	@echo "    Generate $(notdir $@)"
	$(PERL) $(script_external) $(decl)

$(decl):
	@echo "    Generate $(notdir $@)"
	$(PERL) $(script_module_decl) $@ $^

$(dep_c):%.d:%.c
	@echo "    Depend   $(notdir $@)"
	$(CC) -M -MT '$(basename $<).o $(basename $<).d' $(CFLAG) $< | sed -e 's: $(external)::' > $@
	$(if $(filter %main.c, $<),,$(update_decl_depend))

$(dep_asm):%.d:%.s
	@echo "    Depend   $(notdir $@)"
	$(ASM) -M -MT '$(basename $<).o $(basename $<).d' $(ASMFLAG) $< > $@

$(TARGET):$(obj)
	@echo "    Link     $(notdir $@)"
	$(LD) $(LFLAG) $^ -o $@
	@ctags -R $(base)

$(obj_c):%.o:%.c
	@echo "    Compile  $(notdir $<)"
	$(CC) $(CFLAG) $< -o $@

$(obj_asm):%.o:%.s
	@echo "    Assembly $(notdir $<)"
	$(ASM) $(ASMFLAG) $< -o $@

clean:
	@echo "    Clean    Object"
	@$(RM) $(obj) $(initrd_obj)
	@echo "    Clean    Depend"
	@$(RM) $(dep) $(initrd_dep)

help:
	@echo
	@echo "  make            :Default debug build"
	@echo "  make RELEASE=1  :Release build"
	@echo "  make V=1        :Verbose build"
	@echo "  make initrd     :initrd.bin build"
	@echo

## define list ##
define update_decl_depend
    @echo "$(basename $<)_declaration.h: $(addprefix $(dir @),$(shell ls $(dir $@)*.c ))" >> $@
endef

## Initrd ##
INITRD_TARGET      :=$(out)/initrd.bin
INITRD_CC_FLAG     =-c $(if $(RELEASE),-o2,-g) $(addprefix -I,$(inc))

initrd_src         =$(base)/initrd/initrd.c
initrd_obj         =$(subst .c,.o, $(initrd_src))
initrd_dep         =$(subst .c,.d, $(initrd_src))

-include $(initrd_dep)

initrd:$(INITRD_TARGET)

$(initrd_dep):%.d:%.c
	@echo "    Depend   $(notdir $@)"
	$(CC) -M -MT '$(basename $<).o $(basename $<).d' $(INITRD_CC_FLAG) $< > $@
	$(update_decl_depend)

$(INITRD_TARGET):$(initrd_obj)
	@echo "    Link     $(notdir $@)"
	$(CC) -o $@ $<

$(initrd_obj):$(initrd_src)
	@echo "    Compile  $(notdir $<)"
	$(CC) $(INITRD_CC_FLAG) -o $@ $<
	
