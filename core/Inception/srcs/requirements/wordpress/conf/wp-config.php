<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the website, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://developer.wordpress.org/advanced-administration/wordpress/wp-config/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'database_name_here' );

/** Database username */
define( 'DB_USER', 'username_here' );

/** Database password */
define( 'DB_PASSWORD', 'password_here' );

/** Database hostname */
define( 'DB_HOST', 'mariadb' );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         '/|soTya_~i@=%J[:X_!y(#W( 0l*6tVv:C#sU2&U?daBIRQ{H+o7N,[M:=-32w:p');
define('SECURE_AUTH_KEY',  'P>)%}:{EXu0&O@s?Y#j-rW=XrZ]O{iVfy|l-x:uR+%E|6k1-M^9sJV6lgcw@JAYz');
define('LOGGED_IN_KEY',    '%#D!E|{L6+/ri|B}|1m*f&C(E.Olb-&GT-mRmvn^BxCZDW*>pX@BiOTzO|@J^aCF');
define('NONCE_KEY',        '5v;ccYLE[7!Ut+-I>9|-ge}~{FlukifPOEyMF2Ay|`2: 2`Q,Hq*<~W&_,1sbP7S');
define('AUTH_SALT',        '26hs#!.UoR7e-noy)^nzovpgell73?10h-yO H*Z9hta05u>y6<p~!]t]S;`+p3?');
define('SECURE_AUTH_SALT', 'vu=dkif}T^ZP^+^Cz.Gf#bbp.7.5-r@lgN-$})RwZD~R+fm.{]i7/Z]t(cm-W(cT');
define('LOGGED_IN_SALT',   '<NPCWP{ V>`2B]+j0^%|Q#,{XWr. V-=:q$Z:E k|a.$hL+%;%$Y,RwhOl^*Tqt>');
define('NONCE_SALT',       'MT]9#PA:$~D6R@g]8G^l)-[mi&_G)!N+d.]^pk0;]f{|+1QOUG:[}9G|QfK!Pi-7');

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://developer.wordpress.org/advanced-administration/debug/debug-wordpress/
 */
define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
