# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  minecraft_config = debug

else ifeq ($(config),release)
  minecraft_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := minecraft

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

minecraft:
ifneq (,$(minecraft_config))
	@echo "==== Building minecraft ($(minecraft_config)) ===="
	@${MAKE} --no-print-directory -C minecraft -f Makefile config=$(minecraft_config)
endif

clean:
	@${MAKE} --no-print-directory -C minecraft -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   minecraft"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"