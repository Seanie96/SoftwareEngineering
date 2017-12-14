#!/usr/bin/python

import MySQLdb, requests, json, datetime
from requests.auth import HTTPBasicAuth
import time

#insert_user_company method
def insert_user_company(author_id, comp_id, repo_id, weeks, comp_user_exists):
    db = MySQLdb.connect("127.0.0.1",
                         "username",
                         "password",
                         "github_data")
    cursor = db.cursor()

    find_comp_user = "SELECT * FROM company_user WHERE company_id = %d AND user_id = %d" % (comp_id, author_id);
    cursor.execute(find_comp_user)
    results = cursor.fetchall()

    db.close()

    if (len(results) == 0):
        comp_user_insert = "INSERT INTO company_user(company_id, user_id) VALUES(%d, %d)" % (comp_id, author_id)
        db = MySQLdb.connect("127.0.0.1",
                             "username",
                             "password",
                             "github_data")
        cursor = db.cursor()
        try:
            cursor.execute(comp_user_insert)
            db.commit()
        except (MySQLdb.Error, MySQLdb.Warning) as e:
            print(e)
        db.close()

    insert_commits(author_id, repo_id, weeks)


# insert_commits method
def insert_commits(author_id, repo_id, weeks):
    j = 0
    for j in range(0, len(weeks)):
        date_in_unix = weeks[j]['w']
        formatted_date = datetime.datetime.fromtimestamp(int(date_in_unix)).strftime('%Y-%m-%d')
        num_of_commits = weeks[j]['c']
        code_addition = weeks[j]['a']
        code_deletion = weeks[j]['d']
        code_difference = code_addition - code_deletion

        insert_commits = ("INSERT INTO commits(repository_id, user_id, date, number_of_commits, code_addition, code_deletion, code_difference) VALUES(%d, %d, '%s', %d, %d, %d, %d)" % (repo_id, author_id, str(formatted_date), num_of_commits, code_addition, code_deletion, code_difference))
        db = MySQLdb.connect("127.0.0.1",
                            "username",
                            "password",
                            "github_data")
        cursor = db.cursor()
        try:
            cursor.execute(insert_commits)
            db.commit()
        except(MySQLdb.Error, MySQLdb.Warning) as e:
            print(e)
        db.close()
        j = j + 1


db = MySQLdb.connect("127.0.0.1",
                    "username",
                    "password",
                    "github_data")
#companies = ['google']
#repositories = ['WebFundamentals', 'protobuf', 'openhtf', 'shaka-player', 'angle', 'skia-buildbot', 'skia', 'kythe', 'DirectXShaderCompiler', 'flatbuffers', 'ExoPlayer', 'boringssl', 'guava', 'ggrc-core', 'error-prone']

#companies = ['facebook']
#repositories = ['react-native', 'nuclide', 'buck', 'fbthrift', 'bistro', 'rocksdb', 'proxygen', 'fbzmq', 'folly', 'relay', 'react', 'openbmc', 'hhvm', 'reason', 'zstd']

#companies = ['github']
#repositories = ['linguist', 'dmca', 'VisualStudio', 'pages-gem', 'orchestrator', 'cmark', 'gh-ost', 'graphql-client', 'training-kit', 'backup-utils', 'hub', 'refined-github', 'ruby', 'incubator-airflow', 'choosealicense.com']

#companies = ['IBM']
#repositories = ['chatbot-deployer', 'acme-freight', 'rotisserie', 'CognitiveConcierge', 'BluePic', 'swift-enterprise-demo', 'openwhisk-serverless-apis', 'voice-of-the-customer', 'janusgraph-utils', 'metrics-collector-client-swift', 'ubiquity-docker-plugin']
#repositories = ['ubiquity', 'ubiquity-k8s', 'watson-discovery-analyze-data-breaches', 'wcs-ocaml', 'chatbot-deployer', 'acme-freight', 'rotisserie', 'CognitiveConcierge', 'BluePic', 'swift-enterprise-demo', 'openwhisk-serverless-apis', 'voice-of-the-customer', 'janusgraph-utils', 'metrics-collector-client-swift', 'ubiquity-docker-plugin']
#repositories = ['swift-enterprise-demo', 'openwhisk-serverless-apis', 'voice-of-the-customer', 'janusgraph-utils', 'metrics-collector-client-swift', 'ubiquity-docker-plugin']

