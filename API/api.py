#!/bin/python3
from flask import *
import csv, datetime, sys, pymysql

app = Flask(__name__)
now = datetime.datetime.now()

DATABASE_NAME = 'flask_api'
DATABASE_HOST = 'localhost'
DATABASE_SOCK =  None
DATABASE_USER = 'root'
DATABASE_PASS = ''

def get_time():
        return (str(now.year) + "-" + str(now.month) + "-" + str(now.day) + " " + str(now.hour) + ":" + str(now.minute) + ":" + str(now.second))

def connect_to_sql():
    if DATABASE_SOCK != None:
        connect = pymysql.connect(socket = DATABASE_SOCK,
                                  user   = DATABASE_USER,
                                  passwd = DATABASE_PASS,
                                  db     = DATABASE_NAME)
    else:
        connect = pymysql.connect(host   = DATABASE_HOST,
                                  user   = DATABASE_USER,
                                  passwd = DATABASE_PASS,
                                  db     = DATABASE_NAME)
    return connect

##################################################################################################################################################

def usr_already_exists(user_id):
        connect = connect_to_sql()
        cursor = connect.cursor()
        cursor.execute("SELECT * from user where user_id = '%s'" % user_id)
        re = cursor.fetchone()

        if (re == None):
                cursor.close()
                connect.close()
                return False

        cursor.close()
        connect.close()
        return True

def get_user_by_id(user_id):
        try:
                connect = connect_to_sql()
                cursor = connect.cursor()
                cursor.execute("SELECT username FROM user WHERE user_id='%s'" % (user_id))
                res = cursor.fetchall()[0][0]
                connect.close()
                cursor.close()
                return (res)
        except:
                pass

def add_history_line(data, username, is_granted):
        try:
                connect = connect_to_sql()
                cursor = connect.cursor()
                cursor.execute("INSERT INTO history (user_id, username, acces_time, status) VALUES ('%s', '%s', NOW(), '%s')"
                % (data, username, is_granted))
                connect.commit()

                cursor.close()
                connect.close()
        except:
                pass


def add_user(data, username):
        if usr_already_exists(data) == True:
                return
        try:
                connect = connect_to_sql()
                cursor = connect.cursor()
                cursor.execute("INSERT INTO user (user_id, username) VALUES ('%s', '%s')"
                % (data, username))
                connect.commit()

                cursor.close()
                connect.close()
        except:
              pass

if __name__ == '__main__':
        app.run(host="0.0.0.0")

##################################################################################################################################################

@app.route("/", methods = ["POST", "GET"])
def receiveUID():
        try:
                uid = request.get_data().hex()
                if usr_already_exists(uid) == True:
                        add_history_line(uid, get_user_by_id(uid), "ACCES GRANTED")
                        return ("ACCES GRANTED", 200)
        except:
                pass
        add_history_line(uid, "ERROR", "ACCES DENIED")
        return ("ACCES DENIED", 404)
