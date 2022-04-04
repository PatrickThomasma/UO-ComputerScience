def all_same(l: list) -> bool:
    for i in range (len(l)):
        if l[0] != l[i]:
            return False
    return True
def dedup(l: list) -> list:
    if len(l) == 0:
        return l
    bug = []
    prev_item = l[0]
    bug.append(prev_item)
    for item in l:
        if item != prev_item:
            bug.append(item)
            prev_item = item

    return bug
def max_run(l: list) -> int:
    ccounter = 1
    mcounter = 1
    if len(l) == 0:
        return 0
    for i in range(1,len(l)):
        if l[i] == l[i-1]:
            ccounter += 1
            if ccounter > mcounter:
                mcounter = ccounter
        else:
            ccounter = 1
    return mcounter


