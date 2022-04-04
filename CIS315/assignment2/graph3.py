def dfs(adj_list,visited, cur,key,cur_length, ans):
    # check if we have reached our destination
    if(cur==key):
        # if the path length is same then update the count
        if(ans[0]==cur_length):
            ans[1]+=1
        elif(ans[0]<cur_length):
            # otherwise if this path length is greater than update the path length itself
            ans[0]=cur_length
            ans[1]=1
        return

    # visited all the nodes accessible from this node
    for i in range(len(adj_list[cur])):
        if(not visited[adj_list[cur][i][0]]):
            # we dont want repetition so mark this node as visited for the recursive dfs
            visited[adj_list[cur][i][0]]=True
            dfs(adj_list, visited, adj_list[cur][i][0], key, cur_length+adj_list[cur][i][1] ,ans)
            # we want to explore all possible path so we again make this path as unvisited
            visited[adj_list[cur][i][0]]=False

def main():
    # get number of vertex and edges
    l = input().split(' ')
    v = int(l[0])
    e = int(l[1])
    
    # get all edges and store in adj list
    adj_list = []
    visited = []
    for i in range(v):
        adj_list.append([])
        visited.append(False)

    for i in range(e):
        l = input().split(' ')
        s = int(l[0]) #get source
        d = int(l[1]) #get destination
        w = int(l[2]) #get weight
        adj_list[s-1].append((d-1, w))

    ans = [0, 0] #we will store our answer here

    dfs(adj_list,visited, 0, v-1,0, ans) # do a dfs in the graph

    # print solution
    print("longest path: ",ans[0])
    print("number of longest paths: ",ans[1])

main()
