import random

def generate_expression(depth=0):
    if depth > 3:
        return str(random.randint(1, 100))
    
    op = random.choice(['+', '-', '*', '/'])
    left = generate_expression(depth + 1)
    right = generate_expression(depth + 1)
    
    # Avoid div by zero in fuzzer generation for now
    if op == '/' and right == '0':
        right = '1'
        
    return f"({left} {op} {right})"

def generate_c_file(filename):
    with open(filename, 'w') as f:
        f.write("#include <stdio.h>\n\n")
        f.write("int main() {\n")
        f.write(f"    int result = {generate_expression()};\n")
        f.write("    printf(\"%d\\n\", result);\n")
        f.write("    return 0;\n")
        f.write("}\n")

if __name__ == '__main__':
    generate_c_file("fuzz_test.c")
    print("Generated fuzz_test.c")
