# Sorts out strings from a list of ints and strings
def filterList(l):
    return [x for x in l if type(x) is int]