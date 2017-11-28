#!/usr/bin/python

import MySQLdb, requests, json, datetime
from requests.auth import HTTPBasicAuth

#insert_user_company method
def insert_user_company(author_id, comp_id, repo_id, weeks, comp_user_exists):
    if comp_user_exists == 1:
        comp_user_insert = "INSERT INTO company_user(company_id, user_id) VALUES(%d, %d)" % (comp_id, author_id)
        db = MySQLdb.connect("127.0.0.1",
                             "username",
                             "password",
                             "github_data")
        cursor = db.cursor()
        cursor.execute(comp_user_insert)
        db.commit()
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
        cursor.execute(insert_commits)
        db.commit()
        db.close()
        j = j + 1


db = MySQLdb.connect("127.0.0.1",
                    "username",
                    "password",
                    "github_data")
companies = ['hubspot']

x  = 0
for x in range(0, len(companies)):
    company = companies[x]
    get_repos_url = "https://api.github.com/users/" + company + "/repos"
    r = requests.get(get_repos_url, auth=HTTPBasicAuth('Seanie96', 'Greeneyes96!'))
    comp_json = json.loads(r.text)
    comp_id = comp_json[0]['owner']['id']
    comp_name = comp_json[0]['owner']['login']
    comp_url = comp_json[0]['owner']['html_url']

    cursor = db.cursor()

    company_insert = "INSERT INTO company(id, name, url) VALUES(%d, '%s', '%s')" % (comp_id, str(comp_name), str(comp_url))

    print company_insert

    cursor.execute(company_insert)
    db.commit()
    db.close()

    y = 0

    for y in range(0, len(comp_json)):
        repo_id = comp_json[y]['id']
        repo_name = comp_json[y]['name']
        repo_url = comp_json[y]['html_url']

        db = MySQLdb.connect("127.0.0.1",
                            "username",
                            "password",
                            "github_data")
        cursor = db.cursor()
        repo_insert = "INSERT INTO repository(id, name, url, company_id) VALUES(%d, '%s', '%s', %d)" % (repo_id, str(repo_name),str(repo_url), comp_id)

        print repo_insert

        cursor.execute(repo_insert)
        db.commit()
        db.close()
        get_contributors_url = "https://api.github.com/repos/" + str(comp_json[y]['full_name']) + "/stats/contributors"

        r = requests.get(get_contributors_url, auth=HTTPBasicAuth('Seanie96', 'Greeneyes96!'))

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
            cursor.execute(find_cont)
            results = cursor.fetchall()

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
                cursor.execute(user_insert)
                db.commit()
                db.close()

            insert_user_company(author['id'], comp_id, repo_id, weeks, comp_user_exists)

            z = z + 1

        y = y + 1

    x = x + 1
