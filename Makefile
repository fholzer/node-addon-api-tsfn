ADDON_SOURCE=$(shell find src/ -type f)

.PHONY: all
all: crash

.PHONY: crash
crash: build
	@for i in $$(seq 1 1000); do \
			echo "Iteration $$i"; \
			node --expose-gc test/test_binding.js || { \
				echo "got exit code $$? on iteration $$i"; \
				break; \
			}; \
		done

.PHONY: test
test: build
	node --expose-gc test/test_binding.js

.PHONY: build
build: build/Debug/test-native-tsfn.node

build/Debug/test-native-tsfn.node: binding.gyp $(ADDON_SOURCE)
	npx node-gyp configure
	npx node-gyp build -d

.PHONY: clean
clean:
	npx node-gyp clean
