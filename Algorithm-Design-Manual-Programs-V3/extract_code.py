import argparse
import os
import re



OUTPUT_DIR = "fragment"
EXTENSION = ""
MACRO_START = "\s*\/\*\s*\[\[\[\s*(\w+.?\w+)\s*\*\/\s*"
MACRO_END = "\s*\/\*\s*\]\]\]\s*\*\/\s*"



class ParseFile(object):
    def __init__(self, f):
        self.opened_file = f
        self.code = ""


def parse_file(filename):
    print('parsing', filename)
    stack = []
    ff = "{}/{}." + EXTENSION if len(EXTENSION) > 0 else "{}/{}"

    with open(filename, "r", encoding="ISO-8859-1") as f:
        for line in f:
            em = re.match(MACRO_END, line)
            if em:
                tof = stack.pop()
                tof.opened_file.write(tof.code)
                tof.opened_file.close()

                if len(stack) > 0:
                    stack[len(stack)-1].code += tof.code

            sm = re.match(MACRO_START, line)
            if sm:
                of = open(ff.format(OUTPUT_DIR, sm.group(1)), "w+")
                stack.append(ParseFile(f=of))

            if len(stack) > 0 and sm is None and em is None:
                stack[len(stack)-1].code += line


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="Code Snippets")
    parser.add_argument("input_file", help="Input file/Directory to be scanned")
    parser.add_argument("-d", "--directory", help="Desired output directory")
    parser.add_argument("-e", "--extension", help="Desired extension text")
    args = parser.parse_args()

    if args.directory:
        OUTPUT_DIR = args.directory

    if args.extension:
        EXTENSION = args.extension

    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    if os.path.isdir(args.input_file):
        dirname = args.input_file
        directory = os.fsencode(dirname)

        for f in os.listdir(directory):
            if os.path.isfile(dirname + "/" + f.decode(encoding='ISO-8859-1')):
                parse_file(filename=dirname + "/" + f.decode(encoding='ISO-8859-1'))

    else:
        parse_file(filename=args.input_file)

