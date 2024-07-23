FROM debian:buster

RUN apt -y update && apt install -y mariadb-server

COPY ./tools/base.sh /
RUN chmod +x /base.sh
CMD ["/base.sh"]
