CC = clang++
WARNINGS = -Wall -Wextra -Werror -Wpedantic -Wno-int-to-void-pointer-cast
CFLAGS = -g -O2
LIBS = -lglfw -lGL -lGLEW

# Base
FILES = main.cpp Renderer.cpp VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp Shader.cpp Texture.cpp
INCLUDE = -I.

# Tests
FILES += tests/TestClearColor.cpp tests/Test.cpp tests/TestTexture2D.cpp
INCLUDE += -Itests

# STB 
FILES += vendor/stb_image/stb_image.cpp
INCLUDE += -Ivendor/stb_image

# imgui
FILES += vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp vendor/imgui/imgui.cpp vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp
INCLUDE += -Ivendor/imgui -Ivendor/imgui/backends

OBJ_DIR = obj
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(FILES))
OUT_EXE = out.run
DEFINE = -DDEBUG -DGLEW_STATIC

default: $(OUT_EXE)

$(OUT_EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $(WARNINGS) $(LIBS) -o $@ $(OBJECTS) $(DEFINE) $(INCLUDE)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(WARNINGS) -c $< -o $@ $(DEFINE) $(INCLUDE)

clean:
	rm -f $(OUT_EXE) $(OBJECTS)
