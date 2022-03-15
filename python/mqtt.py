from unicodedata import name
import paho.mqtt.client as mqtt
import ddbb
import json

CLIENT_ID = "EIP"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(CLIENT_ID + "/")


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):

    ddbb.insert_register_to_ddbb(name=CLIENT_ID, payload=msg.payload.decode())

    # print(msg.topic+" "+str(msg.payload))

def on_connection_failed():
    print("mal")



# Define client session
client = mqtt.Client(client_id="ruben", clean_session=False)
# Set personalize callbacks
client.on_connect = on_connect
client.on_message = on_message
client.on_connect_fail = on_connection_failed

# Connect with broker 
client.connect("15.188.173.233", port=1883, keepalive=60)


# Manage initialization of database
ddbb.create_table(name=CLIENT_ID)


if __name__ == "__main__":
    try:
        client.loop_forever()
    except KeyboardInterrupt:
        client.loop_stop()
