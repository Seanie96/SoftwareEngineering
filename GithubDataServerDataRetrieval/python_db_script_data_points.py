#!/usr/bin/python

import MySQLdb
import csv
import datetime
from datetime import timedelta

ofile  = open('repos_github_commits.csv', "wb")
writer = csv.writer(ofile, delimiter=',', quotechar='"', quoting=csv.QUOTE_ALL)

#writer.writerow(['Date', 'hhvm', 'react', 'react-native', 'zstd', 'Average'])
#writer.writerow(['Date', 'ggrc-core', 'skia', 'skia-buildbot', 'WebFundamentals', 'flatbuffers', 'guava', 'ExoPlayer', 'error-prone', 'angle', 'protobuf', 'shaka-player', 'kythe', 'openhtf', 'boringssl', 'DirectXShaderCompiler', 'Average'])
#writer.writerow(['Date', 'ubiquity', 'Average'])
#writer.writerow(['Date', 'dotnet', 'CNTK', 'react-native-windows', 'ChakraCore', 'pxt', 'BotFramework-WebChat', 'sqltoolsservice', 'BusinessPlatformApps', 'Average'])
writer.writerow(['Date', 'hub', 'dmca', 'linguist', 'pages-gem', 'Average'])
db = MySQLdb.connect("127.0.0.1",
			"username",
			"password",
			"github_data")

commits_list = []

repositories = ['hub', 'dmca', 'linguist', 'pages-gem']
#repositories = ['dotnet', 'CNTK', 'react-native-windows', 'ChakraCore', 'pxt', 'BotFramework-WebChat', 'sqltoolsservice', 'BusinessPlatformApps']
#repositories = ['hhvm', 'react', 'react-native', 'zstd']
#repositories = ['ubiquity']
#repositories = ['ggrc-core', 'skia', 'skia-buildbot', 'WebFundamentals', 'flatbuffers', 'guava', 'ExoPlayer', 'error-prone', 'angle', 'protobuf', 'shaka-player', 'kythe', 'openhtf', 'boringssl', 'DirectXShaderCompiler']
repository_ids = []

i = 0
for i in range(0, len(repositories)):
    cursor = db.cursor()
    get_ids = "Select * FROM repository WHERE name = '%s';" % (repositories[i])
    cursor.execute(get_ids)
    ids = cursor.fetchall()
    print ids[0][0]
    repository_ids.append(ids[0][0])
    i = i + 1

i = 0
for i in range(0, len(repositories)):
#    date_curr = datetime.datetime.strptime("2016-12-24", "%Y-%m-%d")
    commits_list.append([0] * 12)
    counter  = 1
    while (counter < 13):
        cursor = db.cursor()
        get_commits = "SELECT * FROM commits WHERE repository_id = %d AND MONTH(date) = %d;" % (repository_ids[i], counter)
        cursor.execute(get_commits)
        commits = cursor.fetchall()
        j = 0
        total = 0
        for j in range(0, len(commits)):
            #print commits[j][3]
            total = total + commits[j][3]
        commits_list[i][counter - 1] = total
        print "Month %s: %s" % (counter, total)
        counter = counter + 1
#        date_curr = date_curr + datetime.timedelta(days = 7)
    i = i + 1


i = 1
while (i < 13):
    string = "%d" % (i)
    j = 0
    average = 0
    for j in range(0, len(commits_list)):
        string = "%s,%s" % (string, commits_list[j][i - 1])
        average += commits_list[j][i - 1]
        j = j + 1
    average = average / len(commits_list)
    st = string.split(",")
    st.insert(len(st), average)
    writer.writerow(st)
    i = i + 1
#    date_curr = date_curr + datetime.timedelta(days = 7)
ofile.close()
