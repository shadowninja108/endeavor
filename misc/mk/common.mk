#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/libnx/switch_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#
# CONFIG_JSON is the filename of the NPDM config file (.json), relative to the project folder.
#   If not set, it attempts to use one of the following (in this order):
#     - <Project name>.json
#     - config.json
#---------------------------------------------------------------------------------
export TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
ROOT_SOURCE	:=	$(TOPDIR)/source
MODULES		:=	$(shell find $(ROOT_SOURCE) -mindepth 1 -maxdepth 1 -type d)
SOURCES		:=	$(foreach module,$(MODULES),$(shell find $(module) -type d))
SOURCES		:= 	$(foreach source,$(SOURCES),$(source:$(TOPDIR)/%=%)/)

GENERATED_PATH := $(BUILD)/generated

EXT_PATH := ext

PROTOC := protoc
PROTOS_PATH=$(TOPDIR)/shimmer/protobuf/
PROTOS_BUILD_PATH:=$(GENERATED_PATH)/protobuf
PROTO_SOURCES := $(foreach source,$(PROTOS_PATH),$(source:$(PROTOS_PATH)/%=%)/)
PROTO_EMBEDDED_PATH:=$(EXT_PATH)/EmbeddedProto
PROTOFILES	:= 	$(foreach dir,$(PROTO_SOURCES),$(notdir $(wildcard $(dir)/*.proto)))
PROTOHEADERS := $(PROTOFILES:%.proto=$(PROTOS_BUILD_PATH)/%.h)
PROTO_EMBEDDED_SOURCE := $(PROTO_EMBEDDED_PATH)/src
SOURCES	+= $(PROTO_EMBEDDED_SOURCE)

DATA		:=	data
INCLUDES	:=	include $(PROTO_EMBEDDED_SOURCE) $(GENERATED_PATH)

#---------------------------------------------------------------------------------
# options for code generation
#------------------------------------------------------_+---------------------------
ARCH	:=	-march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIC -fvisibility=hidden

CFLAGS	:=	-g \
			-ffunction-sections \
			-Wno-format-zero-length \
			-fdata-sections \
			$(ARCH) \
			$(DEFINES)

CFLAGS	+=	$(INCLUDE) -D__SWITCH__ -D__RTLD_6XX__

CFLAGS	+= $(EXL_CFLAGS) -I"$(DEVKITPRO)/libnx/include" -I$(ROOT_SOURCE) $(addprefix -I,$(MODULES))

CXXFLAGS	:= $(CFLAGS) $(EXL_CXXFLAGS) -fno-rtti -fno-exceptions -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-threadsafe-statics -std=gnu++23

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	:=  -specs=$(SPECS_PATH)/$(SPECS_NAME) -g $(ARCH) -Wl,-Map,$(notdir $*.map) -nostartfiles

LIBS	:=

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
			$(foreach dir,$(PROTOS_BUILD_PATH),$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SRC	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES 	:=	$(OFILES_BIN) $(OFILES_SRC)
export HFILES_BIN	:=	$(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD) -I$(ROOT_SOURCE)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifeq ($(strip $(CONFIG_JSON)),)
	jsons := $(wildcard *.json)
	ifneq (,$(findstring $(TARGET).json,$(jsons)))
		export APP_JSON := $(TOPDIR)/$(TARGET).json
	else
		ifneq (,$(findstring config.json,$(jsons)))
			export APP_JSON := $(TOPDIR)/config.json
		endif
	endif
else
	export APP_JSON := $(TOPDIR)/$(CONFIG_JSON)
endif

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD): $(PROTOHEADERS)
	@[ -d $@ ] || mkdir -p $@
	@echo $(INCLUDE)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(MK_PATH)/common.mk
	@$(SHELL) $(SCRIPTS_PATH)/post-build.sh

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).nso $(TARGET).npdm $(TARGET).elf


#---------------------------------------------------------------------------------
else
.PHONY:	all 

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

all	:	$(OUTPUT).nso

$(OUTPUT).nso	:	$(OUTPUT).elf $(OUTPUT).npdm

$(OUTPUT).elf	:	$(OFILES)

$(OFILES_SRC)	: $(HFILES_BIN)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	%_bin.h :	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------

$(PROTOS_BUILD_PATH)/%.h: $(PROTOS_PATH)%.proto
	$(shell mkdir -p $(dir $@))
	cd $(PROTO_EMBEDDED_PATH) && $(PROTOC) --plugin=protoc-gen-eams -I$(PROTOS_PATH) --eams_out=$(TOPDIR)/$(PROTOS_BUILD_PATH) $<


# %.pb.cc: %.proto
# 	protoc -I $(PROTOS_PATH) "--cpp_out=$(PROTOS_BUILD_PATH)" $<
# 
# %.pb.o: %.pb.cc	$(PROTOS_BUILD_PATH)
# 	$(SILENTMSG) $(notdir $<)
# 	$(ADD_COMPILE_COMMAND) add $(CXX) "$(CPPFLAGS) $(CXXFLAGS) -c $< -o $@" $<
# 	$(SILENTCMD)$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CPPFLAGS) $(CXXFLAGS) -I/home/somebody/protobuf/src -I/home/somebody/protobuf/third_party/abseil-cpp -c protobuf/$< -o $@ $(ERROR_FILTER) -Wno-deprecated-declarations
# 
# $(PROTOS_BUILD_PATH):
# 	rm -f $(shell find $@ -name "*.pb.*")