class Instruction:
    def __init__(self, line):
        l = line.split(" ")
        self.amount = int(l[1])
        self.start = int(l[3])-1
        self.to = int(l[5])-1

stack_count = 9

def print_stacks(s):
    for l in s:
        print(l)

def execute_instruction(s, i: 'Instruction'):
    for x in range(0,i.amount):
        s[i.to] = s[i.start][0] + s[i.to]
        s[i.start] = s[i.start][1:]

def execute_instruction_b(s, i: 'Instruction'):
    s[i.to] = s[i.start][:i.amount] + s[i.to]
    s[i.start] = s[i.start] = s[i.start][i.amount:]
    
with open('input') as f:
    instructions = []
    stacks = []
    for i in range(0,stack_count):
        stacks.append("")
    instruction_begin = False
    height = 0
    for line in f.read().splitlines():
        if not instruction_begin :
            if line.startswith(" 1   2"):
                instruction_begin = True
            else:
                for i in range (0,stack_count):
                    if 1+(i*4) <= line.__len__():
                        char = line[1+i*4]
                        if not char == ' ':
                            stacks[i] += char
                height = height+1
        elif not line == "":
            i = Instruction(line)
            instructions.append(i)

    # print crates unmodified
    print_stacks(stacks)
    stacks_save = stacks.copy()
    for i in instructions:
        execute_instruction(stacks,i)

    for i in instructions:
        execute_instruction_b(stacks_save, i)

    print("---------AAAAAAAAAAAAAAAAAAAAAA")

    print_stacks(stacks)

    print("---------BBBBBBBBBBBBBBBBBBBBBB")

    print_stacks(stacks_save)

# python is the worst.