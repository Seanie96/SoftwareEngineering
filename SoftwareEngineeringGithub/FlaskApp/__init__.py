from flask import Flask 
app = Flask(__name__) 

@app.route("/<float:test>") 
def hello(test):  
   return "Hello function: %s" % test  

@app.route("/<int:test>") 
def helloWithDiffParam(test):    
   return "Diff function: %s" % test

if __name__ == "__main__":   
  app.run()
