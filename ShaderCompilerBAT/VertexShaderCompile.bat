set /p user_input = 入力してください

set head = %user_input%%.h%
set hlsl = %user_input%%.hlsl%

type nul > %head%.h

echo float4 main( float4 pos : POSITION ) : SV_POSITION >> %hlsl%
echo { >> %hlsl%
echo 	return pos; >> %hlsl%
echo } >> %hlsl%

fxc.exe /T vs_5_0 /E main /Fh %head% %hlsl%