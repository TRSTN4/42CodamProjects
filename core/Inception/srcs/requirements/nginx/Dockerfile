FROM debian:buster

RUN apt -y update && apt install -y nginx openssl

COPY ./conf/default /etc/nginx/sites-available/
COPY ./tools/entrypoint.sh /

RUN chmod +x /entrypoint.sh
CMD ["/entrypoint.sh"]
