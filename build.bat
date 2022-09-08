if not exist "./build" mkdir ./build
if not exist "./build/win" mkdir ./build/win
if not exist "./build/win" mkdir ./build/win/obj
if not exist "./build/win/assets" xcopy assets ./build/win/assets
if "%~1" NEQ "--no-build" cl -DGLEW_STATIC -D_HAS_EXCEPTIONS=0 /MTd /MP /Fo./bin/win/obj\ /Febin/win/game -I./lib/include opengl32.lib shell32.lib gdi32.lib user32.lib ./lib/lib/x64/*.lib src/*.cpp /link /NODEFAULTLIB:MSVCRTD.lib /NODEFAULTLIB:LIBCMT.lib
