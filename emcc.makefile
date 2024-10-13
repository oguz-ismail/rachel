suffix = .js

include common.mk

CC = emcc
CPPFLAGS += -DGENERIC -DREUSE
CFLAGS += -O3 -flto
LDFLAGS += -sMODULARIZE -sEXPORTED_FUNCTIONS=_run -sEXPORT_ES6 $(ldflags)
ldflags = -sEXPORT_NAME=rachel

clean: wasm

wasm:
	rm -f $(bin:.js=.wasm)
