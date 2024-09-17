#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from matplotlib.ticker import MaxNLocator

print ("Génération du graphique\n")

df = pd.read_csv('timestamps.csv')

xlab = 'Temps (ns)'
ylab = 'Thread ID'

figure = plt.figure(figsize=(12,3))
ax = figure.add_subplot()

plt.title('Thread timestamps', fontsize=15, fontweight='bold')

scatter = ax.scatter(df.time, df.threadID, c=df.CPU, cmap='Set3', s=10)
legend = ax.legend(*scatter.legend_elements(), title="CPU")

plt.xlabel(xlab, fontsize=12, fontweight='bold')
plt.ylabel(ylab, fontsize=12, fontweight='bold')
ax.yaxis.set_major_locator(MaxNLocator(integer=True))

plt.show()

