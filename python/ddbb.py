import sqlite3
import json
from pathlib import Path


PATH_DDBB = str(Path().absolute()) + "/data/"
FILE_NAME_DDBB = "client_ddbb.db"

    
#Only first time machine initialize
def create_table(name):
    try:
        con = sqlite3.connect(PATH_DDBB + FILE_NAME_DDBB)
        cur = con.cursor()
        cur.execute(f"create table {name} (datetime timestamp, deviceId varchar(40), temperature_grades tinyint, absolute_humidity tinyint)")
        con.commit()
    except Exception as e:
        print(e)
        
        
def insert_register_to_ddbb(name, payload):
    
    js = json.loads(payload)
    try:
        con = sqlite3.connect(PATH_DDBB + FILE_NAME_DDBB)
        cur = con.cursor()
        cur.execute(f"insert into {name}(datetime, deviceId, temperature_grades, absolute_humidity) values(?, ?, ?, ?)",\
                    (js["datetime"], js["deviceId"], js["data"]["temperature_grades"], js["data"]["absolute_humidity"]))
        con.commit()
        con.close()
    except Exception as e:
        print(e)