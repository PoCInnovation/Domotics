from flask import Flask
from flask import request
import csv

app = Flask(__name__)

@app.route("/", methods = ["POST", "GET"])
def receiveUID():
        fname = "uid.csv"
        file = open(fname, "r")
        try:
                data = request.get_data().hex()
                reader = csv.reader(file)
                for row in reader:
                        if row[0] == data:
                                return ("ACCES GRANTED", 200)
        finally:
                file.close()
        return ("ACCES DENIED", 404)
