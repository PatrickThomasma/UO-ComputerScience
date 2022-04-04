import p51_data_analysis as p51
def equake_readf(fname):
    '''
    (str) -> list
    will grab necessary data for magnitude and return all the magnitudes
    >>>equake_readf(fname)
    [5.2, 5.1, 6.0, 5.9, 5.6, 5.7, 5.0, 5.0, 5.2, 5.1, 5.4, 5.2, 5.6]

    
    '''
    with open(fname,'r') as a:
        magnitudes = []
        a.readline()
        for line in a:
            quake = line.split(',')
            magnitudes.append(float(quake[4]))
            
        return magnitudes
def equake_analysis(magnitudes):
    '''
    list -> tuple
    will find the mean,median,mode of the list
    >>>equake_analysis(magnitudes)
    (5.384615384615385, [5.2], 5.2)
    
    '''
    a = p51.mean(magnitudes)
    b = p51.mode(magnitudes)
    c = p51.median(magnitudes)
    mmm = (a,b,c)
    return mmm
def equake_report(mmm,magnitudes):
    '''
    tuple -> dictionary
    will report the freq table and mean,median,mode of the magnitudes
    >>>equake_report(mmm,magnitudes)
    		 
The mean of Earthquakes is 5.384615384615385
The mode of Earthquakes is [5.2]
The median of Earthquakes is 5.2
ITEM FREQUENCY
5.0       2
5.1       2
5.2       3
5.4       1
5.6       2
5.7       1
5.9       1
6.0       1
None
    
    '''
    print('The mean of Earthquakes is',mmm[0])
    print('The mode of Earthquakes is',mmm[1])
    print('The median of Earthquakes is',mmm[2])
    print(p51.frequencyTable(magnitudes))
    return None
def main():
    '''
    () -> None
    Calls: equake_readf, equake_analysis, equake_report
    Top level function for earthquake data analysis
    '''
    #fname = 'equake25f.txt'
    fname = 'equake50f.txt'
    magnitudes = equake_readf(fname)
    mmm = equake_analysis(magnitudes)
    equake_report(mmm,magnitudes)
    
    return None
main()
