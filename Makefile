INCLUDE=-I. `pkg-config --cflags glu` `pkg-config --cflags glew` -Imul -Icommon -Imodule -Ifile -Ichar_string -Iutopia -Iinclude
CFLAGS=-Wall -g -D_DEBUG ${INCLUDE}
LDLIBS=-lglut `pkg-config --libs glu` `pkg-config --libs glew` -lm
MOD_H=$(shell find $(SOURCEDIR) -name '*.mod.h')
OBJECTS_H=$(MOD_H:%.mod.h=%.h)
DEPS=$(basename($(MAKECMDGOALS)):%=%.d)

include $(OBJECTS_H)

%.h: %.mod.h
	mod_to_h/mod_to_h $^ include/

%.d: %.c
	$(CC) -MM ${INCLUDE} $^ -o include/$@

