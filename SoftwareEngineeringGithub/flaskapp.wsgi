#!/usr/bin/python
import sys 
import logging 
logging.basicConfig(stream=sys.stderr) 
sys.path.insert(0,"/var/www/SoftwareEngineering/SoftwareEngineeringGithub/")  
from FlaskApp import app as application 
application.secret_key = 'Add your secret key'
