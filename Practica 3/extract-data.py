#!/usr/bin/env python

"""
	NOTE: Run this script with a > output redirect to the desired file:
		./extract-data.py > cities.json
"""
import numpy as np

series = []
lats = []
lons = []
pops = []
bins = []

with open("simplemaps-worldcities-basic.csv") as f:
    for line in f:
        cols = [col.strip() for col in line.split(',')]

        try:
            lat = float(cols[2])
            lon = float(cols[3])
            pop = float(cols[4])
        except Exception:
            continue
        
        pops += [pop]
        lats += [lat]
        lons += [lon]
        
        dbin = 0
        if pop > 10000:
            dbin = 1
        if pop > 100000:
            dbin = 2
        if pop > 1000000:
            dbin = 3
        if pop > 10000000:
            dbin = 4
        bins += [dbin]
    
pops = np.array(pops, dtype=float)
pops -= min(pops)
pops /= max(pops)
pops /= 2


for i in range(len(pops)):
    lat = round(lats[i], 3)
    lon = round(lons[i], 3)
    pop = round(pops[i], 5)
    dbin = bins[i]
    series += [lat, lon, pop, dbin]
        
print series