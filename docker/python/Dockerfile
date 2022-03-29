FROM python:3.8.5

WORKDIR /usr/src/app

COPY ./mqtt.py .

RUN pip install postgres paho-mqtt

CMD ["python", "./mqtt.py"]