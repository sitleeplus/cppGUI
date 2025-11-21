■SDL3公式からライブラリをダウンロード(/MD)

　SDL3_ttf-devel-3.2.2-VC
 
　SDL3-devel-3.2.26-VC

■ライブラリ等を配置

　projectdir/include/SDL3
 
　projectdir/include/SDL3_ttf
 
　projectdir/lib/x64/SDL3.dll
 
　projectdir/lib/x64/SDL3.lib
 
　projectdir/lib/x64/SDL3_ttf.dll
 
　projectdir/lib/x64/SDL3_ttf.lib
 

■プロジェクトの依存関係設定
　追加のインクルードディレクトリ：include;
　追加の依存ファイル：lib\x64\SDL3.lib;lib\x64\SDL3_ttf.lib;
　各ヘッダーファイルをプロジェクトに追加

■ビルド後イベントでdllをコピーする
　if exist "$(SolutionDir)SDL3test\lib\x64\SDL3.dll" copy /Y "$(SolutionDir)SDL3test\lib\x64\SDL3.dll" "$(OutDir)"
　if exist "$(SolutionDir)SDL3test\lib\x64\SDL3_ttf.dll" copy /Y "$(SolutionDir)SDL3test\lib\x64\SDL3_ttf.dll" "$(OutDir)"

