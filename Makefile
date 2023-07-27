# Base
CC = clang++
WARNINGS = -Wall -Wextra -Werror -Wpedantic -Wno-int-to-void-pointer-cast
CFLAGS = -O2 -g
FILES = main.cpp Renderer.cpp VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp Shader.cpp Texture.cpp
INCLUDE = -I.
LIBS = -lglfw -lGL -lGLEW
DEFINE = -D_DEBUG -DGLEW_STATIC 

# Tests
FILES += tests/TestClearColor.cpp tests/Test.cpp tests/TestTexture2D.cpp tests/TestCube.cpp tests/TestPhysX.cpp tests/TestDirectionalLight.cpp tests/TestAssimp.cpp
INCLUDE += -Itests

## Vendor
# STB 
FILES += vendor/stb_image/stb_image.cpp
INCLUDE += -Ivendor/stb_image

# Dear ImGui
FILES += vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp vendor/imgui/imgui.cpp vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_opengl3.cpp
INCLUDE += -Ivendor/imgui -Ivendor/imgui/backends

# PhysX
CFLAGS += -fPIC
LIBS += -L/opt/cuda/targets/x86_64-linux/lib -lcuda -Wl,-rpath,"."
LIBS += -Lvendor/physx/checked
LIBS += -lPhysX_static_64 -lPhysXCommon_static_64 -lPhysXFoundation_static_64
LIBS += -lPhysXCharacterKinematic_static_64 -lPhysXCooking_static_64 -lPhysXVehicle_static_64
LIBS += -lPhysXVehicle2_static_64 -lPVDRuntime_64 -lPhysXGpu_64
LIBS += -lPhysXPvdSDK_static_64 -lPhysXExtensions_static_64
INCLUDE += -Ivendor/physx/include
DEFINE += -DPX_CHECKED=1 -DPX_NVTX=0 -DPX_PUBLIC_RELEASE=1 -DPX_SUPPORT_OMNI_PVD=1 -DPX_SUPPORT_PVD=1

# Assimp
LIBS += -lassimp

OBJ_DIR = obj
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(FILES))
OUT_EXE = out.run

default: $(OUT_EXE)

$(OUT_EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $(WARNINGS) -o $@ $(OBJECTS) $(DEFINE) $(INCLUDE) $(LIBS)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(WARNINGS) -c $< -o $@ $(DEFINE) $(INCLUDE)

clean:
	rm -f $(OUT_EXE) $(OBJECTS)
