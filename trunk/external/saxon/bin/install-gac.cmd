
				set NET="%PROGRAMFILES%\Microsoft.NET\SDK\v1.1\Bin"
				%NET%\gacutil /if IKVM.Runtime.dll
				%NET%\gacutil /if IKVM.GNU.Classpath.dll
				%NET%\gacutil /if saxon9.dll 
				%NET%\gacutil /if saxon9api.dll                
      