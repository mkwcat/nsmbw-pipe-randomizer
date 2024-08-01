import os

try:
    os.mkdir("build")
except FileExistsError:
    pass

try:
    os.mkdir("output")
except FileExistsError:
    pass

os.system("Kamek\\cw\\mwcceppc.exe -I- -i Kamek\\k_stdlib -i include -pragma \"cpp1x on\" -gccext on -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -RTTI off -DIS_GAME_VERSION_DYNAMIC -c -o build\\nsmbw-random-pipe.o src\\nsmbw-random-pipe.cpp")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\P1.bin -select-version=P1")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\P2.bin -select-version=P2")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\E1.bin -select-version=E1")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\E1.bin -select-version=E2")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\E1.bin -select-version=J1")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\E1.bin -select-version=J2")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\E1.bin -select-version=K")
os.system("Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\E1.bin -select-version=W")
