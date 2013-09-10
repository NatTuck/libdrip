
BIN := shell

$(BIN): $(BIN).c
	gcc -L/usr/local/lib -o $(BIN) $(BIN).c -ldrip

clean:
	rm -f $(BIN)

.PHONY: clean
