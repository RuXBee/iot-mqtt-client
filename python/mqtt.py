import paho.mqtt.client as mqtt

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("testtopic")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):

    print(msg.topic+" "+str(msg.payload))

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
input()


dic = {
    "temperature": 23,
    "humidity": 28
}
client.publish(topic="testtopic/ruben", payload="", retain=True)
client.publish_callback
# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.

if __name__ == "__main__":
    try:
        client.loop_forever()
    except KeyboardInterrupt:
        client.loop_stop()
