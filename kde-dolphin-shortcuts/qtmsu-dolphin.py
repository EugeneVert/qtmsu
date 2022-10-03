#!/usr/bin/env python

import os
from subprocess import run
from urllib.parse import unquote, urlparse

import pyperclip


def main():
    run(["xdotool", "sleep", "0.25", "getactivewindow", "key", "ctrl+c"])
    c = pyperclip.paste().splitlines()
    for i in range(len(c)):
        c[i] = unquote(urlparse(c[i]).path)
        print(c[i])
    print(c)
    os.chdir(os.path.dirname(c[0]))
    run(["qtmsu", *c])


if __name__ == "__main__":
    main()
