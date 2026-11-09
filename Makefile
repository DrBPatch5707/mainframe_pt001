
BUILD_DIR := build

.PHONY: all client server clean

all: client server

client:
	$(MAKE) -C client
	@mkdir -p $(BUILD_DIR)
	cp client/build/main $(BUILD_DIR)/client

server:
	$(MAKE) -C server
	@mkdir -p $(BUILD_DIR)
	cp server/build/main $(BUILD_DIR)/server

clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean
	rm -rf $(BUILD_DIR)
