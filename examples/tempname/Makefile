
BIN := tempname

$(BIN): $(BIN).c
	gcc -L/usr/local/lib -o $(BIN) $(BIN).c -ldrip

clean:
	rm -f hello

.PHONY: clean
