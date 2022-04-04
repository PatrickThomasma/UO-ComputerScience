"""Patrick Thomasma 
Written and finished on January 26th 2022
For CIS 315 Assignment 2
"""


import math
import sys
from collections import defaultdict

#unused function
def topologicalSortUtil(stack,visited,adj,v):
    visited[v] = True
    #print("v is: " , len(adj))

    for i in adj[v]:
        if (not visited[i[0]]):
            #print("Check: ", i)
            topologicalSortUtil(stack,visited,adj,i[0])
    #print(stack)
    stack.append(v)

    return stack

def daglongestpath(adj_list, visited ,current, key , node_length, ans):
    #V = nodes
    #stack = []
    #counter = 0
    #dist = [-10**9 for i in range(edges)]
    #print(dist)

    #for i in range(V):
        #if (visited[i] == False):
            #stack = topologicalSortUtil(stack, visited, adj_list, i)
            #print("Pop: ", stack)

    #dist[0] = 0
    #print(dist)
    #print(adj_list)
    #print(stack)

    
    if (current == key):
        # if current longest path length is the same then we need to update how many there are
        if (ans[0] == node_length):
            ans[1] += 1
        elif (ans[0] < node_length):
            #If theres another longest path then make that the current longest and go back to 1
            ans[0] = node_length
            ans[1] = 1
#Here we want to visit all the nodes that are avaliable for whatever node we're at
    for i in range (len(adj_list[current])):
        #If we have not visited this node then go to it!
        if(visited[adj_list[current][i][0]] == False):
            #Once this node is visited then we can say we've viewed it and update our list
                visited[adj_list[current][i][0]] = True
                length = node_length + adj_list[current][i][1]
                daglongestpath(adj_list,visited,adj_list[current][i][0],key, length, ans)
                #After the recursive call we will want to turn this node back to false since we want to explore it again to see all possible paths
                #print("Nodes check" , adj_list[current][i])
                visited[adj_list[current][i][0]] = False
 #This code below did NOT work



  #  while (len(stack) > 0):
      #  u = stack[-1]
      #  del stack[-1]
        #print("Checking Adjacent to U: ",u)

      #  if (dist[u] != 10**9):
     #       for i in adj_list[u]:
                #print("Checking i: ", i)
                #print("Checking dist: ", dist[u])
    #            if (dist[i[0]] < dist[u] + i[1]):
   #                 dist[i[0]] = dist[u] + i[1]
  #  longest = 0
  #  for i in dist:
     #   if (i >= longest):
     #       counter += 1
    #        longest = i


   # return longest
    

    


def main():
    #print(sys.stdin.readline().split())
    fileinput = sys.stdin.readline().split()
    nodes,edges = int(fileinput[0]) , int(fileinput[1])  
    #edges = int(sys.stdin.readline().split()[1])
    #print(edges)
#Nodes and edges from whatever input file is going in
    adj_list = []
    visited = []

    for i in range(nodes):
        adj_list.append([])
        visited.append(False)
 
    for i in range(edges):
        valuelist = sys.stdin.readline().split()
        s = int(valuelist[0]) #source
        d = int(valuelist[1]) #destinatin
        w = int(valuelist[2]) #Weight
        adj_list[s - 1].append((d - 1, w))
    adj_list.append([])
    #print(adj_list)
    ans = [0,0] #Answer will be updated then we prin the answer
    daglongestpath(adj_list, visited, 0 , nodes - 1, 0 , ans)
    print("Longest Path: ", ans[0])
    print("Number of Longest paths: " , ans[1])
    #file1 = open("output.txt", "w")
    #S = "Longest Path:"+ " " + str(longest)
    #file1.write(S)
    #file1.close()

    

    return

if __name__ == "__main__":
    main()
