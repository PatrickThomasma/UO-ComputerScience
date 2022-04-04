
import p51_data_analysis as p51
def majors_readf(fname):
    '''
    (str) -> list
    will extract each major and put them in a list
    >>> majors_readf(fname)
    ['PBA', 'CIS', 'MACS', 'MACS', 'BADM', 'MATH', 'EC', 'CIS', 'CIS', 'PBA', 'CIS', 'MUS', 'CIS', 'CIS', 'EXPL', 'CIS', 'CIS', 'CIS', 'PBA', 'CIS', 'CIS',
    'CIS', 'GS', 'EC', 'EXPL', 'EXPL', 'CIS', 'CIS', 'CIS', 'CIS', 'CIS', 'PBA', 'CIS', 'MACS', 'SDSC', 'CIS', 'CIS', 'PSY', 'CIS', 'CIS', 'EC', 'ATCH', 'CIS',
    'BIC', 'CIS', 'EXPL', 'CIS', 'CIS', 'PHYS', 'CIS', 'PBA', 'CIS', 'CIS', 'SOC', 'CIS', 'PBA', 'PS', 'EXPL', 'PAD', 'MATH', 'SDSC', 'CIS', 'MACS', 'BADM', 'PHYS',
    'CIS', 'CIS', 'GS', 'BIC', 'CIS', 'SDSC', 'EXPL', 'CIS', 'CIS', 'EXPL', 'CIS', 'MATH', 'PBA', 'EC', 'CIS', 'PINS', 'MATH', 'BADM', 'MACS', 'CIS', 'CIS',
    'EXPL', 'EXPL', 'MACS', 'EXPL', 'EC', 'PS', 'EXPL', 'CIS', 'CIS', 'EC', 'CIS', 'CIS', 'MATH', 'ART', 'CIS', 'EXPL', 'CIS', 'CH', 'PJ', 'BADM', 'EC', 'PHYS',
    'BADM', 'CIS', 'ESCI', 'CIS', 'MATH', 'CIS', 'CIS', 'EXPL', 'CIS', 'CIS', 'PBA', 'CIS', 'PHYS', 'CIS', 'CIS', 'CIS', 'CIS', 'CIS', 'CIS', 'PSY', 'EXPL', 'CIS',
    'CIS', 'CIS', 'EC', 'CIS', 'BI', 'CIS']
    '''
    with open(fname,'r') as a:
        lines = a.readlines()
        pat = ''
        for i in range(2,len(lines)):
            pat += lines[i]
            majorsli = pat.split()
        
        return majorsli
def majors_analysis(majorsli):
    '''
    (list) -> dictionary
    will find the frequency of the majors that show up in the list
    >>> majors_analysis(majorsli)
    (['CIS'], 23)
    '''
    countdict = {}
    for item in majorsli:
        if item in countdict:
            countdict[item] = countdict[item] + 1
        else:
            countdict[item] = 1
    countlist = countdict.values()
    maxcount = max(countlist)
    
    modelist = []
    for item in countdict:
        if countdict[item] == maxcount:
            modelist.append(item)
    result = len(countlist)
    return (modelist,result)
def majors_report(majors_mode,majors_ct,majorsli):
    '''
    tuple -> dictionary
    Will return a frequency table of each type of result here
    >>> majors_report(majors_mode,majors_ct,majorsli)
    23 majors are represented in CIS 210 this term.
The most represented major(s):CIS
ITEM FREQUENCY
ART       1
ATCH       1
BADM       5
BI       1
BIC       2
CH       1
CIS       64
EC       8
ESCI       1
EXPL       14
GS       2
MACS       6
MATH       6
MUS       1
PAD       1
PBA       8
PHYS       4
PINS       1
PJ       1
PS       2
PSY       2
SDSC       3
SOC       1
    '''
    print("{} majors are represented in CIS 210 this term.".format(majors_ct))
    print("The most represented major(s):",end = "")
    for item in majors_mode:
        print(item, end = "")
    print()
    p51.frequencyTable(majorsli)
    
    return None
def main():
    '''
    () --> None
    Top level function for analysis of CIS 210 majors data
    '''
    fname = 'p71_majors_cis210w19.txt'

    majorsli = majors_readf(fname)
    majors_mode, majors_ct= majors_analysis(majorsli)
    majors_report(majors_mode,majors_ct,majorsli)
    return None
main()
