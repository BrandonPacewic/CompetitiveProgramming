def getOutput():
    file = open('ou.txt', 'r')
    return file.readlines()

def getExpected():
    file = open('ex.txt', 'r')
    return file.readlines()

def compairExpectedVsOutput():
    print('Compairing...')
    output = getOutput()
    expected = getExpected()

    print('-----------\nExpected:\n')
    for i in expected:
        print(i[:len(i) - 1])

    print('----------\nOutput:\n')
    for i in output:
        print(i[:len(i) - 1])

    print('\n----------')

    countGood = 0
    for i in range(len(output)):
        if (output[i] == expected[i]):
            countGood += 1
    
    print('\n' + str(countGood) + ' / ' + str(len(output)) + ' Tests Passed\n')