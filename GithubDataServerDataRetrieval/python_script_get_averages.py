#!/usr/bin/python
import csv

ibm = [8, 5, 8, 20, 38, 49, 14, 6, 0, 10, 6, 6]
google = [355, 358, 347, 444, 373, 397, 496, 468, 428, 442, 385, 241]
github = [156, 164, 174, 151, 187, 206, 201, 170, 176, 158, 227, 240]
facebook = [649, 712, 847, 754, 826, 824, 884, 824, 809, 882, 848, 530]
microsoft = [235, 283, 364, 361, 219, 177, 228, 252, 291, 372, 276, 187]

ofile = open('average_over_all_repos.csv', 'wb')
writer = csv.writer(ofile, delimiter=',', quotechar='"', quoting=csv.QUOTE_ALL)

writer.writerow(['Date', 'Google', 'Facebook', 'Github', 'Microsoft', 'IBM', 'Average'])

i = 1
while (i < 13):
    st = "%d,%d,%d,%d,%d,%d" % (i, google[i - 1], facebook[i - 1], github[i - 1], microsoft[i - 1], ibm[i - 1])
    average = (google[i - 1] + facebook[i - 1] + github[i - 1] + microsoft[i - 1] + ibm[i - 1])/5
    st = "%s,%d" % (st, average)
    string = st.split(",")
    writer.writerow(string)
    i = i + 1

ofile.close()
