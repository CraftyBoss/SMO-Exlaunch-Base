
.PHONY: all clean

all:
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --toolchain=cmake/toolchain.cmake -DFTP_IP=10.0.0.225 -S . -B build && $(MAKE) -C build subsdk9_meta

clean:
	rm -r build || true
