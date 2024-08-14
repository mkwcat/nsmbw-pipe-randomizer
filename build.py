import os, subprocess

try:
    os.mkdir("build")
except FileExistsError:
    pass

try:
    os.mkdir("output")
except FileExistsError:
    pass

subprocess.run(["Kamek\\cw\\mwcceppc.exe", "-I-", "-i", "Kamek\\k_stdlib", "-i", "include", "-pragma", "cpp1x on", "-gccext", "on", "-Cpp_exceptions", "off", "-enum", "int", "-O4,s", "-use_lmw_stmw", "on", "-fp", "hard", "-rostr", "-sdata", "0", "-sdata2", "0", "-RTTI", "off", "-DIS_GAME_VERSION_DYNAMIC", "-c", "-o", "build\\nsmbw-random-pipe.o", "src\\nsmbw-random-pipe.cpp"]).check_returncode()

for region in ["P1", "P2", "E1", "E2", "J1", "J2", "K", "W", "C"]:
    result = subprocess.run(f"Kamek\\Kamek.exe build\\nsmbw-random-pipe.o -dynamic -versions=address-map.txt -externals=externals.txt -output-kamek=output\\nsmbw-pipe-randomizer\\Code\\{region}.bin -select-version={region}".split(" "), stdout=subprocess.PIPE)
    if result.returncode != 0:
        exit(f"Kamek failed linking region {region}")