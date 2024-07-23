#!/bin/bash

mkdir -p /var/www/html
rm -rf /var/www/html/*
cd /var/www/html

curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar 
chmod +x wp-cli.phar 
mv wp-cli.phar /usr/local/bin/wp

wp core download --allow-root

mv /wp-config.php /var/www/html/wp-config.php

sed -i "s/database_name_here/$MYSQL_DB_NAME/1" wp-config.php
sed -i "s/username_here/$MYSQL_USER/1" wp-config.php
sed -i "s/password_here/$MYSQL_PASSWORD/1" wp-config.php

wp core install --url=$DOMAIN_NAME/ --title=$WP_TITLE --admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root
wp user create $WP_SECOND_USER $WP_SECOND_EMAIL --role=editor --user_pass=$WP_SECOND_PASSWORD --allow-root
wp theme install twentysixteen --activate --allow-root
wp plugin update --all --allow-root
 
sed -i 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 9000/g' /etc/php/7.3/fpm/pool.d/www.conf
mkdir /run/php

/usr/sbin/php-fpm7.3 -F
