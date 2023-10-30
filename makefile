BUILD_DIR=build
ARTIFACT=canvas-lib
PACKAGE_DIR=pkg

.PHONY: init
init:
	emcmake cmake "-DCMAKE_EXE_LINKER_FLAGS=-s USE_GLFW=3" -S . -B $(BUILD_DIR) -G "Ninja"

.PHONY: build
build:
	cmake --build $(BUILD_DIR)
	cp $(BUILD_DIR)/$(ARTIFACT).wasm $(PACKAGE_DIR)/$(ARTIFACT).wasm
	cp $(BUILD_DIR)/$(ARTIFACT).wasm demo/public/$(ARTIFACT).wasm
	touch $(BUILD_DIR)/$(ARTIFACT).data
	cp $(BUILD_DIR)/$(ARTIFACT).data demo/public/$(ARTIFACT).data
	cp $(BUILD_DIR)/$(ARTIFACT).js $(PACKAGE_DIR)/$(ARTIFACT).js

clean:
	rm -rf $(BUILD_DIR)