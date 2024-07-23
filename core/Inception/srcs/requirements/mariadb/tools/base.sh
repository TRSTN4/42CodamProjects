#!/bin/bash

sed -i 's/bind-address\s*=.*/bind-address = 0.0.0.0/' /etc/mysql/mariadb.conf.d/50-server.cnf
sed -i 's/#port\s*=.*/port = 3306/' /etc/mysql/mariadb.conf.d/50-server.cnf

service mysql start 

echo "CREATE DATABASE IF NOT EXISTS $MYSQL_DB_NAME ;" > $MYSQL_DB_NAME.sql
echo "CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD' ;" >> $MYSQL_DB_NAME.sql
echo "GRANT ALL PRIVILEGES ON $MYSQL_DB_NAME.* TO '$MYSQL_USER'@'%' ;" >> $MYSQL_DB_NAME.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD' ;" >> $MYSQL_DB_NAME.sql
echo "FLUSH PRIVILEGES;" >> $MYSQL_DB_NAME.sql

mysql < $MYSQL_DB_NAME.sql

kill $(cat /var/run/mysqld/mysqld.pid)

mysqld
