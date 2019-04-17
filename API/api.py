#!/bin/python3
from flask import *
import csv

app = Flask(__name__)

@app.route("/", methods = ["POST", "GET"])
def receiveUID():
        fname = "uid.csv"
        file = open(fname, "r")
        try:
                data = request.get_data().hex()
                print(data)
                reader = csv.reader(file)
                for row in reader:
                        if row[0] == data:
                                return ("ACCES GRANTED", 200)
        finally:
                file.close()
        return ("ACCES DENIED", 404)
