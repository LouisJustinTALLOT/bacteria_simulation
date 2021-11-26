import pandas as pd
import matplotlib.pyplot as plt


def analyse_results():
    df = pd.read_csv("res.csv", sep=";")

    plt.scatter(df["x"], df["y"], c=df["t"], marker='.')

    plt.figure()
    plt.plot(df["t"][1:], df["MSD"][1:])

    plt.show()


if __name__ == "__main__":
    analyse_results()
