#!/bin/bash

mkdir -p /etc/ssl/certs
mkdir -p /etc/ssl/private

KEY_PATH="/etc/ssl/private/my.key"

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout $KEY_PATH -out $CERTS_ \
    -subj "/C=NL/ST=Noord-Holland/L=Amsterdam/O=Codam/OU=Student/CN=tvan-bee.42.fr"

nginx -g "daemon off;"
