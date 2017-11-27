var mysql = require('mysql');
var request = require('request');
var moment = require('moment');

var con_config = {
    host: "localhost",
    user: "username",
    password: "password",
    database: "github_data"
};

var con;

function handleDisconnect() {
    con = mysql.createConnection(con_config);

    con.connect(function(err) {
       if(err) {
            console.log("error when connecting to db, ", err);
            setTimeout(handleDisconnect, 2000);
        }
    });

    con.on('error', function(err) {
        console.log('db_error', err);
        if(err.code === 'PROTOCOL_CONNECTION_LOST') {
            handleDisconnect();
        }   else    {
            throw err;
        }
    });
}

handleDisconnect();

var companies = ['google'];

for(var i = 0; i < companies.length; i++) {
    var company = companies[i];

    var get_repos_url = "https://api.github.com/users/" + company + "/repos";

    var options = {
        url: get_repos_url,
        method: 'GET',
        auth: {
            user: 'Seanie96',
            pass: 'Greeneyes96!'
        },
        headers: {
            'User-Agent': 'request',
        }
    };

    console.log("!");
    request(options, function(error, response, body) {
        var json = JSON.parse(body);
        var comp_id = json[0]['owner']['id'];
        var comp_name = json[0]['owner']['login'];
        var url = json[0]['owner']['html_url'];

        var company_values = [comp_id, comp_name, url];
        var company_insert = "INSERT INTO company(id, name, url) VALUES(?)";
        con.query(company_insert, [company_values], function(err, result) {
            if (err) throw err;
            else  {
                console.log("company: " + comp_name + " inserted");

            console.log("!!");

//            console.log("body ", JSON.stringify(json[0]['full_name']));
        console.log("num of repos: ", json.length);
        for(var j = 0; j < json.length; j++) {
            console.log("at repo ", j);
            var repo_id = json[j]['id'];
            var repo_name = json[j]['name'];
            var repo_url = json[j]['html_url'];
            get_repos_url = "https://api.github.com/repos/" + json[j]['full_name'] + "/stats/contributors";
            options = {
                url: get_repos_url,
                method: 'GET',
                auth: {
                    user: 'Seanie96',
                    pass: 'Greeneyes96!'
                },
                headers: {
                    'User-Agent': 'request',
                }
            };

            var repository_values = [repo_id, repo_name, repo_url, comp_id];
            var repository_insert = "INSERT INTO repository(id, name, url, company_id) VALUES(?)";
            con.query(repository_insert, [repository_values], function(err, result) {
                if (err) throw err;
                else {
                        console.log("  repository: " + JSON.stringify(result) + " inserted");
                        request(options, function(error, response, body) {
                        var json_cont = JSON.parse(body);

                        for(var contributor = 0; contributor < json_cont.length; contributor++) {
                            var author = json_cont[contributor]['author'];
                            var weeks = json_cont[contributor]['weeks'];

                            console.log("length: ", json_cont.length);

                            var user_select = "SELECT * FROM user WHERE name = '" + author['name'] + "'";
                            console.log("selecting a user");
                            con.query(user_select, function(err, result, fields) {
                                if (err) throw err;
                                else {
                                    if(result.length == 1) {
                                        console.log("      user: " + author['name'] + " found");
                                        insert_user_company(author['id'], comp_id, repo_id, weeks);
                                    }   else    {
                                        var user_values = [author['id'], author['login'], author['html_url']];
                                        var user_insert = "INSERT INTO user(id, name, url) VALUES(?)";
                                        console.log("insertin a user");
                                        con.query(user_insert, [user_values], function(err, result) {
                                            if (err) throw err;
                                            else  {
                                                console.log("      user: " + author['name'] + " inserted");
                                                insert_user_company(author['id'], comp_id, repo_id, weeks);
                                            }
                                        });
                                    }
                                }
                            });
                        }
                    });
                }
            });
            console.log("finished repo: ", j);
        }
        }
        });
    });
}

function insert_user_company(author_id, comp_id, repo_id, weeks) {
                            console.log("inserting...........")
                            var comp_user_select = "SELECT * FROM company_user WHERE user_id = "
                                                    + author_id + " AND company_id = " + comp_id;
                            console.log("selecting a company_user");
                            con.query(comp_user_select, function(err, result, fields) {
                                if (err) throw err;
                                else {
                                if(result.length == 1) {
                                    console.log("      company_user: " + JSON.stringify(result) + " found");
                                    insert_commits(author_id, comp_id, repo_id, weeks);
                                }   else    {
                                        var company_user_values = [comp_id, author_id];
                                        var company_user_insert = "INSERT INTO company_user(company_id, user_id) VALUES(?)";
                                        console.log("inserting a company_user");
                                        con.query(company_user_insert, [company_user_values], function(err, result) {
                                            if (err) throw err;
                                            else {
                                                console.log("      company_user: " + JSON.stringify(result) + " inserted");
                                                insert_commits(author_id, comp_id, repo_id, weeks);
                                            }
                                        });
                                    }
                                }
                            });

}

function insert_commits(author_id, comp_id, repo_id, weeks) {

                            var commits_to_insert = [];

                            for(var commits = 0; commits < weeks.length; commits++) {
                                var date_in_unix = weeks[commits]['w'];
                                var ts = moment.unix(date_in_unix);
                                var formatted_date = ts.format("YYYY-MM-DD");
                                var num_of_commits = weeks[commits]['c'];
                                var code_addition = weeks[commits]['a'];
                                var code_deletion = weeks[commits]['d'];
                                var code_difference = code_addition - code_deletion;

                                console.log("inserting a commit");

                                var commits_values = [repo_id, author_id, formatted_date, num_of_commits, code_addition, code_deletion, code_difference];

                            var commits_insert = "INSERT INTO commits(repository_id, user_id, date, number_of_commits, code_addition, code_deletion, code_difference) VALUES(?)";

                            con.query(commits_insert, [commits_values], function(err, result, fields) {
                                if (err) throw err;
                                else {
                                    console.log("           commits: being inserted");
                                }

                            });
                            }
}
