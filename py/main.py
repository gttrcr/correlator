import pandas as pd
from pandas.api.types import is_numeric_dtype
import numpy as np
from scipy.optimize import curve_fit
import itertools

def func(domain, a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0, j=0, k=0, l=0, m=0, n=0, o=0, p=0, q=0, r=0, s=0, t=0, u=0, v=0, w=0, x=0, y=0, z=0, A=0, B=0, C=0, D=0, E=0, F=0, G=0, H=0, I=0, J=0, K=0, L=0, M=0, N=0, O=0, P=0, Q=0, R=0, S=0, T=0, U=0, V=0, W=0, X=0, Y=0, Z=0):
    arr = [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z]
    return a + b * domain[0] + c * domain[1] + d * domain[0]**2 + e * domain[1]**2 + f * domain[0] * domain[1]

filename = "organizations-1000.csv"
print(f"Loading {filename}...")
df = pd.read_csv(filename, delimiter=",")
print(f"{len(df.columns)} columns found [{', '.join(df.columns)}]")
print(f"{len(df.values)} rows found")
print(f"Replacing non numeric data types...", end="[")
replacement = []
for name, type in df.dtypes.items():
    if not is_numeric_dtype(type):
        print(name, end=", ")
        rep_dict = dict(map(lambda x: (x[1], x[0]), enumerate(set(df[name]))))
        df = df.replace(rep_dict)
        replacement.append({name: rep_dict})

print("]")

# for col1_index, col1_name in enumerate(df.columns):
#     for col2_index, col2_name in enumerate(df.columns):
#         if col2_index > col1_index:
#             for deg in range(1, 10):
#                 z = np.polyfit(df[col1_name], df[col2_name], deg, full=True)
#                 if len(z[1]) > 0 and sum(list(map(abs, z[1]))) < pow(10, 1):
#                     print(f"{col1_name}, {col2_name}, {deg}, {', '.join(list(map(str, z[1])))}, {', '.join(list(map(str, z[0])))}")

for rep in range(3, 5):
    nuples = list(itertools.permutations(df.columns, rep))
    for nuple in nuples:
        print(f"Computing [{', '.join(nuple)}]...", end='')
        opt, pcov = curve_fit(func, list(map(lambda x: df[x], nuple[:-1])), df[nuple[-1]])
        print(', '.join(list(map(str, opt))))

# for col1_index, col1_name in enumerate(df.columns):
#     for col2_index, col2_name in enumerate(df.columns):
#         if col2_index > col1_index:
#             for col3_index, col3_name in enumerate(df.columns):
#                 if col3_index > col2_index:
#                     opt, pcov = curve_fit(func, (df[col1_name], df[col2_name]), df[col3_name])
#                     print(opt, pcov)



print("Done")