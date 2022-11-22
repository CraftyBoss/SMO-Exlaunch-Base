LOGGER_IP ?= "" # put log server IP in string
FTP_IP ?= 192.168.1.136 # put console IP here
.PHONY: all clean

all:
	cmake --toolchain=cmake/toolchain.cmake -DFTP_IP=$(FTP_IP) -S . -B build && $(MAKE) -C build subsdk9_meta

clean:
	rm -r build || true

log: all
	python3.8 scripts/tcpServer.py 0.0.0.0
