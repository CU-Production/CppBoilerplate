# C++ 快速模板
CMake + vcpkg

解决Windows平台依赖安装难的问题

## Visual Studio

```bash
vcpkg_windows.bat

# 之后 3rd_party/vcpkg.windows/vcpkg install <包名>

mkdir build
cd build
cmake .. cmake -D VCPKG_TARGET_TRIPLET=x64-windows-static -D CMAKE_TOOLCHAIN_FILE=../3rd_party/vcpkg.windows/scripts/buildsystems/vcpkg.cmake -G "Visual Studio 16 2019" -A "x64"

# 在build中打开sln
```

## CLion

Open the Toolchains settings (File > Settings on Windows and Linux, CLion > Preferences on macOS), and go to the CMake settings (Build, Execution, Deployment > CMake). Finally, in CMake options, add the following line:
   
```bash
   -DCMAKE_TOOLCHAIN_FILE=3rd_party/vcpkg.windows/scripts/buildsystems/vcpkg.cmake
```

## oglBoilerplate

一个简单的opengl模板，配置好了glfw3+glad+glm+stb+tinyobjloader+imgui