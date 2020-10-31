@REM mkdir 3rd_party
cd 3rd_party || goto :error
git clone https://github.com/Microsoft/vcpkg.git vcpkg.windows || goto :error
cd vcpkg.windows || goto :error
git checkout 2020.07 || goto :error
call bootstrap-vcpkg.bat || goto :error

vcpkg.exe install ^
	glfw3:x64-windows-static ^
	glm:x64-windows-static ^
	imgui:x64-windows-static ^
	stb:x64-windows-static ^
	tinyobjloader:x64-windows-static ^
	|| goto :error

cd ..
cd ..

exit /b


:error
echo Failed with error #%errorlevel%.
exit /b %errorlevel%