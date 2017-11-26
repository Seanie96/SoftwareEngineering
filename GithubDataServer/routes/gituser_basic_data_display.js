var express = require('express');
var router = express.Router();
var request = require('request');

/* POST Git data display page. */

router.post('/', function(req, res, next) {
    var json;
    var user_id;
    var html_url;
    var num_of_public_repos;
    var repos_url;
    var bio;
    var loc;
    var name;
    var email;
    var user_type;

    var string = "https://api.github.com/users/" + req.body.GITUSER_NAME;
    var options = {
        url: string,
        headers: {
            'User-Agent': 'request'
        }
    }
    console.log(string);

    request(options , function(error, response, body) {
            json = JSON.parse(body);
            user_id = json.id;
            html_url = json.html_url;
            num_of_public_repos = json.public_repos;
            repos_url = json.repos_url;
            bio = json.bio;
            loc = json.location;
            name = json.name;
            email = json.email;
            user_type = json.type;
            var message = json.message;
            if(typeof(message) == "undefined") {
                res.render('gituser_basic_data_display', {
                                            user_name: req.body.GITUSER_NAME,
                                            id: user_id,
                                            html: html_url,
                                            repos: num_of_public_repos,
                                            bio: bio,
                                            loc: loc,
                                            name: name,
                                            email: email,
                                            user_type: user_type
                                                 });
            }   else    {
                res.render('gituser_basic_not_found');
            }
    });
});

module.exports = router;
