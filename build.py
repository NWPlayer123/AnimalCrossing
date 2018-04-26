from subprocess import Popen
from os.path import exists
from os import walk, mkdir, makedirs

do_run = 1
linker = []
if not exists("build"):
    mkdir("build")
for root, dirs, files in walk("."):
    for name in files:
        if name.endswith(".c"):
            obj_file = ".\\build\\" + root[2:] + "\\" + name[:-2] + ".o"
            pathname = root + "\\" + name
            if not exists(".\\build\\" + root[2:]):
                makedirs(".\\build\\" + root[2:])
            if do_run:
                Popen(["C:/devkitPro/devkitPPC/bin/powerpc-eabi-gcc.exe", "-c",
                        "-fno-builtin", "-Og", "-o", obj_file, pathname]).wait()
            else:
                print(" ".join(["C:/devkitPro/devkitPPC/bin/powerpc-eabi-gcc.exe",
                          "-c", "-fno-builtin", "-Og", "-o", obj_file, pathname]))
            linker.append(obj_file)
if do_run:
    Popen(["C:/devkitPro/devkitPPC/bin/powerpc-eabi-ld.exe"] + linker + \
         ["-nostartfiles", "-T", "linker.ld", "-o", "output.elf"]).wait()
else:
    print(" ".join(["C:/devkitPro/devkitPPC/bin/powerpc-eabi-ld.exe"] + linker + \
                        ["-nostartfiles", "-T", "linker.ld", "-o", "output.elf"]))
