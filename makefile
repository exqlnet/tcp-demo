client: client.cpp
	@mkdir -p out
	$(CC) client.cpp -o out/client

server: server.cpp
	@mkdir -p out
	$(CC) server.cpp -o out/server

all: server client

clean:
	@if [ -d "out" ]; then \
		rm -rf out; \
	fi