DIR      = ./build

EE_BIN  = BARULANDIA.PS2.elf
EE_SRCS = $(wildcard ./source/*.cpp)
EE_OBJS = $(EE_SRCS:.cpp=.o)
EE_OBJS += build/assets.o

EE_INCS     = -I$(PS2SDK)/ports/include -I./include -I$(PS2SDK)/ports/include/stlport
EE_LDFLAGS  = -L$(PS2SDK)/ports/lib -L$(PS2DEV)/gsKit/lib
EE_LIBS     = -lSDL_image -lsdlmixer -lsdl -lz -lSDL_ttf -lstdc++ -lm -lpng -lmikmod \
			  -ljpeg -ltiff -lfreetype -lSDL_gfx

EE_CXXFLAGS += -DPS2 -w -O3
#EE_CXXFLAGS += -DDEBUG

all: $(EE_BIN)

clean:
	rm -f $(EE_OBJS) $(EE_BIN)
	rm -fr $(DIR)

$(DIR)/assets.bin: $(wildcard ./release/USRDIR/*)
	mkdir $(DIR)
	genromfs -d ./release/USRDIR/ -v -V BARULANDIA -f $(DIR)/assets.bin

$(DIR)/assets.cpp: $(DIR)/assets.bin
	bin2c $(DIR)/assets.bin $(DIR)/assets.cpp assets

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal_cpp
