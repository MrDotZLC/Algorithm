import os
from collections import defaultdict

root = r"D:\CodeSpace\Algorithm"
files = defaultdict(list)

for path, _, filenames in os.walk(root):
    for name in filenames:
        files[name].append(os.path.join(path, name))

for name, paths in files.items():
    if len(paths) > 1:
        print(f"\n文件名: {name}")
        for p in paths:
            print("  ", p)
