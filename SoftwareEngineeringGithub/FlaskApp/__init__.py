import requests, json
from flask import Flask, render_template, request

app = Flask(__name__) 

@app.route("/<float:test>") 
def hello(test):  
   return "Hello function: %s" % test  

@app.route("/<int:test>") 
def helloWithDiffParam(test):    
   return "Diff function: %s" % test

@app.route("/")
def index():
   return render_template("index.html")

@app.route("/form", methods=['POST'])
def form():
   name = request.form['pers_user']

   r = requests.get("https://api.github.com/users/" + name)
   res = r.text
   json_on_user = json.loads(res)
   not_found = "Not Found"
   if not ("message" in json_on_user):
     user_id=json_on_user["id"]
     html_url=json_on_user["html_url"]
     num_of_public_repos=json_on_user["public_repos"]
     repos_url=json_on_user["repos_url"]
     bio=json_on_user["bio"]
     location=json_on_user["location"]
     name=json_on_user["name"]
     email=json_on_user["email"]
     user_type=json_on_user["type"]
     return "<html><body><table><tr><td>name</td><td>" + str(name) + "</td></tr><tr><td>id</td><td>" + str(user_id) + "</td></tr><tr><td>url link</td><td><a href='" + str(html_url) + "'>Click here to see users github home page.</a></td></tr><tr><td>bio</td><td>" + str(bio) + "</td></tr><tr><td>email</td><td>" + str(email) + "</td></tr><tr><td>type of user</td><td>" + str(user_type) + "</td></tr><tr><td>location</td><td>" + str(location) + "</td></tr><tr><td>respositories link</td><td><a href='" + str(repos_url) + "'>Json data about the repos that this user has contributed to.</a></td></tr><tr><td>number of public repos</td><td>" + str(num_of_public_repos) + "</td></tr><tr><td></table><a href='/'>Click here to go back!!</a></body></html>" 
   else:
     return render_template("not_found.html")

if __name__ == "__main__":   
  app.run()
