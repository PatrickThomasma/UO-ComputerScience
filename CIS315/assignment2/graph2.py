import sys
import heapq
from queue import PriorityQueue
def CountDistinctLongestPath (n, m, adj_list,route,dist):
    counter = 0
    longest = 0
    queue = PriorityQueue()


    for i in range (0, n + 1):
        dist[i] = -10 ** 9 

    queue.put((0,1))
    dist[1] = 0
    route[1] = 1

    while not queue.empty():
        d , u= queue.get()
        #print(str(d) + ' ' + str(u))
        #d , u = queue.get()
        #print(str(d) + ' ' + str(u))
        #d,  u = queue.get()
        #print (str(d) + ' ' + str(u))
        #d, u = queue.get()
        #print (str(d) + ' ' + str(u))
        #break

        if (d > dist[u]):
            continue
        for e in adj_list[u]:
            #print("E value" , e)
            v = e[0]
            c = e[1]
            if (c + d < dist[v]):
                continue
            if (c + d == dist[v]):
                route[v] += route[u]
                longest = c + d
                #print("Show this" , route[4])
            if (c + d > dist[v]):
                dist[v] = c + d
                route[v] = route[u]

                queue.put((dist[v], v))
    return route[n], longest





def main():
    #print(sys.stdin.readline().split())
    fileinput = sys.stdin.readline().split()
    nodes,edges = int(fileinput[0]) , int(fileinput[1])
    dist = []
    route = []
    #edges = int(sys.stdin.readline().split()[1])
    #print(edges)
#Nodes and edges from whatever input file is going in
    adj_list = []
    for i in range (10000):
        dist.append(0)
        route.append(0)

    for i in range(nodes):
        adj_list.append([])

    for i in range(edges):
        valuelist = sys.stdin.readline().split()
        s = int(valuelist[0]) #source
        d = int(valuelist[1]) #destinatin
        w = int(valuelist[2]) #Weight
        adj_list[s].append((d , w))
    adj_list.append([])
    #print(adj_list)
    #print(adj_list)
    ans = [0,0]
     #Answer will be updated then we prin the answer
    ans = CountDistinctLongestPath(nodes,edges,adj_list, dist, route)
    print("Longest path: ", ans[1])
    print("Number of Longest Paths: " , ans[0])
    #file1 = open("output.txt", "w")
    #S = "Longest Path:"+ " " + str(longest)
    #file1.write(S)
    #file1.close()



    return


if __name__ == "__main__":
    main()

# Based code off finding number of distint shortest paths from geekforgeeks
