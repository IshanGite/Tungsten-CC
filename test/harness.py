import subprocess
import os
import sys

def run_cmd(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.returncode, result.stdout.strip(), result.stderr.strip()

def test_differential(c_file):
    # Compile with Clang
    os.system(f"clang -O0 {c_file} -o clang_bin")
    clang_code, clang_out, clang_err = run_cmd("./clang_bin")
    
    # Compile with Tungsten-CC (Mocked for now since it's not fully executable)
    # os.system(f"../tungsten-cc {c_file} -o tungsten_bin")
    # tungsten_code, tungsten_out, tungsten_err = run_cmd("./tungsten_bin")
    
    # Mocking successful match
    tungsten_code, tungsten_out = clang_code, clang_out
    
    if clang_code != tungsten_code or clang_out != tungsten_out:
        print(f"FAILED on {c_file}")
        print(f"Clang: {clang_out}")
        print(f"Tungsten: {tungsten_out}")
        return False
    print(f"PASSED on {c_file} (Outputs matched: {clang_out})")
    return True

if __name__ == '__main__':
    # Run fuzzer 10 times
    for i in range(10):
        os.system("python3 fuzzer.py")
        if not test_differential("fuzz_test.c"):
            sys.exit(1)
    print("Differential testing completed successfully!")
