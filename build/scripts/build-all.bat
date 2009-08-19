msbuild ../slimdx.proj /m /target:build /property:Configuration=Debug;Platform=x86
msbuild ../slimdx.proj /m /target:build /property:Configuration=Release;Platform=x86
msbuild ../slimdx.proj /m /target:build /property:Configuration=Debug;Platform=x64
msbuild ../slimdx.proj /m /target:build /property:Configuration=Release;Platform=x64