companies = ['microsoft']
repositories = ['TSJS-lib-generator', 'AppCenter-SDK-Android', 'ChakraCore', 'CNTK', 'BotFramework-WebChat', 'vscode-docs', 'BusinessPlatformApps', 'pxt', 'dotnet', 'mwt-ds', 'sqltoolsservice', 'react-native-windows', 'edx-platform', 'vscode', 'AdaptiveCards']

x  = 0

for x in range(0, len(companies)):
    company = companies[x]
    get_repos_url = "https://api.github.com/repos/" + company + "/" + repositories[0]
    r = requests.get(get_repos_url)
    comp_json = json.loads(r.text)
    comp_id = comp_json['owner']['id']
    comp_name = comp_json['owner']['login']
    comp_url = comp_json['owner']['html_url']

    cursor = db.cursor()

    company_insert = "INSERT INTO company(id, name, url) VALUES(%d, '%s', '%s')" % (comp_id, str(comp_name), str(comp_url))

    print company_insert

    cursor.execute(company_insert)
    db.commit()
    db.close()

    y = 0

    for y in range(0, len(repositories)):
        time.sleep(10)
        get_repos_url = "https://api.github.com/repos/" + company + "/" + repositories[y]
        r = requests.get(get_repos_url, auth=HTTPBasicAuth('Seanie96', 'Greeneyes96!'))
        print(r.text)
        comp_json = json.loads(r.text)
        repo_id = comp_json['id']
        repo_name = comp_json['name']
        repo_url = comp_json['html_url']

        time.sleep(10)

        db = MySQLdb.connect("127.0.0.1",
                            "username",
                            "password",
                            "github_data")
        cursor = db.cursor()
        repo_insert = "INSERT INTO repository(id, name, url, company_id) VALUES(%d, '%s', '%s', %d)" % (repo_id, str(repo_name),str(repo_url), comp_id)

        print repo_insert
        try:
            cursor.execute(repo_insert)
            db.commit()
        except(MySQLdb.Error, MySQLdb.Warning) as e:
            print(e)
        db.close()
        time.sleep(10)
        get_contributors_url = "https://api.github.com/repos/" + str(comp_json['full_name']) + "/stats/contributors"
        r = requests.get(get_contributors_url)
        print(r.text)
        cont_json = json.loads(r.text)
        z = 0
        for z in range(0, len(cont_json)):
            author = cont_json[z]['author']
            weeks = cont_json[z]['weeks']


            db = MySQLdb.connect("127.0.0.1",
                            "username",
                            "password",
                            "github_data")
            cursor = db.cursor()

            find_cont = "SELECT * FROM user WHERE name = '%s'" % (str(author['login']));
            try:
                cursor.execute(find_cont)
                results = cursor.fetchall()
            except(MySQLdb.Error, MySQLdb.Warning) as e:
                print(e)

            db.close()

            comp_user_exists = 0

            if len(results) == 0:
                comp_user_exists = 1
                db = MySQLdb.connect("127.0.0.1",
                                   "username",
                                    "password",
                                    "github_data")
                cursor = db.cursor()
                user_insert = "INSERT INTO user(id, name, url) VALUES(%d, '%s', '%s')" % (author['id'], str(author['login']), str(author['html_url']))
                try:
                    cursor.execute(user_insert)
                    db.commit()
                except(MySQLdb.Error, MySQLdb.Warning) as e:
                    print(e)
                db.close()

            insert_user_company(author['id'], comp_id, repo_id, weeks, comp_user_exists)

            z = z + 1
        y = y + 1
    x = x + 1
