CC = gcc
CFLAGS = -O2
BUILD_DIR := build

.PHONY: all udp tcp clean client_udp server_udp client server

all: udp tcp

udp: $(BUILD_DIR)/client_udp $(BUILD_DIR)/server_udp

tcp: $(BUILD_DIR)/client $(BUILD_DIR)/server

$(BUILD_DIR)/client_udp: client_udp.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/server_udp: server_udp.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/client: client.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/server: server.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
