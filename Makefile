all:
%: build
	cd build && CXX=clang++ cmake .. && make $@

build:
	mkdir -p build

.PHONY: clean
clean:
	rm -rf build
