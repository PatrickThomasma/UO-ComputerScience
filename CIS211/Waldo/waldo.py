Waldo = 'w'
Other = '.'
def all_row_exists_waldo(logic: list):
    if len(logic) == 0:
        return True
    else:
        for i in range(0,2):
           if Waldo not in logic[i]:
                return False
        return True


def all_col_exists_waldo(logic):
    if len(logic) == 0:
        return True
    else:
        for i in range(len(logic)):
            bool = []
            for j in range(len(logic[i])):
                if logic[j][i] == Other:
                    bool.append(Other)
                if len(bool) == 3:
                    return False

        return True
def all_row_all_waldo(logic):
    if len(logic) == 0:
        return True
    else:
        for i in range(0,2):
           if Other in logic[i]:
                return False
        return True

def all_col_all_waldo(logic):
    if len(logic) == 0:
        return True
    else:
        for i in range(0,2):
           if Other in logic[i]:
                return False
        return True
def exists_row_exists_waldo(logic):
    if len(logic) == 0:
        return False
    else:
        for i in range(len(logic)):
            if Waldo in logic[i]:
                return True
        return False

def exists_col_exists_waldo(logic):
    if len(logic) == 0:
        return False
    else:
        for i in range(0,2):
           if Waldo in logic[i]:
                return True
        return False

def exists_row_all_waldo(logic):
    if len(logic) == 0:
        return False
    elif len(logic) == 2:
        return True
    else:
        for i in range(len(logic)):
            bool = []
            for j in range(len(logic[i])):
                if logic[i][j] == Waldo:
                    bool.append(Waldo)
                if len(bool) == 3:
                    return True

        return False

def exists_col_all_waldo(logic):
    if len(logic) == 0:
        return False
    else:
        for i in range(len(logic)):
            bool = []
            for j in range(len(logic[i])):
                if logic[j][i] == Waldo:
                    bool.append(Waldo)
                if len(bool) == 3:
                    return True

        return False