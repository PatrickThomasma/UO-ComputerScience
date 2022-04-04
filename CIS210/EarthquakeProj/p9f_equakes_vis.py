'''
Patrick Thomasma
Credits: N/A
Earthquake watch
CIS 210 Project 9 winter 2019
'''
import math
import random
from turtle import *
def readFile(fname):
    '''
    (file) -> dictionary
    opens the earthquake file and will take the latitude,longtitude,and magnitude
    of the earthquake and store them as a point in the graph
    >>>readFile('equake50f.txt')
    {1: [-125.815, 43.756, 5.2], 2: [-122.0086667, 42.2915, 5.1], 3: [-122.0583333, 42.3575, 6.0], 4: [-122.0266667, 42.3161667, 5.9],
    5: [-122.6065, 45.0351667, 5.6], 6: [-122.188, 46.2073333, 5.7], 7: [-122.182, 46.2026667, 5.0],
    8: [-122.1825, 46.208, 5.0], 9: [-122.1973333, 46.2035, 5.2], 10: [-122.1958333, 46.2098333, 5.1], 11: [-125.603, 42.752, 5.4],
    12: [-126.103, 43.687, 5.2], 13: [-125.774, 44.98, 5.6]}
    
    '''
    with open(fname, 'r') as eqf:    
      datadict = {}
      eqf.readline()
      key = 0
      for line in eqf: # identifies each lon,lat, and mag and stores them appropriatly
         vals = line.strip().split(',')
         long = float(vals[2])
         lat = float(vals[1])
         mag = float(vals[4])
         key += 1
         datadict[key] = [long,lat,mag]

      return datadict
def euclidD(point1, point2):
    '''
    (list,list) -> float
    Will take all the locations from point 1 and point 2 and will use Eucaldian
    square root to find the distane between the two point
    >>>euclidD([-125.815,43.756,5.2],[-122.0086667,42.2915,5.1])
    4.079565154435671
    '''
    total = 0
    for index in range(len(point1)):
        diff = (point1[index]-point2[index]) ** 2
        total = total + diff

    euclidDistance = math.sqrt(total)
    return euclidDistance
def createCentroids(k, datadict):
    '''
    (int,dictionary) -> (int)
    Will select a random key to make a centroid out of and then when it is going
    through the loop again it will check to make sure that the key hasnt already
    been used
    >>>createCentroids(k,datadict)
    [[-125.815, 43.756, 5.2], [-122.182, 46.2026667, 5.0],
    [-122.1958333, 46.2098333, 5.1],
    [-122.0583333, 42.3575, 6.0], [-125.774, 44.98, 5.6]]
    '''
    centroids = []
    centroidCount = 0
    centroidKeys = []

    while centroidCount < k:
        rkey = random.randint(1,len(datadict))
        if rkey not in centroidKeys: #creates an amount of centroid for cluters to be around
            centroids.append(datadict[rkey])
            centroidKeys.append(rkey)
            centroidCount = centroidCount + 1

    return centroids
def createClusters(k, centroids, datadict,r):
    '''
    (int,int,dictionary,int)->(int)
    Will create an amount of clusters for the points of earthquakes to be
    held in.
    >>> createClusters(5,centroids,datadict,5)
    [[1, 11, 12], [7, 8, 9, 10], [5, 6], [2, 3, 4], [13]]
    '''
    for apass in range(r):
       # print("****PASS",apass,"****")
        clusters = []
        for i in range(k):
            clusters.append([])

        for akey in datadict:
            distances = []
            for clusterIndex in range(k):

                dist = euclidD(datadict[akey],centroids[clusterIndex])
                distances.append(dist)

            mindist = min(distances)
            index = distances.index(mindist)

            clusters[index].append(akey)

        dimensions = len(datadict[1])
        for clusterIndex in range(k):
            sums = [0]*dimensions #makes an amount of dimensions for the points
            for akey in clusters[clusterIndex]:
                datapoints = datadict[akey]
                for ind in range(len(datapoints)):
                    sums[ind] = sums[ind] + datapoints[ind]
            for ind in range(len(sums)):
                clusterLen = len(clusters[clusterIndex])
                if clusterLen != 0:
                    sums[ind] = sums[ind]/clusterLen

            centroids[clusterIndex] = sums

            #for c in clusters:
             #   print("CLUSTER")
              #  for key in c:
              #      print(datadict[key], end=" ")
               # print()
    return clusters
def visualizeQuakes(k,r,f):
    '''
    (int,int,file) -> None
    Calls each function and then will call to eqdraw to make a map with
    earthquake points plotted on it
    '''
    datadict = readFile(f)
    quakeCentroids = createCentroids(k, datadict)
    clusters = createClusters(k, quakeCentroids, datadict, r)
    eqDraw(k,datadict,clusters)
    return None
    
def eqDraw(k,datadict,clusters):
    '''
    (int,dictionary,int) --> None
    Takes the worldmap.gif map and will put a dot on each earthquake spot depending
    on the longitude and latitude of the cluster
    >>>eqDraw(k,datadict,clusters)
    Turtle map
    '''
    quakeWin = Screen()
    quakeWin.bgpic("worldmap1800_900.gif")
    quakeWin.screensize(1800, 900)

    wFactor = (quakeWin.screensize()[0]/2)/180
    hFactor = (quakeWin.screensize()[1]/2)/90 #creates size of hte map

    hideturtle()
    up()

    colorlist = ["red","green","blue","orange","cyan","yellow","darkorange","navy","aqua",
                 "slateblue","gold","peru","maroon"]

    speed('fastest')

    for clusterIndex in range(k):
        color(colorlist[clusterIndex])
        for akey in clusters[clusterIndex]:
            lon = datadict[akey][0]
            lat = datadict[akey][1]
            goto(lon*wFactor,lat*hFactor)
            dot(datadict[akey][2]*1.5)#will make the dot bigger depending on mag size
    quakeWin.exitonclick()
    return None
def main():
    '''
    () -> None
    Calls: visulizeQuakes
    Top level function for turtle drawing
    '''
    k = 13
    r = 13
    f = 'earthquakes.csv'
    visualizeQuakes(k,r,f)
    return None
main()

