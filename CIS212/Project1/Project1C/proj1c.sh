x=$(grep -n '91' passwd_212 | awk -F ":" '{print $1}')
y=$(expr $x - 1)
head -n $y  passwd_212  >passwd_212_no90s
LINES=$(wc -l passwd_212 | awk '{print $1}')
new=$(expr $LINES - $(grep -n '99'  passwd_212 | awk -F ":" '{print $1}'))
tail -n $new passwd_212  >>passwd_212_no90s
awk -F ":" '{print $7}' passwd_212_no90s | sort | uniq -c | grep /

