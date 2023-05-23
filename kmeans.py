import sys
def main(K,  max_iter = 200):
    N = []
    M=[]
    try:
        K=int(K)
    except:
        print('K must be int')
        return
    if(K < 0):
        print("K must be positive")
    assert(K >= 0) 
    try:
        max_iter=int(max_iter)
    except:
        print('max_iter must be int')
        return
    if(max_iter < 0):
        print("max_iter must be positive")
    assert(max_iter >= 0)    
    for line in sys.stdin:
        line = line[0:-1]
        line_split = line.split(",")
        d = len(line_split)
        N.append(line_split)
    n = len(N)
    if(K>=n):
        print("K>=N is invalid")
    assert(K<n)
    result = [[0 for cord in range(d)] for group in range(K)]
    Mio_count=[1 for cord in range(K)]
    for group in range(K):
        for cord in range(d):
            result[group][cord] = (N[group][cord])
    counter = 0
    max_iter=int(max_iter)
    while (counter < max_iter):
        Mio_count = [0 for cord in range(K)]
        counter += 1
        Mio = [[[0 for cord in range(d)] for group in range (K)] for k in range(2)]
        tmp_Mio = centroids(K,Mio,result,N,Mio_count)
        if(result==tmp_Mio):
            break
        else:
            result = tmp_Mio
    cosmetic(result)


def Norma(x_i, Mio_j):
    d = len(x_i)
    norma = 0
    for cord in range(d):
        norma += pow((float(x_i[cord]) - float(Mio_j[cord])),2)
    return norma

def centroids(K, Mio,result,N,Mio_count):
    d = len(N[0])
    for point in N:
        min_i = Norma(point,result[0])
        i = 0
        for cluster in range(K):
            tmp = Norma(point ,result[cluster])
            if (tmp < min_i):
                min_i = tmp
                i = cluster
        Mio_count[i] += 1
        for r in range(d):
            Mio[0][i][r] = float(Mio[0][i][r]) + float(point[r])
    for cluster in range(K):
        for r in range(d):
            if(Mio_count[cluster] != 0):
                Mio[1][cluster][r] = Mio[0][cluster][r]/Mio_count[cluster]
            else:
                Mio[1][cluster][r] = result[cluster][r]
    return (Mio[1])

def cosmetic(result):
    stringres=""
    for cluster in result:
        for cord in cluster:
            cord=str(round(cord,4))
            digits=0
            passed_dot=False
            for byte in cord:
                if passed_dot:
                    digits+=1
                if byte=='.':
                    passed_dot=True
            stringres+=cord
            for i in range(4-digits):
                stringres+="0"
            stringres+=","
        stringres= stringres[0:-1]
        print(stringres)
        stringres=""

if __name__ == "__main__":
    if (len(sys.argv)==3):
        main(sys.argv[1], sys.argv[2])
    if (len(sys.argv)==2):
        main(sys.argv[1])
    if(len(sys.argv)!=3 and len(sys.argv)!=2):
        print("The number of arguments doesn't match")
