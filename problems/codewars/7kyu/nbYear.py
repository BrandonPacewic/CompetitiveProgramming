def nb_year(p0, percent, aug, p, years=0):
    while p0 < p:
        years += 1
        p0 += int(p0 * (percent / 100))
        p0 += aug

    return years