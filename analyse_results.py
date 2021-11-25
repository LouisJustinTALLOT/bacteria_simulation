import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("res.csv", sep=";")

print(df.head())
plt.scatter(df["x"], df["y"], c=df["t"], marker='.')
plt.show()