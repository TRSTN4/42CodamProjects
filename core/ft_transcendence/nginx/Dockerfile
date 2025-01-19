FROM nginx:latest

RUN apt-get update && apt-get install -y openssl

COPY nginx.conf /etc/nginx/sites-available/default

RUN mkdir -p /etc/ssl/certs/
RUN mkdir -p /etc/ssl/private/

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/nginx-selfsigned.key -out /etc/ssl/certs/nginx-selfsigned.crt -subj "/C=NL/ST=Noord-Holland/L=Amsterdam/O=Codam/OU=Student/CN=tde-brui.42.fr" 

CMD ["nginx", "-g", "daemon off;"]