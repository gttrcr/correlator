import os
import pandas as pd
from pandas.api.types import is_numeric_dtype
import numpy as np
from scipy.optimize import curve_fit
import itertools
from func1 import *
from func2 import *
from func3 import *

filename = "organizations-1000.csv"
filename = "test.csv"
print(f"Loading {filename}...")
df = pd.read_csv(filename, delimiter=";", low_memory=False)
print(f"{len(df.columns)} columns found [{', '.join(df.columns)}]")
print(f"{len(df.values)} rows found")

print(f"Replacing non numeric data types...")
replacement = []
something_to_change = False
for name, type in df.dtypes.items():
    if not is_numeric_dtype(type):
        something_to_change = True
        print(f"\t{name} from {type} to numeric")
        rep_dict = dict(map(lambda x: (x[1], x[0]), enumerate(set(df[name]))))
        df = df.replace(rep_dict)
        replacement.append({name: rep_dict})

if something_to_change:
    df.to_csv(f"used_{os.path.splitext(filename)[0]}.csv", index=False)
else:
    print(f"Wow, every data types is numeric!")

for rep in range(1, 3 + 1):  # 3 is the limit (the size of the space R^3->R)
    nuples = list(itertools.permutations(df.columns, rep + 1))
    for nuple in nuples:
        print(f"#### {', '.join(nuple)} ####")
        for deg in range(1, 10 + 1):  # 10 is the limit (the degree of the polynomial)
            func = globals()[f"func{rep}{deg}"]
            opt, pcov = curve_fit(
                func, list(map(lambda x: df[x], nuple[:-1])), df[nuple[-1]]
            )
            # z = np.polyfit(df[nuple[0]], df[nuple[1]], deg, full=True)
            if np.linalg.det(pcov) < 10 ** (-25):
                print(f"\t{deg} ", ", ".join(list(map(str, opt))))

print("Done")
