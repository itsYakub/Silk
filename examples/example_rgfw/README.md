<div align="center">

# Silk example - RGFW

</div>

- Example submited by: [@ColleagueRiley](https://github.com/ColleagueRiley)

- Compilation command (on linux):
```console
$ cc main.c -lX11 -lXrandr -lm -o example.out
$ ./example.out
```

- Compilation command (on windows):
```console
$ cc main.c -lgdi32 -lwinmm -o example.exe
$ example.exe
```

- Compilation command (on macOS):
```console
$ cc main.c -lm -framework Foundation -framework AppKit -framework CoreVideo -o example.out
$ ./example.out
``` 