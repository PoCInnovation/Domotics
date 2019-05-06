#!/bin/python3
from flask import *
import csv, datetime, sys

app = Flask(__name__)
now = datetime.datetime.now()


def write_log_line(data, is_granted):
        file = open('workshop_log.txt', 'a')
        if len(data) > 8:
                file.write(is_granted + "\t: " + data + ":\t" + str(now.year)
                + ":" + str(now.month) + ":" + str(now.day) + "  "+ str(now.hour)
                + ":" + str(now.minute) + ":" + str(now.second) + "\n")
        else:
                file.write(is_granted + "\t: " + data + ":\t\t" + str(now.year)
                + ":" + str(now.month) + ":" + str(now.day) + "  " + str(now.hour)
                + ":" + str(now.minute) + ":" + str(now.second) + "\n")

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
                                write_log_line(data, "ACCES GRANTED")
                                return ("ACCES GRANTED", 200)
        finally:
                file.close()
        write_log_line(data, "ACCES GRANTED")
        return ("ACCES DENIED", 404)
