PROJ_NAME := WaterRender

CXX := g++
CXX_FLAGS := -Ideps -std=c++17

NATIVE_LIBS := -lm -lGL -lm -lX11 -ldl
DEP_LIBS := \
			./deps/renderer/librenderer.a\
			./deps/GLFW/libglfw3.a\
			./deps/imgui/libimgui.a\

SRC_FILES := $(shell find ./src -name "*.cpp")
OBJ_FILES := $(patsubst ./src/%.cpp, ./obj/%.o, $(SRC_FILES))

.PHONY: all
all: $(PROJ_NAME)

.PHONY: run
run: $(PROJ_NAME)
	./$(PROJ_NAME)

.PHONY: clean
clean:
	rm -rf obj $(PROJ_NAME) *.exe /obj

$(OBJ_FILES) : ./obj/%.o : ./src/%.cpp | create_obj_folder
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(PROJ_NAME) : $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(DEP_LIBS) $(NATIVE_LIBS)

.PHONY: create_obj_folder
create_obj_folder:
	mkdir -p obj
