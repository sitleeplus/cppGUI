https://github.com/jpcy/bgfx-minimal-example/tree/master

のhelloworld.cpp/helloworld-mt.cppがよくできているのでベースにする。


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
とかする。

{
  "name": "scopehal-apps",
  "version": "0.1",
  "builtin-baseline": "b1b19307e2d2ec1eefbdb7ea069de7d4bcd31f01",
  "dependencies": [
    "yaml-cpp",
    "libsigcpp",
    "glfw3",
    "spirv-tools"
  ]
}

