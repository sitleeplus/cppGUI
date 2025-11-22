https://github.com/jpcy/bgfx-minimal-example/tree/master

のhelloworld.cpp/helloworld-mt.cppがよくできているのでベースにする。


■imgui+implotの実装例
https://github.com/sukesh-ak/ImGui-GLFW-OpenGL3

■環境
　・GLFWを入れる。glfw-3.4.bin.WIN64からincludeとlibとdllを持ってくる。glfw3dll.libはglfw3.libにリネームして使う。
 
 bgfx.lib、bx.lib、bimg.libをすべて/MDでビルド
　インクルード
 
　・プリプロセッサの定義
 　　BX_CONFIG_DEBUG=0(Releaseの場合は0、Debugの場合は1)
　・C/C++→コマンドラインに追加
 　/Zc:__cplusplus /Zc:preprocessor
 
■imguiの実装で参考になりそう。キーインプットとか。
git clone https://github.com/JoshuaBrookover/bigg.git
git clone https://github.com/yuki-koyama/bigger.git

cd bigger or bigg

git submodule update --init --recursive

cmake . -G "Visual Studio 17 2022" -DCMAKE_POLICY_VERSION_MINIMUM=3.5


・https://github.com/ngscopeclient/scopehal-apps/tree/master
vcpkg.jsonをつくってvcpkg install
見つからない不具合があったらset PATH=C:\Users\cl-p\source\repos\scopehal-apps\vcpkg_installed\x64-windows\share\glfw3;%PATH%
とかでパスを通す。
{
  "name": "scopehal-apps",
  "version": "0.1",
  "builtin-baseline": "b1b19307e2d2ec1eefbdb7ea069de7d4bcd31f01",
  "dependencies": [
    "yaml-cpp",
    "libsigcpp",
    "glfw3",
    "spirv-tools",
    "glslang",
    "vulkan-headers",
    "vulkan-loader",
    "shaderc",
    "hidapi",
    "zlib",
    "libpng",
    "catch2",
    "fftw3"
  ]
}

vulkan::headersだけはどうにもならなかったのでCMakeLists.txtを編集した。
# 元々:
find_package(VulkanHeaders REQUIRED)

# 動いたもの:
　# Find Vulkan-related packages
#WORKAROUND glslang does not look for SPIRV-Tools-opt but needs it on macOS, harmless elsewhere
find_package(SPIRV-Tools-opt REQUIRED)
if(DEFINED VULKAN_SDK_PATH)
	#WORKAROUND The Vulkan SDK ships incomplete cmake config files.
	# Work around this, which does require FindVulkan.cmake.
	# FindVulkan does not find glslang correctly on macOS
	find_package(Vulkan REQUIRED COMPONENTS glslc shaderc_combined SPIRV-Tools)
	find_package(glslang REQUIRED)
	add_library(Vulkan::Loader ALIAS Vulkan::Vulkan)
else()
	find_package(glslang REQUIRED)

	# Vulkan headers
	find_path(Vulkan_INCLUDE_DIR NAMES vulkan/vulkan.h)
	if(NOT Vulkan_INCLUDE_DIR)
	    message(FATAL_ERROR "Unable to find Vulkan headers")
	endif()

	add_library(Vulkan::Headers INTERFACE IMPORTED)
	set_target_properties(Vulkan::Headers PROPERTIES
	    INTERFACE_INCLUDE_DIRECTORIES "${Vulkan_INCLUDE_DIR}")

	# Vulkan loader (Windows は vulkan-1.lib)
	find_library(VulkanLoader_LIB NAMES vulkan-1 REQUIRED)

	add_library(Vulkan::Loader SHARED IMPORTED)
	# DLL の場所（vcpkg なら installed/x64-windows/bin/vulkan-1.dll）
	set_target_properties(Vulkan::Loader PROPERTIES
	    IMPORTED_LOCATION "${VulkanLoader_LIB}"
	)
	
	# インポートライブラリの場所（vcpkg なら installed/x64-windows/lib/vulkan-1.lib）
	set_target_properties(Vulkan::Loader PROPERTIES
	    IMPORTED_IMPLIB "${VulkanLoader_LIB}"
	)

endif()


ただし、vcpkgでインストールしたところにpath通っておらず、visual studioのビルドは失敗。あきらめる。
