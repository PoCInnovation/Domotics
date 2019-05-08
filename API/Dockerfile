from alpine:latest

RUN apk add --no-cache python3-dev mariadb\
    && pip3 install --upgrade pip

WORKDIR /app

COPY . /app

RUN pip3 --no-cache-dir install -r requierements.txt