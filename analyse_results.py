import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("res.csv", sep=";")

plt.scatter(df["x"], df["y"], c=df["t"], marker='.')

plt.figure()
plt.plot(df["t"][1:], df["RMS"][1:])

plt.show()
