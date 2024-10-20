suffix = .js

include makefile

CC = emcc
CPPFLAGS += -DGENERIC
LDFLAGS += -sMODULARIZE -sEXPORTED_FUNCTIONS=_run -sEXPORT_ES6 $(ldflags)
ldflags = -sEXPORT_NAME=rachel

clean: wasm

wasm:
	rm -f $(bin:.js=.wasm)
