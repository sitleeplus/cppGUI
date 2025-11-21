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

https://github.com/JoshuaBrookover/bigg
