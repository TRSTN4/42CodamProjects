FROM debian:buster

RUN apt -y update && apt install -y php-fpm php-mysql curl

COPY ./conf/wp-config.php /

COPY ./tools/base.sh /
RUN chmod +x /base.sh
CMD ["/base.sh"]
