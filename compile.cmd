copy mpir\win\*.h mpir\

cl bealopt.cpp mpir\win\mpir.lib mpir\win\mpirxx.lib /Zi /nologo /W3 /WX- /O2 /Ob2 /Oi /Ot /Oy /GT /GL /D "_MBCS" /Gm- /EHsc /MT /GS- /Gy /fp:fast /Zc:wchar_t /Zc:forScope /GR- /FAs /Gd /analyze- /favor:INTEL64 /Ox /GA /arch:AVX
