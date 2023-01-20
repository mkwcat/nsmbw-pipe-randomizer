mkdir _build bin
Kamek\cw\mwcceppc.exe -I- -i Kamek\k_stdlib -i include -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -RTTI off -DIS_GAME_VERSION_DYNAMIC -c -o _build\nsmbw-random-pipe.o src\nsmbw-random-pipe.cpp
Kamek\Kamek.exe _build\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=riivo/nsmbw-pipe-randomizer/Code/P1.bin -select-version=P1
Kamek\Kamek.exe _build\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=riivo/nsmbw-pipe-randomizer/Code/E1.bin -select-version=E1
