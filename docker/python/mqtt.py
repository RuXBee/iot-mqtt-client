import psycopg2
import paho.mqtt.client as mqtt
import json


# ========================================================================================
#                                   POSTGRES
# ========================================================================================
# Manage connection with postgres database
def insert_register(payload):
    """insert new register into database

    Args:
        payload (_type_): incomming message from mqtt device as json format
    """        
    # Serialize json file
    js = json.loads(payload)
    
    # Make connection with database
    conn = psycopg2.connect(host="localhost",
                        database="iot",
                        user="postgres",
                        password="1234",
                        port=5432)

    query = """INSERT INTO upna(datetime, device, temperature_grades, absolute_humidity)
             VALUES(%s, %s, %s, %s);"""
    cursor = conn.cursor()
    cursor.execute(query, (js["datetime"], js["deviceId"], js["data"]["temperature_grades"], js["data"]["absolute_humidity"],))
    conn.commit()
    conn.close()
    


# ========================================================================================
#                                   MQTTT
# ========================================================================================
CLIENT_ID = "EIP"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(CLIENT_ID + "/")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):

    print(msg.topic+" "+str(msg.payload))
    js = json.loads(msg.payload)
    insert_register(payload=msg.payload)
    

def on_connection_failed():
    print("mal")


# Define client session
client = mqtt.Client(client_id="ruben", clean_session=True)
# Set personalize callbacks
client.on_connect = on_connect
client.on_message = on_message
client.on_connect_fail = on_connection_failed
# Connect with broker 
client.connect("15.188.173.233", port=1883, keepalive=60)




if __name__ == "__main__":
    try:
        client.loop_forever()
    except KeyboardInterrupt:
        client.loop_stop()
