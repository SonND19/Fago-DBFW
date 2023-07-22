#!/bin/sh

if [ "$(id -u)" != "0" ]; then
    echo
    echo "Please run this script as root"
    echo
    exit 1
fi

if [ ! -x ../greensql-fw ]; then
    echo "../greensql-fw executable not found"
    exit;
fi
cp rc.greensql /etc/init.d/greensql
if [ -d /usr/sbin ]; then
    cp ../greensql-fw /usr/sbin/
else
    cp ../greensql-fw /sbin/
fi
/etc/init.d/greensql start
tail -f /var/log/fagodb.log
tail -f var/log/alert.log
tail -f var/log/event.log
echo "done..."
